#ifndef SAVE_SAVESTATE
#define SAVE_SAVESTATE

#include <iostream>
#include <cstdlib>

#include <boost\serialization\vector.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/unordered_map.hpp>

#include "../StructsEnums.h"
#include "../Items/Item.h"
#include "../Player/Player.h"
#include "../Enemy/Enemy.h"


class Game;

class SaveState{
	friend class boost::serialization::access;

public:
	SaveState();
	SaveState(Game &game);
	~SaveState();

	void saveGame();
	void saveGameData();
	void loadGame();
	void loadGameData();


	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar  & _events;
	}


private:
	Game &_game;

	GameEvents _events;
	std::vector<Consumable_struct> _consumables;
	std::vector<Weapon_struct> _weapons;
	std::vector<Armour_struct> _armours;
	std::vector<Enemy_Stats> _enemies;
	std::vector<std::vector<std::vector<char>>> _maps;

	std::vector<std::shared_ptr<Enemy>> enemies;

	std::shared_ptr<Player> _player;

	std::string __PATH_TO_SAVE_FILE__ = "data\\save\\save.dat";
	std::string __PATH_TO_DATA_FILE__ = "data\\save\\data.dat";

	std::shared_ptr<Item> _item;
};



#endif //!SAVE_SAVESTATE