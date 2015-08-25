#include "InventoryWindow.h"
InventoryWindow::InventoryWindow()
{

	asd = "lol";

	_inventoryWindow.setSize(sf::Vector2f(500.f, 378.f));
	_inventoryWindow.setPosition(100.f, 100.f);
	_inventoryWindow.setFillColor(sf::Color(90, 90, 90, 220));
	_inventoryWindow.setOutlineThickness(2.f);
	_inventoryWindow.setOutlineColor(sf::Color(120, 120, 120, 220));

	_characterWindow.setSize(sf::Vector2f( 177.f, _inventoryWindow.getSize().y - 30.f));
	_characterWindow.setPosition(110.f, 110.f);
	_characterWindow.setFillColor(sf::Color(60, 90, 0, 200));
	_characterWindow.setOutlineThickness(2.f);
	_characterWindow.setOutlineColor(sf::Color(90, 120, 0, 220));

	_backtileTexture.loadFromImage(LoadImageFromResource("ITEM_TILE"));

	_mainHandTile.setSize(sf::Vector2f(33.f, 33.f));
	_offHandTile.setSize(sf::Vector2f(33.f, 33.f));
	_torsoTile.setSize(sf::Vector2f(33.f, 33.f));
	_helmetTile.setSize(sf::Vector2f(33.f, 33.f));
	_legsTile.setSize(sf::Vector2f(33.f, 33.f));
	
	setInventoryWindowTiles();

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
		for (auto tile : tileRow)
			target.draw(tile);
	for (auto item : _player->getPlayerBackpack()) target.draw(*item);
	target.draw(_highlight);

	target.draw(_mainHandTile);
	if (_player->getPlayerWeapon() != nullptr)
		target.draw(*(_player->getPlayerWeapon()));

	target.draw(_offHandTile);
	if (_player->getPlayerArmour(ARMOUR_TYPE::SHIELD) != nullptr)
		target.draw(*(_player->getPlayerArmour(ARMOUR_TYPE::SHIELD)));

	target.draw(_helmetTile);
	if (_player->getPlayerArmour(ARMOUR_TYPE::HELMET) != nullptr)
		target.draw(*(_player->getPlayerArmour(ARMOUR_TYPE::HELMET)));

	target.draw(_torsoTile);
	if (_player->getPlayerArmour(ARMOUR_TYPE::TORSO) != nullptr)
		target.draw(*(_player->getPlayerArmour(ARMOUR_TYPE::TORSO)));

	target.draw(_legsTile);
	if (_player->getPlayerArmour(ARMOUR_TYPE::SHIELD) != nullptr)
		target.draw(*(_player->getPlayerArmour(ARMOUR_TYPE::GREAVES)));
}

void InventoryWindow::setPlayer(std::shared_ptr<Player> player)
{
	_player = player;
}

int InventoryWindow::getHighlitItem()
{
	return  (_highlightPosition.x + (_highlightPosition.y * __MAX_TILE_COLUMN_INV__));
}

void InventoryWindow::setInventoryWindowTiles()
{
	sf::Vector2f position = _characterWindow.getPosition();
	position.x += 2;
	position.y += 2;

	_mainHandTile.setPosition(position.x, position.y);
	_mainHandTile.setTexture(&_backtileTexture);

	_offHandTile.setPosition(position.x + 35, position.y);
	_offHandTile.setTexture(&_backtileTexture);

	_helmetTile.setPosition(position.x + 70, position.y);
	_helmetTile.setTexture(&_backtileTexture);

	_torsoTile.setPosition(position.x +105, position.y);
	_torsoTile.setTexture(&_backtileTexture);

	_legsTile.setPosition(position.x + 140, position.y);
	_legsTile.setTexture(&_backtileTexture);

	_inventoryTiles.clear();
	for (int i = 0; i < __MAX_TILE_ROW_INV__; i++){
		std::vector<sf::RectangleShape> tileRow;
		for (int j = 0; j < __MAX_TILE_COLUMN_INV__; j++){
			sf::RectangleShape tile;

			tile.setSize(sf::Vector2f(33.f, 33.f));
			tile.setPosition(__FIRST_TILE_POSITION_X__ + 35.f * j, __FIRST_TILE_POSITION_Y__ + 35.f * i);
			tile.setTexture(&_backtileTexture);

			tileRow.push_back(tile);
		}
		_inventoryTiles.push_back(tileRow);
	}
}


void InventoryWindow::putItemsOnTiles()
{
	sf::Vector2f newPosition;
	int itemNumber = _player->getPlayerBackpack().size();

	for (int currentItem = 0, columns = 0, rows = 0; currentItem < itemNumber; currentItem++){
		newPosition = sf::Vector2f(__FIRST_TILE_POSITION_X__ + 35.f * columns, __FIRST_TILE_POSITION_Y__ + 35.f * rows);
		_player->getPlayerBackpack()[currentItem]->setImagesPosition(newPosition);
		columns++;
		if (columns == __MAX_TILE_COLUMN_INV__){
			rows++;
			columns = 0;
		}
	}

	if(_player->getPlayerWeapon() != nullptr) 
		_player->getPlayerWeapon()->setImagesPosition(_mainHandTile.getPosition());

	if (_player->getPlayerArmour(ARMOUR_TYPE::SHIELD) != nullptr)
		_player->getPlayerArmour(ARMOUR_TYPE::SHIELD)->setImagesPosition(_offHandTile.getPosition());

	if (_player->getPlayerArmour(ARMOUR_TYPE::HELMET) != nullptr)
		_player->getPlayerArmour(ARMOUR_TYPE::HELMET)->setImagesPosition(_helmetTile.getPosition());

	if (_player->getPlayerArmour(ARMOUR_TYPE::TORSO) != nullptr)
		_player->getPlayerArmour(ARMOUR_TYPE::TORSO)->setImagesPosition(_torsoTile.getPosition());

	if (_player->getPlayerArmour(ARMOUR_TYPE::SHIELD) != nullptr)
		_player->getPlayerArmour(ARMOUR_TYPE::SHIELD)->setImagesPosition(_legsTile.getPosition());


}

void InventoryWindow::handleInput(int key, bool isPressed)
{
	if (key >= sf::Keyboard::Left && key <= sf::Keyboard::Down && isPressed){
		highlightNextItem(key);
	}
	if (key == sf::Keyboard::Return && isPressed){
		int item = selectItem();
		//_player->getPlayerBackpack()[item]->getItemStats();
		try{
			if (_player->getPlayerBackpack().at(item) != nullptr){
				if (_player->getPlayerBackpack()[item]->getItemType() == ITEM_TYPE::ARMOUR){
					std::shared_ptr<Armour> item1 = (std::dynamic_pointer_cast <Armour>(_player->getPlayerBackpack()[item]));
					_player->equipItem(item1);
				}
				if (_player->getPlayerBackpack()[item]->getItemType() == ITEM_TYPE::WEAPON){
					std::shared_ptr<Weapon> item1 = (std::dynamic_pointer_cast <Weapon>(_player->getPlayerBackpack()[item]));
					_player->equipItem(item1);
				}
				else{
					_player->getPlayerBackpack()[item]->getItemStats();
				}
			}
			else{
				std::cout << "blam." << std::endl;
			}
		}
		catch (std::exception e){
		}
		putItemsOnTiles();
	}
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
	_highlitItem = _highlightPosition.x + (_highlightPosition.y * __MAX_TILE_COLUMN_INV__);
	std::cout << "Item No.: " << _highlitItem << std::endl;

}

void InventoryWindow::resizeByGameWindow(sf::Vector2f center)
{
	sf::Vector2f size = _inventoryWindow.getSize();
	_inventoryWindow.setPosition(center.x - size.x / 2, center.y - size.y / 2);
	_characterWindow.setPosition(_inventoryWindow.getPosition().x + 15, _inventoryWindow.getPosition().y + 15);

	__FIRST_TILE_POSITION_X__ = _characterWindow.getPosition().x + _characterWindow.getSize().x + __TILE_SPAN_SIZE_X__;
	__FIRST_TILE_POSITION_Y__ = _characterWindow.getPosition().y;

	_highlight.setPosition(__FIRST_TILE_POSITION_X__ + 35.f * _highlightPosition.x, __FIRST_TILE_POSITION_Y__ + 35.f * _highlightPosition.y);



	setInventoryWindowTiles();
	putItemsOnTiles();

}

int InventoryWindow::selectItem()
{
	return _highlitItem;
}