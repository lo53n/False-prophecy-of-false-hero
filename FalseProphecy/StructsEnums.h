#ifndef STRUCTURES_AND_ENUMS
#define STRUCTURES_AND_ENUMS

#include <string>

enum ITEM_TYPE{
	WEAPON,
	ARMOUR,
	CONSUMABLE
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
	GAUNTLET,
	TORSO,
	GREAVES,
	BOOTS,
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



#endif //!STRUCTURES_AND_ENUMS

