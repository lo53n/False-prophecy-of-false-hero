#ifndef ENEMY_ENEMIESHOLDER
#define ENEMY_ENEMIESHOLDER


#include <vector>
#include <iostream>

#include "../StructsEnums.h"
//#include "EnemiesLoader.h"

class EnemiesHolder{
public:
	static EnemiesHolder& getEnemiesHolder();
	void addToEnemyContainer(Enemy_Stats data);

	int getEnemiesCount();

	void adjustContainer();

	void setData(std::vector<Enemy_Stats> externalData);

	std::vector<Enemy_Stats> _enemiesData;

private:
	EnemiesHolder();
	EnemiesHolder(EnemiesHolder const&);
	void operator=(EnemiesHolder const&);

private:
	static EnemiesHolder *_enemiesHolder;

};


#endif //!ENEMY_ENEMYHOLDER