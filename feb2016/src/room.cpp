#include "room.h"

Room::Room()
	:m_id(-1),
	 m_neighbors(),
	 m_rotations()
{
}

Room::Room(int id)
	:m_id(id),
	 m_neighbors(),
	 m_rotations()
{
}

bool Room::hasNeighbor(Direction direction)
{
	return m_neighbors.find(direction) != m_neighbors.end();
}

void Room::addNeighbor(Direction direction, Room *neighbor)
{
	m_neighbors[direction] = neighbor;
}

void Room::setRotation(Direction direction, Rotation rotation)
{
	m_rotations[direction] = rotation;
}

Room *Room::getNeighbor(Direction direction)
{
	return m_neighbors[direction];
}

Rotation Room::getRotation(Direction direction)
{
	return m_rotations[direction];
}

Direction Room::getRoomDirection(Room *neighbor)
{
	for (Direction direction : s_DirectionArray)
	{
		Room *room = m_neighbors[direction];
		if (room == neighbor) return direction;
	}
	
	return DIRECTION_NONE;
}
