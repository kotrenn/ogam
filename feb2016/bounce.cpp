#include "bounce.h"

#include "resourcemanager.h"

Bounce::Bounce()
	:m_surface(NULL),
	 m_x(250),
	 m_y(250),
	 m_w(0),
	 m_h(0),
	 m_vx(0),
	 m_vy(0),
	 m_numFrames(2),
	 m_frame(0),
	 m_timer()
{
	ResourceManager *rm = ResourceManager::get_instance();
	m_surface = rm->get_image("bounce.png");
	m_surface->set_color_key(0, 0xFF, 0xFF);

	m_w = m_surface->get_w() / m_numFrames;
	m_h = m_surface->get_h();

	int width = 420;
	int height = 420;
	int w2 = width / 2;
	int h2 = height / 2;
	int w4 = width / 4;
	int h4 = height / 4;
	m_x = randint(w4, w4 + w2);
	m_y = randint(h4, h4 + h2);

	while (abs(m_vx) + abs(m_vy) == 0)
	{
		m_vx = randint(-1, 1);
		m_vy = randint(-1, 1);
	}
}

Bounce::~Bounce()
{
}

void Bounce::update()
{
	int wallSize = 20;

	int roomWidth = 420;
	int roomHeight = 420;

	int leftWall = wallSize;
	int rightWall = roomWidth - wallSize;
	int topWall = wallSize;
	int bottomWall = roomHeight - wallSize;

	int bounceX = m_x;
	int bounceY = m_y;
	int bounceW2 = m_w / 2;
	int bounceH2 = m_h / 2;

	int bounceLeft = bounceX - bounceW2;
	int bounceRight = bounceX + bounceW2;
	int bounceTop = bounceY - bounceH2;
	int bounceBottom = bounceY + bounceH2;

	if (bounceLeft   < leftWall)   { m_x = leftWall   + bounceW2; m_vx *= -1; }
	if (bounceTop    < topWall)    { m_y = topWall    + bounceH2; m_vy *= -1; }
	if (bounceRight  > rightWall)  { m_x = rightWall  - bounceW2; m_vx *= -1; }
	if (bounceBottom > bottomWall) { m_y = bottomWall - bounceH2; m_vy *= -1; }

	if (m_timer.done())
	{
		m_frame = (m_frame + 1) % m_numFrames;
		m_timer.reset(1.2);
	}
}

void Bounce::move(double)
{
	m_x += m_vx;
	m_y += m_vy;
}

void Bounce::draw(Surface *dst, int offsetX, int offsetY)
{
	int w2 = m_w / 2;
	int h2 = m_h / 2;
	int cornerX = m_x - w2;
	int cornerY = m_y - h2;
	cornerX += offsetX;
	cornerY += offsetY;

	int roomWidth = 420;
	int roomHeight = 420;

	int srcX = 0;
	int srcY = 0;
	int srcW = m_w;
	int srcH = m_h;

	if (cornerX > roomWidth) return;
	if (cornerY > roomHeight) return;
	if (cornerX + m_w > roomWidth) { srcW = roomWidth - cornerX; }
	if (cornerY + m_h > roomHeight) { srcH = roomHeight - cornerY; }

	srcX += m_w * m_frame;
	
	Rect dims(srcX, srcY, srcW, srcH);
	dst->blit(m_surface, cornerX, cornerY, dims);
}

bool Bounce::collidesWithPlayer(Player *player)
{
	int bounceW2 = m_w / 2;
	int bounceH2 = m_h / 2;
	int bounceX = m_x - bounceW2;
	int bounceY = m_y - bounceH2;
	int bounceW = m_w;
	int bounceH = m_h;

	int playerW = player->getW();
	int playerH = player->getH();
	int playerW2 = playerW / 2;
	int playerH2 = playerH / 2;
	int playerX = player->getX() - playerW2;
	int playerY = player->getY() - playerH2;

	Rect bounceRect(bounceX, bounceY, bounceW, bounceH);
	Rect playerRect(playerX, playerY, playerW, playerH);

	return bounceRect.collides(&playerRect);
}
