#include "LevelLoader.h"

void operator >> (const YAML::Node& obstacleNode, ObstacleData& obstacle)
{
   obstacle.m_type = obstacleNode["type"].as<std::string>();
   obstacle.m_position.x = obstacleNode["position"]["x"].as<float>();
   obstacle.m_position.y = obstacleNode["position"]["y"].as<float>();
   obstacle.m_rotation = obstacleNode["rotation"].as<double>();
}

void operator >> (const YAML::Node& backgroundNode, BackgroundData& background)
{
   background.m_fileName = backgroundNode["file"].as<std::string>();
}

void operator >> (const YAML::Node& tankNode, TankData& tank)
{
	int rgen = std::rand() % 4 + 1;

	//This is the random Gen I use to to select one of the four corners to spawn in 

	if (rgen == 1)
	{

		tank.m_position.x = tankNode["position1"]["x"].as<float>();
		tank.m_position.y = tankNode["position1"]["y"].as<float>();
	}

	if (rgen == 2)
	{

		tank.m_position.x = tankNode["position2"]["x"].as<float>();
		tank.m_position.y = tankNode["position2"]["y"].as<float>();
	}

	if (rgen == 3)
	{

		tank.m_position.x = tankNode["position3"]["x"].as<float>();
		tank.m_position.y = tankNode["position3"]["y"].as<float>();
	}

	if (rgen == 4)
	{

		tank.m_position.x = tankNode["position4"]["x"].as<float>();
		tank.m_position.y = tankNode["position4"]["y"].as<float>();
	}
}


void operator >> (const YAML::Node& targetNode, Target& target)
{
	target.m_type = targetNode["type"].as<std::string>();
	target.m_position.x = targetNode["position"]["x"].as<float>();
	target.m_position.y = targetNode["position"]["y"].as<float>();
	target.targetAlive = true;
}



void operator >> (const YAML::Node& levelNode, LevelData& level)
{
   levelNode["background"] >> level.m_background;

   levelNode["tank"] >> level.m_tank;

   const YAML::Node& obstaclesNode = levelNode["obstacles"].as<YAML::Node>();
  
   for (unsigned i = 0; i < obstaclesNode.size(); ++i)
   {
	  ObstacleData obstacle;
	  obstaclesNode[i] >> obstacle;
	  level.m_obstacles.push_back(obstacle);
   }

   //levelNode["target"] >> level.m_target;
   const YAML::Node& targetNode = levelNode["target"].as<YAML::Node>();

   for (unsigned i = 0; i < targetNode.size(); ++i)
   {
	   Target targets; 
	   targetNode[i] >> targets;
	   level.m_target.push_back(targets);


   }
}

LevelLoader::LevelLoader()
{
}

bool LevelLoader::load(int nr, LevelData& level)
{
   std::stringstream ss;
   ss << "./resources/levels/level";
   ss << nr;
   ss << ".yaml";

   try
   {
	  YAML::Node baseNode = YAML::LoadFile(ss.str());
	  if (baseNode.IsNull())
	  {
		  std::string message("file: " + ss.str() + " not found");
		  throw std::exception(message.c_str());
	  }
	  baseNode >> level;
   }
   catch(YAML::ParserException& e)
   {
       std::cout << e.what() << "\n";
       return false;
   }
   catch (std::exception& e)
   {
	   std::cout << e.what() << "\n";
	   return false;
   }

   return true;
}
