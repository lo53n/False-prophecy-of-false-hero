#include "StatusWindow.h"
StatusWindow::StatusWindow()
{
	_renderTexture.create(414.f, 414.f);
	_sprite.setColor(sf::Color(255, 255, 255, 240));

	_statusWindow.setSize(sf::Vector2f(410.f, 410.f));
	_statusWindow.setPosition(2.f, 2.f);
	_statusWindow.setFillColor(sf::Color(150, 150, 150));
	_statusWindow.setOutlineThickness(2.f);
	_statusWindow.setOutlineColor(sf::Color(190, 190, 190));

	_statsPart.setSize(sf::Vector2f(200.f, 200.f));
	_statsPart.setPosition(5.f, 5.f);
	_statsPart.setFillColor(sf::Color(30, 150, 50));
	_statsPart.setOutlineThickness(2.f);
	_statsPart.setOutlineColor(sf::Color(60, 180, 80));

	_equipementPart.setSize(sf::Vector2f(200.f, 200.f));
	_equipementPart.setPosition(5.f, 210.f);
	_equipementPart.setFillColor(sf::Color(30, 50, 150));
	_equipementPart.setOutlineThickness(2.f);
	_equipementPart.setOutlineColor(sf::Color(60, 80, 180));

	_proficiencesPart.setSize(sf::Vector2f(200.f, 405.f));
	_proficiencesPart.setPosition(210.f, 5.f);
	_proficiencesPart.setFillColor(sf::Color(150, 50, 90));
	_proficiencesPart.setOutlineThickness(2.f);
	_proficiencesPart.setOutlineColor(sf::Color(180, 80, 120));


	_font = LoadFontFromResource("Arialfont");


	_expText.setFont(_font);
	_expText.setCharacterSize(13);
	_expText.setPosition(_statsPart.getPosition() + sf::Vector2f(5.f, 3.f));

	_healthText.setFont(_font);
	_healthText.setCharacterSize(13);
	_healthText.setPosition(_statsPart.getPosition() + sf::Vector2f(5.f, 53.f));

	_healthNumbersText.setFont(_font);
	_healthNumbersText.setCharacterSize(13);
	_healthNumbersText.setPosition(_statsPart.getPosition() + sf::Vector2f(60.f, 53.f));

	_statsText.setFont(_font);
	_statsText.setCharacterSize(13);
	_statsText.setPosition(_statsPart.getPosition() + sf::Vector2f(5.f, 104.f));

	_statsNumbersText.setFont(_font);
	_statsNumbersText.setCharacterSize(13);
	_statsNumbersText.setPosition(_statsPart.getPosition() + sf::Vector2f(85.f, 104.f));


	_equipementText.setFont(_font);
	_equipementText.setCharacterSize(14);
	_equipementText.setPosition(_equipementPart.getPosition() + sf::Vector2f(5.f, 5.f));


	_proficiencesText.setFont(_font);
	_proficiencesText.setCharacterSize(12);
	_proficiencesText.setPosition(_proficiencesPart.getPosition() + sf::Vector2f(5.f, 5.f));

	
	setProgressBars();
}

StatusWindow::~StatusWindow()
{
}

void StatusWindow::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite);
}

void StatusWindow::drawOnRenderTexture()
{
	_renderTexture.clear();

	_renderTexture.draw(_statusWindow);
	_renderTexture.draw(_equipementPart);
	_renderTexture.draw(_statsPart);
	_renderTexture.draw(_proficiencesPart);

	//Stats part
	_renderTexture.draw(_expText);

	_renderTexture.draw(_healthText);
	_renderTexture.draw(_healthNumbersText);

	_renderTexture.draw(_statsText);
	_renderTexture.draw(_statsNumbersText);

	//Equipement part


	//Proficiences part
	_renderTexture.draw(_proficiencesText);
	for (int i = 0, len = _proficienciesBarFull.size(); i < len; i++){
		_renderTexture.draw(_proficienciesBarEmpty[i]);
		_renderTexture.draw(_proficienciesBarFull[i]);
	}

	_renderTexture.display();
	_sprite.setTexture(_renderTexture.getTexture());
}

void StatusWindow::refreshStatus()
{
	refreshStats();
	refreshEquipementStats();
	refreshProficiences();

	drawOnRenderTexture();
}

void StatusWindow::setPlayer(std::shared_ptr<Player> player)
{
	_player = player;
}


void StatusWindow::resizeByGameWindow(sf::Vector2f center)
{
	sf::Vector2f size = _statusWindow.getSize();

	_sprite.setPosition(center.x - size.x / 2, center.y - size.y / 2);
}



void StatusWindow::refreshStats()
{
	Hero_Profile stats = _player->getPlayerStats();
	std::string string = "";

	string += "Level: " + std::to_string(stats.level);
	string += "\nExperience to next level:\n" + std::to_string(stats.exp) + "/" + std::to_string(stats.max_exp);

	_expText.setString(string);

	string = "";

	string += "Health\nMana\nStamina";

	_healthText.setString(string);

	string = "";

	string += std::to_string(stats.hp) + "/" + std::to_string(stats.max_hp) + "\n";
	string += std::to_string(stats.mp) + "/" + std::to_string(stats.max_mp) + "\n";
	string += std::to_string(stats.stam) + "/" + std::to_string(stats.max_stam) + "\n";

	_healthNumbersText.setString(string);

	string = "";

	string += "Strength";
	string += "\nEndurance";
	string += "\nDexterity";
	string += "\nAgility";
	string += "\nIntelligence";
	string += "\nWisdom";

	_statsText.setString(string);

	string = "";

	string += std::to_string(stats.strenght);
	string += "\n" + std::to_string(stats.endurance);
	string += "\n" + std::to_string(stats.dexterity);
	string += "\n" + std::to_string(stats.agility);
	string += "\n" + std::to_string(stats.intelligence);
	string += "\n" + std::to_string(stats.wisdom);

	_statsNumbersText.setString(string);

}
void StatusWindow::refreshEquipementStats()
{

}
void StatusWindow::refreshProficiences()
{
	std::vector<Ability_Proficiencies> proficiences = _player->getPlayerProficiences();
	std::string string = "";

	string += "One-handed, level " + std::to_string(proficiences[0].level);
	string += "\n\nTwo-handed, level " + std::to_string(proficiences[1].level);
	string += "\n\nDual-wield, level " + std::to_string(proficiences[2].level);
	string += "\n\nShield, level " + std::to_string(proficiences[3].level);
	string += "\n\nUnarmed, level " + std::to_string(proficiences[4].level);
	string += "\n\nSword, level " + std::to_string(proficiences[5].level);
	string += "\n\nMace, level " + std::to_string(proficiences[6].level);
	string += "\n\nSpear, level " + std::to_string(proficiences[7].level);
	string += "\n\nAxe, level " + std::to_string(proficiences[8].level);


	string += "\n\nMagic, level " + std::to_string(proficiences[9].level);
	string += "\n\nDefence, level " + std::to_string(proficiences[10].level);
	string += "\n\nBody endurance, level " + std::to_string(proficiences[11].level);
	string += "\n\nPain tolerance, level " + std::to_string(proficiences[12].level);
	string += "\n\nDodging, level " + std::to_string(proficiences[13].level);


	_proficiencesText.setString(string);

	refreshProgressBars(proficiences);
}

void StatusWindow::setProgressBars()
{
	sf::Vector2f position = _proficiencesText.getPosition() + sf::Vector2f(5, 19);

	for (int i = 0; i < 14; i++){
		sf::RectangleShape empty(sf::Vector2f(180, 5));
		sf::RectangleShape full(sf::Vector2f(180, 5));

		empty.setFillColor(sf::Color::Black);
		empty.setOutlineColor(sf::Color(20, 20, 20));
		empty.setOutlineThickness(1.f);

		full.setFillColor(sf::Color(30, 230, 50));

		empty.setPosition(position.x, position.y + (i * 28.f));
		full.setPosition(position.x, position.y + (i * 28.f));
		_proficienciesBarEmpty.push_back(empty);
		_proficienciesBarFull.push_back(full);
	}
}

void StatusWindow::refreshProgressBars(std::vector<Ability_Proficiencies> proficiences)
{
	for (int i = 0, len = _proficienciesBarFull.size(); i < len; i++){
		float scaleX;
		scaleX = (float)proficiences[i].experience / (float)proficiences[i].experience_needed;
		_proficienciesBarFull[i].setScale(scaleX, 1);
	}
}