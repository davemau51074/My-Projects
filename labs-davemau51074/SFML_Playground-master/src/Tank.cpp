#include "Tank.h"
#include <iostream>
#include "bullet.h"

double const Tank::DEG_TO_RAD = thor::Pi / 180.0f;

Tank::Tank(sf::Texture const & texture, sf::Vector2f const & pos, KeyHandler &keyFinder)
: m_texture(texture), m_keyFinder(keyFinder)
{
	
	initSprites(pos);
	bullet bullet1(sf::Texture const & texture, sf::Vector2f const & pos, KeyHandler &keyFinder);

}


sf::Sprite const &Tank::getTurretSprite() const 
{

	return m_turret;

}

void Tank::update(double dt)
{	
	handleKeyInput();

	m_tankBase.setPosition(m_tankBase.getPosition().x + (cos(m_rotation * DEG_TO_RAD) * m_speed * dt/1000), (m_tankBase.getPosition().y + (sin(m_rotation * DEG_TO_RAD) * m_speed* dt / 1000)));
	m_tankBase.setRotation(m_rotation);
	m_turret.setPosition(m_tankBase.getPosition());
	m_turret.setRotation(m_rotation + m_turretRotate);

	if (m_tankBase.getPosition().x < 0)
	{
		m_tankBase.setPosition(1440, m_tankBase.getPosition().y);
	}

	if (m_tankBase.getPosition().x > 1440)
	{
		m_tankBase.setPosition(0, m_tankBase.getPosition().y);
	}

	if (m_tankBase.getPosition().y < 0)
	{
		m_tankBase.setPosition(m_tankBase.getPosition().x, 900);
	}

	if (m_tankBase.getPosition().y > 900)
	{
		m_tankBase.setPosition(m_tankBase.getPosition().x, 0);
	}


	/*if bullet1.bulletAlive == true)
	{
		bullet1.position = m_tankBase;

	}*/
	//if (m_tankBase.getPosition == Tank::collisionDetection)
//	std::cout << m_tankBase.getPosition().x << m_tankBase.getPosition().y << std::endl;
}

void Tank::render(sf::RenderWindow & window) 
{
	window.draw(m_tankBase);
	window.draw(m_turret);
//	window.draw(m_bullet);
}


void Tank::initSprites(sf::Vector2f const & pos)
{
	// Initialise the tank base
	m_tankBase.setTexture(m_texture);
	sf::IntRect baseRect(2, 43, 79, 43);
	m_tankBase.setTextureRect(baseRect);
	m_tankBase.setOrigin(baseRect.width / 2.0, baseRect.height / 2.0);
	m_tankBase.setPosition(pos);

	// Initialise the turret
	m_turret.setTexture(m_texture);
	sf::IntRect turretRect(19, 1, 83, 31);
	m_turret.setTextureRect(turretRect);
	m_turret.setOrigin(turretRect.width / 3.0, turretRect.height / 2.0);
	m_turret.setPosition(pos);

	


}

void Tank::increaseSpeed()
{
	if (m_speed < 100.0)
	{
		m_speed += 0.1;
	}
}

void Tank::decreaseSpeed()
{
	if (m_speed > -100.0)
	{
		m_speed -= 0.1;
	}
}
void Tank::increaseRotation()
{
	m_rotation += 1;
}
void Tank::decreaseRotation()
{
	m_rotation -= 1;
}

void Tank::rotateT()
{
	m_turretRotate += 1;

}


void Tank::detateT()
{
	m_turretRotate -= 1;

}


void Tank::handleKeyInput()
{

	if (m_keyFinder.isPressed(sf::Keyboard::Up))
	{
		increaseSpeed();
	
	}


	if (m_keyFinder.isPressed(sf::Keyboard::Down))
	{
		decreaseSpeed();

	}


	if (m_keyFinder.isPressed(sf::Keyboard::Left))
	{
		decreaseRotation();

	}



	if (m_keyFinder.isPressed(sf::Keyboard::Right))
	{
		increaseRotation();

	}

	if (m_keyFinder.isPressed(sf::Keyboard::A))
	{
		rotateT();

	}

	if (m_keyFinder.isPressed(sf::Keyboard::D))
	{
		detateT();

	}

	if (m_keyFinder.isPressed(sf::Keyboard::Escape))
	{

		//system(Exit);
	}


	
}