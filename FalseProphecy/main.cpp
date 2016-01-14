#include <iostream>
#include <unordered_map>
#include <ctime>

#include "Game/Game.h"

#include "LoadFromResource.h"
#include "UIResource.h"


#include "SFML/Graphics.hpp"



int main()
{
	std::seed_seq seq;
	srand((unsigned int)time(0));
	Game game;
	game.run();

	return 0;
}
