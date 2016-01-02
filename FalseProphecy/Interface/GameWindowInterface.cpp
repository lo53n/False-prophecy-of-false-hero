#include "GameWindowInterface.h"

GameWindowInterface::GameWindowInterface()
{
	_upperInterface.setPosition(0.f, 0.f);
	_upperInterface.setSize(sf::Vector2f(800.f, __UPPER_INTERFACE_HEIGHT__));
	_upperInterface.setFillColor(sf::Color(230, 220, 230, 200));
	_upperInterface.setOutlineThickness(2.f);
	_upperInterface.setOutlineColor(sf::Color(150, 130, 110, 90));

	sf::Vector2f barLen(200.f, 15.f);

	for (int i = 0; i < 3; i++){
		sf::RectangleShape emptyBar(barLen);
		emptyBar.setPosition(30.f, 14.f + i*21.f);
		emptyBar.setFillColor(sf::Color::Black);
		emptyBar.setOutlineColor(sf::Color(0, 0, 0, 190));
		emptyBar.setOutlineThickness(1.f);
		_emptyResourceBar.push_back(emptyBar);
	}

	_hpBar.setPosition(30.f, 14.f);
	_hpBar.setSize(barLen);
	_hpBar.setFillColor(sf::Color(240, 20, 20, 255));
	_hpBar.setOutlineThickness(1.f);
	_hpBar.setOutlineColor(sf::Color(240, 20, 20, 50));


	_staminaBar.setPosition(30.f, 35.f);
	_staminaBar.setSize(barLen);
	_staminaBar.setFillColor(sf::Color(20, 240, 20, 255));
	_staminaBar.setOutlineThickness(1.f);
	_staminaBar.setOutlineColor(sf::Color(20, 240, 20, 50));


	_expBar.setPosition(30.f, 56.f);
	_expBar.setSize(barLen);
	_expBar.setScale(0, 1);
	_expBar.setFillColor(sf::Color(240, 240, 90, 255));
	_expBar.setOutlineThickness(1.f);
	_expBar.setOutlineColor(sf::Color(20, 20, 240, 50));

	sf::Vector2f upperSize = _upperInterface.getSize();

	_helpIconBackground.setPosition(upperSize.x - 160, __ICON_PLACEMENT_Y__);
	_helpIconBackground.setSize(sf::Vector2f(32.f, 32.f));
	_helpIconBackground.setFillColor(sf::Color(90, 90, 30, 255));
	_helpIconBackground.setOutlineThickness(3.f);
	_helpIconBackground.setOutlineColor(sf::Color(90, 90, 30, 50));

	_helpIconTexture.loadFromImage(LoadImageFromResource("HELP_ICON"));

	_helpIcon.setPosition(upperSize.x - 160, __ICON_PLACEMENT_Y__);
	_helpIcon.setSize(sf::Vector2f(32.f, 32.f));
	_helpIcon.setTexture(&_helpIconTexture);

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

	_menuIconTexture.loadFromImage(LoadImageFromResource("MENU_ICON"));

	_menuIcon.setPosition(upperSize.x - 40, __ICON_PLACEMENT_Y__);
	_menuIcon.setSize(sf::Vector2f(32.f, 32.f));
	_menuIcon.setTexture(&_menuIconTexture);


	_font = LoadFontFromResource("arialfont");

	_helpText.setString("[F1]");
	_helpText.setCharacterSize(14);
	_helpText.setFont(_font);
	_helpText.setStyle(sf::Text::Bold);
	_helpText.setColor(sf::Color::Black);
	_helpText.setPosition(upperSize.x - 110, __TEXT_PLACEMENT_Y__);

	_inventoryText.setString("[I]");
	_inventoryText.setCharacterSize(14);
	_inventoryText.setFont(_font);
	_inventoryText.setStyle(sf::Text::Bold);
	_inventoryText.setColor(sf::Color::Black);
	_inventoryText.setPosition(upperSize.x - 110, __TEXT_PLACEMENT_Y__);

	_statusText.setString("[C]");
	_statusText.setCharacterSize(14);
	_statusText.setFont(_font);
	_statusText.setStyle(sf::Text::Bold);
	_statusText.setColor(sf::Color::Black);
	_statusText.setPosition(upperSize.x - 73, __TEXT_PLACEMENT_Y__);

	_menuText.setString("[ESC]");
	_menuText.setCharacterSize(14);
	_menuText.setFont(_font);
	_menuText.setStyle(sf::Text::Bold);
	_menuText.setColor(sf::Color::Black);
	_menuText.setPosition(upperSize.x - 39, __TEXT_PLACEMENT_Y__);


	_hpBarText.setString("HP");
	_hpBarText.setCharacterSize(14);
	_hpBarText.setFont(_font);
	_hpBarText.setStyle(sf::Text::Bold);
	_hpBarText.setColor(sf::Color(30, 30, 30, 250));
	_hpBarText.setPosition(_hpBar.getPosition() - sf::Vector2f(22, 2));

	_staminaBarText.setString("SP");
	_staminaBarText.setCharacterSize(14);
	_staminaBarText.setFont(_font);
	_staminaBarText.setStyle(sf::Text::Bold);
	_staminaBarText.setColor(sf::Color(30, 30, 30, 250));
	_staminaBarText.setPosition(_staminaBar.getPosition() - sf::Vector2f(22, 2));

	_expBarText.setString("XP");
	_expBarText.setCharacterSize(14);
	_expBarText.setFont(_font);
	_expBarText.setStyle(sf::Text::Bold);
	_expBarText.setColor(sf::Color(30, 30, 30, 250));
	_expBarText.setPosition(_expBar.getPosition() - sf::Vector2f(22, 2));

}


GameWindowInterface::~GameWindowInterface()
{

}

float GameWindowInterface::getInterfaceHeight()
{
	return _upperInterface.getSize().y;
}

void GameWindowInterface::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_upperInterface);

	for (auto bar : _emptyResourceBar) target.draw(bar);
	target.draw(_hpBar);
	target.draw(_hpBarText);
	target.draw(_expBar);
	target.draw(_expBarText);
	target.draw(_staminaBar);
	target.draw(_staminaBarText);

	target.draw(_helpIconBackground);
	target.draw(_inventoryIconBackground);
	target.draw(_statusIconBackground);
	target.draw(_menuIconBackground);

	target.draw(_helpIcon);
	target.draw(_inventoryIcon);
	target.draw(_statusIcon);
	target.draw(_menuIcon);

	target.draw(_helpText);
	target.draw(_inventoryText);
	target.draw(_statusText);
	target.draw(_menuText);

}

void GameWindowInterface::setGameWindowInterfaceSizeByResize(sf::Vector2f newSize)
{
	_upperInterface.setSize(sf::Vector2f(newSize.x, __UPPER_INTERFACE_HEIGHT__));
	_upperInterface.setPosition(sf::Vector2f(0, 0));

	sf::Vector2f upperSize = _upperInterface.getSize();

	_helpIconBackground.setPosition(upperSize.x - 160, __ICON_PLACEMENT_Y__);
	_inventoryIconBackground.setPosition(upperSize.x - 120, __ICON_PLACEMENT_Y__);
	_statusIconBackground.setPosition(upperSize.x - 80, __ICON_PLACEMENT_Y__);
	_menuIconBackground.setPosition(upperSize.x - 40, __ICON_PLACEMENT_Y__);

	_helpIcon.setPosition(upperSize.x - 160, __ICON_PLACEMENT_Y__);
	_inventoryIcon.setPosition(upperSize.x - 120, __ICON_PLACEMENT_Y__);
	_statusIcon.setPosition(upperSize.x - 80, __ICON_PLACEMENT_Y__);
	_menuIcon.setPosition(upperSize.x - 40, __ICON_PLACEMENT_Y__);

	_helpText.setPosition(upperSize.x - 158, __TEXT_PLACEMENT_Y__);
	_inventoryText.setPosition(upperSize.x - 112, __TEXT_PLACEMENT_Y__);
	_statusText.setPosition(upperSize.x - 75, __TEXT_PLACEMENT_Y__);
	_menuText.setPosition(upperSize.x - 45, __TEXT_PLACEMENT_Y__);

}

void GameWindowInterface::refreshBars(Hero_Profile &stats)
{
	float scaleX = 0.0f;
	scaleX = (float)stats.hp / (float)stats.max_hp;
	_hpBar.setScale(scaleX, 1);

	scaleX = (float)stats.exp / (float)stats.max_exp;
	_expBar.setScale(scaleX, 1);

	scaleX = (float)stats.stam / (float)stats.max_stam;
	_staminaBar.setScale(scaleX, 1);


}