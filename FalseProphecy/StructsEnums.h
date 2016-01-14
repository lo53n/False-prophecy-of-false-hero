#ifndef STRUCTURES_AND_ENUMS
#define STRUCTURES_AND_ENUMS

#include <string>

#include <boost\archive\binary_iarchive.hpp>
#include <boost\archive\binary_oarchive.hpp>


#define DEBUG_WITH_LINE std::cout << __FUNCSIG__ << " :[" << __LINE__ << "] "
//////////
//EVENTS//
//////////

enum EVENT_TYPE{
	START_OF_GAME,				//start of plot
	FIRST_INSTRUCTIONS,			//about movement
	FIRST_STEP,					//info about laying items
	ITEMS_FIRST_LOOKOUT,		//lookout for items
	ITEMS_INSTRUCTIONS,			//instuctions about items
	FIRST_ENEMY_MEET,			//first enemy meet
	FIRST_ENEMY_MEET_SECOND,	//first enemy meet second part
	ENEMY_INSTRUCTIONS,			//enemy info
	FIRST_ENEMY_KILLED,			//first enemy killed
	HALFWAY_TO_BOSS,			//in halfway to first boss


	FIRST_BOSS,					//map with first boss
	FIRST_BOSS_KILLED,			//as in name

	PRIESTESS_FOUND_TOO_WEAK,	//hero is too weak to match priestess
	PRIESTESS_FOUND_HERO_LOST,	//hero is too weak and loses mind
	PRIESTESS_FOUND,			//priestess is found when hero is strong enough
	PRIESTESS_KILLED,			//priestess is killed aka win

	HERO_DIES,					//dead hero
	HERO_DIES_SECOND			//dead hero part two
};
struct GameEvents{
	bool start_of_game = false;
	bool first_instructions = false;
	bool first_step = false;
	bool items_first_lookout = false;
	bool items_instructions = false;
	bool first_enemy_meet = false;
	bool first_enemy_meet_second = false;
	bool enemy_instructions = false;
	bool first_enemy_killed = false;
	bool halfway_to_boss = false;

	bool first_boss = false;
	bool first_boss_killed = false;

	bool priestess_found_too_weak = false;
	bool priestess_found_hero_lost = false;
	bool priestess_found = false;
	bool priestess_killed = false;

	bool hero_dies = false;
	bool hero_dies_second = false;

	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar  & start_of_game;
		ar  & first_instructions;
		ar  & first_step;
		ar  & items_first_lookout;
		ar  & items_instructions;
		ar  & first_enemy_meet;
		ar  & first_enemy_meet_second;
		ar  & enemy_instructions;
		ar  & first_enemy_killed;
		ar  & halfway_to_boss;


		ar  & first_boss;
		ar  & first_boss_killed;
	}


	GameEvents(){}
	GameEvents(bool s_o_g, bool f_i, bool f_s, bool i_f_l, bool i_i, bool f_e_m, bool f_e_m_s, bool e_i, bool f_e_k, bool h_t_b, /*1st boss*/bool f_b, bool f_b_k) :
		start_of_game(s_o_g),
		first_instructions(f_i),
		first_step(f_s),
		items_first_lookout(i_f_l),
		items_instructions(i_i),
		first_enemy_meet(f_e_m),
		first_enemy_meet_second(f_e_m_s),
		enemy_instructions(e_i),
		first_enemy_killed(f_e_k),
		halfway_to_boss(h_t_b),

		first_boss(f_b),
		first_boss_killed(f_b_k)
	{}
};



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
	int str_req, end_req, dex_req, agi_req, int_req, wil_req;
	int base_rating, current_rating;


	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar  & name;
		ar  & img_path;
		ar  & size;
		ar  & type;
		ar  & weapon_handle;
		ar  & primary_multiplier;
		ar  & primary_multiplier_value;
		ar  & secondary_multiplier;
		ar  & secondary_multiplier_value;
		ar  & min_dmg & max_dmg;
		ar  & str_req & end_req & dex_req & agi_req & int_req & wil_req;
		ar  & base_rating & current_rating;
	}

	Weapon_struct(){}
	Weapon_struct(std::string _name, std::string _img_path, int _size, int _type, int _weapon_handle,
		int _primary_multiplier, int _primary_multiplier_value, int _secondary_multiplier, int _secondary_multiplier_value,
		int _min_dmg, int _max_dmg, int _base_rating, int _current_rating,
		int _str_req, int _end_req, int _dex_req, int _agi_req, int _int_req, int _wil_req)
		:
		name(_name), img_path(_img_path), size(_size), type(_type), weapon_handle(_weapon_handle),
		primary_multiplier(_primary_multiplier), primary_multiplier_value(_primary_multiplier_value), secondary_multiplier(_secondary_multiplier), secondary_multiplier_value(_secondary_multiplier_value),
		min_dmg(_min_dmg), max_dmg(_max_dmg), base_rating(_base_rating), current_rating(_current_rating),
		str_req(_str_req), end_req(_end_req), dex_req(_dex_req), agi_req(_agi_req), int_req(_int_req), wil_req(_wil_req)
	{}

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
	int str_req, dex_req, agi_req, int_req, end_req, wil_req;
	int base_rating, current_rating;


	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar  & name;
		ar  & img_path;
		ar  & armour_class;
		ar  & type;
		ar  & defence;
		ar  & dodge;
		ar  & block;
		ar  & base_rating & current_rating;
		ar  & str_req & end_req & dex_req & agi_req & int_req & wil_req;
	}


	Armour_struct(){}
	Armour_struct(std::string _name, std::string _img_path, int _armour_class, int _type, 
		int _defence, int _dodge, int _block, int _base_rating, int _current_rating,
		int _str_req, int _end_req, int _dex_req, int _agi_req, int _int_req, int _wil_req)
		:
		name(_name), img_path(_img_path), armour_class(_armour_class), type(_type), defence(_defence),
		dodge(_dodge), block(_block), base_rating(_base_rating), current_rating(_current_rating),
		str_req(_str_req), end_req(_end_req), dex_req(_dex_req), agi_req(_agi_req), int_req(_int_req), wil_req(_wil_req)
	{}
};


enum CONSUMABLE_TYPE{
	FOOD_TYPE,
	POTION_TYPE,
	PILL_TYPE
};

enum CONSUMABLE_EFFECT{
	BODY_UP,
	REFLEX_UP,
	MIND_UP,
	EXP_UP,
	HP_REGEN,
	SP_REGEN,
	REGENERATE_TICK,
	STR_UP,
	END_UP,
	DEX_UP,
	AGI_UP,
	INT_UP,
	WIL_UP
};

struct Consumable_struct{
	std::string name;
	std::string img_path;
	int type;
	int effect_type;
	int effect_strength;
	int base_rating;


	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar  & name;
		ar  & img_path;
		ar  & type;
		ar  & effect_type;
		ar  & effect_strength;
		ar  & base_rating;
	}


	Consumable_struct(){}
	Consumable_struct(std::string _name, std::string _img_path, int _type, int _effect_type, int _effect_strength, int _base_rating)
		:
		name(_name), img_path(_img_path), type(_type), effect_type(_effect_type), effect_strength(_effect_strength), base_rating(_base_rating)
	{}
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
	int block;
	int dodge;
	float damage_reduction, max_reduction, dodge_chance, max_dodge, block_chance, max_block;
	int strenght;
	int endurance;
	int agility;
	int dexterity;
	int intelligence;
	int willpower;
	int luck;
	int posx, posy;


	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar  & level;
		ar  & exp & max_exp;
		ar  & hp & max_hp;
		ar  & mp & max_mp;
		ar  & stam & max_stam;
		ar  & min_dmg & max_dmg;
		ar  & defence & block & dodge;
		ar  & damage_reduction & max_reduction & dodge_chance & max_dodge & block_chance & max_block;
		ar  & strenght;
		ar  & endurance;
		ar  & agility;
		ar  & dexterity;
		ar  & intelligence;
		ar  & willpower;
		ar  & luck;
		ar  & posx & posy;
	}


	Hero_Profile(){}
	Hero_Profile(int _level, int _exp, int _max_exp, int _hp, int _max_hp, int _mp, int _max_mp, int _stam, int _max_stam,
		int _min_dmg, int _max_dmg, int _defence, int _block, int _dodge,
		float _damage_reduction, float _max_reduction, float _dodge_chance, float _max_dodge, float _block_chance, float _max_block,
		int _str, int _end, int _agi, int _dex, int _int, int _wil, int _luck,
		int _posx, int _posy)
		:
		level(_level), exp(_exp), max_exp(_max_exp), hp(_hp), max_hp(_max_hp), mp(_mp), max_mp(_max_mp), stam(_stam), max_stam(_max_stam),
		min_dmg(_min_dmg), max_dmg(_max_dmg), defence(_defence), block(_block), dodge(_dodge),
		damage_reduction(_damage_reduction), max_reduction(_max_reduction), dodge_chance(_dodge_chance), max_dodge(_max_dodge), block_chance(_block_chance), max_block(_max_block),
		strenght(_str), intelligence(_int), endurance(_end), willpower(_wil), luck(_luck), dexterity(_dex), agility(_agi),
		posx(_posx), posy(_posy)
	{}




};

struct Hero_Ratings{
	int hero_rating;
	int weapon_rating;
	int offhand_rating;
	int head_rating;
	int torso_rating;
	int legs_rating;
	int overral_rating;


	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar  & hero_rating;
		ar  & weapon_rating;
		ar  & offhand_rating;
		ar  & head_rating;
		ar  & torso_rating;
		ar  & legs_rating;
		ar  & overral_rating;
	}


	Hero_Ratings(){}
	Hero_Ratings(int _hero_rating, int _weapon_rating, int _offhand_rating, int _head_rating, int _torso_rating, int _legs_rating, int _overral_rating)
		:
		hero_rating(_hero_rating),
		weapon_rating(_weapon_rating),
		offhand_rating(_offhand_rating),
		head_rating(_head_rating),
		torso_rating(_torso_rating),
		legs_rating(_legs_rating),
		overral_rating(_overral_rating)
	{}

};


struct Ability_Proficiencies{
	std::string name;
	int id;
	int level;
	int experience;
	int experience_needed;
	float effectiveness;

	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar  & name;
		ar  & id;
		ar  & level;
		ar  & experience;
		ar  & experience_needed;
		ar  & effectiveness;
	}


	Ability_Proficiencies(){}
	Ability_Proficiencies(std::string _name, int _id, int _level, int _exp, int _exp_needed, float _effectiveness)
		:
		name(_name), id(_id), level(_level), experience(_exp), experience_needed(_exp_needed), effectiveness(_effectiveness)
	{}


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
	bool special = false;
	int hitpoints;
	int max_hitpoints;
	int attack;
	int defence;
	int type;
	int enemy_class;
	int experience;
	int base_rating, current_rating;


	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar  & name;
		ar  & img_path;
		ar  & hitpoints;
		ar  & max_hitpoints;
		ar  & attack;
		ar  & defence;
		ar  & type;
		ar  & enemy_class;
		ar  & experience;
		ar  & base_rating & current_rating;
	}

	Enemy_Stats(){}
	Enemy_Stats(std::string _name, std::string _path, int _hp, int _max_hp, int _atk, int _def, int _type, int _enemy_class, int _exp, int _base_rating, int _current_rating)
		:
		name(_name), img_path(_path), hitpoints(_hp), max_hitpoints(_max_hp), attack(_atk), defence(_def), type(_type), enemy_class(_enemy_class),
		experience(_exp), base_rating(_base_rating), current_rating(_current_rating)
	{}

};

#endif //!STRUCTURES_AND_ENUMS

