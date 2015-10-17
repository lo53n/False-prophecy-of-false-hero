#ifndef DEVMODE_DEVMODE
#define DEVMODE_DEVMODE

#include "SFML\Graphics.hpp"

#include "../LoadFromResource.h"
#include "../StructsEnums.h"

#include "../Player/Player.h"

#include "../Items/ItemsLoader.h"
#include "../Enemy/EnemiesLoader.h"
#include "../Map/MapLoader.h"

class DevMode : public sf::Drawable{

public:

	enum DEV_RESULT_TYPE{
		CREATE_ENEMY,
		CHANGE_MAP
	};

	struct Result{
		int type;
		int value;
	};


	DevMode();
	~DevMode();

	Result handlePlayerInput(int key, bool isPressed);

	void setPositionAndSize(sf::Vector2f position, sf::Vector2f size);
	void resizeMenu(sf::Vector2f new_size);
	void updateLocation();
	void goBack();

	void setPlayer(std::shared_ptr<Player> player);

private:

	sf::RectangleShape _developerMenu;
	
	sf::Font _font;

	sf::Text _locationText;
	sf::Text _optionsText;
	sf::Text _overviewText;



	MapsHolder *_mapsHolder = &MapsHolder::getMapsHolder();
	ItemsHolder *_itemsHolder = &ItemsHolder::getItemsHolder();
	EnemiesHolder *_enemiesHolder = &EnemiesHolder::getEnemiesHolder();

	std::shared_ptr<Player> _player;

	std::vector<Weapon_struct> _weaponList;
	std::vector<Armour_struct> _armourList;
	std::vector<Enemy_Stats> _enemyList;
	std::vector<std::vector<std::vector<char>>> _mapList;

	//Developer state to undo//
	bool _categories = true;

		bool _viewLoadable = false;
			bool _viewLoadableDistinct = false;


		bool _giveItem = false;
			bool _giveItemType = false;
				bool _giveItemTypeCategory = false;
					bool _giveItemTypeCategoryDistinct = false;

		bool _setMap = false;
			bool _setMapDistinct = false;

		bool _modifyCharacter = false;
			bool _modifyCharacterRefill = false;
			bool _modifyCharacterExperience = false;
			bool _modifyCharacterStats = false;
			bool _modifyCharacterProficiences = false;

		bool _spawnEnemy = false;
			bool _spawnEnemyType = false;

		int option;

	/////////////////
	//Magic Numbers//
	/////////////////
	
			float __LOCATION_TEXT_SPAN__ = 20.f;
			float __OPTION_TEXT_SPAN__ = 60.f;



private:

	void setCategories();

	void setViewLoadable(int key);
	void setViewLoadableDistinct(int key);



	void chooseCategories(int key);

	void chooseViewLoadable(int key);


	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


};




#endif //!DEVMODE_DEVMODE