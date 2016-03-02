#include "roompainter.h"

RoomPainter::RoomPainter()
	:m_roomSurfaces()
{
}

RoomPainter::~RoomPainter()
{
}

map<Direction, Surface *> RoomPainter::makeRoom(int roomWidth, int roomHeight)
{
	initRooms(roomWidth, roomHeight);

	const int numChoices = 6;
	int choices[numChoices] = { 1, 2, 2, 2, 3, 3 };
	int algo = choices[randint(0, numChoices - 1)];

	switch (algo)
	{
	case 1: makeCircleRoom(); break;
	case 2: makeVoronoiRoom(); break;
	case 3: makeMazeRoom(); break;
	}

	return m_roomSurfaces;
}

void RoomPainter::initRooms(int roomWidth, int roomHeight)
{
	m_roomWidth = roomWidth;
	m_roomHeight = roomHeight;
	
	for (Direction direction : s_DirectionArray)
		m_roomSurfaces[direction] = new Surface(roomWidth, roomHeight);
}

Uint32 RoomPainter::randomColor() const
{
	int r = randint(0, 200);
	int g = randint(0, 200);
	int b = randint(0, 200);
	return mapRGB(r, g, b);
}

vector<Uint32> RoomPainter::randomColors(int numColors) const
{
	// Pick some random colors
	vector<Uint32> colors(numColors);
	for (int c = 0; c < numColors; ++c)
		colors[c] = randomColor();

	return colors;
}

vector<Uint32> RoomPainter::randomSimilarColors(int numColors) const
{
	int baseR = randint(0, 200);
	int baseG = randint(0, 200);
	int baseB = randint(0, 200);

	int delta = 20;

	vector<Uint32> colors(numColors);
	for (int c = 0; c < numColors; ++c)
	{
		int dr = randint(-delta, delta);
		int dg = randint(-delta, delta);
		int db = randint(-delta, delta);

		int r = baseR + dr;
		int g = baseG + dg;
		int b = baseB + db;

		r = (r < 0)? 0 : (r > 255)? 255 : r;
		g = (g < 0)? 0 : (g > 255)? 255 : g;
		b = (b < 0)? 0 : (b > 255)? 255 : b;

		colors[c] = mapRGB(r, g, b);
	}

	return colors;
}

void RoomPainter::paintPixel(Uint32 color, int x, int y)
{
	for (Direction direction : s_DirectionArray)
	{
		int reflectX = m_roomWidth - x - 1;
		int reflectY = m_roomHeight - y - 1;
		int newX = -1;
		int newY = -1;

		switch (direction)
		{
		case NORTH: newX = x; newY = y; break;
		case SOUTH: newX = reflectX; newY = reflectY; break;
		case WEST: newX = y; newY = reflectX; break;
		case EAST: newX = reflectY; newY = x; break;
		default: break;
		}

		Surface *surface = m_roomSurfaces[direction];
		surface->draw_point(color, newX, newY);
	}
}

void RoomPainter::makeCircleRoom()
{
	// Decide how many colors we want
	int numColors = randint(2, 3);
	if (randint(1, 5) == 1) numColors++;

	// Pick some random colors
	vector<Uint32> colors = randomColors(numColors);

	// Pick a random center for the circle
	int w2 = m_roomWidth / 2;
	int h2 = m_roomHeight / 2;
	int cx = w2;
	int cy = h2;

	// Don't let the center of the circle be too close to the center of the room
	int minDist = (m_roomWidth + m_roomHeight) / 20;
	while ((cx - w2) * (cx - w2) + (cy - h2) * (cy - h2) < minDist * minDist)
	{
		cx = randint(0, m_roomWidth - 1);
		cy = randint(0, m_roomHeight - 1);
	}

	// Width of the color bands
	int colorWidth = randint(5, 20);

	// Color every pixel
	for (int x = 0; x < m_roomWidth; ++x)
	{
		for (int y = 0; y < m_roomHeight; ++y)
		{
			// Find the distance from the center of the circle
			int dx = cx - x;
			int dy = cy - y;
			float dist = sqrt(dx * dx + dy * dy) / colorWidth;

			// Look up the color
			int colorIndex = (int)dist;
			colorIndex %= numColors;

			// Paint the base color
			Uint32 color = colors[colorIndex];
			paintPixel(color, x, y);

			// Interpolate with the next color in a cyclic shift
			int nextColorIndex = (colorIndex + 1) % numColors;
			Uint32 nextColor = colors[nextColorIndex];
			float alpha = dist - (int)dist;

			// From Perlin's notes on an improved interpolation function for noise
			// 6 * a^5 - 15 * a^4 + 10 * a^3
			alpha = alpha * alpha * alpha * (alpha * (alpha * 6.f - 15.f) + 10.f);
			int a = (int)(255 * alpha);
			nextColor = mapRGBA(nextColor, a);
			paintPixel(nextColor, x, y);
		}
	}
}

void RoomPainter::makeVoronoiRoom()
{
	// Decide how many colors we want
	int numColors = randint(6, 11);

	// Pick some random colors
	vector<Uint32> bgColors = randomSimilarColors(numColors);
	Uint32 specialColor = randomColor();

	// Decide now many cells
	int numCells = randint(50, 70);
	int xPoints[numCells];
	int yPoints[numCells];

	// Initialize locations
	for (int i = 0; i < numCells; ++i)
	{
		xPoints[i] = randint(0, m_roomWidth - 1);
		yPoints[i] = randint(0, m_roomHeight - 1);
	}

	// Pick colors for each cell
	Uint32 cellColors[numCells];
	for (int i = 0; i < numCells; ++i)
	{
		int colorIndex = randint(1, numColors) - 1;
		cellColors[i] = bgColors[colorIndex];
		if (randint(1, 10) == 1)
			cellColors[i] = specialColor;
	}

	// Decide which distance metric to use
	int metric = randint(1, s_numMetrics);

	// Color every pixel
	for (int x = 0; x < m_roomWidth; ++x)
	{
		for (int y = 0; y < m_roomHeight; ++y)
		{
			// Find the color of the closest point
			int minDist = dist(metric, x, y, xPoints[0], yPoints[0]);
			int minIndex = 0;
			                   
			for (int i = 1; i < numCells; ++i)
			{
				int nextDist = dist(metric, x, y, xPoints[i], yPoints[i]);
				if (nextDist < minDist)
				{
					minDist = nextDist;
					minIndex = i;
				}
			}
			
			// Paint the base color
			Uint32 color = cellColors[minIndex];
			paintPixel(color, x, y);
		}
	}
}

int RoomPainter::dist(int metric, int x0, int y0, int x1, int y1) const
{
	int dx = x1 - x0;
	int dy = y1 - y0;
	
	switch (metric)
	{
	case 1: // Euclidean
		return (int)sqrt(dx * dx + dy * dy);
	case 2: // Manhattan
		return abs(dx) + abs(dy);
	case 3: // Chebyshev
		return max(abs(dx), abs(dy));
	default:
		return 0;
	}
}

void RoomPainter::makeMazeRoom()
{
	// Generate a maze
	int cellWidth = 4;
	int cellHeight = 4;
	int mazeWidth = m_roomWidth / cellWidth + 1;
	int mazeHeight = m_roomHeight / cellHeight + 1;

	int area = mazeWidth * mazeHeight;

	int cells[mazeWidth][mazeHeight];
	for (int x = 0; x < mazeWidth; ++x)
		for (int y = 0; y < mazeHeight; ++y)
			cells[x][y] = -1;

	int startX = randint(0, mazeWidth - 1);
	int startY = randint(0, mazeHeight - 1);

	int stackX[area * 4];
	int stackY[area * 4];
	int stackD[area * 4];

	stackX[0] = startX;
	stackY[0] = startY;
	stackD[0] = 0;

	int stackSize = 1;

	while (stackSize > 0)
	{
		// Pop the stack
		--stackSize;
		int curX = stackX[stackSize];
		int curY = stackY[stackSize];
		int curD = stackD[stackSize];

		// If it's already colored--move on
		if (cells[curX][curY] >= 0) continue;

		// Store the depth we reached this cell at
		cells[curX][curY] = curD;

		// Visit neighbors
		int velX[] = { -1, 1, 0, 0 };
		int velY[] = { 0, 0, -1, 1 };

		// Create a shuffle
		int shuffle[4];

		// Init shuffle array
		for (int i = 0; i < 4; ++i)
			shuffle[i] = i;

		// Now shuffle
		for (int i = 0; i < 4; ++i)
		{
			int j = i + randint(0, 4 - i - 1);
			int tmp = shuffle[i];
			shuffle[i] = shuffle[j];
			shuffle[j] = tmp;
		}

		for (int i = 0; i < 4; ++i)
		{
			// Index after shuffling
			int k = shuffle[i];
			
			// Compute the neighboring location
			int newX = curX + velX[k];
			int newY = curY + velY[k];

			// Move on if out of bounds
			if (newX < 0 || newY < 0 ||
			    newX >= mazeWidth ||
			    newY >= mazeHeight)
				continue;

			// Compute the neighboring depth
			int newD = curD + 1;

			// Push onto the stack
			stackX[stackSize] = newX;
			stackY[stackSize] = newY;
			stackD[stackSize] = newD;
			++stackSize;
		}
	}
	
	// Pick a random center for a "circle"
	int w2 = mazeWidth / 2;
	int h2 = mazeHeight / 2;
	int cx = w2;
	int cy = h2;

	// Don't let the center of the circle be too close to the center of the room
	int minDist = (mazeWidth + mazeHeight) / 15;
	while ((cx - w2) * (cx - w2) + (cy - h2) * (cy - h2) < minDist * minDist)
	{
		cx = randint(minDist, mazeWidth - minDist);
		cy = randint(minDist, mazeHeight - minDist);
	}

	int radius = randint(6, 10);


	// Now let's add some colors!!!!

	int baseColors = randint(2, 4);
	int scale = randint(140, 180);

	// Initialize some random base colors
	int baseR[baseColors];
	int baseG[baseColors];
	int baseB[baseColors];

	for (int i = 0; i < baseColors; ++i)
	{
		baseR[i] = randint(0, 200);
		baseG[i] = randint(0, 200);
		baseB[i] = randint(0, 200);
	}

	// Interpolate between the base colors
	vector<Uint32> colors;
	for (int i = 0; i < baseColors; ++i)
	{
		int j = (i + 1) % baseColors;
		for (int k = 0; k < scale; ++k)
		{
			int dr = baseR[j] - baseR[i];
			int dg = baseG[j] - baseG[i];
			int db = baseB[j] - baseB[i];

			int r = baseR[i] + (k * dr) / scale;
			int g = baseG[i] + (k * dg) / scale;
			int b = baseB[i] + (k * db) / scale;
			
			Uint32 newColor = mapRGB(r, g, b);
			colors.push_back(newColor);
		}
	}

	int numColors = colors.size();
	vector<Uint32> specialColors = randomSimilarColors(4);

	for (int x = 0; x < mazeWidth; ++x)
	{
		for (int y = 0; y < mazeHeight; ++y)
		{
			int cellIndex = cells[x][y];
			Uint32 color = colors[cellIndex % numColors];

			int d = dist(2, x, y, cx, cy); // Manhattan
			if (d <= radius) color = specialColors[d % specialColors.size()];

			for (int dx = 0; dx < cellWidth; ++dx)
				for (int dy = 0; dy < cellHeight; ++dy)
					paintPixel(color, x * cellWidth + dx, y * cellHeight + dy);
		}
	}
}
