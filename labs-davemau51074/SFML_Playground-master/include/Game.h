#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "LevelLoader.h"
#include "Tank.h"
#include "Bullet.h"
#include "KeyHandler.h"
#include "CollisionDetector.h"

/// <summary>
/// @brief Main class for the SFML Playground project.
/// 
/// This will be a single class framework for learning about SFML.
/// </summary>
class Game
{
public:
	Game();	
	sf::SoundBuffer buffer;
	sf::SoundBuffer buffer2;
	sf::Sound boom;
	sf::Sound sound;
	void run();
protected:	
	void update(double dt);
	void render();
	void generateWalls();
	void processEvents();	
	void processGameEvents(sf::Event&);
	sf::Sprite m_sprite;
	int score = 0;
	sf::Clock m_clock;
	

	//THis is wqhere i Create the sprites gor me Tanak 
	std::vector<std::unique_ptr<sf::Sprite>> m_wallSprites;
	std::vector<std::unique_ptr<sf::Sprite>> m_targetSprite;
	std::vector<std::unique_ptr<sf::Sprite>> m_targetSprite2;
	sf::Texture m_texture;


	std::unique_ptr<Tank> m_tank;
	std::unique_ptr<Tank> m_turret;
	std::unique_ptr<Tank> m_tankbase;
	std::vector<sf::Sprite>  m_sprites;
	sf::Texture m_background;
	sf::Sprite m_backgroundSprite;
	sf::Sprite m_targetsprite;
	LevelData m_level;
	KeyHandler m_keyHandler;
	int timer;
	
	//thiS IS the bools for my bullet 
	bool bulletAlive = false;
	bool targetAlive = true;
	bool targetAlive2 = false;
	void generateTargets();
	bool checkTankWallCollision();
	bool checkBulletWallCollision();
	bool checkTargetCollision();
	//std::vector<sf::Sprite>  m_sprites;
	sf::RenderWindow m_window;
	sf::Texture target;
	sf::Texture myTexture;
	sf::Font text;
	sf::Text message;
	sf::Text message2;
	
	
	
	// main window
	std::unique_ptr<bullet> m_bullet;
	
	void fire();
	
};
