#ifndef INTERFACE_GAMEWINDOWINTERFACE
#define INTERFACE_GAMEWINDOWINTERFACE

#include <cstdlib>
#include <iostream>


#include "SFML\Graphics.hpp"

#include "../LoadFromResource.h"
#include "../StructsEnums.h"
#include "../UIResource.h"


class GameWindowInterface : public sf::Drawable{

public:

	float getInterfaceHeight();

	void refreshBars(Hero_Profile &stats);

	void refreshWholeInterface();

	void setGameWindowInterfaceSizeByResize(sf::Vector2f newSize);

	GameWindowInterface();
	~GameWindowInterface();

private:

	sf::RectangleShape _upperInterface;
	sf::RectangleShape _lowerInterface;


	std::vector<sf::RectangleShape> _emptyResourceBar;
	sf::RectangleShape _hpBar;
	sf::RectangleShape _staminaBar;
	sf::RectangleShape _expBar;

	sf::Text _hpBarText;
	sf::Text _staminaBarText;
	sf::Text _expBarText;

	sf::RectangleShape _inventoryIconBackground;
	sf::RectangleShape _statusIconBackground;
	sf::RectangleShape _menuIconBackground;

	sf::Texture _inventoryIconTexture;
	sf::Texture _statusIconTexture;
	sf::Texture _menuIconTexture;

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
	const float __UPPER_INTERFACE_HEIGHT__ = 90.f;
	const float __ICON_PLACEMENT_Y__ = 23.f;
	const float __TEXT_PLACEMENT_Y__ = 58.f;

private:


	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


};





#endif //!INTERFACE_GAMEWINDOWINTERFACE