#include "ArmoursLoader.h"
ArmoursLoader::ArmoursLoader(std::shared_ptr<ErrorHandler> errorHandler)
	:
	_errorHandler(errorHandler)
{
	_armoursData.reserve(100000);
}

ArmoursLoader::~ArmoursLoader()
{

}

std::vector<Armour_struct>& ArmoursLoader::getArmoursData()
{
	return _armoursData;
}

void ArmoursLoader::prepareStruct()
{
	_errorMsg = "";

	_currentData.name = "";
	_currentData.type = -1;
	_currentData.armour_class = -1;

	_currentData.isMagic = false;

	_currentData.defence = -1;
	_currentData.dodge = -1;
	_currentData.block = -1;
	_currentData.speed = -1;


	_currentData.str_req = 0;
	_currentData.end_req = 0;
	_currentData.agi_req = 0;
	_currentData.dex_req = 0;
	_currentData.int_req = 0;
	_currentData.wil_req = 0;

	_armourCount++;
}

void ArmoursLoader::showStruct()
{

	std::cout << "Name: " << _currentData.name << std::endl;
	std::cout << "Img: " << _currentData.img_path << std::endl;
	std::cout << "Type: " << _currentData.type << std::endl;
	std::cout << "Class: " << _currentData.armour_class << std::endl;

	std::cout << "isMagic?: " << _currentData.isMagic << std::endl;

	std::cout << "Speed: " << _currentData.speed << std::endl;

	std::cout << "Str req: " << _currentData.str_req << std::endl;
	std::cout << "End req: " << _currentData.end_req << std::endl;
	std::cout << "Agi req: " << _currentData.agi_req << std::endl;
	std::cout << "Dex req: " << _currentData.dex_req << std::endl;
	std::cout << "Int req: " << _currentData.int_req << std::endl;
	std::cout << "Wil req: " << _currentData.wil_req << std::endl;

}

void ArmoursLoader::saveStruct()
{
	bool isSuccessful  = checkStructCorrectness();
	//showStruct();
	if (isSuccessful)
		_armoursData.push_back(_currentData);
	else std::cout << "Unable to load armour No. " << _armourCount << std::endl;
	prepareStruct();
}
void ArmoursLoader::loadFromFile()
{
	prepareStruct();
	std::fstream armoursFile;
	armoursFile.open("data/armours.txt");


	std::string stringLine;
	while (!armoursFile.eof()){
		getline(armoursFile, stringLine);
		//std::cout << stringLine << std::endl;
		if (stringLine.size() == 0) continue;
		if (stringLine.size() > 6) parseLine(stringLine);
		if (stringLine == "[---]") saveStruct();
	}
	_armoursData.shrink_to_fit();

}

void ArmoursLoader::parseLine(std::string stringLine)
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
int ArmoursLoader::checkTag(std::string tag)
{
	if (tag == "NAME") return TAGVALUE::NAME;
	if (tag == "IMG") return TAGVALUE::IMG;
	else if (tag == "CLASS") return TAGVALUE::CLASS;
	else if (tag == "TYPE") return TAGVALUE::TYPE;
	else if (tag == "SPEED") return TAGVALUE::SPEED;
	else if (tag == "DEFENCE") return TAGVALUE::DEFENCE;
	else if (tag == "DODGE") return TAGVALUE::DODGE;
	else if (tag == "BLOCK") return TAGVALUE::BLOCK;
	else if (tag == "STR_REQ") return TAGVALUE::STR_REQ;
	else if (tag == "END_REQ") return TAGVALUE::END_REQ;
	else if (tag == "AGI_REQ") return TAGVALUE::AGI_REQ;
	else if (tag == "DEX_REQ") return TAGVALUE::DEX_REQ;
	else if (tag == "INT_REQ") return TAGVALUE::INT_REQ;
	else if (tag == "WIL_REQ") return TAGVALUE::WIL_REQ;

	//if nothing works, surely there is problem
	return -1;
}

void ArmoursLoader::parseTag(std::vector<std::string> &output)
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
		_currentData.img_path = "data\\img\\armour\\" + output[1];
		break;

		//parse armour class
	case TAGVALUE::CLASS:
		if (output[1] == "CLOTH")
			_currentData.armour_class = ARMOUR_CLASS::CLOTH;
		else if (output[1] == "LEATHER")
			_currentData.armour_class = ARMOUR_CLASS::LEATHER;
		else if (output[1] == "METAL")
			_currentData.armour_class = ARMOUR_CLASS::METAL;
		else if (output[1] == "LIGHT")
			_currentData.armour_class = ARMOUR_CLASS::LIGHT;
		else if (output[1] == "MEDIUM")
			_currentData.armour_class = ARMOUR_CLASS::AVERAGE;
		else if (output[1] == "HEAVY")
			_currentData.armour_class = ARMOUR_CLASS::HEAVY;
		else _currentData.armour_class = -1;
		break;


		//parse armour type
	case TAGVALUE::TYPE:
		if (output[1] == "HELMET")
			_currentData.type = ARMOUR_TYPE::HELMET;
		else if (output[1] == "TORSO")
			_currentData.type = ARMOUR_TYPE::TORSO;
		else if (output[1] == "GREAVES")
			_currentData.type = ARMOUR_TYPE::GREAVES;
		else if (output[1] == "SHIELD")
			_currentData.type = ARMOUR_TYPE::SHIELD;
		else _currentData.type = -1;
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

		//parse armour dodge chance
	case TAGVALUE::DODGE:
		try{
			value = std::stoi(output[1]);
		}
		catch (const std::invalid_argument&){
			value = -1;
		}
		_currentData.dodge = value;
		break;

		//parse shield block chance
	case TAGVALUE::BLOCK:
		try{
			value = std::stoi(output[1]);
		}
		catch (const std::invalid_argument&){
			value = -1;
		}
		_currentData.block = value;
		break;

		//parse armour speed boost
	case TAGVALUE::SPEED:
		try{
			value = std::stoi(output[1]);
		}
		catch (const std::invalid_argument&){
			value = -1;
		}
		_currentData.speed = value;
		break;


		//parse armour requirement
	case TAGVALUE::STR_REQ:
		try{
			value = std::stoi(output[1]);
		}
		catch (const std::invalid_argument&){
			value = 0;
		}
		_currentData.str_req = value;
		break;

	case TAGVALUE::END_REQ:
		try{
			value = std::stoi(output[1]);
		}
		catch (const std::invalid_argument&){
			value = 0;
		}
		_currentData.end_req = value;
		break;

	case TAGVALUE::AGI_REQ:
		try{
			value = std::stoi(output[1]);
		}
		catch (const std::invalid_argument&){
			value = 0;
		}
		_currentData.agi_req = value;
		break;

	case TAGVALUE::DEX_REQ:
		try{
			value = std::stoi(output[1]);
		}
		catch (const std::invalid_argument&){
			value = 0;
		}
		_currentData.dex_req = value;
		break;

	case TAGVALUE::INT_REQ:
		try{
			value = std::stoi(output[1]);
		}
		catch (const std::invalid_argument&){
			value = 0;
		}
		_currentData.int_req = value;
		break;

	case TAGVALUE::WIL_REQ:
		try{
			value = std::stoi(output[1]);
		}
		catch (const std::invalid_argument&){
			value = 0;
		}
		_currentData.wil_req = value;
		break;

	}
}


/////////////////////
//Correctness Check//
/////////////////////
bool ArmoursLoader::checkStructCorrectness()
{
	_errorMsg = "";
	std::string error;

	bool isSuccessful = true;
	bool isFatal = false;

	//At first, let's check for abnormalities beyond repair//
	if (_currentData.name == "")  {
		_errorMsg += "\n   No name.";
		_currentData.name = "Armour no. " + std::to_string(_armourCount);
	}

	if (_currentData.type == -1)   {
		_errorMsg += "\n   Invalid armour type.";
	}

	if (_currentData.armour_class == -1)    {
		_errorMsg += "\n   Invalid armour class.";
	}
	if (_currentData.speed == -1)    {
		_errorMsg += "\n   Invalid armour speed.";
	}
	if (_currentData.block == -1 && _currentData.type == ARMOUR_TYPE::SHIELD)    {
		_errorMsg += "\n   Invalid shield block chance.";
	}
	if (_currentData.defence == -1 && _currentData.dodge == -1)    {
		_errorMsg += "\n   Invalid armour defence options.";
	}

	//compile fatal error message
	if (!_errorMsg.empty()){
		error = "Fatal error in loading armour " + _currentData.name + ". \nArmour not loaded. Reasons:" + _errorMsg + "\n";
		_errorMsg = "";
		isFatal = true;
	}


	//Now time to fix stuff. If unfixable, then sorry, but I don't really see no options as for now to fail.//
	//boo, none. no ideas how to correct anything here.//


	if ((_currentData.armour_class < 4 && _currentData.type == 3) || (_currentData.armour_class >= 4 && _currentData.type < 3))
		correctStruct(TAGVALUE::CLASS);

	if (_currentData.dodge == -1 && _currentData.armour_class == ARMOUR_CLASS::CLOTH) {
		if (!correctStruct(TAGVALUE::DODGE)){
			_errorMsg += "\n   Invalid armour dodge.";
			isFatal = true;
		}
	}

	if (_currentData.defence == -1 && _currentData.armour_class == ARMOUR_CLASS::METAL) {
		if (!correctStruct(TAGVALUE::DEFENCE)){
			_errorMsg += "\n   Invalid armour defence.";
			isFatal = true;
		}
	}

	//send error message
	if (!_errorMsg.empty() || isFatal){
		error += "Error in loading armour " + _currentData.name + ":" + _errorMsg;
		_errorHandler->processError(error);
		if (isFatal) return false;
	}

	//calculate rating//
	Calculations::calculateBaseRating(_currentData);
	std::cout << "Armour Rating: " << _currentData.rating << std::endl;

	return isSuccessful;
}
//No ideas, how to correct invalid armour structure. Incorrect one mostly will be disposed as for now.
bool ArmoursLoader::correctStruct(int tag)
{

	switch(tag){

	case TAGVALUE::CLASS:
		_errorMsg += "\n   Wrong class. Changed ";
		switch (_currentData.armour_class){
		case ARMOUR_CLASS::CLOTH:
			if (_currentData.type == ARMOUR_TYPE::SHIELD) _currentData.armour_class = ARMOUR_CLASS::LIGHT;
			_errorMsg += "Cloth -> Light";
			break;
		case ARMOUR_CLASS::LEATHER:
			if (_currentData.type == ARMOUR_TYPE::SHIELD) _currentData.armour_class = ARMOUR_CLASS::AVERAGE;
			_errorMsg += "Leather -> Average";
			break;
		case ARMOUR_CLASS::METAL:
			if (_currentData.type == ARMOUR_TYPE::SHIELD) _currentData.armour_class = ARMOUR_CLASS::HEAVY;
			_errorMsg += "Metal -> Heavy";
			break;

		case ARMOUR_CLASS::LIGHT:
			if (_currentData.type != ARMOUR_TYPE::SHIELD) _currentData.armour_class = ARMOUR_CLASS::CLOTH;
			_errorMsg += "Light -> Cloth";
			break;
		case ARMOUR_CLASS::AVERAGE:
			if (_currentData.type != ARMOUR_TYPE::SHIELD) _currentData.armour_class = ARMOUR_CLASS::LEATHER;
			_errorMsg += "Average -> Leather";
			break;
		case ARMOUR_CLASS::HEAVY:
			if (_currentData.type != ARMOUR_TYPE::SHIELD) _currentData.armour_class = ARMOUR_CLASS::METAL;
			_errorMsg += "Heavy -> Metal";
			break;

		}
		break;

	case TAGVALUE::DODGE:
		if (_currentData.defence == -1) return false;
		_currentData.dodge = _currentData.defence;
		break;

	case TAGVALUE::DEFENCE:
		if (_currentData.dodge == -1) return false;
		_currentData.defence = _currentData.dodge;
		break;
	}
	return true;
}