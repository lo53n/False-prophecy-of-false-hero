#ifndef ENEMY_ENEMYLOADER
#define ENEMY_ENEMYLOADER

#include <vector>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <sstream>


#include <stdexcept>
#include <memory>

#include "../StatsCalculations.h"
#include "../Errors/ErrorHandler.h"

class EnemiesLoader{
public:
	void loadFromFile();

	EnemiesLoader(std::shared_ptr<ErrorHandler> errorHandler);
	~EnemiesLoader();

	std::vector<Enemy_Stats>& getEnemiesData();
	std::vector<Enemy_Stats>& getSpecialEnemiesData();

private:

	std::shared_ptr<ErrorHandler> _errorHandler;
	std::string _errorMsg;

	std::vector<Enemy_Stats> _enemiesData;

	enum TAGVALUE{
		NAME,
		IMG,
		HP,
		ATTACK,
		DEFENCE,
		TYPE,
		BASE_EXP
	};

	Enemy_Stats _currentData;
	int _enemiesCount;
	
private:
	void parseLine(std::string stringLine);
	void parseTag(std::vector<std::string> &output);
	int checkTag(std::string tag);

	void prepareStruct();

	void saveStruct();

	bool checkStructCorrectness();
	bool correctStruct(int tag);

	void showStruct();



};



#endif //!ENEMY_ENEMYLOADER