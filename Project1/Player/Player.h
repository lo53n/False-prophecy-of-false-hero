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
	sf::Vector2f& getPlayerPosition();		//get player position on map
	sf::Vector2f& getPlayerPositionOnGrid();//get player position in px
private:
	sf::Sprite _playerSprite;
	sf::RenderTexture _playerTexture;
	
	sf::Vector2f _position;			//Position on map
	sf::Vector2f _positionOnGrid;	//Position in px


	/////////////////
	//Magic numbers//
	/////////////////

	const float __PLAYER_HEIGHT__ = 32.f;
	const float __PLAYER_WIDTH__ = 32.f;



private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
#endif //!PLAYER_PLAYER