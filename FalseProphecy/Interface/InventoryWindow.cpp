#include "InventoryWindow.h"
InventoryWindow::InventoryWindow()
{

	_renderTexture.create(394, 382);
	_sprite.setColor(sf::Color(255, 255, 255, 240));

	//Change size also in resize function in Game.cpp
	_inventoryWindow.setSize(sf::Vector2f(390.f, 378.f));
	_inventoryWindow.setPosition(2.f, 2.f);
	_inventoryWindow.setFillColor(sf::Color(90, 90, 90));
	_inventoryWindow.setOutlineThickness(2.f);
	_inventoryWindow.setOutlineColor(sf::Color(120, 120, 120));

	_characterWindow.setSize(sf::Vector2f( 177.f, _inventoryWindow.getSize().y - 30.f));
	_characterWindow.setPosition(18.f, 18.f);
	_characterWindow.setFillColor(sf::Color(60, 90, 0));
	_characterWindow.setOutlineThickness(2.f);
	_characterWindow.setOutlineColor(sf::Color(90, 120, 0));

	_backtileTexture.loadFromImage(LoadImageFromResource("ITEM_TILE"));

	_mainHandTile.setSize(sf::Vector2f(33.f, 33.f));
	_offHandTile.setSize(sf::Vector2f(33.f, 33.f));
	_torsoTile.setSize(sf::Vector2f(33.f, 33.f));
	_helmetTile.setSize(sf::Vector2f(33.f, 33.f));
	_legsTile.setSize(sf::Vector2f(33.f, 33.f));
	
	setInventoryWindowTiles();

	_highlightBag = sf::Vector2i(0,0);
	_highlightEquipment = sf::Vector2i(0,0);


	_highlightPosition = sf::Vector2i(0, 0);

	_highlight.setSize(sf::Vector2f(32.f, 32.f));
	_highlight.setPosition(__FIRST_TILE_POSITION_X__ + 35.f * _highlightPosition.x, __FIRST_TILE_POSITION_Y__ + 35.f * _highlightPosition.y);
	_highlight.setFillColor(sf::Color::Transparent);
	_highlight.setOutlineThickness(2.f);
	_highlight.setOutlineColor(sf::Color(0, 180, 255));

	//position set in setInventoryWindowTiles()
	_font = LoadFontFromResource("Arialfont");
	_itemStats.setFont(_font);
	_itemStats.setCharacterSize(13);

	_itemStats.setString("asdasd");

}

InventoryWindow::~InventoryWindow()
{

}

void InventoryWindow::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite);
}

void InventoryWindow::drawOnRenderTexture()
{
	_renderTexture.clear();

	_renderTexture.draw(_inventoryWindow);
	_renderTexture.draw(_characterWindow);

	for (auto tileRow : _inventoryTiles)
	for (auto tile : tileRow)
	_renderTexture.draw(tile);
	for (auto item : _player->getPlayerBackpack()) {
		_renderTexture.draw(*item);
		if (item == nullptr) break;
	}
	_renderTexture.draw(_highlight);

	_renderTexture.draw(_mainHandTile);
	if (_player->getPlayerWeapon() != nullptr)
		_renderTexture.draw(*(_player->getPlayerWeapon()));

	_renderTexture.draw(_offHandTile);
	if (_player->getPlayerArmour(ARMOUR_TYPE::SHIELD) != nullptr)
		_renderTexture.draw(*(_player->getPlayerArmour(ARMOUR_TYPE::SHIELD)));

	_renderTexture.draw(_helmetTile);
	if (_player->getPlayerArmour(ARMOUR_TYPE::HELMET) != nullptr)
		_renderTexture.draw(*(_player->getPlayerArmour(ARMOUR_TYPE::HELMET)));

	_renderTexture.draw(_torsoTile);
	if (_player->getPlayerArmour(ARMOUR_TYPE::TORSO) != nullptr)
		_renderTexture.draw(*(_player->getPlayerArmour(ARMOUR_TYPE::TORSO)));

	_renderTexture.draw(_legsTile);
	if (_player->getPlayerArmour(ARMOUR_TYPE::GREAVES) != nullptr)
		_renderTexture.draw(*(_player->getPlayerArmour(ARMOUR_TYPE::GREAVES)));

	if (_isItemHighlit) _renderTexture.draw(_itemStats);

	_renderTexture.display();
	_sprite.setTexture(_renderTexture.getTexture());

}

void InventoryWindow::setPlayer(std::shared_ptr<Player> player)
{
	_player = player;
}

int InventoryWindow::getHighlitItem()
{
	return selectItem();
}


bool InventoryWindow::isHighlitInBag()
{
	return _isHighlitInBag;
}


void InventoryWindow::setInventoryWindowTiles()
{
	sf::Vector2f position = _characterWindow.getPosition();
	position.x += 2;
	position.y += 2;

	_mainHandTile.setPosition(position.x, position.y);
	_mainHandTile.setTexture(&_backtileTexture);

	__FIRST_EQ_TILE_POS_X__ = _mainHandTile.getPosition().x;
	__FIRST_EQ_TILE_POS_Y__ = _mainHandTile.getPosition().y;

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

			tile.setSize(sf::Vector2f(31.f, 31.f));
			tile.setPosition((int)__FIRST_TILE_POSITION_X__ + 35.f * j, (int)__FIRST_TILE_POSITION_Y__ + 35.f * i);
			tile.setTexture(&_backtileTexture);

			tileRow.push_back(tile);
		}
		_inventoryTiles.push_back(tileRow);
	}

	_itemStats.setPosition((int)__FIRST_EQ_TILE_POS_X__, (int)__FIRST_EQ_TILE_POS_Y__ + 40);
	//drawOnRenderTexture();
}


void InventoryWindow::putItemsOnTiles()
{
	sf::Vector2f newPosition;
	int itemNumber = _player->getPlayerBackpack().size();

	for (int currentItem = 0, columns = 0, rows = 0; currentItem < itemNumber; currentItem++){
		newPosition = sf::Vector2f((int)__FIRST_TILE_POSITION_X__ + 35.f * columns, (int)__FIRST_TILE_POSITION_Y__ + 35.f * rows);
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

	if (_player->getPlayerArmour(ARMOUR_TYPE::GREAVES) != nullptr)
		_player->getPlayerArmour(ARMOUR_TYPE::GREAVES)->setImagesPosition(_legsTile.getPosition());

	checkIfItemExists();

}

void InventoryWindow::handleInput(int key, bool isPressed, bool& isItemsManipulated)
{
	if (key >= sf::Keyboard::Left && key <= sf::Keyboard::Down && isPressed){
		highlightNextItem(key);
	}


	if (key == sf::Keyboard::Tab && isPressed){

		changeHighlitSlots();

	}

	if (key == sf::Keyboard::Return && isPressed){
		int item = selectItem();
		//_player->getPlayerBackpack()[item]->getItemStats();
		try{
			if (_isHighlitInBag){
				if (_player->getPlayerBackpack().at(item) != nullptr){
					if (_player->getPlayerBackpack()[item]->getItemType() == ITEM_TYPE::ARMOUR){
						std::shared_ptr<Armour> item1 = (std::dynamic_pointer_cast <Armour>(_player->getPlayerBackpack()[item]));
						if (_player->checkRequirements(item1))
							_player->equipItem(item1);
					}
					else if (_player->getPlayerBackpack()[item]->getItemType() == ITEM_TYPE::WEAPON){
						std::shared_ptr<Weapon> item1 = (std::dynamic_pointer_cast <Weapon>(_player->getPlayerBackpack()[item]));
						if (_player->checkRequirements(item1))
							_player->equipItem(item1);
					}
					else if (_player->getPlayerBackpack()[item]->getItemType() == ITEM_TYPE::CONSUMABLE){
						std::shared_ptr<Consumable> item1 = (std::dynamic_pointer_cast <Consumable>(_player->getPlayerBackpack()[item]));
						_player->useItem(item1);
					}
					else{
						_player->getPlayerBackpack()[item]->getItemStats();
					}
				}
				else{
				}
			}

			else{
				_player->unequipItem(item);
			}


		}
		catch (std::exception e){
		}
		isItemsManipulated = true;
		putItemsOnTiles();
	}
	checkIfItemExists();
	drawOnRenderTexture();
}



void InventoryWindow::highlightNextItem(int direction){

	if (_isHighlitInBag){
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

			//case default:

		}

		_highlight.setPosition((int)__FIRST_TILE_POSITION_X__ + 35.f * _highlightPosition.x, (int)__FIRST_TILE_POSITION_Y__ + 35.f * _highlightPosition.y);
		_highlitItem = _highlightPosition.x + (_highlightPosition.y * __MAX_TILE_COLUMN_INV__);
		//std::cout << "Item No.: " << _highlitItem << std::endl;
	}
	else{

		switch (direction){
		case sf::Keyboard::Left:
			_highlightPosition.x = (_highlightPosition.x - 1) % __MAX_EQ_ROW__;
			if (_highlightPosition.x < 0) _highlightPosition.x = __MAX_EQ_ROW__ - 1;
			break;
		case sf::Keyboard::Right:
			_highlightPosition.x = (_highlightPosition.x + 1) % __MAX_EQ_ROW__;
			break;

			//case default:

		}

		_highlight.setPosition((int)__FIRST_EQ_TILE_POS_X__ + 35.f * _highlightPosition.x, (int)__FIRST_EQ_TILE_POS_Y__ + 35.f * _highlightPosition.y);
		_highlitItem = _highlightPosition.x;
		//std::cout << "Item No.: " << _highlitItem << std::endl;

	}
}

void InventoryWindow::resizeByGameWindow(sf::Vector2f center)
{
	sf::Vector2f size = _inventoryWindow.getSize();
	/*_inventoryWindow.setPosition(center.x - size.x / 2, center.y - size.y / 2);
	_characterWindow.setPosition(_inventoryWindow.getPosition().x + 15, _inventoryWindow.getPosition().y + 15);

	__FIRST_TILE_POSITION_X__ = _characterWindow.getPosition().x + _characterWindow.getSize().x + __TILE_SPAN_SIZE_X__;
	__FIRST_TILE_POSITION_Y__ = _characterWindow.getPosition().y;

	_highlight.setPosition((int)__FIRST_TILE_POSITION_X__ + 35.f * _highlightPosition.x, (int)__FIRST_TILE_POSITION_Y__ + 35.f * _highlightPosition.y);



	setInventoryWindowTiles();
	putItemsOnTiles();*/

	_sprite.setPosition(center.x - size.x / 2, center.y - size.y / 2);
}

int InventoryWindow::selectItem()
{
	return _highlitItem;
}

void InventoryWindow::changeHighlitSlots()
{
	if (_isHighlitInBag){
		//is in equipment
		_isHighlitInBag = false;
		std::cout << _isHighlitInBag << std::endl;
		_highlightBag = _highlightPosition;
		_highlightPosition = _highlightEquipment;
		_highlight.setPosition(__FIRST_EQ_TILE_POS_X__ + 35.f * _highlightPosition.x, __FIRST_EQ_TILE_POS_Y__ + 35.f * _highlightPosition.y);
		_highlight.setSize(sf::Vector2f(33.f, 33.f));
		_highlitItem = _highlightPosition.x;

	}
	else {
		//is in bag
		_isHighlitInBag = true;
		std::cout << _isHighlitInBag << std::endl;
		_highlightEquipment = _highlightPosition;
		_highlightPosition = _highlightBag;
		_highlight.setPosition(__FIRST_TILE_POSITION_X__ + 35.f * _highlightPosition.x, __FIRST_TILE_POSITION_Y__ + 35.f * _highlightPosition.y);
		_highlight.setSize(sf::Vector2f(32.f, 32.f));
		_highlitItem = _highlightPosition.x + (_highlightPosition.y * __MAX_TILE_COLUMN_INV__);
	}
}

void InventoryWindow::checkIfItemExists()
{
	_isItemHighlit = false;
	std::shared_ptr<Item> item;
	try{
		//check in bag//
		if (_isHighlitInBag){
			item = _player->getPlayerBackpack().at(_highlitItem);
			if (item != nullptr){
				_isItemHighlit = true;

			}
			else _isItemHighlit = false;
		}
		//now check the eq//
		else{
			switch (_highlitItem){
			case 0:
				item = _player->getPlayerWeapon();
				if (item != nullptr){
					_isItemHighlit = true;
				}
				else _isItemHighlit = false;
				break;
			case 1:
				item = _player->getPlayerArmour(ARMOUR_TYPE::SHIELD);
				if (item != nullptr){
					_isItemHighlit = true;
				}
				else _isItemHighlit = false;
				break;
			case 2:
				item = _player->getPlayerArmour(ARMOUR_TYPE::HELMET);
				if (item != nullptr){
					_isItemHighlit = true;
				}
				else _isItemHighlit = false;
				break;
			case 3:
				item = _player->getPlayerArmour(ARMOUR_TYPE::TORSO);
				if (item != nullptr){
					_isItemHighlit = true;
				}
				else _isItemHighlit = false;
				break;
			case 4:
				item = _player->getPlayerArmour(ARMOUR_TYPE::GREAVES);
				if (item != nullptr){
					_isItemHighlit = true;
				}
				else _isItemHighlit = false;
				break;
			default: return;
			}
		}

		if (_isItemHighlit){
			createItemDescription(item);
		}
	}
	catch (std::exception){
		_isItemHighlit = false;
	}

}

void InventoryWindow::createItemDescription(std::shared_ptr<Item> item_generic)
{
	std::string descriptionString = "";
	if (item_generic->getItemType() == ITEM_TYPE::WEAPON){
		
		std::shared_ptr<Weapon> weapon = (std::dynamic_pointer_cast <Weapon>(item_generic));
		Weapon_struct stats = weapon->getStatsStruct();
		descriptionString += "Name: " + stats.name;
		//TODO: put to next line if name string too long

		//Set weapon type in pattern Type: <size> <handle> <weapon type>
		descriptionString += "\n\nType: ";

		switch (stats.size){
		case WEAPON_SIZE::SMALL:
			descriptionString += "Small ";
			break;
		case WEAPON_SIZE::MEDIUM:
			descriptionString += "Medium ";
			break;
		case WEAPON_SIZE::LARGE:
			descriptionString += "Large ";
			break;
		}

		switch (stats.weapon_handle){
		case WEAPON_HANDLE::ONEHANDED:
			descriptionString += "one-handed ";
			break;
		case WEAPON_HANDLE::TWOHANDED:
			descriptionString += "two-handed ";
			break;
		}

		switch (stats.type){
		case WEAPON_TYPE::AXE:
			descriptionString += "axe";
			break;
		case WEAPON_TYPE::MACE:
			descriptionString += "mace";
			break;
		case WEAPON_TYPE::SWORD:
			descriptionString += "sword";
			break;
		case WEAPON_TYPE::SPEAR:
			descriptionString += "spear";
			break;
		}

		//Show item base attack
		descriptionString += "\n\nBase attack: " + std::to_string(stats.min_dmg);
		descriptionString += " - " + std::to_string(stats.max_dmg);


		//Show weapon multipliers
		descriptionString += "\n\nPrimary multiplier:\n    ";
		switch (stats.primary_multiplier){
		case HERO_STATS_NAMES::STRENGTH:
			descriptionString += "Strength " + std::to_string(stats.primary_multiplier_value) + "%";
			break;
		case HERO_STATS_NAMES::ENDURANCE:
			descriptionString += "Endurance " + std::to_string(stats.primary_multiplier_value) + "%";
			break;
		case HERO_STATS_NAMES::AGILITY:
			descriptionString += "Agility " + std::to_string(stats.primary_multiplier_value) + "%";
			break;
		case HERO_STATS_NAMES::DEXTERITY:
			descriptionString += "Dexterity " + std::to_string(stats.primary_multiplier_value) + "%";
			break;
		case HERO_STATS_NAMES::INTELLIGENCE:
			descriptionString += "Intelligence " + std::to_string(stats.primary_multiplier_value) + "%";
			break;
		case HERO_STATS_NAMES::WILLPOWER:
			descriptionString += "Wellpower " + std::to_string(stats.primary_multiplier_value) + "%";
			break;
		}

		if (stats.secondary_multiplier > -1){
			descriptionString += "\nSecondary multiplier:\n    ";
			switch (stats.secondary_multiplier){
			case HERO_STATS_NAMES::STRENGTH:
				descriptionString += "Strength " + std::to_string(stats.secondary_multiplier_value) + "%";
				break;
			case HERO_STATS_NAMES::ENDURANCE:
				descriptionString += "Endurance " + std::to_string(stats.secondary_multiplier_value) + "%";
				break;
			case HERO_STATS_NAMES::AGILITY:
				descriptionString += "Agility " + std::to_string(stats.secondary_multiplier_value) + "%";
				break;
			case HERO_STATS_NAMES::DEXTERITY:
				descriptionString += "Dexterity " + std::to_string(stats.secondary_multiplier_value) + "%";
				break;
			case HERO_STATS_NAMES::INTELLIGENCE:
				descriptionString += "Intelligence " + std::to_string(stats.secondary_multiplier_value) + "%";
				break;
			case HERO_STATS_NAMES::WILLPOWER:
				descriptionString += "Wellpower " + std::to_string(stats.secondary_multiplier_value) + "%";
				break;
			}
		}
		//Item requirements
		if (stats.agi_req == 0 &&
			stats.dex_req == 0 &&
			stats.end_req == 0 &&
			stats.int_req == 0 &&
			stats.str_req == 0 &&
			stats.wil_req == 0){
			descriptionString += "\n\nNo requirements";
		}
		else{
			descriptionString += "\n\nRequirements:";
			if (stats.str_req > 0){
				descriptionString += "\n     " + std::to_string(stats.str_req) + " Strength";
			}
			if (stats.end_req > 0){
				descriptionString += "\n     " + std::to_string(stats.end_req) + " Endurance";
			}
			if (stats.dex_req > 0){
				descriptionString += "\n     " + std::to_string(stats.dex_req) + " Dexterity";
			}
			if (stats.agi_req > 0){
				descriptionString += "\n     " + std::to_string(stats.agi_req) + " Agility";
			}
			if (stats.int_req > 0){
				descriptionString += "\n     " + std::to_string(stats.int_req) + " Intelligence";
			}
			if (stats.wil_req > 0){
				descriptionString += "\n     " + std::to_string(stats.wil_req) + " Willpower";
			}
		}

	}
	else if (item_generic->getItemType() == ITEM_TYPE::ARMOUR){

		std::shared_ptr<Armour> armour = (std::dynamic_pointer_cast <Armour>(item_generic));

		Armour_struct stats = armour->getStatsStruct();
		descriptionString += "Name: " + stats.name;
		//TODO: put to next line if name string too long
		

		//Set armour type in pattern Type: <class> <type>
		descriptionString += "\n\nType: ";

		switch (stats.armour_class){
		case ARMOUR_CLASS::CLOTH:
			descriptionString += "Cloth ";
			break;
		case ARMOUR_CLASS::LEATHER:
			descriptionString += "Leather ";
			break;
		case ARMOUR_CLASS::METAL:
			descriptionString += "Metal ";
			break;
		case ARMOUR_CLASS::LIGHT:
			descriptionString += "Light ";
			break;
		case ARMOUR_CLASS::AVERAGE:
			descriptionString += "Medium ";
			break;
		case ARMOUR_CLASS::HEAVY:
			descriptionString += "Heavy ";
			break;
		}

		switch (stats.type){
		case ARMOUR_TYPE::SHIELD:
			descriptionString += "shield";
			break;
		case ARMOUR_TYPE::HELMET:
			descriptionString += "helmet";
			break;
		case ARMOUR_TYPE::TORSO:
			descriptionString += "body";
			break;
		case ARMOUR_TYPE::GREAVES:
			descriptionString += "boots";
			break;
		}

		//Show item base defence options
		if (stats.armour_class != ARMOUR_CLASS::CLOTH) descriptionString += "\n\nBase defence: " + std::to_string(stats.defence);
		if (stats.armour_class != ARMOUR_CLASS::METAL) descriptionString += "\n\nBase dodge: " + std::to_string(stats.dodge);

		//Show item base speed
		int modifier = 1;
		if (stats.armour_class == ARMOUR_CLASS::CLOTH) modifier = -1;

		//Item requirements
		if (stats.agi_req == 0 &&
			stats.dex_req == 0 &&
			stats.end_req == 0 &&
			stats.int_req == 0 &&
			stats.str_req == 0 &&
			stats.wil_req == 0){
			descriptionString += "\n\nNo requirements";
		}
		else{
			descriptionString += "\n\nRequirements:";
			if (stats.str_req > 0){
				descriptionString += "\n     " + std::to_string(stats.str_req) + " Strength";
			}
			if (stats.end_req > 0){
				descriptionString += "\n     " + std::to_string(stats.end_req) + " Endurance";
			}
			if (stats.dex_req > 0){
				descriptionString += "\n     " + std::to_string(stats.dex_req) + " Dexterity";
			}
			if (stats.agi_req > 0){
				descriptionString += "\n     " + std::to_string(stats.agi_req) + " Agility";
			}
			if (stats.int_req > 0){
				descriptionString += "\n     " + std::to_string(stats.int_req) + " Intelligence";
			}
			if (stats.wil_req > 0){
				descriptionString += "\n     " + std::to_string(stats.wil_req) + " Willpower";
			}
		}

	}
	else if (item_generic->getItemType() == ITEM_TYPE::CONSUMABLE){

		std::shared_ptr<Consumable> consumable = (std::dynamic_pointer_cast <Consumable>(item_generic));

		Consumable_struct stats = consumable->getStatsStruct();
		descriptionString += "Name: " + stats.name;
		//TODO: put to next line if name string too long


		//Set consumable type in patter <effect> <consumable type>
		descriptionString += "\n\nType: ";


		switch (stats.effect_type){
		case CONSUMABLE_EFFECT::AGI_UP:
			descriptionString += "Agility";
			break;
		case CONSUMABLE_EFFECT::STR_UP:
			descriptionString += "Strength";
			break;
		case CONSUMABLE_EFFECT::END_UP:
			descriptionString += "Endurance";
			break;
		case CONSUMABLE_EFFECT::DEX_UP:
			descriptionString += "Dexterity";
			break;
		case CONSUMABLE_EFFECT::WIL_UP:
			descriptionString += "Willpower";
			break;
		case CONSUMABLE_EFFECT::INT_UP:
			descriptionString += "Intelligence";
			break;
		case CONSUMABLE_EFFECT::BODY_UP:
			descriptionString += "Body";
			break;
		case CONSUMABLE_EFFECT::REFLEX_UP:
			descriptionString += "Reflex";
			break;
		case CONSUMABLE_EFFECT::MIND_UP:
			descriptionString += "Mind";
			break;
		case CONSUMABLE_EFFECT::EXP_UP:
			descriptionString += "Experience";
			break;
		case CONSUMABLE_EFFECT::HP_REGEN:
			descriptionString += "Health";
			break;
		case CONSUMABLE_EFFECT::SP_REGEN:
			descriptionString += "Stamina";
			break;
		case CONSUMABLE_EFFECT::REGENERATE_TICK:
			descriptionString += "Regeneration";
			break;
		}


		switch (stats.type){
		case CONSUMABLE_TYPE::PILL_TYPE:
			descriptionString += " pill.";
			break;
		case CONSUMABLE_TYPE::FOOD_TYPE:
			descriptionString += " food.";
			break;
		case CONSUMABLE_TYPE::POTION_TYPE:
			descriptionString += " potion.";
			break;
		}

		//Show as in "Effect: <effect>"

		descriptionString += "\n\nEffect: ";
		if (stats.effect_strength >= 0){
			descriptionString += "+" + std::to_string(stats.effect_strength);
		}
		else{
			descriptionString += "-" + std::to_string(stats.effect_strength);
		}

		if (stats.effect_type == CONSUMABLE_EFFECT::HP_REGEN ||
			stats.effect_type == CONSUMABLE_EFFECT::SP_REGEN ||
			stats.effect_type == CONSUMABLE_EFFECT::REGENERATE_TICK){
			descriptionString += "%";
			switch (stats.effect_type){
			case CONSUMABLE_EFFECT::HP_REGEN:
				descriptionString += " health.";
				break;
			case CONSUMABLE_EFFECT::SP_REGEN:
				descriptionString += " stamina.";
				break;
			case CONSUMABLE_EFFECT::REGENERATE_TICK:
				descriptionString += " healt and stamina.";
				break;
			}
		}
		else{
			switch (stats.effect_type){
			case CONSUMABLE_EFFECT::AGI_UP:
				descriptionString += " to agility.";
				break;
			case CONSUMABLE_EFFECT::STR_UP:
				descriptionString += " to strength.";
				break;
			case CONSUMABLE_EFFECT::END_UP:
				descriptionString += " to endurance.";
				break;
			case CONSUMABLE_EFFECT::DEX_UP:
				descriptionString += " to dexterity.";
				break;
			case CONSUMABLE_EFFECT::WIL_UP:
				descriptionString += " to willpower.";
				break;
			case CONSUMABLE_EFFECT::INT_UP:
				descriptionString += " to intelligence.";
				break;
			case CONSUMABLE_EFFECT::BODY_UP:
				descriptionString += " to strength and\n endurance.";
				break;
			case CONSUMABLE_EFFECT::REFLEX_UP:
				descriptionString += " to dexterity and\n agility.";
				break;
			case CONSUMABLE_EFFECT::MIND_UP:
				descriptionString += " to intelligence and\n willpower";
				break;
			case CONSUMABLE_EFFECT::EXP_UP:
				descriptionString += " to experience.";
				break;

			}

		}
	}
	else _isItemHighlit = false;


	_itemStats.setString(descriptionString);
}