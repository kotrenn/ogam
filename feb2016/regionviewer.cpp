#include "regionviewer.h"

#include "resourcemanager.h"
#include "system.h"

int threadMakeSurfaces(void *data)
{
	srand(time(0));
	RegionViewer *regionViewer = (RegionViewer *)data;

	int numRooms = regionViewer->numRooms();
	
	for (int room = 0; room < numRooms; ++room)
		regionViewer->makeSurfaces(room);

	return 0;
}

RegionViewer::RegionViewer(Region *region)
	:m_region(region),
	 m_roomSurfaces(),
	 m_roomWidth(420),
	 m_roomHeight(420),
	 m_roomPainter(),
	 m_wallSurface(NULL),
	 m_numPainted(0),
	 m_lock(NULL),
	 m_loadColor(m_roomPainter.randomColor()),
	 m_loadingSurface(NULL),
	 m_loadingX(0),
	 m_loadingY(0)
{
	//System::get_instance()->get_size(&m_roomWidth, &m_roomHeight);

	m_lock = SDL_CreateSemaphore(1);

	ResourceManager *rm = ResourceManager::get_instance();
	m_wallSurface = rm->get_image("wall.png");
	m_wallSurface->set_color_key(0, 0xFF, 0xFF);

	m_loadingSurface = rm->get_image("loading.png");

	System *system = System::get_instance();
	int systemWidth = system->get_width();
	int systemHeight = system->get_height();

	int loadingWidth = m_loadingSurface->get_w();
	int loadingHeight = m_loadingSurface->get_h();

	m_loadingX = (systemWidth - loadingWidth) / 2;
	m_loadingY = (systemHeight - loadingHeight) / 4;

	unsigned int numRooms = region->numRooms();

	for (Direction direction : s_DirectionArray)
		m_roomSurfaces[direction] = vector<Surface *>(numRooms);

	SDL_CreateThread(threadMakeSurfaces, this);
}

RegionViewer::~RegionViewer()
{
	SDL_DestroySemaphore(m_lock);
}

int RegionViewer::getNumPainted()
{
	int ret = -1;
	
	SDL_SemWait(m_lock);
	
	ret = m_numPainted;
	
	SDL_SemPost(m_lock);
	
	return ret;
}

void RegionViewer::incNumPainted()
{
	SDL_SemWait(m_lock);
	
	m_numPainted += 1;
	
	SDL_SemPost(m_lock);
}

void RegionViewer::draw(Surface *dst, int room, Direction direction)
{
	if (finishedPainting())
	{
		Surface *roomSurface = m_roomSurfaces[direction][room];
		drawRoom(dst, roomSurface, 0, 0);
	}
	else
		drawProgress(dst);
}

void RegionViewer::drawProgress(Surface *dst)
{
	dst->blit(m_loadingSurface, m_loadingX, m_loadingY);
	
	int numPainted = getNumPainted();

	System *system = System::get_instance();

	int width = 400;
	int height = 20;
	int topX = system->get_width() / 2 - width / 2;
	int topY = system->get_height() / 2 - 40;
	int bottomX = topX + width;
	int bottomY = topY + height;

	double dNumPainted = (double)numPainted;
	double ratio = dNumPainted / numRooms();
	int percentWidth = (int)(width * ratio);

	dst->draw_line(m_loadColor, topX - 1, topY - 1, bottomX + 1, topY - 1);
	dst->draw_line(m_loadColor, topX - 1, topY - 1, topX - 1, bottomY + 1);
	dst->draw_line(m_loadColor, bottomX + 1, topY - 1, bottomX + 1, bottomY + 1);
	dst->draw_line(m_loadColor, topX - 1, bottomY + 1, bottomX + 1, bottomY + 1);

	Rect dims(topX, topY, percentWidth, height);
	dst->draw_rect_3d(m_loadColor, dims);
}

void RegionViewer::drawTransition(Surface *dst,
                                  int room,
                                  Direction direction,
                                  int prevRoom,
                                  Direction prevDirection,
                                  Direction transitionDirection,
                                  double time,
                                  Player *player,
                                  list<Bounce *> bounceList,
                                  list<Bounce *> prevBounceList)
{
	if (!finishedPainting())
	{
		draw(dst, room, direction);
		return;
	}
	
	Surface *prevSurface = m_roomSurfaces[prevDirection][prevRoom];
	Surface *nextSurface = m_roomSurfaces[direction][room];

	int vx = 0;
	int vy = 0;

	switch (transitionDirection)
	{
	case NORTH: vy = -1; break;
	case SOUTH: vy = 1; break;
	case WEST: vx = -1; break;
	case EAST: vx = 1; break;
	default: break;
	}

	vx *= m_roomWidth;
	vy *= m_roomHeight;

	int prevX = -vx * (1 - time);
	int prevY = -vy * (1 - time);
	int nextX = vx * time;
	int nextY = vy * time;

	drawRoom(dst, prevSurface, prevX, prevY);
	drawRoom(dst, nextSurface, nextX, nextY);

	player->draw(dst, nextX, nextY);
	for (auto bounce : bounceList)
		bounce->draw(dst, nextX, nextY);
	for (auto bounce : prevBounceList)
		bounce->draw(dst, prevX, prevY);
}

void RegionViewer::drawRoom(Surface *dst, Surface *roomSurface, int x, int y)
{
	int srcX = 0;
	int srcY = 0;
	int srcW = m_roomWidth;
	int srcH = m_roomHeight;
	int dstX = x;
	int dstY = y;

	if (x < 0) { srcX = -x; srcW = m_roomWidth + x; dstX = 0; }
	if (y < 0) { srcY = -y; srcH = m_roomHeight + y; dstY = 0; }
	if (x > 0) { srcW = m_roomWidth - x; }
	if (y > 0) { srcH = m_roomHeight - y; }

	Rect srcDims(srcX, srcY, srcW, srcH);
	dst->blit(roomSurface, dstX, dstY, srcDims);
}

void RegionViewer::makeSurfaces(int room)
{
	map<Direction, Surface *> surfaces;
	surfaces = m_roomPainter.makeRoom(m_roomWidth, m_roomHeight);
	
	for (Direction direction : s_DirectionArray)
	{
		m_roomSurfaces[direction][room] = surfaces[direction];
		m_roomSurfaces[direction][room]->blit(m_wallSurface, 0, 0);
	}

	incNumPainted();
	
	return;
}

Surface *RegionViewer::getRoomSurface(int room, Direction direction)
{
	return m_roomSurfaces[direction][room];
}
