#ifndef __REGION_VIEWER_H
#define __REGION_VIEWER_H

#include "bounce.h"
#include "player.h"
#include "region.h"
#include "roompainter.h"
#include "surface.h"

class RegionViewer
{
public:
	RegionViewer(Region *region);
	~RegionViewer();

	int numRooms() { return m_region->numRooms(); }
	bool finishedPainting() { return getNumPainted() >= numRooms(); }

	void draw(Surface *dst, int room, Direction direction);
	void drawTransition(Surface *dst,
	                    int room,
	                    Direction direction,
	                    int prevRoom,
	                    Direction prevDirection,
	                    Direction transitionDirection,
	                    double time,
	                    Player *player,
	                    list<Bounce* > bounceList,
	                    list<Bounce *> prevBounceList);

	int getRoomWidth() const { return m_roomWidth; }
	int getRoomHeight() const { return m_roomHeight; }
	Surface *getRoomSurface(int room, Direction direction);
	void makeSurfaces(int room);
private:
	int getNumPainted();
	void incNumPainted();
	void drawProgress(Surface *dst);
	void drawRoom(Surface *dst, Surface *roomSurface, int x, int y);

	Region *m_region;
	map<Direction, vector<Surface *>> m_roomSurfaces;
	int m_roomWidth;
	int m_roomHeight;
	RoomPainter m_roomPainter;
	Surface *m_wallSurface;

	int m_numPainted;
	SDL_sem *m_lock;
	Uint32 m_loadColor;

	Surface *m_loadingSurface;
	int m_loadingX;
	int m_loadingY;
};

#endif
