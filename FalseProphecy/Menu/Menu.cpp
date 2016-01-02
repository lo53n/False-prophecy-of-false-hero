#include "Menu.h"


Menu::Menu()
{
	sf::Vector2f textSize(600, 480);
	_renderTexture.create(textSize.x, textSize.y);
	_renderTexture.setSmooth(true);

	_font = LoadFontFromResource("Arialfont");

	sf::RectangleShape button1, button2, button3;
	sf::Vector2f size(240, 60);
	sf::Vector2f pos(textSize.x/2 - size.x/2, 200);

	_highlight.setSize(size);
	_highlight.setPosition(pos);
	_highlight.setFillColor(sf::Color::Transparent);
	_highlight.setOutlineThickness(4.f);
	_highlight.setOutlineColor(sf::Color(0, 180, 255));


	int number = 0;
	pos.y = 200 + 80 * number;
	button1.setPosition(pos);
	button1.setSize(size);
	button1.setFillColor(sf::Color(180, 180, 180));
	button1.setOutlineColor(sf::Color(100, 100, 100, 210));
	button1.setOutlineThickness(4.f);
	_buttons.push_back(button1);
	number++;

	pos.y = 200 + 80 * number;
	button2.setPosition(pos);
	button2.setSize(size);
	button2.setFillColor(sf::Color(180, 180, 180));
	button2.setOutlineColor(sf::Color(100, 100, 100, 210));
	button2.setOutlineThickness(4.f);
	_buttons.push_back(button2);
	number++;

	pos.y = 200 + 80 * number;
	button3.setPosition(pos);
	button3.setSize(size);
	button3.setFillColor(sf::Color(180, 180, 180));
	button3.setOutlineColor(sf::Color(100, 100, 100, 210));
	button3.setOutlineThickness(4.f);
	_buttons.push_back(button3);
	number++;

	sf::Text text1, text2, text3;

	text1.setFont(_font);
	text1.setCharacterSize(30);
	text1.setStyle(sf::Text::Bold);
	text1.setColor(sf::Color(55, 55, 50, 240));
	text1.setString("Continue game");
	_buttonTexts.push_back(text1);

	text2.setFont(_font);
	text2.setCharacterSize(30);
	text2.setStyle(sf::Text::Bold);
	text2.setColor(sf::Color(55, 55, 50, 240));
	text2.setString("New game");
	_buttonTexts.push_back(text2);

	text3.setFont(_font);
	text3.setCharacterSize(30);
	text3.setStyle(sf::Text::Bold);
	text3.setColor(sf::Color(55, 55, 50, 240));
	text3.setString("Exit");
	_buttonTexts.push_back(text3);

	for (int i = 0, len = _buttons.size(); i < len; i++){
		sf::FloatRect rect = _buttons[i].getGlobalBounds();
		sf::Vector2f pos;
		pos.x = rect.left + rect.width / 2 - _buttonTexts[i].getGlobalBounds().width / 2;
		pos.y = rect.top + rect.height / 2 - _buttonTexts[i].getGlobalBounds().height/1.5 - i *2;
		_buttonTexts[i].setPosition(pos);
	}

	sf::Text title1, title2, title3;

	title1.setFont(_font);
	title1.setCharacterSize(120);
	title1.setStyle(sf::Text::Bold | sf::Text::Italic);
	title1.setColor(sf::Color(180, 180, 160, 180));
	title1.setString("Prophecy");
	title1.setPosition(textSize.x / 2 - title1.getGlobalBounds().width / 2, 20);

	title2.setFont(_font);
	title2.setCharacterSize(120);
	title2.setStyle(sf::Text::Bold | sf::Text::Italic);
	title2.setColor(sf::Color(110, 110, 90, 180));
	title2.setString("Prophecy");
	title2.setPosition(textSize.x / 2 - title2.getGlobalBounds().width / 2 - 2, 20 - 2);

	title3.setFont(_font);
	title3.setCharacterSize(16);
	title3.setStyle(sf::Text::Italic);
	title3.setColor(sf::Color(200, 200, 200, 255));
	title3.setString(L"by Micha³ Sochacki");
	title3.setPosition(title2.getPosition().x + title2.getGlobalBounds().width - title3.getGlobalBounds().width/1.5,
					   title2.getPosition().y + title2.getGlobalBounds().height + 35);

	_title.push_back(title1);
	_title.push_back(title2);
	_title.push_back(title3);


	refresh();
}


int Menu::getHighlit()
{
	return _highlitItem;
}


void Menu::refresh()
{
	_renderTexture.clear();

	for (auto button : _buttons){
		_renderTexture.draw(button);
	}
	for (auto text : _buttonTexts){
		_renderTexture.draw(text);
	}
	for (auto title : _title){
		_renderTexture.draw(title);
	}

	_renderTexture.draw(_highlight);
	_renderTexture.display();
	_sprite.setTexture(_renderTexture.getTexture());
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite);
}

void Menu::handleInput(int key, bool isPressed)
{
	if ((key == sf::Keyboard::Up || key == sf::Keyboard::Down)&& isPressed){
		highlightNext(key);
	}
}


void Menu::resizeByGameWindow(sf::Vector2f center)
{
	sf::Vector2f size = sf::Vector2f(_sprite.getGlobalBounds().width, _sprite.getGlobalBounds().height);

	_sprite.setPosition(center.x - size.x / 2, center.y - size.y / 2);
}

void Menu::highlightNext(int key)
{
	switch (key){
	case sf::Keyboard::Up:
		if (_highlitItem == 0){
			return;
		}
		else{
			_highlitItem--;
			_highlight.setPosition(_buttons[_highlitItem].getPosition());
		}
		break;

	case sf::Keyboard::Down:
		if (_highlitItem == _buttons.size()-1){
			return;
		}
		else{
			_highlitItem++;
			_highlight.setPosition(_buttons[_highlitItem].getPosition());
		}

		break;
	}
	refresh();
}