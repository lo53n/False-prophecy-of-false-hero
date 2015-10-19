#include "WeaponsLoader.h"

WeaponsLoader::WeaponsLoader(std::shared_ptr<ErrorHandler> errorHandler)
	:
	_errorHandler(errorHandler)
{
	_weaponsData.reserve(100000);
}
WeaponsLoader::~WeaponsLoader()
{

}

void WeaponsLoader::prepareStruct()
{

	_currentData.name = "";
	_currentData.size = -1;
	_currentData.type = -1;
	_currentData.weapon_handle = -1;

	_currentData.isMagic = false;
	_currentData.primary_multiplier = -1;
	_currentData.primary_multiplier_value = -1;
	_currentData.secondary_multiplier = -1;
	_currentData.secondary_multiplier_value = -1;

	_currentData.speed = -1;

	_currentData.min_dmg = -1;
	_currentData.max_dmg = -1;

	_currentData.str_req = 0;
	_currentData.end_req = 0;
	_currentData.agi_req = 0;
	_currentData.dex_req = 0;
	_currentData.int_req = 0;
	_currentData.wil_req = 0;

	_weaponCount++;
}

void WeaponsLoader::showStruct()
{

	std::cout << "Name: " << _currentData.name << std::endl;
	std::cout << "Img: " << _currentData.img_path << std::endl;
	std::cout << "Size: " << _currentData.size << std::endl;
	std::cout << "Type: " << _currentData.type << std::endl;
	std::cout << "Handle: " << _currentData.weapon_handle << std::endl;

	std::cout << "isMagic?: " << _currentData.isMagic << std::endl;
	std::cout << "Prim_mult: " << _currentData.primary_multiplier << std::endl;
	std::cout << "Prim_mult_val: " << _currentData.primary_multiplier_value << std::endl;
	std::cout << "Sec_mult: " << _currentData.secondary_multiplier << std::endl;
	std::cout << "Sec_mult_val: " << _currentData.secondary_multiplier_value << std::endl;

	std::cout << "Speed: " << _currentData.speed << std::endl;

	std::cout << "Min dmg: " << _currentData.min_dmg << std::endl;
	std::cout << "Max dmg: " << _currentData.max_dmg << std::endl;

	std::cout << "Str req: " << _currentData.str_req << std::endl;
	std::cout << "End req: " << _currentData.end_req << std::endl;
	std::cout << "Agi req: " << _currentData.agi_req << std::endl;
	std::cout << "Dex req: " << _currentData.dex_req << std::endl;
	std::cout << "Int req: " << _currentData.int_req << std::endl;
	std::cout << "Wil req: " << _currentData.wil_req << std::endl;




}

void WeaponsLoader::saveStruct()
{
	bool isSuccessful = checkStructCorrectness();
	//showStruct();
	if (isSuccessful)
		_weaponsData.push_back(_currentData);
	else std::cout << "Unable to load weapon No. " << _weaponCount << std::endl;
	prepareStruct();
}

void WeaponsLoader::loadFromFile()
{
	prepareStruct();
	std::fstream weaponsFile;
	weaponsFile.open("data/weapons.txt");


	std::string stringLine;
	while (!weaponsFile.eof()){
		getline(weaponsFile, stringLine);
		//std::cout << stringLine << std::endl;
		if (stringLine.size() == 0) continue;
		if (stringLine.size() > 6) parseLine(stringLine);
		if (stringLine == "[---]") saveStruct();
	}
	ItemsHolder *_itemsHolder = &ItemsHolder::getItemsHolder();
	_weaponsData.shrink_to_fit();
	_itemsHolder->setData(_weaponsData);
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
		_currentData.name = output[1];
		break;
	
	//parse texture location
	case TAGVALUE::IMG:
		_currentData.img_path = "data\\img\\weapon\\" + output[1];
		break;

	//parse weapon handle
	case TAGVALUE::HANDLE:
		if (output[1] == "ONEHANDED")
			_currentData.weapon_handle = WEAPON_HANDLE::ONEHANDED;
		else if (output[1] == "TWOHANDED")
			_currentData.weapon_handle = WEAPON_HANDLE::TWOHANDED;
		else _currentData.weapon_handle = -1;
		break;
	
	//parse weapon type
	case TAGVALUE::TYPE:
		if (output[1] == "SWORD") 
			_currentData.type = WEAPON_TYPE::SWORD;
		else if (output[1] == "AXE") 
			_currentData.type = WEAPON_TYPE::AXE;
		else if (output[1] == "MACE")
			_currentData.type = WEAPON_TYPE::MACE;
		else if (output[1] == "SPEAR")
			_currentData.type = WEAPON_TYPE::SPEAR;
		else _currentData.type = -1;
		break;
	
	//parse weapon size
	case TAGVALUE::SIZE:
		if (output[1] == "SMALL") 
			_currentData.size = WEAPON_SIZE::SMALL;
		else if (output[1] == "MEDIUM")
			_currentData.size = WEAPON_SIZE::MEDIUM;
		else if (output[1] == "LARGE")
			_currentData.size = WEAPON_SIZE::LARGE;
		else _currentData.size = -1;
		break;

	//parse weapon damage primary multiplier
	case TAGVALUE::PRIMARY_MULTIPLIER:
		if (output[1] == "STR") 
			_currentData.primary_multiplier = HERO_STATS_NAMES::STRENGTH;

		else if (output[1] == "END") 
			_currentData.primary_multiplier = HERO_STATS_NAMES::ENDURANCE;

		else if (output[1] == "AGI") 
			_currentData.primary_multiplier = HERO_STATS_NAMES::AGILITY;

		else if (output[1] == "DEX") 
			_currentData.primary_multiplier = HERO_STATS_NAMES::DEXTERITY;

		else if (output[1] == "INT") {
			_currentData.primary_multiplier = HERO_STATS_NAMES::INTELLIGENCE;
			_currentData.isMagic = true;
		}
		else if (output[1] == "WIL") {
			_currentData.primary_multiplier = HERO_STATS_NAMES::WILLPOWER;
			_currentData.isMagic = true;
		}

		else _currentData.primary_multiplier = -1;

		break;
	
	//parse weapon damage primary multiplier value
	case TAGVALUE::PRIMARY_MULTIPLIER_VALUE:
		try{
			value = std::stoi(output[1]);
		}
		catch (const std::invalid_argument&){
			value = -1;
		}
		_currentData.primary_multiplier_value = value;
		break;
	//parse weapon damage secondary multiplier
	case TAGVALUE::SECONDARY_MULTIPLIER:
		if (output[1] == "STR") 
			_currentData.secondary_multiplier = HERO_STATS_NAMES::STRENGTH;

		else if (output[1] == "END") 
			_currentData.secondary_multiplier = HERO_STATS_NAMES::ENDURANCE;

		else if (output[1] == "AGI") 
			_currentData.secondary_multiplier = HERO_STATS_NAMES::AGILITY;

		else if (output[1] == "DEX") 
			_currentData.secondary_multiplier = HERO_STATS_NAMES::DEXTERITY;

		else if (output[1] == "INT") {
			_currentData.secondary_multiplier = HERO_STATS_NAMES::INTELLIGENCE;

			_currentData.isMagic = true;
		}
		else if (output[1] == "WIL") {
			_currentData.secondary_multiplier = HERO_STATS_NAMES::WILLPOWER;
			_currentData.isMagic = true;
		}

		else _currentData.primary_multiplier = -1;
		break;

	//parse weapon damage secondary multiplier value
	case TAGVALUE::SECONDARY_MULTIPLIER_VALUE:
		try{
			value = std::stoi(output[1]);
		}
		catch (const std::invalid_argument&){
			value = -1;
		}
		_currentData.secondary_multiplier_value = value;
		break;

	//parse weapon speed
	case TAGVALUE::SPEED:
		try{
			value = std::stoi(output[1]);
		}
		catch (const std::invalid_argument&){
			value = -1;
		}
		_currentData.speed = value;
		break;

	//parse weapon min - max dmg

	case TAGVALUE::MIN_DMG:
		try{
			value = std::stoi(output[1]);
		}
		catch (const std::invalid_argument&){
			value = -1;
		}
		_currentData.min_dmg = value;
		break;

	case TAGVALUE::MAX_DMG:
		try{
			value = std::stoi(output[1]);
		}
		catch (const std::invalid_argument&){
			value = -1;
		}
		_currentData.max_dmg = value;
		break;

	//parse weapon requirement

	case TAGVALUE::STR_REQ:
		try{
			value = std::stoi(output[1]);
		}
		catch (const std::invalid_argument&){
			value = -1;
		}
		_currentData.str_req = value;
		break;

	case TAGVALUE::END_REQ:
		try{
			value = std::stoi(output[1]);
		}
		catch (const std::invalid_argument&){
			value = -1;
		}
		_currentData.end_req = value;
		break;

	case TAGVALUE::AGI_REQ:
		try{
			value = std::stoi(output[1]);
		}
		catch (const std::invalid_argument&){
			value = -1;
		}
		_currentData.agi_req = value;
		break;

	case TAGVALUE::DEX_REQ:
		try{
			value = std::stoi(output[1]);
		}
		catch (const std::invalid_argument&){
			value = -1;
		}
		_currentData.dex_req = value;
		break;

	case TAGVALUE::INT_REQ:
		try{
			value = std::stoi(output[1]);
		}
		catch (const std::invalid_argument&){
			value = -1;
		}
		_currentData.int_req = value;
		break;

	case TAGVALUE::WIL_REQ:
		try{
			value = std::stoi(output[1]);
		}
		catch (const std::invalid_argument&){
			value = -1;
		}
		_currentData.wil_req = value;
		break;

	default: return;
	}
}


int WeaponsLoader::checkTag(std::string tag)
{
	if (tag == "NAME") return TAGVALUE::NAME;
	if (tag == "IMG") return TAGVALUE::IMG;
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

/////////////////////
//Correctness Check//
/////////////////////
bool WeaponsLoader::checkStructCorrectness()
{

	_errorMsg = "";
	std::string error;

	bool isSuccessful = true;
	bool isFatal = false;

	//At first, let's check for abnormalities beyond repair//
	if (_currentData.name == "") {
		_errorMsg += "\n   No name.";
		_currentData.name = "Weapon no. " + std::to_string(_weaponCount);
	}

	if (_currentData.size == -1 && _currentData.weapon_handle == -1)  {
		_errorMsg += "\n   Invalid weapon size and handle.";
	}

	if (_currentData.speed == -1) {
		_errorMsg += "\n   Invalid weapon speed.";
	}
	if (_currentData.min_dmg == -1 || _currentData.max_dmg == -1) {
		_errorMsg += "\n   Invalid damage range.";
	}

	//compile fatal error message
	if (!_errorMsg.empty()){
		error = "Fatal error in loading weapon " + _currentData.name + ". \nWeapon not loaded. Reasons:" + _errorMsg + "\n";
		_errorMsg = "";
		isFatal = true;
	}

	//Now time to fix stuff. If unfixable, then sorry, but I don't really see no options as for now to fail.//
	if (_currentData.type == -1){
		isSuccessful = correctStruct(TAGVALUE::TYPE);
		if (!isSuccessful) return false;
	}
	if (_currentData.size == -1){
		isSuccessful = correctStruct(TAGVALUE::SIZE);
		if (!isSuccessful) return false;
	}
	if (_currentData.weapon_handle == -1){
		isSuccessful = correctStruct(TAGVALUE::HANDLE);
		if (!isSuccessful) return false;
	}
	if (_currentData.primary_multiplier == -1){
		isSuccessful = correctStruct(TAGVALUE::PRIMARY_MULTIPLIER);
		if (!isSuccessful) return false;
	}


	//send error message
	if (!_errorMsg.empty() || isFatal){
		error += "Error in loading weapon " + _currentData.name + ":"+ _errorMsg;
		_errorHandler->processError(error);
		if (isFatal) return false;
	}


	return isSuccessful;
}

//////////////////////////
//Correct data if needed//
//////////////////////////

bool WeaponsLoader::correctStruct(int tag)
{
	bool isSuccess = true;

	switch (tag){

		//fix weapon multipliers
	case TAGVALUE::PRIMARY_MULTIPLIER:

		_errorMsg += "\n   Invalid primary multiplier, correction based on other stats.";

		//std::cout << "Correcting weapon scheme No. " << _weaponCount << " primary multipliers." << std::endl;
		//check for weapon handle
		switch (_currentData.weapon_handle){
		case WEAPON_HANDLE::ONEHANDED:
			if (_currentData.size == WEAPON_SIZE::LARGE) _currentData.size = WEAPON_SIZE::MEDIUM;
			//check for weapon type
			switch (_currentData.type){
			case WEAPON_TYPE::AXE:
				//check for weapon size
				switch (_currentData.size){
				case WEAPON_SIZE::SMALL:
					_currentData.primary_multiplier = HERO_STATS_NAMES::AGILITY;
					_currentData.primary_multiplier_value = rand() % (__UPPER_LIMIT_TO_COMPUTE_MULTIPLIERS__ / _currentData.speed) + __BASE_PRIMARY_ONEHANDED_MULTIPLIER__;
					_currentData.secondary_multiplier = HERO_STATS_NAMES::DEXTERITY;
					_currentData.secondary_multiplier_value = rand() % (__UPPER_LIMIT_TO_COMPUTE_MULTIPLIERS__ / (_currentData.speed * 2)) + __BASE_SECONDARY_ONEHANDED_MULTIPLIER__;
					break;
				case WEAPON_SIZE::MEDIUM:
					_currentData.primary_multiplier = HERO_STATS_NAMES::STRENGTH;
					_currentData.primary_multiplier_value = rand() % (__UPPER_LIMIT_TO_COMPUTE_MULTIPLIERS__ / _currentData.speed) + __BASE_PRIMARY_ONEHANDED_MULTIPLIER__;
					_currentData.secondary_multiplier = HERO_STATS_NAMES::AGILITY;
					_currentData.secondary_multiplier_value = rand() % (__UPPER_LIMIT_TO_COMPUTE_MULTIPLIERS__ / (_currentData.speed * 2)) + __BASE_SECONDARY_ONEHANDED_MULTIPLIER__;
					break;
				}
				break;
			case WEAPON_TYPE::MACE:
				//check for weapon size
				switch (_currentData.size){
				case WEAPON_SIZE::SMALL:
					_currentData.primary_multiplier = HERO_STATS_NAMES::STRENGTH;
					_currentData.primary_multiplier_value = (int)((rand() % (__UPPER_LIMIT_TO_COMPUTE_MULTIPLIERS__ / _currentData.speed)) * 1.5f) + __BASE_PRIMARY_ONEHANDED_MULTIPLIER__;
					_currentData.secondary_multiplier = -1;
					_currentData.secondary_multiplier_value = -1;
					break;
				case WEAPON_SIZE::MEDIUM:
					_currentData.primary_multiplier = HERO_STATS_NAMES::STRENGTH;
					_currentData.primary_multiplier_value = rand() % (__UPPER_LIMIT_TO_COMPUTE_MULTIPLIERS__ / _currentData.speed + __BASE_PRIMARY_ONEHANDED_MULTIPLIER__);
					_currentData.secondary_multiplier = HERO_STATS_NAMES::ENDURANCE;
					_currentData.secondary_multiplier_value = rand() % (__UPPER_LIMIT_TO_COMPUTE_MULTIPLIERS__ / (_currentData.speed * 2)) + __BASE_SECONDARY_ONEHANDED_MULTIPLIER__;
					break;
				}
				break;
			case WEAPON_TYPE::SPEAR:
				//check for weapon size
				switch (_currentData.size){
				case WEAPON_SIZE::SMALL:
					_currentData.primary_multiplier = HERO_STATS_NAMES::AGILITY;
					_currentData.primary_multiplier_value = rand() % (__UPPER_LIMIT_TO_COMPUTE_MULTIPLIERS__ / _currentData.speed) + __BASE_PRIMARY_ONEHANDED_MULTIPLIER__;
					_currentData.secondary_multiplier = HERO_STATS_NAMES::DEXTERITY;
					_currentData.secondary_multiplier_value = rand() % (__UPPER_LIMIT_TO_COMPUTE_MULTIPLIERS__ / (_currentData.speed * 2)) + __BASE_SECONDARY_ONEHANDED_MULTIPLIER__;
					break;
				case WEAPON_SIZE::MEDIUM:
					_currentData.primary_multiplier = HERO_STATS_NAMES::AGILITY;
					_currentData.primary_multiplier_value = rand() % (__UPPER_LIMIT_TO_COMPUTE_MULTIPLIERS__ / _currentData.speed) + __BASE_PRIMARY_ONEHANDED_MULTIPLIER__;
					_currentData.secondary_multiplier = HERO_STATS_NAMES::DEXTERITY;
					_currentData.secondary_multiplier_value = rand() % (__UPPER_LIMIT_TO_COMPUTE_MULTIPLIERS__ / (_currentData.speed * 2)) + __BASE_SECONDARY_ONEHANDED_MULTIPLIER__;
					break;
				}
				break;
			case WEAPON_TYPE::SWORD:
				//check for weapon size
				switch (_currentData.size){
				case WEAPON_SIZE::SMALL:
					_currentData.primary_multiplier = HERO_STATS_NAMES::AGILITY;
					_currentData.primary_multiplier_value = rand() % (int)(__UPPER_LIMIT_TO_COMPUTE_MULTIPLIERS__ / (_currentData.speed * 0.75f)) + __BASE_PRIMARY_ONEHANDED_MULTIPLIER__;
					_currentData.secondary_multiplier = HERO_STATS_NAMES::DEXTERITY;
					_currentData.secondary_multiplier_value = rand() % (int)(__UPPER_LIMIT_TO_COMPUTE_MULTIPLIERS__ / (_currentData.speed * 0.75f)) + __BASE_SECONDARY_ONEHANDED_MULTIPLIER__;
					break;
				case WEAPON_SIZE::MEDIUM:
					_currentData.primary_multiplier = HERO_STATS_NAMES::AGILITY;
					_currentData.primary_multiplier_value = rand() % (int)(__UPPER_LIMIT_TO_COMPUTE_MULTIPLIERS__ / (_currentData.speed * 0.6f)) + __BASE_PRIMARY_ONEHANDED_MULTIPLIER__;
					_currentData.secondary_multiplier = HERO_STATS_NAMES::STRENGTH;
					_currentData.secondary_multiplier_value = rand() % (int)(__UPPER_LIMIT_TO_COMPUTE_MULTIPLIERS__ / (_currentData.speed * 1.4f)) + __BASE_SECONDARY_ONEHANDED_MULTIPLIER__;
					break;
				}
				break;
			}
			break;
		case WEAPON_HANDLE::TWOHANDED:
			if (_currentData.size == WEAPON_SIZE::SMALL) _currentData.size = WEAPON_SIZE::MEDIUM;
			//check for weapon type
			switch (_currentData.type){
			case WEAPON_TYPE::AXE:
				//check for weapon size
				switch (_currentData.size){
				case WEAPON_SIZE::MEDIUM:
					_currentData.primary_multiplier = HERO_STATS_NAMES::STRENGTH;
					_currentData.primary_multiplier_value = rand() % (__UPPER_LIMIT_TO_COMPUTE_MULTIPLIERS__ / _currentData.speed) + __BASE_PRIMARY_TWOHANDED_MULTIPLIER__;
					_currentData.secondary_multiplier = HERO_STATS_NAMES::AGILITY;
					_currentData.secondary_multiplier_value = rand() % (int)(__UPPER_LIMIT_TO_COMPUTE_MULTIPLIERS__ / (_currentData.speed * 2.25f)) + __BASE_SECONDARY_TWOHANDED_MULTIPLIER__;
					break;
				case WEAPON_SIZE::LARGE:
					_currentData.primary_multiplier = HERO_STATS_NAMES::STRENGTH;
					_currentData.primary_multiplier_value = rand() % (__UPPER_LIMIT_TO_COMPUTE_MULTIPLIERS__ / _currentData.speed) + __BASE_PRIMARY_TWOHANDED_MULTIPLIER__;
					_currentData.secondary_multiplier = HERO_STATS_NAMES::ENDURANCE;
					_currentData.secondary_multiplier_value = rand() % (__UPPER_LIMIT_TO_COMPUTE_MULTIPLIERS__ / (_currentData.speed * 2)) + __BASE_SECONDARY_TWOHANDED_MULTIPLIER__;
					break;
				}
				break;
			case WEAPON_TYPE::MACE:
				//check for weapon size
				switch (_currentData.size){
				case WEAPON_SIZE::MEDIUM:
					_currentData.primary_multiplier = HERO_STATS_NAMES::STRENGTH;
					_currentData.primary_multiplier_value = (int)((rand() % (__UPPER_LIMIT_TO_COMPUTE_MULTIPLIERS__ / _currentData.speed)) * 0.5f) + __BASE_PRIMARY_TWOHANDED_MULTIPLIER__;
					_currentData.secondary_multiplier = HERO_STATS_NAMES::ENDURANCE;
					_currentData.secondary_multiplier_value = rand() % (__UPPER_LIMIT_TO_COMPUTE_MULTIPLIERS__ / _currentData.speed) + __BASE_SECONDARY_TWOHANDED_MULTIPLIER__;
					break;
				case WEAPON_SIZE::LARGE:
					_currentData.primary_multiplier = HERO_STATS_NAMES::ENDURANCE;
					_currentData.primary_multiplier_value = rand() % (int)(__UPPER_LIMIT_TO_COMPUTE_MULTIPLIERS__ / (_currentData.speed * 1.25f)) + __BASE_PRIMARY_TWOHANDED_MULTIPLIER__;
					_currentData.secondary_multiplier = HERO_STATS_NAMES::STRENGTH;
					_currentData.secondary_multiplier_value = rand() % (int)(__UPPER_LIMIT_TO_COMPUTE_MULTIPLIERS__ / (_currentData.speed * 1.25f)) + __BASE_SECONDARY_TWOHANDED_MULTIPLIER__;
					break;
				}
				break;
			case WEAPON_TYPE::SPEAR:
				//check for weapon size
				switch (_currentData.size){
				case WEAPON_SIZE::MEDIUM:
					_currentData.primary_multiplier = HERO_STATS_NAMES::AGILITY;
					_currentData.primary_multiplier_value = rand() % (int)(__UPPER_LIMIT_TO_COMPUTE_MULTIPLIERS__ / (_currentData.speed * 1.25f)) + __BASE_PRIMARY_TWOHANDED_MULTIPLIER__;
					_currentData.secondary_multiplier = HERO_STATS_NAMES::DEXTERITY;
					_currentData.secondary_multiplier_value = rand() % (int)(__UPPER_LIMIT_TO_COMPUTE_MULTIPLIERS__ / (_currentData.speed * 1.25f)) + __BASE_SECONDARY_TWOHANDED_MULTIPLIER__;
					break;
				case WEAPON_SIZE::LARGE:
					_currentData.primary_multiplier = HERO_STATS_NAMES::STRENGTH;
					_currentData.primary_multiplier_value = rand() % (__UPPER_LIMIT_TO_COMPUTE_MULTIPLIERS__ / _currentData.speed) + __BASE_PRIMARY_TWOHANDED_MULTIPLIER__;
					_currentData.secondary_multiplier = HERO_STATS_NAMES::AGILITY;
					_currentData.secondary_multiplier_value = rand() % (__UPPER_LIMIT_TO_COMPUTE_MULTIPLIERS__ / (_currentData.speed * 2)) + __BASE_SECONDARY_TWOHANDED_MULTIPLIER__;
					break;
				}
				break;
			case WEAPON_TYPE::SWORD:
				//check for weapon size
				switch (_currentData.size){
				case WEAPON_SIZE::MEDIUM:
					_currentData.primary_multiplier = HERO_STATS_NAMES::DEXTERITY;
					_currentData.primary_multiplier_value = rand() % (int)(__UPPER_LIMIT_TO_COMPUTE_MULTIPLIERS__ / (_currentData.speed * 0.9f)) + __BASE_PRIMARY_TWOHANDED_MULTIPLIER__;
					_currentData.secondary_multiplier = HERO_STATS_NAMES::STRENGTH;
					_currentData.secondary_multiplier_value = rand() % (int)(__UPPER_LIMIT_TO_COMPUTE_MULTIPLIERS__ / (_currentData.speed * 0.9f)) + __BASE_SECONDARY_TWOHANDED_MULTIPLIER__;
					break;
				case WEAPON_SIZE::LARGE:
					_currentData.primary_multiplier = HERO_STATS_NAMES::STRENGTH;
					_currentData.primary_multiplier_value = rand() % (int)(__UPPER_LIMIT_TO_COMPUTE_MULTIPLIERS__ / (_currentData.speed * 0.6f)) + __BASE_PRIMARY_TWOHANDED_MULTIPLIER__;
					_currentData.secondary_multiplier = HERO_STATS_NAMES::DEXTERITY;
					_currentData.secondary_multiplier_value = rand() % (int)(__UPPER_LIMIT_TO_COMPUTE_MULTIPLIERS__ / (_currentData.speed * 1.4f)) + __BASE_SECONDARY_TWOHANDED_MULTIPLIER__;
					break;
				}
				break;
			}
			break;
		}
		break;

		case TAGVALUE::SIZE:

			_errorMsg += "\n   Invalid weapon size, correction based on other stats.";

			//std::cout << "Correcting weapon scheme No. " << _weaponCount << " weapon size." << std::endl;
			int newSize;

			switch (_currentData.weapon_handle){
			case WEAPON_HANDLE::ONEHANDED:
				newSize = rand() % 3;
				if (newSize == 2) _currentData.size = WEAPON_SIZE::MEDIUM;
				else _currentData.size = WEAPON_SIZE::SMALL;
				break;
			case WEAPON_HANDLE::TWOHANDED:
				newSize = rand() % 3;
				if (newSize == 2) _currentData.size = WEAPON_SIZE::MEDIUM;
				else _currentData.size = WEAPON_SIZE::LARGE;
				break;
			}
			break;

		case TAGVALUE::HANDLE:

			_errorMsg += "\n   Invalid weapon handling, correction based on other stats.";

			//std::cout << "Correcting weapon scheme No. " << _weaponCount << " weapon handle." << std::endl;
			int newHandle;

			switch (_currentData.size){
			case WEAPON_SIZE::SMALL:
				_currentData.weapon_handle = WEAPON_HANDLE::ONEHANDED;
				break;
			case WEAPON_SIZE::MEDIUM:
				newHandle = rand() % 2;
				if (newHandle == 0) _currentData.weapon_handle = WEAPON_HANDLE::ONEHANDED;
				else _currentData.weapon_handle = WEAPON_HANDLE::TWOHANDED;
				break;
			case WEAPON_SIZE::LARGE:
				_currentData.weapon_handle = WEAPON_HANDLE::TWOHANDED;
				break;
			}
			break;

		case TAGVALUE::TYPE:
			_errorMsg += "\n   Invalid weapon type, chosen radomly.";
			//std::cout << "Correcting weapon scheme No. " << _weaponCount << " weapon type." << std::endl;
			int newType;
			newType = rand() % 4;
			_currentData.type = newType;
			break;
	}
	//showStruct();
	return isSuccess;
}