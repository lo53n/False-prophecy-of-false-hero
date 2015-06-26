#ifndef ITEM_ITEM
#define ITEM_ITEM

#include <cstdlib>
#include <iostream>
#include <vector>

#include "SFML/Graphics.hpp"



class Item : public sf::Drawable{


public:

	void setItemTexture();

	void setName();
	std::string getName();



private:

	std::string name;

	bool _isItemVisible = false;
	bool _isBackgroundVisible = false;

	sf::Texture _itemTexture;
	sf::Texture _backgroundTexture;

	sf::RectangleShape _itemShape;
	sf::RectangleShape _backgroundShape;



private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};




#endif //!!ITEM_ITEM