#include "GameWindowInterface.h"

GameWindowInterface::GameWindowInterface()
{
	_upperInterface.setPosition(0.f, 0.f);
	_upperInterface.setSize(sf::Vector2f(800.f, __UPPER_INTERFACE_HEIGHT__));
	_upperInterface.setFillColor(sf::Color(230, 220, 230, 200));
	_upperInterface.setOutlineThickness(2.f);
	_upperInterface.setOutlineColor(sf::Color(150, 130, 110, 90));

	for (int i = 0; i < 3; i++){
		sf::RectangleShape emptyBar(sf::Vector2f(200.f, 20.f));
		emptyBar.setPosition(30.f, 14.f + i*22.f);
		emptyBar.setFillColor(sf::Color::Black);
		emptyBar.setOutlineColor(sf::Color(0, 0, 0, 190));
		emptyBar.setOutlineThickness(1.f);
		_emptyResourceBar.push_back(emptyBar);
	}

	_hpBar.setPosition(30.f, 14.f);
	_hpBar.setSize(sf::Vector2f(100.f, 20.f));
	_hpBar.setFillColor(sf::Color(240, 20, 20, 255));
	_hpBar.setOutlineThickness(1.f);
	_hpBar.setOutlineColor(sf::Color(240, 20, 20, 50));

	_manaBar.setPosition(30.f, 36.f);
	_manaBar.setSize(sf::Vector2f(100.f, 20.f));
	_manaBar.setFillColor(sf::Color(20, 20, 240, 255));
	_manaBar.setOutlineThickness(1.f);
	_manaBar.setOutlineColor(sf::Color(20, 20, 240, 50));

	_staminaBar.setPosition(30.f, 58.f);
	_staminaBar.setSize(sf::Vector2f(100.f, 20.f));
	_staminaBar.setFillColor(sf::Color(20, 240, 20, 255));
	_staminaBar.setOutlineThickness(1.f);
	_staminaBar.setOutlineColor(sf::Color(20, 240, 20, 50));

	sf::Vector2f upperSize = _upperInterface.getSize();

	_inventoryIconBackground.setPosition(upperSize.x - 120, __ICON_PLACEMENT_Y__);
	_inventoryIconBackground.setSize(sf::Vector2f(32.f, 32.f));
	_inventoryIconBackground.setFillColor(sf::Color(90, 90, 30, 255));
	_inventoryIconBackground.setOutlineThickness(3.f);
	_inventoryIconBackground.setOutlineColor(sf::Color(90, 90, 30, 50));

	_inventoryIconTexture.loadFromImage(LoadImageFromResource("INV_ICON"));

	_inventoryIcon.setPosition(upperSize.x - 120, __ICON_PLACEMENT_Y__);
	_inventoryIcon.setSize(sf::Vector2f(32.f, 32.f));
	_inventoryIcon.setTexture(&_inventoryIconTexture);

	_statusIconBackground.setPosition(upperSize.x - 80, __ICON_PLACEMENT_Y__);
	_statusIconBackground.setSize(sf::Vector2f(32.f, 32.f));
	_statusIconBackground.setFillColor(sf::Color(90, 90, 30, 255));
	_statusIconBackground.setOutlineThickness(3.f);
	_statusIconBackground.setOutlineColor(sf::Color(90, 90, 30, 50));

	_statusIconTexture.loadFromImage(LoadImageFromResource("STAT_ICON"));

	_statusIcon.setPosition(upperSize.x - 80, __ICON_PLACEMENT_Y__);
	_statusIcon.setSize(sf::Vector2f(32.f, 32.f));
	_statusIcon.setTexture(&_statusIconTexture);

	_menuIconBackground.setPosition(upperSize.x - 40, __ICON_PLACEMENT_Y__);
	_menuIconBackground.setSize(sf::Vector2f(32.f, 32.f));
	_menuIconBackground.setFillColor(sf::Color(90, 90, 30, 255));
	_menuIconBackground.setOutlineThickness(3.f);
	_menuIconBackground.setOutlineColor(sf::Color(90, 90, 30, 50));



	_font = LoadFontFromResource("Arialfont");

	_inventoryText.setString("[I]");
	_inventoryText.setCharacterSize(14);
	_inventoryText.setFont(_font);
	_inventoryText.setColor(sf::Color::Black);
	_inventoryText.setPosition(upperSize.x - 110, __TEXT_PLACEMENT_Y__);

	_statusText.setString("[C]");
	_statusText.setCharacterSize(14);
	_statusText.setFont(_font);
	_statusText.setColor(sf::Color::Black);
	_statusText.setPosition(upperSize.x - 73, __TEXT_PLACEMENT_Y__);

	_menuText.setString("[ESC]");
	_menuText.setCharacterSize(14);
	_menuText.setFont(_font);
	_menuText.setColor(sf::Color::Black);
	_menuText.setPosition(upperSize.x - 41, __TEXT_PLACEMENT_Y__);



}


GameWindowInterface::~GameWindowInterface()
{

}


void GameWindowInterface::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_upperInterface);

	for(auto bar : _emptyResourceBar) target.draw(bar);
	target.draw(_hpBar);
	target.draw(_manaBar);
	target.draw(_staminaBar);

	target.draw(_inventoryIconBackground);
	target.draw(_statusIconBackground);
	target.draw(_menuIconBackground);

	target.draw(_inventoryIcon);
	target.draw(_statusIcon);
	//target.draw(_menuIcon);

	target.draw(_inventoryText);
	target.draw(_statusText);
	target.draw(_menuText);
}

void GameWindowInterface::setGameWindowInterfaceSizeByResize(sf::Vector2f newSize)
{
	_upperInterface.setSize(sf::Vector2f(newSize.x, __UPPER_INTERFACE_HEIGHT__));
	_upperInterface.setPosition(sf::Vector2f(0, 0));

	sf::Vector2f upperSize = _upperInterface.getSize();

	_inventoryIconBackground.setPosition(upperSize.x - 120, __ICON_PLACEMENT_Y__);
	_statusIconBackground.setPosition(upperSize.x - 80, __ICON_PLACEMENT_Y__);
	_menuIconBackground.setPosition(upperSize.x - 40, __ICON_PLACEMENT_Y__);

	_inventoryIcon.setPosition(upperSize.x - 120, __ICON_PLACEMENT_Y__);
	_statusIcon.setPosition(upperSize.x - 80, __ICON_PLACEMENT_Y__);
	//_menuIcon.setPosition(upperSize.x - 40, __ICON_PLACEMENT_Y__);

	_inventoryText.setPosition(upperSize.x - 110, __TEXT_PLACEMENT_Y__);
	_statusText.setPosition(upperSize.x - 73, __TEXT_PLACEMENT_Y__);
	_menuText.setPosition(upperSize.x - 41, __TEXT_PLACEMENT_Y__);
}