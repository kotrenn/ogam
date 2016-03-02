#ifndef __ROOM_H
#define __ROOM_H

#include "common.h"
#include "direction.h"
#include "rotation.h"

class Room
{
public:
	Room();
	Room(int id);

	int getID() { return m_id; }
	
	bool hasNeighbor(Direction direction);
	int numNeighbors() { return m_neighbors.size(); }

	void addNeighbor(Direction direction, Room *neighbor);
	void setRotation(Direction direction, Rotation rotation);
	
	Room *getNeighbor(Direction direction);
	Rotation getRotation(Direction direction);

	Direction getRoomDirection(Room *neighbor);
private:
	int m_id;
	map<Direction, Room *> m_neighbors;
	map<Direction, Rotation> m_rotations;
};

#endif
