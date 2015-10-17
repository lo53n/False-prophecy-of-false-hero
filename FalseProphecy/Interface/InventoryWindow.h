#ifndef INTERFACE_INVENTORYWINDOW
#define INTERFACE_INVENTORYWINDOW

#include <memory>

#include "SFML\Graphics.hpp"

#include "../LoadFromResource.h"
#include "../UIResource.h"
#include "../Player/Player.h"


class InventoryWindow : public sf::Drawable{

public:

	void handleInput(int key, bool isPressed);
	void highlightNextItem(int direction);


	int getHighlitItem();

	void putItemsOnTiles();

	int selectItem();

	void setPlayer(std::shared_ptr<Player> player);

	void resizeByGameWindow(sf::Vector2f center);

	bool isHighlitInBag();

	InventoryWindow();
	~InventoryWindow();

	std::shared_ptr<Player> _player;


private:

	sf::RenderTexture _renderTexture;
	sf::Sprite _sprite;

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

	int _highlitItem;
	int _highlitSlot;

	sf::Vector2i _highlightBag;
	sf::Vector2i _highlightEquipment;

	bool _isHighlitInBag = true;
	bool _isItemHighlit = false;

	sf::Text _itemStats;
	sf::Font _font;

	/////////////////
	//Magic numbers//
	/////////////////
	//how many colums aka x axis
	int __MAX_TILE_COLUMN_INV__ = 5;
	//how many rows aka y axis
	int __MAX_TILE_ROW_INV__ = 10;
	//how many eq tiles
	int __MAX_EQ_ROW__ = 5;

	float __FIRST_TILE_POSITION_X__ = 206;
	float __FIRST_TILE_POSITION_Y__ = 19;

	float __FIRST_EQ_TILE_POS_X__;
	float __FIRST_EQ_TILE_POS_Y__;

	float __TILE_SPAN_SIZE_X__ = 15.f;
	float __TILE_SPAN_SIZE_Y__ = 15.f;
private:

	void drawOnRenderTexture();
	void setInventoryWindowTiles();
	void changeHighlitSlots();
	void checkIfItemExists();
	void createItemDescription(std::shared_ptr<Item> item_generic);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};



#endif //!INTERFACE_INVENTORYWINDOW