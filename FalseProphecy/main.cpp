#include <iostream>
#include <unordered_map>
#include <ctime>

#include "Game/Game.h"

#include "LoadFromResource.h"
#include "UIResource.h"


#include "SFML/Graphics.hpp"



int main()
{

	srand((unsigned int)time(0));
	Game game;
	game.run();

	return 0;
}
