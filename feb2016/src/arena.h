#ifndef __ARENA_H
#define __ARENA_H

#include "bounce.h"
#include "direction.h"
#include "input.h"
#include "player.h"
#include "region.h"
#include "regionviewer.h"
#include "screen.h"
#include "timer.h"

class Arena : public Screen
{
public:
	Arena(InputDevice *inputDevice, int regionSize);
	virtual ~Arena();

	void key_pressed(SDLKey key, SDLMod mod);
	void key_released(SDLKey key, SDLMod mod);

	void update();
	void move(double dt);
	void draw(Surface *dst);
private:
	void initGoalPreview();
	void moveRoom(Direction moveDirection);
	void checkWallCollisions();
	void checkIfPlayerLeftRoom();
	void checkBounceCollisions();
	void resetPlayer();
	
	Region *m_region;
	int m_playerLocation;
	Rotation m_roomRotation;
	Direction m_roomDirection;
	RegionViewer *m_regionViewer;
	double m_transitionDelay;
	Timer m_transitionTimer;
	int m_prevLocation;
	Direction m_prevRoomDirection;
	Direction m_transitionDirection;
	Player *m_player;
	int m_goalLocation;
	Direction m_goalDirection;
	int m_goalScale;
	Surface *m_goalPreview;
	bool m_musicPlaying;
	Surface *m_hereSurface;
	Surface *m_wrongSurface;
	Surface *m_winSurface;
	list<Bounce *> m_bounceList;
	list<Bounce *> m_prevBounceList;
};

#endif
