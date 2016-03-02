#ifndef __ROOM_PAINTER_H
#define __ROOM_PAINTER_H

#include "direction.h"
#include "surface.h"

class RoomPainter
{
public:
	RoomPainter();
	~RoomPainter();

	map<Direction, Surface *> makeRoom(int roomWidth, int roomHeight);
	Uint32 randomColor() const;
private:
	void initRooms(int roomWidth, int roomHeight);
	vector<Uint32> randomColors(int numColors) const;
	vector<Uint32> randomSimilarColors(int numColors) const;
	void paintPixel(Uint32 color, int x, int y);
	int dist(int metric, int x0, int y0, int x1, int y1) const;
	
	void makeCircleRoom();
	void makeVoronoiRoom();
	void makeMazeRoom();

	const static int s_numMetrics = 3;

	int m_roomWidth;
	int m_roomHeight;
	map<Direction, Surface *> m_roomSurfaces;
};

#endif
