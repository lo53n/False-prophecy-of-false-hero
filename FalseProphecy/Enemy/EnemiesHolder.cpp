#include "EnemiesHolder.h"

EnemiesHolder::EnemiesHolder()
{

}

EnemiesHolder& EnemiesHolder::getEnemiesHolder()
{
	static EnemiesHolder instance;
	return instance;
}

void EnemiesHolder::adjustContainer()
{
	_enemiesData.shrink_to_fit();
}

int EnemiesHolder::getEnemiesCount()
{
	return _enemiesData.size();
}

void EnemiesHolder::setData(std::vector<Enemy_Stats> externalData)
{
	_enemiesData = externalData;
}