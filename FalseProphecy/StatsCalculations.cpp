#include "StatsCalculations.h"

namespace Calculations{

	void calculateBaseRating(Weapon_struct &stats)
	{

		int rating = 0;
		rating += (int)((float)(stats.min_dmg + stats.max_dmg) / 2);

		rating -= stats.agi_req / 5;
		rating -= stats.dex_req / 5;
		rating -= stats.str_req / 5;
		rating -= stats.end_req / 5;
		rating -= stats.int_req / 5;
		rating -= stats.wil_req / 5;

		rating += stats.primary_multiplier_value / 10;
		if (stats.secondary_multiplier >= 0 && stats.secondary_multiplier_value > 0){
			rating += stats.secondary_multiplier_value / 10;
		}
		
		stats.rating = rating;


	}

	void calculateBaseRating(Armour_struct &stats)
	{
		int rating = 0;
		switch (stats.armour_class){
		case ARMOUR_CLASS::LIGHT:
		case ARMOUR_CLASS::CLOTH:
			rating += stats.dodge / 2;

			break;
		case ARMOUR_CLASS::AVERAGE:
		case ARMOUR_CLASS::LEATHER:
			rating += stats.dodge / 2;
			rating += stats.defence / 2;

			break;
		case ARMOUR_CLASS::HEAVY:
		case ARMOUR_CLASS::METAL:
			rating += stats.defence / 2;

			break;
		}
		if (stats.type == ARMOUR_TYPE::SHIELD){
			rating += stats.block / 2;
		}

		rating -= stats.agi_req / 5;
		rating -= stats.dex_req / 5;
		rating -= stats.str_req / 5;
		rating -= stats.end_req / 5;
		rating -= stats.int_req / 5;
		rating -= stats.wil_req / 5;

		stats.rating = rating;
	}

	void calculateBaseRating(Enemy_Stats &stats)
	{
		int rating = 0;

		rating += stats.max_hitpoints / 5;
		rating += stats.attack * 2;
		rating += stats.defence * 2;
		rating += stats.experience / 10;

		stats.rating = rating;
	}

	void calculateNewStats(Weapon_struct &stats, int heroRating)
	{
		int rating_difference = 0;
		float percentage_difference = 0.00f;

		rating_difference = heroRating - stats.rating;
		std::cout << rating_difference << std::endl;
		//difference < 0 weapon better than hero, needs nerf
		//difference > 0 weapon worse than hero, needs buff
		//difference = 0 weapon as good as hero, no change

		//Nerfing//
		if (rating_difference < 0){
			percentage_difference = 1 - ((float)(rating_difference * -1) / (float)heroRating);
			std::cout << percentage_difference << std::endl;
			if (percentage_difference < 0.05){
				percentage_difference = 0.05;
			}

		}
		//buffing//
		else if (rating_difference > 0){
			percentage_difference = 1 + ((float)rating_difference / (float)heroRating);
		}

		std::cout << percentage_difference << std::endl;

		//calculating new stats//
		stats.min_dmg = (int)((float)stats.min_dmg * percentage_difference);
		stats.max_dmg = (int)((float)stats.max_dmg * percentage_difference);

		int multiplier = 1;
		if (rating_difference < 0){
			multiplier = -1;
		}

		float req_inc = percentage_difference * multiplier;

		stats.agi_req = (int)((float)stats.agi_req * req_inc);
		stats.dex_req = (int)((float)stats.dex_req * req_inc);
		stats.str_req = (int)((float)stats.str_req * req_inc);
		stats.end_req = (int)((float)stats.end_req * req_inc);
		stats.int_req = (int)((float)stats.int_req * req_inc);
		stats.wil_req = (int)((float)stats.wil_req * req_inc);

		calculateBaseRating(stats);

	}

	void calculateNewStats(Armour_struct &stats, int heroRating)
	{

	}

	void calculateNewStats(Enemy_Stats &stats, int heroRating)
	{

	}
}