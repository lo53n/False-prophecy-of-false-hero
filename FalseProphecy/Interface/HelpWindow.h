#ifndef INTERFACE_HELPWINDOW
#define INTERFACE_HELPWINDOW

#include "SFML\Graphics.hpp"

#include "../LoadFromResource.h"



class HelpWindow : public sf::Drawable{

public:

	HelpWindow();


	void resizeByGameWindow(sf::Vector2f center);

private:

	sf::RenderTexture _texture;
	sf::Sprite _sprite;

	sf::RectangleShape _window;
	sf::Font _font;
	sf::Text _text;

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};


#endif //!INTERFACE_WINDOW