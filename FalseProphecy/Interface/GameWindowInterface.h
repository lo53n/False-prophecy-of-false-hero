#ifndef INTERFACE_GAMEWINDOWINTERFACE
#define INTERFACE_GAMEWINDOWINTERFACE

#include <cstdlib>
#include <iostream>


#include "SFML\Graphics.hpp"

#include "../LoadFromResource.h"
#include "../UIResource.h"


class GameWindowInterface : public sf::Drawable{

public:




	GameWindowInterface();
	~GameWindowInterface();

private:

	sf::RectangleShape _upperInterface;
	sf::RectangleShape _lowerInterface;


	std::vector<sf::RectangleShape> _emptyResourceBar;
	sf::RectangleShape _hpBar;
	sf::RectangleShape _manaBar;
	sf::RectangleShape _staminaBar;


	sf::RectangleShape _inventoryIcon;
	sf::RectangleShape _statusIcon;
	sf::RectangleShape _menuIcon;
	sf::Text _inventoryText;
	sf::Text _statusText;
	sf::Text _menuText;

	sf::Font _font;
	/////////////////
	//Magic numbers//
	/////////////////

	const std::string __FONT_NAME__ = "ARIALFONT";

private:


	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


};





#endif //!INTERFACE_GAMEWINDOWINTERFACE