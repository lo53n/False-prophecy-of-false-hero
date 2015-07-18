#include "StatusWindow.h"
StatusWindow::StatusWindow()
{
	_statusWindow.setSize(sf::Vector2f(500.f, 400.f));
	_statusWindow.setPosition(100.f, 100.f);
	_statusWindow.setFillColor(sf::Color(150, 150, 150, 200));
	_statusWindow.setOutlineThickness(2.f);
	_statusWindow.setOutlineColor(sf::Color(190, 190, 190, 200));

	_statsPart.setSize(sf::Vector2f(200.f, 300.f));
	_statsPart.setPosition(120.f, 150.f);
	_statsPart.setFillColor(sf::Color(30, 150, 50, 200));
	_statsPart.setOutlineThickness(2.f);
	_statsPart.setOutlineColor(sf::Color(60, 180, 80, 200));

	_abilitiesPart.setSize(sf::Vector2f(250.f, 300.f));
	_abilitiesPart.setPosition(330.f, 150.f);
	_abilitiesPart.setFillColor(sf::Color(150, 50, 90, 200));
	_abilitiesPart.setOutlineThickness(2.f);
	_abilitiesPart.setOutlineColor(sf::Color(180, 80, 120, 200));
}

StatusWindow::~StatusWindow()
{

}

void StatusWindow::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_statusWindow);
	target.draw(_statsPart);
	target.draw(_abilitiesPart);
}