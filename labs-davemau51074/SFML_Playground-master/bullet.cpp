
#include "bullet.h"
#include "Tank.h"
#include <Thor/Math.hpp>
//#include <Tank>

double const DEG_TO_RAD = thor::Pi / 180.0f;

bullet::bullet(sf::Texture const & texture, sf::Vector2f const & pos, KeyHandler &keyFinder)
	: m_texture(texture), m_keyFinder(keyFinder)
{

	initSprites(pos);
}




void bullet::initSprites(sf::Vector2f const & pos)
{
	m_bullet.setTexture(m_texture);
	sf::IntRect bulletRect(8, 178, 8, 8);
	m_bullet.setTextureRect(bulletRect);
	m_bullet.setOrigin(bulletRect.width / 3.0, bulletRect.height / 2.0);
	m_bullet.setPosition(pos);

}


void bullet::update(double dt)
{
	//bulletAlive = true;
	//spawnATBarrel(m_bullet.getPosition(), bulletRotation);
	if (bulletAlive)
	{
		sf::Vector2f pos;
		sf::Vector2f newPos;

		newPos.x = m_bullet.getPosition().x + (cos(bulletRotation * DEG_TO_RAD) * bulletSpeed * dt / 1000);
		newPos.y = m_bullet.getPosition().y + (sin(bulletRotation * DEG_TO_RAD) * bulletSpeed * dt / 1000);
		m_bullet.setPosition(newPos);
	}
	m_bullet.setRotation(bulletRotation + 90);
	//bulletPosition = m_tankbase.getPosition();

	//if (m_tankBase.getPosition == Tank::collisionDetection)
	//	std::cout << m_tankBase.getPosition().x << m_tankBase.getPosition().y << std::endl;
}

void bullet::render(sf::RenderWindow & window)
{
//	window.draw(m_tankBase);
	window.draw(m_bullet);
	//window.draw(m_bullet);
}



// THis is foir the buulllet to spaw nat the barrell of the Tnksa 
void bullet::spawnATBarrel(sf::Vector2f pos, float rotation)
{
	bulletAlive = true;
	m_bullet.setPosition(pos.x + (std::cos((rotation * DEG_TO_RAD)) * (43.0f + m_bullet.getTextureRect().height)),
		                 pos.y + (std::sin((rotation * DEG_TO_RAD)) * (43.0f + m_bullet.getTextureRect().height)));
	bulletRotation = rotation;
	m_bullet.setRotation(rotation + 90.0f);
}


sf::Sprite const &bullet::getBulletSprite() const
{

	return m_bullet;

}