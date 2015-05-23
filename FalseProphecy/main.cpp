#include <iostream>

#include "Game/Game.h"
#include "Map\MapBuilderPattern.h"
#include "Map\NormalBuilder.h"

int main()
{

	Game game;
	game.run();
	


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
		window.draw(*map_);
		window.display();
	}*/

	system("pause");
	return 0;
}
