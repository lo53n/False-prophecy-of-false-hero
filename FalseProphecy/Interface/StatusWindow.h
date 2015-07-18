#ifndef INTERFACE_STATUSWINDOW
#define INTERFACE_STATUSWINDOW


#include "SFML\Graphics.hpp"

class StatusWindow : public sf::Drawable{

public:



	StatusWindow();
	~StatusWindow();

private:

	sf::RectangleShape _statusWindow;
	sf::RectangleShape _statsPart;
	sf::RectangleShape _abilitiesPart;


private:


	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};




#endif //!INTERFACE_STATUSWINDOW