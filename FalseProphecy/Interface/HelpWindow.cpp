#include "HelpWindow.h"

HelpWindow::HelpWindow()
{
	_font = LoadFontFromResource("Arialfont");

	_texture.create(404, 216);
	_texture.clear();

	_window.setSize(sf::Vector2f(400, 212));
	_window.setOutlineColor(sf::Color(255, 255, 255));
	_window.setOutlineThickness(2.f);
	_window.setFillColor(sf::Color(180, 180, 180));
	_window.setPosition(2.f, 2.f);

	_text.setFont(_font);
	_text.setPosition(6.f, 1.f);
	_text.setCharacterSize(18);
	_text.setColor(sf::Color(40, 40, 40));
	_text.setString("Arrow keys to move hero.\nKeypad to move camera around.\nKeypad_5 to center view on hero.\n[R] to rest and regenerate some health and stmaina.\n[D] to pick up or drop items.\n[C] to open status window.\n[I] to open inventory window.\n[ESC] to open game menu.\n[Return] while in inventory to use or un/equip item.\n[F1] to toggle help window.");

	_texture.draw(_window);
	_texture.draw(_text);
	_texture.display();
	_sprite.setTexture(_texture.getTexture());

}

void HelpWindow::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite);
}

void HelpWindow::resizeByGameWindow(sf::Vector2f center)
{
	sf::Vector2f size = _window.getSize();

	_sprite.setPosition(center.x - size.x / 2, center.y - size.y / 2);
}