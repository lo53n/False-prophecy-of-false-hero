#ifndef INTERFACE_INVENTORYWINDOW
#define INTERFACE_INVENTORYWINDOW


#include "SFML\Graphics.hpp"

#include "../LoadFromResource.h"
#include "../UIResource.h"

class InventoryWindow : public sf::Drawable{

public:

	void highlightNextItem(int direction);

	InventoryWindow();
	~InventoryWindow();

private:

	sf::RectangleShape _inventoryWindow;
	sf::RectangleShape _characterWindow;
	std::vector<std::vector<sf::RectangleShape>> _inventoryTiles;

	sf::Texture _backtileTexture;

	///////////////////
	//highlight stuff//
	///////////////////
	sf::RectangleShape _highlight;
	sf::Vector2i _highlightPosition;



	/////////////////
	//Magic numbers//
	/////////////////
	int __MAX_TILE_COLUMN_INV__ = 5;
	int __MAX_TILE_ROW_INV__ = 10;

	float __FIRST_TILE_POSITION_X__ = 330.f;
	float __FIRST_TILE_POSITION_Y__ = 110.f;
private:


	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};



#endif //!INTERFACE_INVENTORYWINDOW