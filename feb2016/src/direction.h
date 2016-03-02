#ifndef __DIRECTION_H
#define __DIRECTION_H

#include "rotation.h"

typedef enum
{
	NORTH, EAST, SOUTH, WEST, DIRECTION_NONE
} Direction;

const char *directionName(Direction direction);
Direction applyRotation(Direction direction, Rotation rotation);

static const Direction s_DirectionArray[] = { NORTH, EAST, SOUTH, WEST };

#endif
