#include "direction.h"

const char *directionName(Direction direction)
{
	switch (direction)
	{
	case NORTH: return "NORTH";
	case SOUTH: return "SOUTH";
	case WEST: return "WEST";
	case EAST: return "EAST";
	default: return "Unknown direction";
	}
	return "Unknown direction";
}

Direction applyRotation(Direction direction, Rotation rotation)
{
	switch (direction)
	{
	case NORTH:
		switch(rotation)
		{
		case ROTATE_NONE: return NORTH;
		case ROTATE_LEFT: return WEST;
		case ROTATE_RIGHT: return EAST;
		case ROTATE_180: return SOUTH;
		}
	case SOUTH:
		switch(rotation)
		{
		case ROTATE_NONE: return SOUTH;
		case ROTATE_LEFT: return EAST;
		case ROTATE_RIGHT: return WEST;
		case ROTATE_180: return NORTH;
		}
	case WEST:
		switch(rotation)
		{
		case ROTATE_NONE: return WEST;
		case ROTATE_LEFT: return SOUTH;
		case ROTATE_RIGHT: return NORTH;
		case ROTATE_180: return EAST;
		}
	case EAST:
		switch(rotation)
		{
		case ROTATE_NONE: return EAST;
		case ROTATE_LEFT: return NORTH;
		case ROTATE_RIGHT: return SOUTH;
		case ROTATE_180: return WEST;
		}
	default:
		return DIRECTION_NONE;
	}
}
