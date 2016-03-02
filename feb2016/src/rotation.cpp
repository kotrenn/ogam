#include "rotation.h"

const char *rotationName(Rotation rotation)
{
	switch (rotation)
	{
	case ROTATE_NONE: return "No rotation";
	case ROTATE_LEFT: return "Left rotation";
	case ROTATE_RIGHT: return "Right rotation";
	case ROTATE_180: return "180-degree rotation";
	}
	return "Unknown rotation";
}

Rotation applyRotation(Rotation lhs, Rotation rhs)
{
	switch (lhs)
	{
	case ROTATE_NONE: return rhs;
	case ROTATE_LEFT:
		switch (rhs)
		{
		case ROTATE_NONE: return ROTATE_LEFT;
		case ROTATE_LEFT: return ROTATE_180;
		case ROTATE_RIGHT: return ROTATE_NONE;
		case ROTATE_180: return ROTATE_RIGHT;
		default: break;
		}
	case ROTATE_RIGHT:
		switch (rhs)
		{
		case ROTATE_NONE: return ROTATE_RIGHT;
		case ROTATE_LEFT: return ROTATE_NONE;
		case ROTATE_RIGHT: return ROTATE_180;
		case ROTATE_180: return ROTATE_LEFT;
		default: break;
		}
	case ROTATE_180:
		switch (rhs)
		{
		case ROTATE_NONE: return ROTATE_180;
		case ROTATE_LEFT: return ROTATE_RIGHT;
		case ROTATE_RIGHT: return ROTATE_LEFT;
		case ROTATE_180: return ROTATE_NONE;
		default: break;
		}
	}
	
	return ROTATE_NONE;		
}

Rotation invertRotation(Rotation rotation)
{
	switch (rotation)
	{
	case ROTATE_NONE: return ROTATE_NONE;
	case ROTATE_LEFT: return ROTATE_RIGHT;
	case ROTATE_RIGHT: return ROTATE_LEFT;
	case ROTATE_180: return ROTATE_180;
	default: return ROTATE_NONE;
	}
}
