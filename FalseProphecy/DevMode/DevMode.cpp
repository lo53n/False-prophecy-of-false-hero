#include "DevMode.h"
DevMode::DevMode()
{

	_developerMenu.setFillColor(sf::Color(29, 29, 253, 230));
	
	_locationText.setPosition(40.f, _developerMenu.getGlobalBounds().top + __LOCATION_TEXT_SPAN__);
	_locationText.setFont(_font);
	_locationText.setCharacterSize(18);
	_locationText.setColor(sf::Color::White);


	_optionsText.setPosition(60.f, _developerMenu.getGlobalBounds().top + __OPTION_TEXT_SPAN__);
	_optionsText.setFont(_font);
	_optionsText.setCharacterSize(14);
	_optionsText.setColor(sf::Color::White);

	setCategories();
	updateLocation();
	//Load font from resource file.
	_font = LoadFontFromResource("Arialfont");

}

DevMode::~DevMode()
{

}

void DevMode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_developerMenu);
	target.draw(_locationText);
	target.draw(_optionsText);
}

void DevMode::setPlayer(std::shared_ptr<Player> player)
{
	_player = player;
}

void DevMode::setPositionAndSize(sf::Vector2f position, sf::Vector2f size)
{
	_developerMenu.setSize(size);
	_developerMenu.setPosition(position);

	_locationText.setPosition(40.f, _developerMenu.getGlobalBounds().top + __LOCATION_TEXT_SPAN__);
	_optionsText.setPosition(60.f, _developerMenu.getGlobalBounds().top + __OPTION_TEXT_SPAN__);
}

void DevMode::resizeMenu(sf::Vector2f size)
{
	_developerMenu.setSize(size);

	_locationText.setPosition(40.f, _developerMenu.getGlobalBounds().top + __LOCATION_TEXT_SPAN__);
	_optionsText.setPosition(60.f, _developerMenu.getGlobalBounds().top + __OPTION_TEXT_SPAN__);
}

DevMode::Result DevMode::handlePlayerInput(int key, bool isPressed)
{
	if (key >= sf::Keyboard::Num0 && key <= sf::Keyboard::Num9 && isPressed){
		std::cout << key << std::endl;
		if (_viewLoadableDistinct){
			setViewLoadableDistinct(key);
		}
		else if (_viewLoadable){
			setViewLoadable(key);
		}
	}


	updateLocation();
	Result result;
	result.type = 1;
	result.value = 1;
	return result;
}





void DevMode::updateLocation()
{
	std::string location = "";
	if (_categories) location += "Category";
	if (_viewLoadable){
		location += " -> View loadables";
		if (_viewLoadableDistinct){
			location += " -> Select distinct";
		}
	}

	if (_giveItem){
		location += " -> Give item";
		if (_giveItemType){
			location += " -> Select type";
			if (_giveItemTypeCategory){
				location += " -> Select category";
				if (_giveItemTypeCategoryDistinct){
					location += " -> Select distinct";
				}
			}
		}
	}



	_locationText.setString(location);

}

void DevMode::setCategories()
{
	std::string string = "";

	string += "1. View loadables\n2. Give item\n3. Set map\n4. Modify character\n5. Spawn enemy";
	_optionsText.setString(string);
}

void DevMode::setViewLoadable(int key)
{
	if (key >= sf::Keyboard::Num1 && key <= sf::Keyboard::Num5){
		_viewLoadableDistinct = true;
		option = key % sf::Keyboard::Num1;
	}
	switch (key){
	case sf::Keyboard::Num1:
		_mapList = _mapsHolder->getAllMaps();
		break;
	case sf::Keyboard::Num2:
		_enemyList = _enemiesHolder->_enemiesData;
		break;
	case sf::Keyboard::Num3:
		_weaponList = _itemsHolder->_weaponsData;
		break;
	case sf::Keyboard::Num4:
		_armourList= _itemsHolder->_armoursData;
		break;
	case sf::Keyboard::Num5:
		std::cout << "sheit" << std::endl;
		break;
	}

	std::string string = "";
	string = "1. Show maps\n2. Show enemies\n3. Show weapons\n4. Show armours\n5. Show consumables";
	_optionsText.setString(string);

}

void DevMode::setViewLoadableDistinct(int key)
{
	switch (key){
	case sf::Keyboard::Num1:
		_viewLoadableDistinct = true;
		break;
	}
}
