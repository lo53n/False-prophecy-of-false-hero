#include "ConsumablesLoader.h"
ConsumablesLoader::ConsumablesLoader(std::shared_ptr<ErrorHandler> errorHandler)
	:
	_errorHandler(errorHandler)
{
	_consumablesData.reserve(100000);
}

ConsumablesLoader::~ConsumablesLoader()
{

}

std::vector<Consumable_struct>& ConsumablesLoader::getConsumablesData()
{
	return _consumablesData;
}

void ConsumablesLoader::prepareStruct()
{
	_errorMsg = "";

	_currentData.name = "";
	_currentData.type = -1;
	_currentData.effect_type = -1;
	_currentData.effect_strength = -1;
	

	_consumableCount++;
}

void ConsumablesLoader::showStruct()
{

	std::cout << "Name: " << _currentData.name << std::endl;
	std::cout << "Img: " << _currentData.img_path << std::endl;
	std::cout << "Type: " << _currentData.type << std::endl;
	std::cout << "Effect type: " << _currentData.effect_type << std::endl;
	std::cout << "Effect strenght: " << _currentData.effect_strength << std::endl;


}

void ConsumablesLoader::saveStruct()
{
	bool isSuccessful = checkStructCorrectness();
	//showStruct();
	if (isSuccessful)
		_consumablesData.push_back(_currentData);
	else std::cout << "Unable to load armour No. " << _consumableCount << std::endl;
	prepareStruct();
}
void ConsumablesLoader::loadFromFile()
{
	prepareStruct();
	std::fstream consumablesFile;
	consumablesFile.open("data/consumables.txt");


	std::string stringLine;
	while (!consumablesFile.eof()){
		getline(consumablesFile, stringLine);
		//std::cout << stringLine << std::endl;
		if (stringLine.size() == 0) continue;
		if (stringLine.size() > 6) parseLine(stringLine);
		if (stringLine == "[---]") saveStruct();
	}
	_consumablesData.shrink_to_fit();

}

void ConsumablesLoader::parseLine(std::string stringLine)
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
int ConsumablesLoader::checkTag(std::string tag)
{
	if (tag == "NAME") return TAGVALUE::NAME;
	if (tag == "IMG") return TAGVALUE::IMG;
	else if (tag == "EFFECT") return TAGVALUE::EFFECT_TYPE;
	else if (tag == "TYPE") return TAGVALUE::TYPE;
	else if (tag == "EFFECT_STRENGTH") return TAGVALUE::EFFECT_STRENGHT;

	//if nothing works, surely there is problem
	return -1;
}

void ConsumablesLoader::parseTag(std::vector<std::string> &output)
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
		_currentData.img_path = "data\\img\\consumable\\" + output[1];
		break;

		//parse consumable type
	case TAGVALUE::TYPE:
		if (output[1] == "FOOD")
			_currentData.type = CONSUMABLE_TYPE::FOOD_TYPE;
		else if (output[1] == "PILL")
			_currentData.type = CONSUMABLE_TYPE::PILL_TYPE;
		else if (output[1] == "POTION")
			_currentData.type = CONSUMABLE_TYPE::POTION_TYPE;
		else _currentData.type = -1;
		break;


		//parse consumable effect type
	case TAGVALUE::EFFECT_TYPE:
		if (output[1] == "BODY_UP")
			_currentData.effect_type = CONSUMABLE_EFFECT::BODY_UP;
		else if (output[1] == "REFLEX_UP")
			_currentData.effect_type = CONSUMABLE_EFFECT::REFLEX_UP;
		else if (output[1] == "MIND_UP")
			_currentData.effect_type = CONSUMABLE_EFFECT::MIND_UP;
		else if (output[1] == "EXP_UP")
			_currentData.effect_type = CONSUMABLE_EFFECT::EXP_UP;
		else if (output[1] == "HP_REGEN")
			_currentData.effect_type = CONSUMABLE_EFFECT::HP_REGEN;
		else if (output[1] == "SP_REGEN")
			_currentData.effect_type = CONSUMABLE_EFFECT::SP_REGEN;
		else if (output[1] == "REGENERATE")
			_currentData.effect_type = CONSUMABLE_EFFECT::REGENERATE_TICK;
		else if (output[1] == "STR_UP")
			_currentData.effect_type = CONSUMABLE_EFFECT::STR_UP;
		else if (output[1] == "END_UP")
			_currentData.effect_type = CONSUMABLE_EFFECT::END_UP;
		else if (output[1] == "DEX_UP")
			_currentData.effect_type = CONSUMABLE_EFFECT::DEX_UP;
		else if (output[1] == "AGI_UP")
			_currentData.effect_type = CONSUMABLE_EFFECT::AGI_UP;
		else if (output[1] == "INT_UP")
			_currentData.effect_type = CONSUMABLE_EFFECT::INT_UP;
		else if (output[1] == "WIL_UP")
			_currentData.effect_type = CONSUMABLE_EFFECT::WIL_UP;
		else _currentData.effect_type = -1;
		break;

		//parse consumable effect strength
	case TAGVALUE::EFFECT_STRENGHT:
		try{
			value = std::stoi(output[1]);
		}
		catch (const std::invalid_argument&){
			value = -1;
		}
		_currentData.effect_strength = value;
		break;

	}
}


/////////////////////
//Correctness Check//
/////////////////////
bool ConsumablesLoader::checkStructCorrectness()
{
	_errorMsg = "";
	std::string error;

	bool isSuccessful = true;
	bool isFatal = false;

	//At first, let's check for abnormalities beyond repair//
	if (_currentData.name == "")  {
		_errorMsg += "\n   No name.";
		_currentData.name = "Consumable no. " + std::to_string(_consumableCount);
	}

	if (_currentData.type == -1)   {
		_errorMsg += "\n   Invalid consumable type.";
	}

	if (_currentData.effect_type == -1)    {
		_errorMsg += "\n   Invalid consumable effect type.";
	}
	if (_currentData.effect_strength == -1)    {
		_errorMsg += "\n   Invalid consumable effect strength.";
	}

	//compile fatal error message
	if (!_errorMsg.empty()){
		error = "Fatal error in loading consumable " + _currentData.name + ". \nConsumable not loaded. Reasons:" + _errorMsg + "\n";
		_errorMsg = "";
		isFatal = true;
	}


	//Now time to fix stuff. If unfixable, then sorry, but I don't really see no options as for now to fail.//
	//boo, none. no ideas how to correct anything here.//


	
	//send error message
	if (!_errorMsg.empty() || isFatal){
		_errorHandler->processError(error);
		if (isFatal) return false;
	}

	//calculate rating//
	Calculations::calculateBaseRating(_currentData);
	std::cout << "Consumable Rating: " << _currentData.base_rating << std::endl;

	return isSuccessful;
}
//No ideas, how to correct invalid consumable structure. Incorrect one mostly will be disposed as for now.
bool ConsumablesLoader::correctStruct(int tag)
{

	
	return true;
}