#ifndef PLAYER_PLAYER
#define PLAYER_PLAYER

#include <vector>
#include <iostream>

#include <SFML\Graphics.hpp>

class Player : public sf::Drawable{

public:
	Player();
	~Player();

	enum MOVEMENT{
		UP,
		RIGHT,
		DOWN,
		LEFT
	};

	////////////
	//Movement//
	////////////
	void movePlayer(int direction);


	///////////
	//Getters//
	///////////
	sf::Vector2f& getPlayerPositionOnMap();		//get player position on map
	sf::Vector2i& getPlayerPositionOnGrid();//get player position in px

	///////////
	//Setters//
	///////////
	void setPlayerPositionOnMap(sf::Vector2f newPositionOnMap);		//set player position in px
	void setPlayerPositionOnGrid(sf::Vector2i newPositionOnGrid);	//set player position on map
private:
	sf::Sprite _playerSprite;
	sf::RenderTexture _playerTexture;
	
	sf::Vector2f _positionOnMap;	//Position in px
	sf::Vector2i _positionOnGrid;	//Position on map


	/////////////////
	//Magic numbers//
	/////////////////

	const float __PLAYER_HEIGHT__ = 32.0f;
	const float __PLAYER_WIDTH__ = 32.0f;



private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
#endif //!PLAYER_PLAYER