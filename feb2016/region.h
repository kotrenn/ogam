#ifndef __REGION_H
#define __REGION_H

#include "common.h"
#include "room.h"

class Region
{
public:
	Region();
	Region(int numRooms);
	~Region();

	void addLink(int src, Direction direction, int dst);
	void computeRotations();

	Room *getRoom(int room) { return m_rooms[room]; }

	unsigned int numRooms() const { return m_rooms.size(); }
private:
	Rotation computeRotation(Direction srcDirection, Direction dstDirection);
	
	vector<Room *> m_rooms;
};

#endif
