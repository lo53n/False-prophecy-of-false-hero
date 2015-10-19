#ifndef ERRORS_ERRORHANDLER
#define ERRORS_ERRORHANDLER

#include <vector>

#include "SFML/Graphics.hpp"

#include "../LoadFromResource.h"
#include "../UIResource.h"

class ErrorHandler : public sf::Drawable{


public:

	bool getErrorStatus();

	void resizeByGameWindow(sf::Vector2f center);

	void handleInput(int key, bool isPressed);

	void processError(std::vector<std::string> messages);
	void processError(std::string message);
	void showMessage();

	ErrorHandler();
	~ErrorHandler();


private:

	std::vector<std::string> _messages;

	sf::RenderTexture _renderTexture;
	sf::Sprite _sprite;

	sf::RectangleShape _errorWindow;

	sf::Font _font;
	sf::Text _errorMsg;
	sf::Text _errorConfirmUpper;
	sf::Text _errorConfirmLower;

	int _messageState;

	bool isErrorMessage = false;
	int errorNumber = 0;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void refreshErrorWindow();
};



#endif //!ERRORS_ERRORHANDLER