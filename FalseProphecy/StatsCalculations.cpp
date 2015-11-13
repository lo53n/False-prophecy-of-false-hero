#include "StatsCalculations.h"

namespace Calculations{

	void calculateBaseRating(Weapon_struct &stats, bool second_calc)
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

		if (!second_calc){
			stats.base_rating = stats.current_rating = rating;
		}
		else{
			stats.current_rating = rating;
		}


	}

	void calculateBaseRating(Armour_struct &stats, bool second_calc)
	{
		int rating = 0;
		switch (stats.armour_class){
		case ARMOUR_CLASS::LIGHT:
		case ARMOUR_CLASS::CLOTH:
			rating += stats.dodge;
			break;

		case ARMOUR_CLASS::AVERAGE:
		case ARMOUR_CLASS::LEATHER:
			rating += stats.dodge;
			rating += stats.defence;
			break;

		case ARMOUR_CLASS::HEAVY:
		case ARMOUR_CLASS::METAL:
			rating += stats.defence;
			break;
		}
		if (stats.type == ARMOUR_TYPE::SHIELD){
			rating += stats.block;
		}

		rating -= stats.agi_req / 5;
		rating -= stats.dex_req / 5;
		rating -= stats.str_req / 5;
		rating -= stats.end_req / 5;
		rating -= stats.int_req / 5;
		rating -= stats.wil_req / 5;

		if (!second_calc){
			stats.base_rating = stats.current_rating = rating;
		}
		else{
			stats.current_rating = rating;
		}
	}

	void calculateBaseRating(Enemy_Stats &stats, bool second_calc)
	{
		int rating = 0;

		rating += stats.max_hitpoints / 5;
		rating += stats.attack * 2;
		rating += stats.defence * 2;
		rating += stats.experience / 10;

		if (!second_calc){
			stats.base_rating = stats.current_rating = rating;
		}
		else{
			stats.current_rating = rating;
		}
	}

	void calculateNewStats(Weapon_struct &stats, int heroRating)
	{
		int rating_difference = 0;
		float percentage_difference = 0.00f;
		float multiplier = 1.f;

		//strenghen new item//
		if (rand() % 100 >= 85){
			makeMagicItem(stats.isMagic, heroRating, multiplier);
		}

		rating_difference = heroRating - stats.base_rating;
		//difference < 0 weapon better than hero, needs nerf
		//difference > 0 weapon worse than hero, needs buff
		//difference = 0 weapon as good as hero, no change

		//Nerfing//
		if (rating_difference < 0){
			percentage_difference = 1 - ((float)(rating_difference * -1) / (float)heroRating);
			if (percentage_difference < 0.05){
				percentage_difference = 0.05;
			}

		}
		//buffing//
		else if (rating_difference > 0){
			percentage_difference = 1 + ((float)rating_difference / (float)heroRating);
		}


		//calculating new stats//
		stats.min_dmg = (int)((float)stats.min_dmg * percentage_difference);
		stats.max_dmg = (int)((float)stats.max_dmg * percentage_difference);


		float req_inc = percentage_difference * multiplier;

		stats.agi_req = (int)((float)stats.agi_req * req_inc);
		stats.dex_req = (int)((float)stats.dex_req * req_inc);
		stats.str_req = (int)((float)stats.str_req * req_inc);
		stats.end_req = (int)((float)stats.end_req * req_inc);
		stats.int_req = (int)((float)stats.int_req * req_inc);
		stats.wil_req = (int)((float)stats.wil_req * req_inc);

		calculateBaseRating(stats, true);

	}

	void calculateNewStats(Armour_struct &stats, int heroRating)
	{
		int rating_difference = 0;
		float percentage_difference = 0.00f;
		float multiplier = 1.f;

		//strenghen new item//
		if (rand() % 100 >= 85){
			makeMagicItem(stats.isMagic, heroRating, multiplier);
		}

		rating_difference = heroRating - stats.base_rating;
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


		switch (stats.armour_class){
		case ARMOUR_CLASS::LIGHT:
		case ARMOUR_CLASS::CLOTH:
			stats.dodge = (int)((float)stats.dodge * percentage_difference);

			break;
		case ARMOUR_CLASS::AVERAGE:
		case ARMOUR_CLASS::LEATHER:
			stats.dodge = (int)((float)stats.dodge * percentage_difference);
			stats.defence = (int)((float)stats.defence * percentage_difference);

			break;
		case ARMOUR_CLASS::HEAVY:
		case ARMOUR_CLASS::METAL:
			stats.defence = (int)((float)stats.defence * percentage_difference);

			break;
		}
		if (stats.type == ARMOUR_TYPE::SHIELD){
			stats.block = (int)((float)stats.block * percentage_difference);
		}


		float req_inc = percentage_difference *multiplier;
		std::cout << "Req_inc: " << req_inc << std::endl;

		stats.agi_req = (int)((float)stats.agi_req * req_inc);
		stats.dex_req = (int)((float)stats.dex_req * req_inc);
		stats.str_req = (int)((float)stats.str_req * req_inc);
		stats.end_req = (int)((float)stats.end_req * req_inc);
		stats.int_req = (int)((float)stats.int_req * req_inc);
		stats.wil_req = (int)((float)stats.wil_req * req_inc);

		calculateBaseRating(stats, true);

	}

	void calculateNewStats(Enemy_Stats &stats, int heroRating)
	{

	}



	void makeMagicItem(bool &magic_type, int &rating, float &multiplier)
	{
		magic_type = true;
		rating *= 2;
		multiplier = 0.75f;

		if (rand() % 100 >= 90){
			rating *= 3;
			multiplier = 0.60f;
		}
	}

}