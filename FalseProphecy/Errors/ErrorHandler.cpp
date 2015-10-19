#include "ErrorHandler.h"

ErrorHandler::ErrorHandler()
{
	_messages.push_back("asd");
	_messages.clear();

	sf::Vector2f size(404.f, 404.0f);
	_renderTexture.create((unsigned int) size.x, (unsigned int) size.y);

	_font = LoadFontFromResource("Arialfont");
	_errorMsg.setFont(_font);
	_errorMsg.setCharacterSize(14);
	_errorMsg.setPosition(5.0f, 5.0f);
	_errorMsg.setColor(sf::Color(0, 0, 0));

	_errorConfirmUpper.setFont(_font);
	_errorConfirmUpper.setCharacterSize(15);
	_errorConfirmUpper.setString("[Enter] for next message.");
	_errorConfirmUpper.setPosition((int)(size.x / 2 - _errorConfirmUpper.getGlobalBounds().width / 2), 350.0f);
	_errorConfirmUpper.setColor(sf::Color(0, 0, 0));

	_errorConfirmLower.setFont(_font);
	_errorConfirmLower.setCharacterSize(15);
	_errorConfirmLower.setString("[ESC] to discard all.");
	_errorConfirmLower.setPosition((int)(size.x / 2 - _errorConfirmLower.getGlobalBounds().width / 2), 370.0f);
	_errorConfirmLower.setColor(sf::Color(0, 0, 0));

	_errorWindow.setSize(sf::Vector2f(400.0f, 400.0f));
	_errorWindow.setPosition(sf::Vector2f(2.0f, 2.0f));
	_errorWindow.setOutlineThickness(2.0f);
	_errorWindow.setOutlineColor(sf::Color(240, 240, 240));
	_errorWindow.setFillColor(sf::Color(255, 255, 255));


}

ErrorHandler::~ErrorHandler()
{

}

bool ErrorHandler::getErrorStatus()
{
	return isErrorMessage;
}

void ErrorHandler::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite);
}

void ErrorHandler::handleInput(int key, bool isPressed)
{
	if (isPressed){
		switch (key){
		case sf::Keyboard::Return:
			refreshErrorWindow();
			break;
		case sf::Keyboard::Escape:
			errorNumber = 0;
			_messages.clear();
			isErrorMessage = false;

			break;

		default:break;
		}
	}
}

void ErrorHandler::processError(std::vector<std::string> messages)
{
	if (_messages.size() == 0){
		_messages = messages;
		isErrorMessage = true;
		refreshErrorWindow();
	}
	else
	{
		for (int i = 0, len = messages.size(); i < len; i++){
			_messages.push_back(messages[i]);
		}
	}
}


void ErrorHandler::processError(std::string message)
{
	if (_messages.size() == 0){
		_messages.push_back(message);
		isErrorMessage = true;
		refreshErrorWindow();
	}
	else
	{
		_messages.push_back(message);
		
	}

}
void ErrorHandler::refreshErrorWindow()
{
	if (_messages.size() == errorNumber){
		isErrorMessage = false;
		_messages.clear();
		errorNumber = 0;
		return;
	}


	_errorMsg.setString(_messages[errorNumber]);
	errorNumber++;

	_renderTexture.clear();
	_renderTexture.draw(_errorWindow);
	_renderTexture.draw(_errorMsg);
	_renderTexture.draw(_errorConfirmUpper);
	_renderTexture.draw(_errorConfirmLower);
	_renderTexture.display();
	_sprite.setTexture(_renderTexture.getTexture());
}

void ErrorHandler::resizeByGameWindow(sf::Vector2f center)
{
	sf::Vector2f size = _errorWindow.getSize();

	_sprite.setPosition(center.x - size.x / 2, center.y - size.y / 2);
}