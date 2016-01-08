#include "SaveState.h"
#include "../Game/Game.h"

SaveState::SaveState(Game &game) : _game(game)
{
	//std::cout << &_game << std::endl;
	_events = _game._eventsHandler->getEventsStructure();

}

SaveState::~SaveState()
{

}

void SaveState::saveGame()
{


	_events = _game._eventsHandler->getEventsStructure();
	std::ofstream ofs(__PATH_TO_SAVE_FILE__);
	boost::archive::binary_oarchive oa(ofs);

	//std::shared_ptr<Player> player =;

	//save game state
	oa << _game._eventsHandler->getEventsStructure();
	oa << _game._player;
	oa << _game._currentMapNumber;

	oa << _game._maps;

	//oa << _game._currentMap->getEnemies();
	//oa << _game._currentMap;
	//oa << _game._mapsWithAvaiableExits;
	//std::cout << _events.start_of_game << _events.first_instructions << _events.first_step << _events.items_first_lookout << _events.items_instructions << std::endl;

	saveGameData();
}

void SaveState::loadGame()
{
	std::ifstream ifs(__PATH_TO_SAVE_FILE__);
	boost::archive::binary_iarchive ia(ifs);


	std::shared_ptr<Player> player;

	std::vector<std::shared_ptr<Map>> maps;
	int currentMapNumber;

	//load game state
	ia >> _events;
	ia >> player;
	ia >> currentMapNumber;

	ia >> maps;

	//ia >> enemies;
	//ia >> _game._currentMap;
//	ia >> _game._mapsWithAvaiableExits;
	//_game._player = player;
	//_game._player->restoreData();
	//_game._currentMap->getEnemies() = enemies;
	//std::cout << _events.start_of_game << _events.first_instructions << _events.first_step<< _events.items_first_lookout << _events.items_instructions << std::endl;
	


	std::cout << std::endl;
	loadGameData();

	_game._player = player;
	_game._currentMapNumber = currentMapNumber;
	_game._maps = maps;
	_game._eventsHandler->restoreEventData(_events);
}

void SaveState::saveGameData()
{
	_events = _game._eventsHandler->getEventsStructure();
	std::ofstream ofs(__PATH_TO_DATA_FILE__);
	boost::archive::binary_oarchive oa(ofs);
	ResourcesHolder *_resHolder = &ResourcesHolder::getResourcesHolder();

	//save data for item and map generation
	oa << _resHolder->getAllConsumables();
	oa << _resHolder->getAllWeapons();
	oa << _resHolder->getAllArmours();
	oa << _resHolder->getAllEnemies();
	oa << _resHolder->getAllMaps();



}

void SaveState::loadGameData()
{
	std::ifstream ifs(__PATH_TO_DATA_FILE__);
	boost::archive::binary_iarchive ia(ifs);

	ResourcesHolder *_resHolder = &ResourcesHolder::getResourcesHolder();

	//load data for item and map generation
	try{
		ia >> _consumables;
		_resHolder->setData(_consumables);
	}
	catch (boost::archive::archive_exception){}

	try{
		ia >> _weapons;
		_resHolder->setData(_weapons);
	}
	catch (boost::archive::archive_exception){}

	try{
		ia >> _armours;
		_resHolder->setData(_armours);
	}
	catch (boost::archive::archive_exception){}

	try{
		ia >> _enemies;
		_resHolder->setData(_enemies);
	}
	catch (boost::archive::archive_exception){}

	try{
		ia >> _maps;
		_resHolder->setData(_maps);
	}
	catch (boost::archive::archive_exception){}


}
