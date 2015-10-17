#ifndef INTERFACE_STATUSWINDOW
#define INTERFACE_STATUSWINDOW


#include "SFML\Graphics.hpp"

#include "..\Player\Player.h"
#include "..\StructsEnums.h"
#include "..\LoadFromResource.h"



class StatusWindow : public sf::Drawable{

public:

	void refreshStatus();
	void resizeByGameWindow(sf::Vector2f center);
	void setPlayer(std::shared_ptr<Player> player);

	StatusWindow();
	~StatusWindow();

private:


	std::shared_ptr<Player> _player;

	sf::Sprite _sprite;
	sf::RenderTexture _renderTexture;

	sf::RectangleShape _statusWindow;
	sf::RectangleShape _statsPart;
	sf::RectangleShape _equipementPart;
	sf::RectangleShape _proficiencesPart;

	sf::Font _font;

	sf::Text _expText;
	sf::Text _healthText;
	sf::Text _healthNumbersText;

	sf::Text _statsText;
	sf::Text _statsNumbersText;
	sf::Text _equipementText;

	sf::Text _proficiencesText;
	std::vector<sf::RectangleShape> _proficienciesBarEmpty;
	std::vector<sf::RectangleShape> _proficienciesBarFull;


private:

	void drawOnRenderTexture();
	
	void refreshStats();
	void refreshEquipementStats();
	void refreshProficiences();

	void setProgressBars();
	void refreshProgressBars(std::vector<Ability_Proficiencies> proficiences);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};




#endif //!INTERFACE_STATUSWINDOW