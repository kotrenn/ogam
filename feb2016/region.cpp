#include "region.h"

Region::Region()
	:m_rooms()
{
}

Region::Region(int numRooms)
	:m_rooms(numRooms)
{
	for (int i = 0; i < numRooms; ++i)
		m_rooms[i] = new Room(i);
}

Region::~Region()
{
	for (Room *room : m_rooms)
		delete room;
}

void Region::addLink(int src, Direction direction, int dst)
{
	Room *srcRoom = m_rooms[src];
	Room *dstRoom = m_rooms[dst];

	srcRoom->addNeighbor(direction, dstRoom);
}

void Region::computeRotations()
{
	for (Room *room : m_rooms)
	{
		for (Direction direction : s_DirectionArray)
		{
			Room *neighbor = room->getNeighbor(direction);
			Direction dstDirection = neighbor->getRoomDirection(room);
			Rotation rotation = computeRotation(direction, dstDirection);
			room->setRotation(direction, rotation);
		}
	}
}

Rotation Region::computeRotation(Direction srcDirection, Direction dstDirection)
{
	switch (srcDirection)
	{
	case NORTH:
		switch(dstDirection)
		{
		case NORTH: return ROTATE_180;
		case SOUTH: return ROTATE_NONE;
		case WEST: return ROTATE_LEFT;
		case EAST: return ROTATE_RIGHT;
		default: return ROTATE_NONE;
		}
	case SOUTH:
		switch(dstDirection)
		{
		case NORTH: return ROTATE_NONE;
		case SOUTH: return ROTATE_180;
		case WEST: return ROTATE_RIGHT;
		case EAST: return ROTATE_LEFT;
		default: return ROTATE_NONE;
		}
	case WEST:
		switch(dstDirection)
		{
		case NORTH: return ROTATE_RIGHT;
		case SOUTH: return ROTATE_LEFT;
		case WEST: return ROTATE_180;
		case EAST: return ROTATE_NONE;
		default: return ROTATE_NONE;
		}
	case EAST:
		switch(dstDirection)
		{
		case NORTH: return ROTATE_LEFT;
		case SOUTH: return ROTATE_RIGHT;
		case WEST: return ROTATE_NONE;
		case EAST: return ROTATE_180;
		default: return ROTATE_NONE;
		}
	default:
		return ROTATE_NONE;
	}
}
