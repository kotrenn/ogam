#ifndef __BOUNCE_H
#define __BOUNCE_H

#include "player.h"
#include "surface.h"
#include "timer.h"

class Bounce
{
public:
	Bounce();
	~Bounce();

	void update();
	void move(double dt);
	void draw(Surface *dst, int offsetX = 0, int offsetY = 0);

	int getX() const { return m_x; }
	int getY() const { return m_y; }
	int getW() const { return m_w; }
	int getH() const { return m_h; }

	void setX(int x) { m_x = x; }
	void setY(int y) { m_y = y; }

	bool collidesWithPlayer(Player *player);
private:
	Surface *m_surface;
	int m_x;
	int m_y;
	int m_w;
	int m_h;
	int m_vx;
	int m_vy;
	int m_numFrames;
	int m_frame;
	Timer m_timer;
};

#endif
