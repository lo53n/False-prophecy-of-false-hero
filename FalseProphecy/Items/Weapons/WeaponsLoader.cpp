#include "WeaponsLoader.h"

WeaponsLoader::WeaponsLoader()
{

}
WeaponsLoader::~WeaponsLoader()
{

}

void WeaponsLoader::prepareStruct()
{
	currentData.name = "";
	currentData.size = 0;
	currentData.type = 0;
	currentData.weapon_handle = 0;

	currentData.primary_multiplier = 0;
	currentData.primary_multiplier_value = 0;
	currentData.secondary_multiplier = 0;
	currentData.secondary_multiplier_value = 0;

	currentData.speed = 0;

	currentData.min_dmg = 0;
	currentData.max_dmg = 0;

	currentData.str_req = 0;
	currentData.end_req = 0;
	currentData.agi_req = 0;
	currentData.dex_req = 0;
	currentData.int_req = 0;
	currentData.wil_req = 0;
}

void WeaponsLoader::showStruct()
{

	std::cout << "Name: " << currentData.name << std::endl;
	std::cout << "Size: " << currentData.size << std::endl;
	std::cout << "Type: " << currentData.type << std::endl;
	std::cout << "Handle: " << currentData.weapon_handle << std::endl;

	std::cout << "Prim_mult: " << currentData.primary_multiplier << std::endl;
	std::cout << "Prim_mult_val: " << currentData.primary_multiplier_value << std::endl;
	std::cout << "Sec_mult: " << currentData.secondary_multiplier << std::endl;
	std::cout << "Sec_mult_val: " << currentData.secondary_multiplier_value << std::endl;

	std::cout << "Speed: " << currentData.speed << std::endl;

	std::cout << "Min dmg: " << currentData.min_dmg << std::endl;
	std::cout << "Max dmg: " << currentData.max_dmg << std::endl;

	std::cout << "Str req: " << currentData.str_req << std::endl;
	std::cout << "End req: " << currentData.end_req << std::endl;
	std::cout << "Agi req: " << currentData.agi_req << std::endl;
	std::cout << "Dex req: " << currentData.dex_req << std::endl;
	std::cout << "Int req: " << currentData.int_req << std::endl;
	std::cout << "Wil req: " << currentData.wil_req << std::endl;




}


void WeaponsLoader::loadFromFile()
{
	prepareStruct();
	std::fstream weaponsFile;
	weaponsFile.open("data/weapons.txt");

	std::string stringLine;

	while (!weaponsFile.eof()){
		getline(weaponsFile, stringLine);
		std::cout << stringLine << std::endl;
		if(stringLine.size() > 6) parseLine(stringLine);
	}
	showStruct();
}


void WeaponsLoader::parseLine(std::string stringLine)
{
	std::string delimiter = "::";

	std::string token;
	std::vector<std::string> output;
	size_t pos = 0;

	while ((pos = stringLine.find(delimiter)) != std::string::npos){

		token = stringLine.substr(0, pos);
		token.erase(0, 2);

		output.push_back(token);
		stringLine.erase(0, pos + delimiter.length());
	}
	stringLine.erase(stringLine.length() - 2, stringLine.length());
	output.push_back(stringLine);

	parseTag(output);

	//for (auto string : output) std::cout << string << std::endl;

}


void WeaponsLoader::parseTag(std::vector<std::string> &output)
{
	int tagType = checkTag(output[0]);
	int value;
	if (tagType == -1) return;

	switch (tagType){
	
	//parse name
	case TAGVALUE::NAME:
		std::cout << output[1] << std::endl;
		currentData.name = output[1];
		system("pause");
		break;
	
	//parse weapon handle
	case TAGVALUE::HANDLE:
		if (output[1] == "ONEHANDED") currentData.weapon_handle = WEAPON_HANDLE::ONEHANDED;
		else if (output[1] == "TWOHANDED") currentData.weapon_handle = WEAPON_HANDLE::TWOHANDED;
		else currentData.weapon_handle = -1;
		break;
	
	//parse weapon type
	case TAGVALUE::TYPE:
		if (output[1] == "SWORD") currentData.type = WEAPON_TYPE::SWORD;
		else if (output[1] == "AXE") currentData.type = WEAPON_TYPE::AXE;
		else if (output[1] == "MACE") currentData.type = WEAPON_TYPE::MACE;
		else if (output[1] == "SPEAR") currentData.type = WEAPON_TYPE::SPEAR;
		else currentData.type = -1;
		break;
	
	//parse weapon size
	case TAGVALUE::SIZE:
		if (output[1] == "SMALL") currentData.size = WEAPON_SIZE::SMALL;
		else if (output[1] == "MEDIUM") currentData.size = WEAPON_SIZE::MEDIUM;
		else if (output[1] == "LARGE") currentData.size = WEAPON_SIZE::LARGE;
		else currentData.size = -1;
		break;

	//parse weapon damage primary multiplier
	case TAGVALUE::PRIMARY_MULTIPLIER:
		if (output[1] == "STR") currentData.primary_multiplier = HERO_STATS_NAMES::STRENGTH;
		else if (output[1] == "END") currentData.primary_multiplier = HERO_STATS_NAMES::ENDURANCE;
		else if (output[1] == "AGI") currentData.primary_multiplier = HERO_STATS_NAMES::AGILITY;
		else if (output[1] == "DEX") currentData.primary_multiplier = HERO_STATS_NAMES::DEXTERITY;
		else if (output[1] == "INT") currentData.primary_multiplier = HERO_STATS_NAMES::INTELLIGENCE;
		else if (output[1] == "WIL") currentData.primary_multiplier = HERO_STATS_NAMES::WILLPOWER;
		else currentData.primary_multiplier = -1;
		break;
	
	//parse weapon damage primary multiplier value
	case TAGVALUE::PRIMARY_MULTIPLIER_VALUE:
		value = std::stoi(output[1]);
		currentData.primary_multiplier_value = value;
		break;
	//parse weapon damage secondary multiplier
	case TAGVALUE::SECONDARY_MULTIPLIER:
		if (output[1] == "STR") currentData.secondary_multiplier = HERO_STATS_NAMES::STRENGTH;
		else if (output[1] == "END") currentData.secondary_multiplier = HERO_STATS_NAMES::ENDURANCE;
		else if (output[1] == "AGI") currentData.secondary_multiplier = HERO_STATS_NAMES::AGILITY;
		else if (output[1] == "DEX") currentData.secondary_multiplier = HERO_STATS_NAMES::DEXTERITY;
		else if (output[1] == "INT") currentData.secondary_multiplier = HERO_STATS_NAMES::INTELLIGENCE;
		else if (output[1] == "WIL") currentData.secondary_multiplier = HERO_STATS_NAMES::WILLPOWER;
		else currentData.primary_multiplier = -1;
		break;

	//parse weapon damage secondary multiplier value
	case TAGVALUE::SECONDARY_MULTIPLIER_VALUE:
		value = std::stoi(output[1]);
		currentData.secondary_multiplier_value = value;
		break;

	//parse weapon speed
	case TAGVALUE::SPEED:
		value = std::stoi(output[1]);
		currentData.speed = value;
		break;

	//parse weapon min - max dmg

	case TAGVALUE::MIN_DMG:
		value = std::stoi(output[1]);
		currentData.min_dmg = value;
		break;

	case TAGVALUE::MAX_DMG:
		value = std::stoi(output[1]);
		currentData.max_dmg = value;
		break;

	//parse weapon requirement

	case TAGVALUE::STR_REQ:
		value = std::stoi(output[1]);
		currentData.str_req = value;
		break;

	case TAGVALUE::END_REQ:
		value = std::stoi(output[1]);
		currentData.end_req = value;
		break;

	case TAGVALUE::AGI_REQ:
		value = std::stoi(output[1]);
		currentData.agi_req = value;
		break;

	case TAGVALUE::DEX_REQ:
		value = std::stoi(output[1]);
		currentData.dex_req = value;
		break;

	case TAGVALUE::INT_REQ:
		value = std::stoi(output[1]);
		currentData.int_req = value;
		break;

	case TAGVALUE::WIL_REQ:
		value = std::stoi(output[1]);
		currentData.wil_req = value;
		break;

	default: return;
	}
}


int WeaponsLoader::checkTag(std::string tag)
{
	if (tag == "NAME") return TAGVALUE::NAME;
	else if (tag == "HANDLE") return TAGVALUE::HANDLE;
	else if (tag == "SIZE") return TAGVALUE::SIZE;
	else if (tag == "TYPE") return TAGVALUE::TYPE;
	else if (tag == "PRIMARY_MULTIPLIER") return TAGVALUE::PRIMARY_MULTIPLIER;
	else if (tag == "PRIMARY_MULTIPLIER_VALUE") return TAGVALUE::PRIMARY_MULTIPLIER_VALUE;
	else if (tag == "SECONDARY_MULTIPLIER") return TAGVALUE::SECONDARY_MULTIPLIER;
	else if (tag == "SECONDARY_MULTIPLIER_VALUE") return TAGVALUE::SECONDARY_MULTIPLIER_VALUE;
	else if (tag == "SPEED") return TAGVALUE::SPEED;
	else if (tag == "MIN_DMG") return TAGVALUE::MIN_DMG;
	else if (tag == "MAX_DMG") return TAGVALUE::MAX_DMG;
	else if (tag == "STR_REQ") return TAGVALUE::STR_REQ;
	else if (tag == "END_REQ") return TAGVALUE::END_REQ;
	else if (tag == "AGI_REQ") return TAGVALUE::AGI_REQ;
	else if (tag == "DEX_REQ") return TAGVALUE::DEX_REQ;
	else if (tag == "INT_REQ") return TAGVALUE::INT_REQ;
	else if (tag == "WIL_REQ") return TAGVALUE::WIL_REQ;

	//if nothing works, surely there is problem
	return -1;
}