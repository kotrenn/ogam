#include "arena.h"

#include "regionbuilder.h"
#include "resourcemanager.h"
#include "system.h"
#include "title.h"

Arena::Arena(InputDevice *inputDevice, int regionSize)
	:Screen(inputDevice),
	 m_region(NULL),
	 m_playerLocation(0),
	 m_roomRotation(ROTATE_NONE),
	 m_roomDirection(NORTH),
	 m_regionViewer(NULL),
	 m_transitionDelay(0.5),
	 m_transitionTimer(),
	 m_prevLocation(-1),
	 m_prevRoomDirection(DIRECTION_NONE),
	 m_transitionDirection(DIRECTION_NONE),
	 m_player(NULL),
	 m_goalLocation(0),
	 m_goalDirection(DIRECTION_NONE),
	 m_goalScale(3),
	 m_goalPreview(NULL),
	 m_musicPlaying(false),
	 m_hereSurface(NULL),
	 m_wrongSurface(NULL),
	 m_winSurface(NULL),
	 m_bounceList(),
	 m_prevBounceList()
{
	System *system = System::get_instance();
	system->add_key_listener(this);

	m_region = RegionBuilder::buildRegion(regionSize);
	
	m_regionViewer = new RegionViewer(m_region);

	m_player = new Player(inputDevice);

	int numRooms = m_region->numRooms();
	m_goalLocation = (numRooms > 1)? randint(1, numRooms - 1) : 0;
	m_goalDirection = s_DirectionArray[randint(0, 3)];

	ResourceManager *rm = ResourceManager::get_instance();
	m_hereSurface = rm->get_image("here.png");
	m_wrongSurface = rm->get_image("wrong.png");
	m_winSurface = rm->get_image("win.png");
}

Arena::~Arena()
{
	for (auto bounce : m_bounceList)
		delete bounce;
	for (auto bounce : m_prevBounceList)
		delete bounce;
	
	delete m_goalPreview;
	
	delete m_player;

	delete m_regionViewer;
	delete m_region;
}

void Arena::initGoalPreview()
{
	Surface *roomSurface = m_regionViewer->getRoomSurface(m_goalLocation, m_goalDirection);

	int roomWidth = m_regionViewer->getRoomWidth();
	int roomHeight = m_regionViewer->getRoomHeight();

	int roomWS = roomWidth / m_goalScale;
	int roomHS = roomHeight / m_goalScale;

	m_goalPreview = new Surface(roomWS, roomHS);
	
	for (int x = 0; x < roomWS; ++x)
	{
		for (int y = 0; y < roomHS; ++y)
		{
			Uint32 color = roomSurface->get_pixel(x * m_goalScale, y * m_goalScale);
			m_goalPreview->draw_point(color, x, y);
		}
	}
}

void Arena::key_pressed(SDLKey, SDLMod)
{
}

void Arena::key_released(SDLKey key, SDLMod)
{
	if (!m_transitionTimer.done()) return;
	
	bool moved = false;
	Direction inputDirection;
	if (key == SDLK_w) { inputDirection = NORTH; moved = true; }
	if (key == SDLK_s) { inputDirection = SOUTH; moved = true; }
	if (key == SDLK_a) { inputDirection = WEST; moved = true; }
	if (key == SDLK_d) { inputDirection = EAST; moved = true; }

	if (moved)
		moveRoom(inputDirection);
	
	if (key == SDLK_q && m_regionViewer->finishedPainting())
	{
		ResourceManager *rm = ResourceManager::get_instance();
		rm->stop_music(200);
		
		Title *title = new Title(m_inputDevice);
		transition(title);
	}
}

void Arena::moveRoom(Direction moveDirection)
{
	// Store previous state
	m_prevLocation = m_playerLocation;
	m_prevRoomDirection = m_roomDirection;

	// Store what direction we're moving in
	m_transitionDirection = moveDirection;

	// Apply local room rotation to the input
	Rotation invertedRotation = invertRotation(m_roomRotation);
	moveDirection = applyRotation(moveDirection, invertedRotation);

	// Look up the next room
	Room *currentRoom = m_region->getRoom(m_playerLocation);
	Room *neighbor = currentRoom->getNeighbor(moveDirection);
	m_playerLocation = neighbor->getID();

	// Determine the rotation of the new room
	Rotation transitionRotation = currentRoom->getRotation(moveDirection);
	m_roomRotation = applyRotation(m_roomRotation, transitionRotation);
	m_roomDirection = applyRotation(m_roomDirection, transitionRotation);

	// Move bounces around
	for (auto bounce : m_prevBounceList)
		delete bounce;
	m_prevBounceList.clear();
	for (auto bounce : m_bounceList)
		m_prevBounceList.push_back(bounce);
	m_bounceList.clear();
	if (m_playerLocation != m_goalLocation || m_roomDirection != m_goalDirection)
	{
		m_bounceList.push_back(new Bounce());
		while (randint(1, 3) == 1)
			m_bounceList.push_back(new Bounce());
	}

	// Fire off the animation timer for moving between rooms
	m_transitionTimer.reset(m_transitionDelay);
}

void Arena::update()
{
	if (!m_regionViewer->finishedPainting()) return;

	if (!m_musicPlaying)
	{
		ResourceManager *rm = ResourceManager::get_instance();
		rm->play_music("music.ogg");
		m_musicPlaying = true;
	}

	if (m_goalPreview == NULL)
		initGoalPreview();
	
	if (m_transitionTimer.done())
	{
		m_player->update();
		for (auto bounce : m_bounceList)
			bounce->update();
	}

	checkWallCollisions();
	checkIfPlayerLeftRoom();
	checkBounceCollisions();
}

void Arena::checkWallCollisions()
{
	int wallSize = 20;
	int gapSize = 20;
	int gapS2 = gapSize / 2;

	int roomWidth  = m_regionViewer->getRoomWidth();
	int roomHeight = m_regionViewer->getRoomHeight();
	int roomW2 = roomWidth / 2;
	int roomH2 = roomHeight / 2;

	int leftWall   = wallSize;
	int rightWall  = roomWidth - wallSize;
	int topWall    = wallSize;
	int bottomWall = roomHeight - wallSize;

	int gapLeft   = roomW2 - gapS2;
	int gapRight  = roomW2 + gapS2;
	int gapTop    = roomH2 - gapS2;
	int gapBottom = roomH2 + gapS2;

	int playerX  = m_player->getX();
	int playerY  = m_player->getY();
	int playerW2 = m_player->getW() / 2;
	int playerH2 = m_player->getH() / 2;

	int playerLeft   = playerX - playerW2;
	int playerRight  = playerX + playerW2;
	int playerTop    = playerY - playerH2;
	int playerBottom = playerY + playerH2;

	bool midRow = playerTop  >= gapTop  && playerBottom <= gapBottom;
	bool midCol = playerLeft >= gapLeft && playerRight  <= gapRight;

	bool partialMidRowAbove = gapBottom >= playerBottom && playerBottom >= gapTop;
	bool partialMidRowBelow = gapBottom >= playerTop    && playerTop    >= gapTop;
	bool partialMidColLeft  = gapRight  >= playerRight  && playerRight  >= gapLeft;
	bool partialMidColRight = gapRight  >= playerLeft   && playerLeft   >= gapLeft;

	bool partialMidRow = partialMidRowAbove || partialMidRowBelow || midRow;
	bool partialMidCol = partialMidColLeft  || partialMidColRight || midCol;
	
	int newX = playerX;
	int newY = playerY;

	if (playerLeft   < leftWall   && !partialMidRow) newX = leftWall   + playerW2;
	if (playerRight  > rightWall  && !partialMidRow) newX = rightWall  - playerW2;
	if (playerTop    < topWall    && !partialMidCol) newY = topWall    + playerH2;
	if (playerBottom > bottomWall && !partialMidCol) newY = bottomWall - playerH2;


	if (partialMidRow && !midRow && (playerLeft < leftWall || playerRight  > rightWall))
	{
		if (playerTop    < gapTop)    newY = gapTop    + playerH2;
		if (playerBottom > gapBottom) newY = gapBottom - playerH2;
	}

	if (partialMidCol && !midCol && (playerTop  < topWall  || playerBottom > bottomWall))
	{
		if (playerLeft  < gapLeft)  newX = gapLeft  + playerW2;
		if (playerRight > gapRight) newX = gapRight - playerW2;
	}

	m_player->setX(newX);
	m_player->setY(newY);
}

void Arena::checkIfPlayerLeftRoom()
{
	int playerX = m_player->getX();
	int playerY = m_player->getY();

	int roomWidth = m_regionViewer->getRoomWidth();
	int roomHeight = m_regionViewer->getRoomHeight();

	int reflectX = roomWidth - playerX - 1;
	int reflectY = roomHeight - playerY - 1;

	int newX = playerX;
	int newY = playerY;

	Direction moveDirection = DIRECTION_NONE;
	if (playerX < 0)           moveDirection = WEST;
	if (playerX >= roomWidth)  moveDirection = EAST;
	if (playerY < 0)           moveDirection = NORTH;
	if (playerY >= roomHeight) moveDirection = SOUTH;

	if (moveDirection == NORTH || moveDirection == SOUTH) newY = reflectY;
	if (moveDirection == WEST  || moveDirection == EAST)  newX = reflectX;

	if (moveDirection == DIRECTION_NONE) return;

	m_player->setX(newX);
	m_player->setY(newY);
	m_player->move(0.1);
	m_player->move(0.1);
	
	moveRoom(moveDirection);
}

void Arena::checkBounceCollisions()
{
	bool collision = false;
	for (auto bounce : m_bounceList)
		if (bounce->collidesWithPlayer(m_player))
			collision = true;

	if (collision)
		resetPlayer();
}

void Arena::resetPlayer()
{
	for (auto bounce : m_bounceList)
		delete bounce;
	for (auto bounce : m_prevBounceList)
		delete bounce;

	m_bounceList.clear();
	m_prevBounceList.clear();

	m_playerLocation = 0;
	m_roomRotation = ROTATE_NONE;
	m_roomDirection = NORTH;
	m_prevLocation = -1;
	m_prevRoomDirection = DIRECTION_NONE;
	m_transitionDirection = DIRECTION_NONE;
	m_player->respawn();
}

void Arena::move(double dt)
{
	if (!m_regionViewer->finishedPainting()) return;
	
	if (m_transitionTimer.done())
	{
		m_player->move(dt);
		for (auto bounce : m_bounceList)
			bounce->move(dt);
	}
}

void Arena::draw(Surface *dst)
{
	if (!m_regionViewer->finishedPainting())
	{
		m_regionViewer->draw(dst, m_playerLocation, m_roomDirection);
		return;
	}
	
	ResourceManager *rm = ResourceManager::get_instance();
	Font *font = rm->get_font();
	font->draw_string(dst, 5, 455, "Q - RETURN TO TITLE");
	
	if (m_transitionTimer.done())
	{
		m_regionViewer->draw(dst, m_playerLocation, m_roomDirection);
		m_player->draw(dst);
		for (auto bounce : m_bounceList)
			bounce->draw(dst);
	}
	else
	{
		m_regionViewer->drawTransition(dst,
		                               m_playerLocation,
		                               m_roomDirection,
		                               m_prevLocation,
		                               m_prevRoomDirection,
		                               m_transitionDirection,
		                               m_transitionTimer.get_time() / m_transitionDelay,
		                               m_player,
		                               m_bounceList,
		                               m_prevBounceList);
	}

	if (m_goalPreview == NULL) return;

	System *system = System::get_instance();

	int systemWidth = system->get_width();
	int systemHeight = system->get_height();
	
	int previewWidth = m_goalPreview->get_w();
	int previewHeight = m_goalPreview->get_h();
	
	int goalX = systemWidth - previewWidth - 40;
	int goalY = (systemHeight - previewHeight) / 2 + 20;
	
	dst->blit(m_goalPreview, goalX, goalY);

	int roomWidth = m_regionViewer->getRoomWidth();
	int hereX = roomWidth + 12;
	int hereY = 10;
	dst->blit(m_hereSurface, hereX, hereY);

	if (m_playerLocation == m_goalLocation)
	{
		int statusX = 420;
		int statusY = 330;
		if (m_roomDirection == m_goalDirection)
			dst->blit(m_winSurface, statusX, statusY);
		else
			dst->blit(m_wrongSurface, statusX, statusY);
	}
}
