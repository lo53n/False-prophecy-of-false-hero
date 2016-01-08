#ifndef ENEMY_ENEMY
#define ENEMY_ENEMY

#include <vector>
#include <iostream>
#include <memory>


#include <SFML\Graphics.hpp>

#include "../StatsCalculations.h"



class Enemy : public sf::Drawable {



	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & _enemy_id;
		ar & _tile_underneath;
		ar & _stats;
		ar & _baseStats;
		ar & _positionOnGrid;
		ar & _positionOnMap;
	}



public:

	enum MOVEMENT{
		UP,
		RIGHT,
		DOWN,
		LEFT
	};

	///////////
	//Getters//
	///////////

	//Get enemy position on map (px)
	sf::Vector2f& getEnemyPositionOnMap();
	//Get enemy position on map (x,y)
	sf::Vector2i& getEnemyPositionOnGrid();
	//Get tile underneath the enemy on map
	char getTileUnderneathEnemy();
	//Get enemy identifier
	int getEnemyId();
	//Get enemy stats structure
	Enemy_Stats getEnemyStats();
	//Get enemy type
	int getEnemyType();
	//Get enemy rating
	int getEnemyRating();
	//Get enemy class
	int getEnemyClass();
	///////////
	//Setters//
	///////////

	//Set enemy position on map (px)
	void setEnemyPositionOnMap(sf::Vector2f newPositionOnMap);
	//Set enemy position on map (x,y)
	void setEnemyPositionOnGrid(sf::Vector2i newPositionOnGrid);
	//Set tile underneath the enemy on map
	void setTileUnderneathEnemy(char newTile);


	/////////////////
	//Agressiveness//
	/////////////////

	void setAlarmStatus(bool status);
	bool isAlarmed();
	void isPlayerInAggroRange(int range);
	void setAggroRange();

	//////////////
	//Directions//
	//////////////

	void setDirection(int direction);
	int getActualDirection();
	int getPreviousDirection();
	int getBackPreviousDirection();

	/////////////
	//Animation//
	/////////////
	bool checkIfThereIsNeedToAnimate();
	void moveSprite(float change);
	void checkDirection(sf::Vector2i newPos);
	/////////////

	char swapTileUnderneathToNextOne(char newTile);

	void takeHit(int damage);

	void increaseTicks(int &amount);
	void decreaseTicks();
	bool checkIfCanTakeAction();
	void moveEnemy(sf::Vector2i newPos); 

	void killEnemy();
	void resurrectEnemy();
	void reinforceEnemy(int heroRating);
	void resurrectAndReinforce(int heroRating);

	bool checkIfAlive();

	void restoreData();

	Enemy();
	Enemy(int id, char tile, Enemy_Stats stats, Enemy_Stats base_stats, sf::Vector2i posOnGrid, sf::Vector2f posOnMap);

	Enemy(int enemy_id, Enemy_Stats enemy_template, sf::Vector2i positionOnGrid, char newTile, int heroRating);
	~Enemy();

private:



	/////////
	//Stats//
	/////////
	int _enemy_id;
	Enemy_Stats _stats;
	Enemy_Stats _baseStats;

	int _ticksForActions = 0;

	int _aggroRange = 0;

	bool _canTakeAction = false;

	char _tile_underneath;

	bool isAlive = true;
	bool _isAlarmed = false;

	sf::Vector2f _positionOnMap;	//Position in px
	sf::Vector2i _positionOnGrid;	//Position on map

	sf::Texture _enemyTexture;
	sf::RectangleShape _enemyShape;
	sf::Sprite _enemySprite;

	sf::Texture _enemyCorpseTexture;
	sf::RectangleShape _enemyCorpseShape;
	sf::Sprite _enemyCorpseSprite;

	sf::RectangleShape _hpBar;
	sf::RectangleShape _underHpBar;


	int _direction;
	int _direction_1 = -1;
	int _direction_2 = -1;
	bool _isNeedToMoveSprite = false;


	////////////////
	//Magic Number//
	////////////////

	const float __ENEMY_HEIGHT__ = 32.f;
	const float __ENEMY_WIDTH__ = 32.f;

	const std::string __ENEMY_DEFAULT_BEAST__ = "data\\img\\enemy\\defaultbeast.png";
	const std::string __ENEMY_DEFAULT_DEMON__ = "data\\img\\enemy\\defaultdemon.png";
	const std::string __ENEMY_DEFAULT_UNDEAD__ = "data\\img\\enemy\\defaultundead.png";
	const std::string __ENEMY_DEFAULT_GOLEM__ = "data\\img\\enemy\\defaultgolem.png";
	const std::string __ENEMY_DEFAULT_HUMANOID__ = "data\\img\\enemy\\defaulthumanoid.png";
	const std::string __ENEMY_DEFAULT_HUMAN__ = "data\\img\\enemy\\defaulthuman.png";

private:


	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


};


namespace boost{
	namespace serialization{

		template<class Archive>
		void serialize(Archive & ar, sf::Vector2i & v, const unsigned int version)
		{
			ar & v.x;
			ar & v.y;
		}
		template<class Archive>
		void serialize(Archive & ar, sf::Vector2f & v, const unsigned int version)
		{
			ar & v.x;
			ar & v.y;
		}
	}

}


#endif //!ENEMY_ENEMY