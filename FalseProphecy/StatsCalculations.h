#ifndef STATS_CALCULATIONS
#define STATS_CALCULATIONS

#include "StructsEnums.h"
#include <iostream>

namespace Calculations{

	void calculateBaseRating(Weapon_struct &stats, bool second_calc = false);
	void calculateBaseRating(Armour_struct &stats, bool second_calc = false);
	void calculateBaseRating(Enemy_Stats &stats, bool second_calc = false);


	void calculateNewStats(Weapon_struct &stats, int heroRating);
	void calculateNewStats(Armour_struct &stats, int heroRating);
	void calculateNewStats(Enemy_Stats &stats, int heroRating);


	void makeMagicItem(bool &magic_type, int &rating, float &multiplier);

}


#endif //!STATS_CALCULATIONS