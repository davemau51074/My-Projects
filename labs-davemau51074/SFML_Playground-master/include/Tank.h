#pragma once
#include <SFML/Graphics.hpp>
#include <Thor/Math.hpp>
#include "KeyHandler.h"
#include "LevelLoader.h"

/// <summary>
/// @brief A simple tank controller.
/// 
/// This class will manage all tank movement and rotations.
/// </summary>
class Tank
{

		double m_rotation = 0;
		double m_turretRotate = 0;
	public:	
		Tank(sf::Texture const & texture, sf::Vector2f const & pos, KeyHandler &keyFinder);
		void update(double dt);
		void render(sf::RenderWindow & window);
		void increaseSpeed();
		double m_speed = 0;
		void handleKeyInput();

	void decreaseSpeed();

	void increaseRotation();

	void decreaseRotation();
	sf::Sprite const & getTurretSprite() const;

	void rotateT();
	void detateT();

	double static const DEG_TO_RAD;
private:
	void initSprites(sf::Vector2f const & pos);
	sf::Sprite m_tankBase;
	sf::Sprite m_turret;
	
	//bullet bullet1;
	sf::Texture const & m_texture; 
	KeyHandler &m_keyFinder;
		
};
