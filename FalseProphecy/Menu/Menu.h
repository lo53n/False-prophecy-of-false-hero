#ifndef MENU_MENU
#define MENU_MENU

#include <memory>
#include <vector>
#include <SFML\Graphics.hpp>

#include "../LoadFromResource.h"
class Menu : public sf::Drawable{

public:


	int getHighlit();

	void refresh();
	void resizeByGameWindow(sf::Vector2f center);
	void highlightNext(int key);

	void handleInput(int key, bool isPressed);

	Menu();

private:


	sf::RenderTexture _renderTexture;
	sf::Sprite _sprite;

	sf::RectangleShape _highlight;
	std::vector<sf::RectangleShape> _buttons;
	std::vector< sf::Text> _buttonTexts;
	std::vector<sf::Text> _title;
	sf::Font _font;

	int _highlitItem = 0;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};





#endif //!MENU_MENU