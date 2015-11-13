#ifndef STATS_CALCULATIONS
#define STATS_CALCULATIONS

#include "StructsEnums.h"
#include <iostream>

namespace Calculations{

	void calculateBaseRating(Weapon_struct &stats);
	void calculateBaseRating(Armour_struct &stats);
	void calculateBaseRating(Enemy_Stats &stats);


	void calculateNewStats(Weapon_struct &stats, int heroRating);
	void calculateNewStats(Armour_struct &stats, int heroRating);
	void calculateNewStats(Enemy_Stats &stats, int heroRating);



}


#endif //!STATS_CALCULATIONS