#ifndef __PLAYER_H
#define __PLAYER_H

#include "input.h"
#include "surface.h"

class Player : public InputListener
{
public:
	Player(InputDevice *inputDevice);
	virtual ~Player();

	void respawn();

	void update();
	void move(double dt);
	void draw(Surface *dst, int offsetX = 0, int offsetY = 0);

	int getX() const { return m_x; }
	int getY() const { return m_y; }
	int getW() const { return m_w; }
	int getH() const { return m_h; }

	void setX(int x) { m_x = x; }
	void setY(int y) { m_y = y; }
private:
	Surface *m_surface;
	int m_x;
	int m_y;
	int m_w;
	int m_h;
	int m_vx;
	int m_vy;
};

#endif
