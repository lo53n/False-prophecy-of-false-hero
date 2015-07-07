#ifndef ITEM_ITEM
#define ITEM_ITEM

#include <cstdlib>
#include <iostream>
#include <vector>

#include "SFML/Graphics.hpp"



class Item : public sf::Drawable{


public:

	void setItemTexture();

	void setImagesPosition(sf::Vector2f newPosition);

	Item();
	~Item();


public:

	bool _isItemVisible = false;
	bool _isBackgroundVisible = false;

	sf::Texture _itemTexture;
	sf::Texture _backgroundTexture;

	sf::RectangleShape _itemShape;
	sf::RectangleShape _backgroundShape;

	////////////////////////
	//Public Magic Numbers//
	////////////////////////

	std::string __TILE_IMAGE__ = "data\\img\\etc\\backtile.png";

private:


	int _itemType;




private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};




#endif //!!ITEM_ITEM