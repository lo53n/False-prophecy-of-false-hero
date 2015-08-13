#ifndef INTERFACE_INVENTORYWINDOW
#define INTERFACE_INVENTORYWINDOW


#include "SFML\Graphics.hpp"

#include "../LoadFromResource.h"
#include "../UIResource.h"
#include "../Player/Player.h"

class InventoryWindow : public sf::Drawable{

public:

	void highlightNextItem(int direction);

	void putItemsOnTiles();

	void setPlayer(std::shared_ptr<Player> player);

	void resizeByGameWindow(sf::Vector2f center);

	InventoryWindow();
	~InventoryWindow();

	std::shared_ptr<Player> _player;

private:

	sf::RectangleShape _inventoryWindow;
	sf::RectangleShape _characterWindow;
	std::vector<std::vector<sf::RectangleShape>> _inventoryTiles;


	sf::RectangleShape _mainHandTile;
	sf::RectangleShape _offHandTile;
	sf::RectangleShape _helmetTile;
	sf::RectangleShape _torsoTile;
	sf::RectangleShape _legsTile;

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

	float __TILE_SPAN_SIZE_X__ = 15.f;
	float __TILE_SPAN_SIZE_Y__ = 15.f;
private:

	void setInventoryWindowTiles();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};



#endif //!INTERFACE_INVENTORYWINDOW