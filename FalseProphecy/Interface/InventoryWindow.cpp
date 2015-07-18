#include "InventoryWindow.h"
InventoryWindow::InventoryWindow()
{
	_inventoryWindow.setSize(sf::Vector2f(500.f, 400.f));
	_inventoryWindow.setPosition(100.f, 100.f);
	_inventoryWindow.setFillColor(sf::Color(90, 90, 90, 220));
	_inventoryWindow.setOutlineThickness(2.f);
	_inventoryWindow.setOutlineColor(sf::Color(120, 120, 120, 220));

	_characterWindow.setSize(sf::Vector2f(200.f, 300.f));
	_characterWindow.setPosition(110.f, 110.f);
	_characterWindow.setFillColor(sf::Color(60, 90, 0, 200));
	_characterWindow.setOutlineThickness(2.f);
	_characterWindow.setOutlineColor(sf::Color(90, 120, 0, 220));

	_backtileTexture.loadFromImage(LoadImageFromResource("ITEM_TILE"));

	for (int i = 0; i < __MAX_TILE_ROW_INV__; i++){
		std::vector<sf::RectangleShape> tileRow;
		for (int j = 0; j < __MAX_TILE_COLUMN_INV__; j++){
			sf::RectangleShape tile;

			tile.setSize(sf::Vector2f(32.f, 32.f));
			tile.setPosition(__FIRST_TILE_POSITION_X__ + 35.f * j, __FIRST_TILE_POSITION_Y__ + 35.f * i);
			tile.setTexture(&_backtileTexture);




			tileRow.push_back(tile);
		}
		_inventoryTiles.push_back(tileRow);
		}

	_highlightPosition = sf::Vector2i(0, 0);

	_highlight.setSize(sf::Vector2f(32.f, 32.f));
	_highlight.setPosition(__FIRST_TILE_POSITION_X__ + 35.f * _highlightPosition.x, __FIRST_TILE_POSITION_Y__ + 35.f * _highlightPosition.y);
	_highlight.setFillColor(sf::Color::Transparent);
	_highlight.setOutlineThickness(2.f);
	_highlight.setOutlineColor(sf::Color(0, 180, 255, 220));
}

InventoryWindow::~InventoryWindow()
{

}

void InventoryWindow::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_inventoryWindow);
	target.draw(_characterWindow);

	for (auto tileRow : _inventoryTiles) 
		for(auto tile : tileRow) 
			target.draw(tile);

	target.draw(_highlight);
}

void InventoryWindow::highlightNextItem(int direction){
	switch (direction){
	case sf::Keyboard::Up:
		_highlightPosition.y = (_highlightPosition.y - 1) % __MAX_TILE_ROW_INV__;
		if (_highlightPosition.y < 0) _highlightPosition.y = __MAX_TILE_ROW_INV__ - 1;
		break;
	case sf::Keyboard::Down:
		_highlightPosition.y = (_highlightPosition.y + 1) % __MAX_TILE_ROW_INV__;
		break;
	case sf::Keyboard::Left:
		_highlightPosition.x = (_highlightPosition.x - 1) % __MAX_TILE_COLUMN_INV__;
		if (_highlightPosition.x < 0) _highlightPosition.x = __MAX_TILE_COLUMN_INV__ - 1;
		break;
	case sf::Keyboard::Right:
		_highlightPosition.x = (_highlightPosition.x + 1) % __MAX_TILE_COLUMN_INV__;
		break;

	}
	_highlight.setPosition(__FIRST_TILE_POSITION_X__ + 35.f * _highlightPosition.x, __FIRST_TILE_POSITION_Y__ + 35.f * _highlightPosition.y);
}