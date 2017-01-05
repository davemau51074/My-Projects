#include "Game.h"

/// <summary>
/// @author DOG
/// @date June 2016
/// @version 1.0
/// 
/// </summary>

// Updates per milliseconds
static double const MS_PER_UPDATE = 10.0;

// My sounds and sound bufers 
sf::SoundBuffer soundbuff;
sf::SoundBuffer soundbuff2;
sf::Sound sound;
sf::Sound sound2;
/// <summary>
/// @brief Default constructor.
/// 
/// Create a new window and initialise member objects.
/// </summary>
///  sf::Texture myTexture;

Game::Game()
: m_window(sf::VideoMode(1440, 900, 32), "SFML Playground", sf::Style::Default)
{

	//this is where I load in my sound file 
	if (!soundbuff.loadFromFile("resources/sound.wav"))
	{
		std::cout << "problem loading sound file" << std::endl;
	}

	if (!soundbuff2.loadFromFile("resources/boom.wav"))
	{
		std::cout << "problem loading sound file" << std::endl;
	}


	// this is where I load in my text font
	if (!text.loadFromFile("resources\\MSYH.TTC"))
	{
		std::cout << "problem loading text file" << std::endl;
	}

	m_window.setVerticalSyncEnabled(true);
	int currentLvl = 1;
	if (!LevelLoader::load(currentLvl, m_level))
	{
		std::cout << "Level not loaded" << std::endl;
	}
	//sf::Texture myTexture;
	if (!myTexture.loadFromFile("./resources/images/E-100.png"))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}
	// this is where I load in my background
	if (!m_background.loadFromFile(m_level.m_background.m_fileName))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}


	if (!m_texture.loadFromFile("./resources/images/SpriteSheet.png"))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}
	// this is where I load in my Target
	if (!target.loadFromFile("resources/images/Target.png"))
	{
		std::cout << "problem loading text file" << std::endl;
	}

	//this is where I create the Tank
	m_tank.reset(new Tank(m_texture, m_level.m_tank.m_position, m_keyHandler));
	m_sprite.setTexture(myTexture);
	m_backgroundSprite.setTexture(m_background);
	m_sprite.setOrigin(sf::Vector2f(myTexture.getSize().x/ 2, myTexture.getSize().y / 2));
	m_sprite.setPosition(m_level.m_tank.m_position);
	sound.setBuffer(buffer);
	//This is wqhere Im creating the bullet
	m_bullet.reset(new bullet(m_texture, m_level.m_tank.m_position, m_keyHandler));
	generateWalls();
	generateTargets();
}



/// <summary>
/// Main game entry point - runs until user quits.
/// </summary>
void Game::run()
{
	sf::Clock clock;
	sf::Int32 lag = 0;

	while (m_window.isOpen())
	{
		sf::Time dt = clock.restart();

		lag += dt.asMilliseconds();
		timer = +1;
		processEvents();

		while (lag > MS_PER_UPDATE)
		{
			update(MS_PER_UPDATE);
			lag -= MS_PER_UPDATE;
		}
		update(MS_PER_UPDATE);

		render();
			
	}
}


// This is how I generate my walls for the game 
void Game::generateWalls()
{


	sf::IntRect wallRect(2, 129, 33, 23);
	//Create walls

	for (ObstacleData const &obstacle : m_level.m_obstacles)
	{
		std::unique_ptr<sf::Sprite> sprite(new sf::Sprite());
		sprite->setTexture(m_texture);
		sprite->setTextureRect(wallRect);
		sprite->setOrigin(wallRect.width / 20, wallRect.height / 20);
		sprite->setPosition(obstacle.m_position);
		sprite->setRotation(obstacle.m_rotation);
		m_wallSprites.push_back(std::move(sprite));



	}



}



void Game::generateTargets()
{

	//Wht I usae to generate my targets 
	for (Target const &obstacle : m_level.m_target)
	{
		std::unique_ptr<sf::Sprite> m_targetsprites(new sf::Sprite());
		m_targetsprites->setTexture(target);
		m_targetsprites->setPosition(obstacle.m_position.x + 100, obstacle.m_position.y + 100);
		m_targetsprites->setScale(0.5, 0.5);
		m_targetSprite.push_back(std::move(m_targetsprites));

	}



}

bool Game::checkTankWallCollision()
{
	//This is the fucnvtion that checks each wall and the tank 
	for (std::unique_ptr<sf::Sprite> const & sprite : m_wallSprites)
	{
		if (CollisionDetector::collision(m_tank->getTurretSprite(), *sprite))
		{
			return true;
			
		}
	
	}
	return false;
}

bool Game::checkBulletWallCollision()
{
	
	//This is the fucnvtion that checks each wall and the bullet  
		for (std::unique_ptr<sf::Sprite> const & sprite : m_wallSprites)
		{
			if (CollisionDetector::collision(m_bullet->getBulletSprite(), *sprite))
			{

			//	boom.setBuffer(soundbuff2);
				boom.play();
				return true;
			}

		}
	
	return false;
}


	//THIS IS THE COLLISION FOR THE TARGET AND THE BULLET
bool Game::checkTargetCollision()
{

	for (std::unique_ptr<sf::Sprite> const & sprite : m_targetSprite)
	{
		if (CollisionDetector::collision(m_bullet->getBulletSprite(), *sprite))
		{
			sprite->setPosition(-1000, -1000);
			std::cout << "Hit" << std::endl;
			return true;
			targetAlive = false;
			
		}
	}
	return false;
}
	

//THis is for to check the Bullet against the barrel
void Game::fire()
{
	m_bullet->spawnATBarrel(m_tank->getTurretSprite().getPosition(),
		m_tank->getTurretSprite().getRotation());
}



/// <summary>
/// @brief Check for events
/// 
/// Allows window to function and exit. 
/// Events are passed on to the Game::processGameEvents() method
/// </summary>
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
		processGameEvents(event);
	}
}

/// <summary>
/// @brief Handle all user input.
/// 
/// Detect and handle keyboard input.
/// </summary>
/// <param name="event">system event</param>
void Game::processGameEvents(sf::Event& event)
{
	// check if the event is a a mouse button release
		switch (event.type)
		{
			
		case sf::Event::KeyPressed:
			m_keyHandler.updateKey(event.key.code, true);
			//When the player presses space the bullet bool is set to true and 
			//the souund file for the bullet is played 
			if (m_keyHandler.isPressed(sf::Keyboard::Space))
			{
				fire();
				sound.setBuffer(soundbuff);
				sound.play();
				bulletAlive = true;
			}
			break;
		case sf::Event::KeyReleased:
			m_keyHandler.updateKey(event.key.code, false);
			break;
		default:
			break;
		}


	
	
}

/// <summary>
/// Method to handle all game updates
/// </summary>
/// <param name="time">update delta time</param>
void Game::update(double dt)
{
	//this is where I update the text and fonts 
	message.setFont(text);
	message.setString("Time:  " + std::to_string((int) m_clock.getElapsedTime().asSeconds()) );
	message.setPosition(50, 40);
	message.setColor(sf::Color::Black);
	message2.setFont(text);
	message2.setString("Score: " + std::to_string((int)score));
	message2.setPosition(50, 70);
	message2.setColor(sf::Color::Black);
	message.setCharacterSize(30);
	message2.setCharacterSize(30);
	//*******************************************
	m_tank->update(dt);
	m_bullet->update(dt);
	if (checkTankWallCollision())
	{
		m_tank->m_speed = -m_tank->m_speed/1.5;
	//	m_tankbase->m_speed = -m_tankbase->m_speed/2;
	}

	//This if checks to seee if the bullet is interescting with a wall
	if (checkBulletWallCollision())
	{
		m_bullet->bulletAlive = false;	
		bulletAlive = false;
	}
	//This if checks to seee if the bullet is interescting with a Target
	if (checkTargetCollision())
	{
		score += 5;
	}
}


/// <summary>
/// @brief draw the window for the game.
/// 
/// </summary>
void Game::render()
{
	
	m_window.clear(sf::Color(0, 0, 0, 0));
	m_window.draw(m_backgroundSprite);
	m_tank->render(m_window);

	//I have a bool to ensure the bullet is only drawing when needed 
	if (bulletAlive == true)
	{
		m_bullet->render(m_window);
	}

	//THis is where I draw my two text messages
	m_window.draw(message);
	m_window.draw(message2);
	for (auto &sprite : m_wallSprites)
	{
		m_window.draw(*sprite);
	}
	

	//the for loop used for drawing my targets 
		for (auto &sprite : m_targetSprite)
		{
			if (targetAlive == true)
			{
				m_window.draw(*sprite);
			}
		}
	
	m_window.display();
	
}


