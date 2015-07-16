#include "GameWindowInterface.h"

GameWindowInterface::GameWindowInterface()
{
	_upperInterface.setPosition(0.f, 0.f);
	_upperInterface.setSize(sf::Vector2f(800.f, 90.f));
	_upperInterface.setFillColor(sf::Color(230, 220, 230, 200));
	_upperInterface.setOutlineThickness(2.f);
	_upperInterface.setOutlineColor(sf::Color(150, 130, 110, 90));

	for (int i = 0; i < 3; i++){
		sf::RectangleShape emptyBar(sf::Vector2f(200.f, 20.f));
		emptyBar.setPosition(30.f, 13.f + i*22.f);
		emptyBar.setFillColor(sf::Color::Black);
		emptyBar.setOutlineColor(sf::Color(0, 0, 0, 190));
		emptyBar.setOutlineThickness(1.f);
		_emptyResourceBar.push_back(emptyBar);
	}

	_hpBar.setPosition(30.f, 13.f);
	_hpBar.setSize(sf::Vector2f(100.f, 20.f));
	_hpBar.setFillColor(sf::Color(240, 20, 20, 255));
	_hpBar.setOutlineThickness(1.f);
	_hpBar.setOutlineColor(sf::Color(240, 20, 20, 50));

	_manaBar.setPosition(30.f, 35.f);
	_manaBar.setSize(sf::Vector2f(100.f, 20.f));
	_manaBar.setFillColor(sf::Color(20, 20, 240, 255));
	_manaBar.setOutlineThickness(1.f);
	_manaBar.setOutlineColor(sf::Color(20, 20, 240, 50));

	_staminaBar.setPosition(30.f, 57.f);
	_staminaBar.setSize(sf::Vector2f(100.f, 20.f));
	_staminaBar.setFillColor(sf::Color(20, 240, 20, 255));
	_staminaBar.setOutlineThickness(1.f);
	_staminaBar.setOutlineColor(sf::Color(20, 240, 20, 50));

	_inventoryIcon.setPosition(400.f, 29.f);
	_inventoryIcon.setSize(sf::Vector2f(32.f, 32.f));
	_inventoryIcon.setFillColor(sf::Color(90, 90, 30, 255));
	_inventoryIcon.setOutlineThickness(3.f);
	_inventoryIcon.setOutlineColor(sf::Color(90, 90, 30, 50));

	_statusIcon.setPosition(480.f, 29.f);
	_statusIcon.setSize(sf::Vector2f(32.f, 32.f));
	_statusIcon.setFillColor(sf::Color(90, 90, 30, 255));
	_statusIcon.setOutlineThickness(3.f);
	_statusIcon.setOutlineColor(sf::Color(90, 90, 30, 50));

	_menuIcon.setPosition(560.f, 29.f);
	_menuIcon.setSize(sf::Vector2f(32.f, 32.f));
	_menuIcon.setFillColor(sf::Color(90, 90, 30, 255));
	_menuIcon.setOutlineThickness(3.f);
	_menuIcon.setOutlineColor(sf::Color(90, 90, 30, 50));

	_font = LoadFontFromResource("Arialfont");

	_inventoryText.setString("[I]");
	_inventoryText.setCharacterSize(14);
	_inventoryText.setFont(_font);
	_inventoryText.setColor(sf::Color::Black);
	_inventoryText.setPosition(409.f, 64.f);

	_statusText.setString("[C]");
	_statusText.setCharacterSize(14);
	_statusText.setFont(_font);
	_statusText.setColor(sf::Color::Black);
	_statusText.setPosition(487.f, 64.f);

	_menuText.setString("[ESC]");
	_menuText.setCharacterSize(14);
	_menuText.setFont(_font);
	_menuText.setColor(sf::Color::Black);
	_menuText.setPosition(559.f, 64.f);



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

	target.draw(_inventoryIcon);
	target.draw(_statusIcon);
	target.draw(_menuIcon);

	target.draw(_inventoryText);
	target.draw(_statusText);
	target.draw(_menuText);
}