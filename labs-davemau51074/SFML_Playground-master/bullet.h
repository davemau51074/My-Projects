#pragma once

#include <SFML/Graphics.hpp>
#include "LevelLoader.h"
#include "Tank.h"
#include "KeyHandler.h"
#include "CollisionDetector.h"



class bullet
{
	public:
		bullet(sf::Texture const & texture, sf::Vector2f const & pos, KeyHandler &keyFinder);
	double bulletRotation = 0;
	double bulletPosition = 0;
	double bulletSpeed = 500;
	bool bulletAlive = false;
	void update(double dt);
	void render(sf::RenderWindow & window);
	void spawnATBarrel(sf::Vector2f pos, float rotation);

	sf::Texture const & m_texture;
	sf::Sprite const & getBulletSprite() const;
	sf::Sprite m_TankBase;
	sf::Sprite m_bullet;
	KeyHandler &m_keyFinder;
	void initSprites(sf::Vector2f const & pos);
	//bullet bullet; 

};