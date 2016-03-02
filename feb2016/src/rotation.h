#ifndef __ROTATION_H
#define __ROTATION_H

typedef enum
{
	ROTATE_NONE, ROTATE_LEFT, ROTATE_RIGHT, ROTATE_180
} Rotation;

const char *rotationName(Rotation rotation);
Rotation applyRotation(Rotation lhs, Rotation rhs);
Rotation invertRotation(Rotation rotation);

static const Rotation s_RotationArray[] = { ROTATE_NONE,
                                            ROTATE_LEFT,
                                            ROTATE_RIGHT,
                                            ROTATE_180 };

#endif
