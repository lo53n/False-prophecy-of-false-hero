#ifndef ENEMY_ENEMY
#define ENEMY_ENEMY

#include <vector>
#include <iostream>
#include <memory>


#include <SFML\Graphics.hpp>

#include "../StructsEnums.h"



class Enemy : public sf::Drawable {
public:

	///////////
	//Getters//
	///////////

	//Get enemy position on map (px)
	sf::Vector2f& getEnemyPositionOnMap();
	//Get enemy position on map (x,y)
	sf::Vector2i& getEnemyPositionOnGrid();
	//Get tile underneath the enemy on map
	char getTileUnderneathEnemy();
	///////////
	//Setters//
	///////////

	//Set enemy position on map (px)
	void setEnemyPositionOnMap(sf::Vector2f newPositionOnMap);
	//Set enemy position on map (x,y)
	void setEnemyPositionOnGrid(sf::Vector2i newPositionOnGrid);
	//Set tile underneath the enemy on map
	void SetTileUnderneathEnemy(char newTile);


	char swapTileUnderneathToNextOne(char newTile);

	void killEnemy();
	void resurrectEnemy();
	void reinforceEnemy();
	void resurrectAndReinforce();

	bool checkIfAlive();

	Enemy(sf::Vector2i positionOnGrid, char newTile);
	~Enemy();

private:


	/////////
	//Stats//
	/////////
	Enemy_Stats _stats;

	char _tile_underneath;

	bool isAlive = true;

	sf::Vector2f _positionOnMap;	//Position in px
	sf::Vector2i _positionOnGrid;	//Position on map

	sf::Texture _enemyTexture;
	sf::RectangleShape _enemyShape;

	////////////////
	//Magic Number//
	////////////////

	const float __ENEMY_HEIGHT__ = 32.f;
	const float __ENEMY_WIDTH__ = 32.f;

private:


	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


};




#endif //!ENEMY_ENEMY