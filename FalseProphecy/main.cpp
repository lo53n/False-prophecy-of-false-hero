#include <iostream>
#include <unordered_map>
#include <ctime>

#include "Game/Game.h"
//#include "Map/MapBuilderPattern.h"
//#include "Map/NormalBuilder.h"

#include "LoadFromResource.h"
#include "UIResource.h"


#include "SFML/Graphics.hpp"

int main()
{

	srand((unsigned int)time(0));
	Game game;
	game.run();

	//std::unordered_map<int, int> map;
	//map[1] = 99999;
	//if (map[9] == NULL)
	//	std::cout << map[1] << std::endl;
	//for (auto kv : map) {
	//	std::cout << kv.first << " "<< kv.second << std::endl;
	//}
	//std::vector<std::string> weaponvector;

	//std::string __DEFAULT_AXE_IMAGE__ = "data\\img\\weapon\\axedefault.png";
	//std::string __DEFAULT_SWORD_IMAGE__ = "data\\img\\weapon\\sworddefault.png";

	//sf::Clock clock;
	//sf::Time time;
	//ItemsHolder *holder = &ItemsHolder::getItemsHolder();
	//ItemsLoader itemsloader;
	//system("pause"); 
	//clock.restart();
	//itemsloader.loadResources();
	//time = clock.restart();
	//system("pause");
	//std::cout << holder->getWeaponsCount() << std::endl;
	//std::cout << time.asMilliseconds() << std::endl;


	//sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
	//sf::Texture text, tile1;
	//std::cout << holder->_weaponsData[0].img_path << std::endl;
	//if (!text.loadFromFile(holder->_weaponsData[0 ].img_path))
	//	text.loadFromFile(__DEFAULT_SWORD_IMAGE__);
	//sf::RectangleShape shape, tile;
	//tile1.loadFromFile("data/img/etc/backtile.png");
	//tile.setTexture(&tile1);
	//tile.setPosition(10, 10);
	//tile.setSize(sf::Vector2f(32.f, 32.f));
	//shape.setTexture(&text);
	//shape.setSize(sf::Vector2f(32.f, 32.f));
	//shape.setPosition(10, 10);

	//window.clear();
	//window.draw(tile);
	//window.draw(shape);
	//window.display();


	/*MapsHolder *mapsHolder_ = &MapsHolder::getMapsHolder();
	MapLoader mapLoader;
	mapLoader.loadFromFile();
	Map *map_ = new Map();
	Map *map1_ = new Map();

	map_->setMap(mapsHolder_->getMapFromHolder(0));
	map_->printConsoleMap();

	MapBuilder mapBuilder;
	NormalBuilder normalBuilder;

	normalBuilder.setMap(map_);
	mapBuilder.setLandBuilder(&normalBuilder);
	mapBuilder.buildMap(&map_->getMap());

	map_->drawMap();

	

	sf::Font font = LoadFontFromResource("Arialfont");
	sf::Text text;
	text.setCharacterSize(12);
	text.setFont(font);
	text.setPosition(100.f, 100.f);
	text.setString("asdasda");


	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(GWI);
		// window.draw(text);
		window.display();
	}
	*/
	
	//system("pause");
	return 0;
}
