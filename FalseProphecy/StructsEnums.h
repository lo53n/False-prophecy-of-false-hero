#ifndef STRUCTURES_AND_ENUMS
#define STRUCTURES_AND_ENUMS

#include <string>


#define DEBUG_WITH_LINE std::cout << __FUNCSIG__ << " :[" << __LINE__ << "] "

///////////////////////////
//Items structs and enums//
///////////////////////////

enum ITEM_TYPE{
	WEAPON,
	ARMOUR,
	CONSUMABLE
};

enum WEAPON_TYPE{
	UNARMED = 3,
	SWORD = 4,
	MACE = 5,
	SPEAR = 6,
	AXE = 7
};

enum WEAPON_SIZE{
	SMALL,
	MEDIUM,
	LARGE
};

enum WEAPON_HANDLE{
	ONEHANDED = 0,
	TWOHANDED = 1
};


struct Weapon_struct{
	std::string name;
	std::string img_path;
	int texture_id;
	bool isDefault;
	int size;
	int type;
	int weapon_handle;
	int primary_multiplier;
	int primary_multiplier_value;
	int secondary_multiplier;
	int secondary_multiplier_value;
	bool isMagic;
	int min_dmg;
	int max_dmg;
	int str_req, dex_req, agi_req, int_req, end_req, wil_req;
	int base_rating, current_rating;
};

enum ARMOUR_TYPE{
	HELMET,
	TORSO,
	GREAVES,
	SHIELD
};

enum ARMOUR_CLASS{
	NAKED,
	CLOTH,
	LEATHER,
	METAL,
	EMPTYHAND,
	LIGHT,
	AVERAGE,
	HEAVY
};

struct Armour_struct{
	std::string name;
	std::string img_path;
	int texture_id;
	bool isDefault;
	int type;
	int armour_class;
	bool isMagic;
	int defence;
	int dodge;
	int block;
	int str_req, dex_req, agi_req, int_req, end_req, wil_req;
	int base_rating, current_rating;

};



enum HERO_STATS_NAMES{
	STRENGTH,
	ENDURANCE,
	DEXTERITY, //affects whole body 
	AGILITY, //affects hand and legs nibbleness
	INTELLIGENCE,
	WILLPOWER,
	LUCK
};

//If no. is changed - change it in Player.cpp in abilities startup
enum HERO_ABILITIES_NUMBER{
	ONEHANDED_PROFICIENCY,
	TWOHANDED_PROFICIENCY,
	SHIELD_PROFICIENCY,
	UNARMED_PROFICIENCY,
	SWORD_PROFICIENCY,
	MACE_PROFICIENCY,
	SPEAR_PROFICIENCY,
	AXE_PROFICIENCY,
	DEFENCE_PROFICIENCY,
	BODY_ENDURANCE,
};

struct Hero_Profile{
	int level;
	int exp, max_exp;
	int hp, max_hp;
	int mp, max_mp;
	int stam, max_stam;
	int min_dmg, max_dmg;
	int defence;
	float damage_reduction, max_reduction, dodge_chance, max_dodge, block_chance, max_block;
	int dodge;
	int block;
	int strenght;
	int endurance;
	int intelligence;
	int willpower;
	int agility;
	int dexterity;
	int luck;
};

struct Hero_Ratings{
	int hero_rating;
	int weapon_rating;
	int offhand_rating;
	int head_rating;
	int torso_rating;
	int legs_rating;
	int overral_rating;
};


struct Ability_Proficiencies{
	std::string name;
	int id;
	int level;
	int experience;
	int experience_needed;
	float effectiveness;
};

//If new appears, change also in EnemiesLoader (also in StasCalculation?!)
enum ENEMY_TYPE{
	UNDEAD_ENEMY,
	DEMON_ENEMY,
	BEAST_ENEMY,
	HUMANOID_ENEMY,
	HUMAN_ENEMY,
	GOLEM_ENEMY
};

enum ENEMY_CLASS{
	NORMAL_ENEMY = 0,
	RARE_ENEMY = 1,
	MAGIC_ENEMY = 3,
	ELITE_ENEMY = 5,
	MINIBOSS_ENEMY = 8,
	BOSS_ENEMY = 10,
	UNIQUE_ENEMY = 11
};


struct Enemy_Stats{
	std::string name;
	std::string img_path;
	int texture_id;
	bool isDefault;
	int hitpoints;
	int max_hitpoints;
	int attack;
	int defence;
	int type;
	int enemy_class;
	int experience;
	int base_rating, current_rating;
};

#endif //!STRUCTURES_AND_ENUMS

