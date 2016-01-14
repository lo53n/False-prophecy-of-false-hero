#include "StatsCalculations.h"

namespace Calculations{

	void calculateBaseRating(Weapon_struct &stats, bool second_calc) 
	{

		int rating = 0;
		rating += stats.min_dmg + stats.max_dmg;

		rating += stats.primary_multiplier_value / 6;
		if (stats.secondary_multiplier >= 0 && stats.secondary_multiplier_value > 0){
			rating += stats.secondary_multiplier_value / 6;
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
			rating += stats.dodge * 1.5;
			rating += stats.defence * 1.5;
			break;

		case ARMOUR_CLASS::HEAVY:
		case ARMOUR_CLASS::METAL:
			rating += stats.defence;
			break;
		}
		if (stats.type == ARMOUR_TYPE::SHIELD){
			rating += stats.block;
		}


		if (!second_calc){
			stats.base_rating = stats.current_rating = rating;
		}
		else{
			stats.current_rating = rating;
		}
	}

	void calculateBaseRating(Consumable_struct &stats)
	{

		int rating = 0;

		switch (stats.effect_type){
		case CONSUMABLE_EFFECT::AGI_UP:
		case CONSUMABLE_EFFECT::STR_UP:
		case CONSUMABLE_EFFECT::END_UP:
		case CONSUMABLE_EFFECT::DEX_UP:
		case CONSUMABLE_EFFECT::WIL_UP:
		case CONSUMABLE_EFFECT::INT_UP:
			rating = 100 * stats.effect_strength;
			break;

		case CONSUMABLE_EFFECT::BODY_UP:
		case CONSUMABLE_EFFECT::MIND_UP:
		case CONSUMABLE_EFFECT::REFLEX_UP:
			rating = 175 * stats.effect_strength;
			break;

		case CONSUMABLE_EFFECT::HP_REGEN:
			rating = 5 * stats.effect_strength;
			break;
		case CONSUMABLE_EFFECT::SP_REGEN:
			rating = 10 * stats.effect_strength;
			break;
		case CONSUMABLE_EFFECT::REGENERATE_TICK:
			rating = 15 * stats.effect_strength;
			break;

		case CONSUMABLE_EFFECT::EXP_UP:
			rating = 10 * stats.effect_strength;
			break;



		}

		stats.base_rating = rating;
	}

	void calculateBaseRating(Enemy_Stats &stats, bool second_calc)
	{
		int rating = 0;

		rating += stats.max_hitpoints / 5;
		rating += stats.attack;
		rating += stats.defence;
		rating += stats.experience / 20;

		if (!second_calc){
			stats.base_rating = stats.current_rating = rating;
		}
		else{
			stats.current_rating = rating;
		}
	}

	void calculateNewStats(Weapon_struct &stats, int enemyRating)
	{
		int rating_difference = 0;
		float percentage_difference = 0.00f;
		float multiplier = 1.f;


		//extra rating modifing//
		int rat_multip;
		float rat_multip1 = 0.0f;
		if (rand() % 2 == 1){
			rat_multip = -1;
		}
		else{
			rat_multip = 1;
		}
		rat_multip1 = (float)(rand() % 20) / 100.0f;
		//std::cout << "Old EnemyRating: " << enemyRating;
		enemyRating += (int)((float)enemyRating * rat_multip * rat_multip1);
		//std::cout << " New EnemyRating: " << enemyRating << std::endl;


		//strenghen new item//
		if (rand() % 100 >= 85){
			makeMagicItem(stats.isMagic, enemyRating, multiplier);
		}

		rating_difference = enemyRating - stats.base_rating;
		//difference < 0 weapon better than hero, needs nerf
		//difference > 0 weapon worse than hero, needs buff
		//difference = 0 weapon as good as hero, no change

		//Nerfing//
		if (rating_difference < 0){
			percentage_difference = 1 - ((float)(rating_difference * -1) / (float)enemyRating);
			if (percentage_difference < 0.05f){
				percentage_difference = 0.05f;
			}

		}
		//buffing//
		else if (rating_difference > 0){
			percentage_difference = 1 + ((float)rating_difference / (float)enemyRating);
		}


		//calculating new stats//
		stats.min_dmg = (int)((float)stats.min_dmg * percentage_difference);
		stats.max_dmg = (int)((float)stats.max_dmg * percentage_difference);


		float req_inc = percentage_difference * multiplier / 2;

		stats.agi_req = (int)((float)stats.agi_req * req_inc);
		stats.dex_req = (int)((float)stats.dex_req * req_inc);
		stats.str_req = (int)((float)stats.str_req * req_inc);
		stats.end_req = (int)((float)stats.end_req * req_inc);
		stats.int_req = (int)((float)stats.int_req * req_inc);
		stats.wil_req = (int)((float)stats.wil_req * req_inc);

		calculateBaseRating(stats, true);

	}

	void calculateNewStats(Armour_struct &stats, int enemyRating)
	{
		int rating_difference = 0;
		float percentage_difference = 0.00f;
		float multiplier = 1.f;

		//extra rating modifing//
		int rat_multip;
		float rat_multip1 = 0.0f;
		if (rand() % 2 == 1){
			rat_multip = -1;
		}
		else{
			rat_multip = 1;
		}
		rat_multip1 = (float)(rand() % 20) / 100.0f;
		//std::cout << "Old EnemyRating: " << enemyRating;
		enemyRating += (int)((float)enemyRating * rat_multip * rat_multip1);
		//std::cout << " New EnemyRating: " << enemyRating << std::endl;


		//strenghen new item//
		if (rand() % 100 >= 85){
			makeMagicItem(stats.isMagic, enemyRating, multiplier);
		}

		rating_difference = enemyRating - stats.base_rating;
		//std::cout << rating_difference << std::endl;
		//difference < 0 weapon better than hero, needs nerf
		//difference > 0 weapon worse than hero, needs buff
		//difference = 0 weapon as good as hero, no change

		//Nerfing//
		if (rating_difference < 0){
			percentage_difference = 1 - ((float)(rating_difference * -1) / (float)enemyRating);
			//std::cout << percentage_difference << std::endl;
			if (percentage_difference < 0.05f){
				percentage_difference = 0.05f;
			}

		}
		//buffing//
		else if (rating_difference > 0){
			percentage_difference = 1 + ((float)rating_difference / (float)enemyRating);
		}

		//std::cout << percentage_difference << std::endl;


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


		float req_inc = percentage_difference *multiplier / 2;
		//std::cout << "Req_inc: " << req_inc << std::endl;

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

		int rating_difference = 0;
		float percentage_difference = 0.00f;

		float multiplier = 1.f;

		//extra rating modifing//
		int rat_multip;
		float rat_multip1 = 0.0f;
		if (rand() % 2 == 1){
			rat_multip = -1;
		}
		else{
			rat_multip = 1;
		}
		rat_multip1 = (float)(rand() % 20) / 100.0f;
		//std::cout << "Old HeroRAting: " << heroRating;
		heroRating += (int)((float)heroRating * rat_multip * rat_multip1);
		//std::cout << " New HeroRAting: " << heroRating << std::endl;


		//strenghen new enemy//
		if (rand() % 100 > 80){
			increaseEnemyRarity(stats.enemy_class, heroRating, multiplier);
		}
		else{
			stats.enemy_class = ENEMY_CLASS::NORMAL_ENEMY;
		}

		rating_difference = heroRating - stats.base_rating;
		//difference < 0 weapon better than hero, needs nerf
		//difference > 0 weapon worse than hero, needs buff
		//difference = 0 weapon as good as hero, no change

		//Nerfing//
		if (rating_difference < 0){
			percentage_difference = 1 - ((float)(rating_difference * -1) / (float)heroRating);
			if (percentage_difference < 0.01f){
				percentage_difference = 0.01f;
			}

		}
		//buffing//
		else if (rating_difference > 0){
			percentage_difference = 1 + ((float)rating_difference / (float)heroRating);
		}
		//aplly enemy class multiplier
		percentage_difference *= multiplier;

		

		//HP will be added in Enemy class. DOn't forget it.
		stats.max_hitpoints = (int)((float)stats.max_hitpoints * percentage_difference);
		stats.attack = (int)((float)stats.attack * percentage_difference);
		stats.defence = (int)((float)stats.defence * percentage_difference);
		stats.experience = (int)((float)stats.experience* percentage_difference);


		calculateBaseRating(stats, true);
		//std::cout << "Base Rating: " << stats.base_rating << "Curr Rating: " << stats.current_rating << " class: " << stats.enemy_class << std::endl;

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

	void increaseEnemyRarity(int &enemy_class, int &rating, float &multiplier)
	{
		//become "rare"
		int random = rand() % 1000;
		if (random >= 400){ //60% chance of becoming "magic" or better
			random -= 400;
			if (random >= 300){ //50% chance of becoming "elite" or better
				random -= 300;
				if (random > 150){ //50% chance of becoming "miniboss" or better
					random -= 150;
					if (random >= 75){ //50% chance of becoming "boss" or better
						//boss
						enemy_class = ENEMY_CLASS::BOSS_ENEMY;
						rating = (int)((float)rating * 3);
						multiplier += 0.5f;
						return;
					}
					//minibos
					enemy_class = ENEMY_CLASS::MINIBOSS_ENEMY;
					rating = (int)((float)rating * 2.5);
					multiplier += 0.4f;
					return;
				}
				//elite
				enemy_class = ENEMY_CLASS::ELITE_ENEMY;
				rating = (int)((float)rating * 2);
				multiplier += 0.3f;
				return;
			}
			//magic
			enemy_class = ENEMY_CLASS::MAGIC_ENEMY;
			rating = (int)((float)rating * 1.66);
			multiplier += 0.2f;
			return;
		}
		//rare
		enemy_class = ENEMY_CLASS::RARE_ENEMY;
		rating = (int)((float)rating * 1.25);
		multiplier += 0.1f;
		return;
	}
}