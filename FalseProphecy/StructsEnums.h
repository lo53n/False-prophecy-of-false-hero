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
	UNARMED = 4,
	SWORD = 5,
	MACE = 6,
	SPEAR = 7,
	AXE = 8
};

enum WEAPON_SIZE{
	SMALL,
	MEDIUM,
	LARGE
};

enum WEAPON_HANDLE{
	ONEHANDED = 0,
	TWOHANDED = 1,
	DUALWIELD = 2
};


struct Weapon_struct{
	std::string name;
	std::string img_path;
	int size;
	int type;
	int weapon_handle;
	int primary_multiplier;
	int primary_multiplier_value;
	int secondary_multiplier;
	int secondary_multiplier_value;
	bool isMagic;
	int speed;
	int min_dmg;
	int max_dmg;
	int str_req, dex_req, agi_req, int_req, end_req, wil_req;
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
	int type;
	int armour_class;
	bool isMagic;
	int defence;
	int dodge;
	int block;
	int speed;
	int str_req, dex_req, agi_req, int_req, end_req, wil_req;

};



enum HERO_STATS_NAMES{
	STRENGTH,
	ENDURANCE,
	DEXTERITY,
	AGILITY,
	INTELLIGENCE,
	WILLPOWER,
	LUCK
};

//If no. is changed - change it in Player.cpp in abilities startup
enum HERO_ABILITIES_NUMBER{
	ONEHANDED_PROFICIENCY,
	TWOHANDED_PROFICIENCY,
	DUALWIELD_PROFICIENCY,
	SHIELD_PROFICIENCY,
	UNARMED_PROFICIENCY,
	SWORD_PROFICIENCY,
	MACE_PROFICIENCY,
	SPEAR_PROFICIENCY,
	AXE_PROFICIENCY,
	MAGIC_PROFICIENCY,
	DEFENCE_PROFICIENCY,
	BODY_ENDURANCE,
	PAIN_ENDURANCE,
	DODGING_PROFICIENCY
};

struct Hero_Profile{
	int level;
	int exp, max_exp;
	int hp, max_hp;
	int mp, max_mp;
	int stam, max_stam;
	int min_dmg, max_dmg;
	int defence;
	int min_speed, speed;
	int max_dodge, dodge;
	int max_block, block;
	int strenght;
	int endurance;
	int intelligence;
	int willpower;
	int agility;
	int dexterity;
	int luck;
};

struct Ability_Proficiencies{
	std::string name;
	int id;
	int level;
	int experience;
	int experience_needed;
	float effectiveness;
};


enum ENEMY_TYPE{
	UNDEAD,
	DEMON,
	BEAST,
	HUMANOID,
	HUMAN,
	GOLEM
};

enum ENEMY_CLASS{
	NORMAL,
	RARE,
	MAGIC,
	ELITE,
	MINIBOSS,
	BOSS,
	UNIQUE
};


struct Enemy_Stats{
	std::string name;
	std::string img_path;
	int hitpoints;
	int max_hitpoints;
	int attack;
	int defence;
	int speed;
	int type;
	int enemy_class;
	int experience;
	int value;
};

#endif //!STRUCTURES_AND_ENUMS

