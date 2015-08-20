#ifndef STRUCTURES_AND_ENUMS
#define STRUCTURES_AND_ENUMS

#include <string>


///////////////////////////
//Items structs and enums//
///////////////////////////

enum ITEM_TYPE{
	WEAPON,
	ARMOUR,
	CONSUMABLE
};

enum WEAPON_TYPE{
	SWORD,
	MACE,
	SPEAR,
	AXE
};

enum WEAPON_SIZE{
	SMALL,
	MEDIUM,
	LARGE
};

enum WEAPON_HANDLE{
	ONEHANDED,
	TWOHANDED
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
	CLOTH,
	LEATHER,
	MAIL,
	HEAVY,
	PLATE
};

struct Armour_struct{
	std::string name;
	std::string img_path;
	int type;
	int armour_class;
	bool isMagic;
	int defence;
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

enum HERO_ABILITIES_NUMBER{
	ONEHANDED_PROFICIENTY,
	TWOHANDED_PROFICIENTY,
	SHIELD_PROFICIENTY,
	SWORD_PROFICIENTY,
	MACE_PROFICIENTY,
	SPEAR_PROFICIENTY,
	AXE_PROFICIENTY,
	DEFENCE_PROFICIENTY,
	MAGIC_PROFICIENTY,
	BODY_ENDURANCE,
	PAIN_ENDURANCE,
	DODGING_PROFICIENTY
};

struct Hero_Profile{

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
	int attack;
	int defence;
	int speed;
	int type;
	int enemy_class;
};

#endif //!STRUCTURES_AND_ENUMS

