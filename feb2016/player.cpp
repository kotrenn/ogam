#include "player.h"

#include "direction.h"
#include "resourcemanager.h"
#include "system.h"

Player::Player(InputDevice *inputDevice)
	:InputListener(inputDevice),
	 m_surface(NULL),
	 m_x(0),
	 m_y(0),
	 m_w(0),
	 m_h(0),
	 m_vx(0),
	 m_vy(0)
{
	ResourceManager *rm = ResourceManager::get_instance();
	m_surface = rm->get_image("player.png");
	m_surface->set_color_key(0, 0xFF, 0xFF);

	m_w = m_surface->get_w();
	m_h = m_surface->get_h();

	respawn();
}

Player::~Player()
{
}

void Player::respawn()
{
	m_x = 210;
	m_y = 210;
	m_vx = 0;
	m_vy = 0;
}

void Player::update()
{
	int speed = 1;
	m_vx = 0;
	m_vy = 0;
	
	if (m_input->pressed(BUTTON_UP))    m_vy = -speed;
	if (m_input->pressed(BUTTON_DOWN))  m_vy = speed;
	if (m_input->pressed(BUTTON_LEFT))  m_vx = -speed;
	if (m_input->pressed(BUTTON_RIGHT)) m_vx = speed;
}

void Player::move(double)
{
	if (abs(m_vx) + abs(m_vy) == 0) return;

	m_x += m_vx;
	m_y += m_vy;
}

void Player::draw(Surface *dst, int offsetX, int offsetY)
{
	int w2 = m_w / 2;
	int h2 = m_h / 2;
	int cornerX = m_x - w2;
	int cornerY = m_y - h2;
	cornerX += offsetX;
	cornerY += offsetY;
	dst->blit(m_surface, cornerX, cornerY);
}
