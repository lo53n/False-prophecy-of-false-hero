#include "EnemiesLoader.h"

EnemiesLoader::EnemiesLoader(std::shared_ptr<ErrorHandler> errorHandler)
	:
	_errorHandler(errorHandler)
{
	_enemiesData.reserve(100000);
}
EnemiesLoader::~EnemiesLoader()
{

}

std::vector<Enemy_Stats>& EnemiesLoader::getEnemiesData()
{
	return _enemiesData;
}

void EnemiesLoader::prepareStruct()
{
	_errorMsg = "";


	_currentData.name = "";
	_currentData.img_path = "";

	_currentData.type = -1;

	_currentData.hitpoints = -1;
	_currentData.max_hitpoints = -1;

	_currentData.attack = -1;
	_currentData.defence = -1;

	_currentData.experience = -1;

	_enemiesCount++;
}

void EnemiesLoader::showStruct()
{
	std::cout << "Name: " << _currentData.name << std::endl;
	std::cout << "Img: " << _currentData.img_path << std::endl;

	std::cout << "Hp: " << _currentData.max_hitpoints << std::endl;
	std::cout << "Atk: " << _currentData.attack << std::endl;
	std::cout << "Def: " << _currentData.defence << std::endl;

	std::cout << "Type: " << _currentData.type << std::endl;
	std::cout << "Exp: " << _currentData.experience << std::endl;
}


std::vector<Enemy_Stats>& EnemiesLoader::getSpecialEnemiesData()
{
	_enemiesData.clear();
	prepareStruct();

	_currentData.name = "Rattling bones";
	_currentData.img_path = "data\\img\\enemy\\rb.png";
	_currentData.type = ENEMY_TYPE::UNDEAD_ENEMY;
	_currentData.hitpoints = 5;
	_currentData.max_hitpoints = 5;
	_currentData.attack = 5;
	_currentData.defence = 3;
	_currentData.experience = 10;
	_enemiesData.push_back(_currentData);

	prepareStruct();
	_currentData.name = "Blazing Ravager";
	_currentData.img_path = "data\\img\\enemy\\blazing.png";
	_currentData.type = ENEMY_TYPE::HUMAN_ENEMY;
	_currentData.hitpoints = 5000;
	_currentData.max_hitpoints = 5000;
	_currentData.attack = 500;
	_currentData.defence = 300;
	_currentData.experience = 10000;
	_enemiesData.push_back(_currentData);


	return _enemiesData;

}

void EnemiesLoader::saveStruct()
{
	bool isSuccessful = checkStructCorrectness();
	//showStruct();
	if (isSuccessful)
		_enemiesData.push_back(_currentData);
	else std::cout << "Unable to load enemy No. " << _enemiesCount << std::endl;

	prepareStruct();

}

void EnemiesLoader::loadFromFile()
{
	prepareStruct();
	std::fstream enemiesFile;
	enemiesFile.open("data/enemies.txt");


	std::string stringLine;
	while (!enemiesFile.eof()){
		getline(enemiesFile, stringLine);
		//std::cout << stringLine << std::endl;
		if (stringLine.size() == 0) continue;
		if (stringLine.size() > 6) parseLine(stringLine);
		if (stringLine == "[---]") saveStruct();
	}
	_enemiesData.shrink_to_fit();

}

void EnemiesLoader::parseLine(std::string stringLine)
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

	//for (auto string : output) std::cout << string << " ";
	//std::cout << std::endl;

}

int EnemiesLoader::checkTag(std::string tag)
{
	if (tag == "NAME") return TAGVALUE::NAME;
	if (tag == "IMG") return TAGVALUE::IMG;
	else if (tag == "HP") return TAGVALUE::HP;
	else if (tag == "ATTACK") return TAGVALUE::ATTACK;
	else if (tag == "DEFENCE") return TAGVALUE::DEFENCE;
	else if (tag == "TYPE") return TAGVALUE::TYPE;
	else if (tag == "BASE_EXP") return TAGVALUE::BASE_EXP;

	//if nothing works, surely there is problem
	return -1;
}

void EnemiesLoader::parseTag(std::vector<std::string> &output)
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
		_currentData.img_path = "data\\img\\enemy\\" + output[1];
		break;

		//parse enemy type.
	case TAGVALUE::TYPE:
		if (output[1] == "UNDEAD")
			_currentData.type = ENEMY_TYPE::UNDEAD_ENEMY;
		else if (output[1] == "DEMON")
			_currentData.type = ENEMY_TYPE::DEMON_ENEMY;
		else if (output[1] == "BEAST")
			_currentData.type = ENEMY_TYPE::BEAST_ENEMY;
		else if (output[1] == "HUMANOID")
			_currentData.type = ENEMY_TYPE::HUMANOID_ENEMY;
		else if (output[1] == "HUMAN")
			_currentData.type = ENEMY_TYPE::HUMAN_ENEMY;
		else if (output[1] == "GOLEM")
			_currentData.type = ENEMY_TYPE::GOLEM_ENEMY;
		else _currentData.type = -1;
		break;


		//parse enemy hitpoints
	case TAGVALUE::HP:
		try{
			value = std::stoi(output[1]);
		}
		catch (const std::invalid_argument&){
			value = -1;
		}
		_currentData.max_hitpoints = value;
		break;

		//parse attack power
	case TAGVALUE::ATTACK:
		try{
			value = std::stoi(output[1]);
		}
		catch (const std::invalid_argument&){
			value = -1;
		}
		_currentData.attack = value;
		break;

		//parse armour defence
	case TAGVALUE::DEFENCE:
		try{
			value = std::stoi(output[1]);
		}
		catch (const std::invalid_argument&){
			value = -1;
		}
		_currentData.defence = value;
		break;


		//parse enemy base exp
	case TAGVALUE::BASE_EXP:
		try{
			value = std::stoi(output[1]);
		}
		catch (const std::invalid_argument&){
			value = -1;
		}
		_currentData.experience = value;
		break;

	}
}

/////////////////////
//Correctness Check//
/////////////////////
bool EnemiesLoader::checkStructCorrectness()
{
	_errorMsg = "";
	std::string error;

	bool isSuccessful = true;

	//At first, let's check for abnormalities beyond repair//
	if (_currentData.name == "")  {
		_errorMsg += "\n   No name.";
		_currentData.name = "Enemy no. " + std::to_string(_enemiesCount);
	}

	if (_currentData.type == -1)    {
		_errorMsg += "\n   Invalid enemy type.";
	}
	if (_currentData.attack == -1)    {
		_errorMsg += "\n   Invalid enemy attack.";
	}
	if (_currentData.defence == -1)    {
		_errorMsg += "\n   Invalid enemy defence.";
	}
	if (_currentData.max_hitpoints == -1)    {
		_errorMsg += "\n   Invalid enemy hitpoints.";
	}
	if (_currentData.experience == -1)    {
		_errorMsg += "\n   Invalid enemy experience.";
	}


	if (!_errorMsg.empty()){
		error = "Fatal error in loading enemy " + _currentData.name + ". \nEnemy not loaded. Reasons:" + _errorMsg + "\n";
		_errorHandler->processError(error);
		return false;
	}


	//Now time to fix stuff. If unfixable, then sorry, but I don't really see no options as for now to fail.//
	//boo, none. no ideas how to correct anything here.//


	//calculate rating//
	Calculations::calculateBaseRating(_currentData);
	//std::cout << "Enemy Rating: " << _currentData.current_rating << std::endl;

	return isSuccessful;
}
//No ideas, how to correct invalid armour structure. Incorrect one will be disposed as for now.
bool EnemiesLoader::correctStruct(int tag)
{
	return true;
}