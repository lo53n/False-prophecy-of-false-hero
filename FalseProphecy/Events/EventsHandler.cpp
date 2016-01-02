#include "EventsHandler.h"

EventsHandler::EventsHandler()
{

	sf::Vector2f size(464.f, 394.0f);
	_renderTexture.create((unsigned int)size.x, (unsigned int)size.y);

	_font = LoadFontFromResource("Arialfont");
	_eventMsg.setFont(_font);
	_eventMsg.setCharacterSize(18);
	_eventMsg.setPosition(7.0f, 7.0f);
	_eventMsg.setColor(sf::Color(0, 0, 0));

	_eventConfirmUpper.setFont(_font);
	_eventConfirmUpper.setCharacterSize(15);
	_eventConfirmUpper.setString("[Enter] to close.");
	_eventConfirmUpper.setPosition((int)(size.x / 2 - _eventConfirmUpper.getGlobalBounds().width / 2), 3650.0f);
	_eventConfirmUpper.setColor(sf::Color(0, 0, 0));

	_eventConfirmLower.setFont(_font);
	_eventConfirmLower.setCharacterSize(15);
	_eventConfirmLower.setString("[ESC] to discard all.");
	_eventConfirmLower.setPosition((int)(size.x / 2 - _eventConfirmLower.getGlobalBounds().width / 2), 370.0f);
	_eventConfirmLower.setColor(sf::Color(0, 0, 0));


	_eventWindow.setSize(sf::Vector2f(460.0f, 390.0f));
	_eventWindow.setPosition(sf::Vector2f(2.0f, 2.0f));
	_eventWindow.setOutlineThickness(2.0f);
	_eventWindow.setOutlineColor(sf::Color(150, 150, 240));
	_eventWindow.setFillColor(sf::Color(110,110, 255));


	_hero_pos = sf::Vector2i(0, 0);

}
EventsHandler::~EventsHandler()
{

}

bool EventsHandler::getEventStatus()
{
	return isEventMessage;
}

GameEvents EventsHandler::getEventsStructure()
{
	return _events;
}

void EventsHandler::restoreEventData(GameEvents &events)
{
	_events = events;
}


void EventsHandler::printStruct()
{

}
void EventsHandler::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite);
}


void EventsHandler::handleInput(int key, bool isPressed)
{
	if (isPressed){
		switch (key){
		/*case sf::Keyboard::Return:
			refreshEventWindow();
			break;*/
		case sf::Keyboard::Return:
			_messages.clear();
			isEventMessage = false;

			if (_events.start_of_game && !_events.first_instructions){
				triggerEvent(EVENT_TYPE::FIRST_INSTRUCTIONS);
			}
			if (_events.first_step && !_events.items_first_lookout){
				triggerEvent(EVENT_TYPE::ITEMS_FIRST_LOOKOUT);
			}
			if (_events.items_first_lookout && !_events.items_instructions && !isEventMessage){
				triggerEvent(EVENT_TYPE::ITEMS_INSTRUCTIONS);
			}

			break;

		default:break;
		}
	}
}




void EventsHandler::refreshEventWindow()
{
	//if (_messages.size() == errorNumber){
	//	isErrorMessage = false;
	//	_messages.clear();
	//	errorNumber = 0;
	//	return;
	//}


	//_errorMsg.setString(_messages[errorNumber]);
	//errorNumber++;

	_renderTexture.clear();
	_renderTexture.draw(_eventWindow);
	_renderTexture.draw(_eventMsg);
	_renderTexture.draw(_eventConfirmUpper);
	//_renderTexture.draw(_eventConfirmLower);
	_renderTexture.display();
	_sprite.setTexture(_renderTexture.getTexture());
}



void EventsHandler::resizeByGameWindow(sf::Vector2f center)
{
	sf::Vector2f size = _eventWindow.getSize();

	_sprite.setPosition(center.x - size.x / 2, center.y - size.y / 2);
}



void EventsHandler::triggerEvent(int event_number)
{

	switch (event_number){

	case EVENT_TYPE::START_OF_GAME:
		_events.start_of_game = true;
		isEventMessage = true;
		triggerStartOfGameEvent();


		break;

	case EVENT_TYPE::FIRST_INSTRUCTIONS:
		_events.first_instructions = true;
		isEventMessage = true;
		triggerFirstInstructionsEvent();

		break;

	case EVENT_TYPE::FIRST_STEP:
		_events.first_step = true;
		isEventMessage = true;
		triggerFirstStepEvent();

		break;

	case EVENT_TYPE::ITEMS_FIRST_LOOKOUT:
		_events.items_first_lookout = true;
		isEventMessage = true;
		triggerItemsFirstLookoutEvent();

		break;

	case EVENT_TYPE::ITEMS_INSTRUCTIONS:
		_events.items_instructions = true;
		isEventMessage = true;
		triggerItemsInstructionEvent();

		break;

	case EVENT_TYPE::FIRST_ENEMY_MEET:
		_events.first_enemy_meet = true;
		isEventMessage = true;
		triggerFirstEnemyEvent();

		break;

	case EVENT_TYPE::FIRST_ENEMY_KILLED:
		_events.first_enemy_killed = true;
		isEventMessage = true;
		triggerKilledFirstEnemyEvent();

		break;

	case EVENT_TYPE::FIRST_BOSS:
		_events.first_boss = true;
		isEventMessage = true;
		triggerFirstBossEvent();

		break;
	
	}

	refreshEventWindow();

}

void EventsHandler::updateEventTracker(Hero_Profile hero_stats, sf::Vector2i hero_pos, int curr_map)
{


	//Now, lets hunt for events!

	if (!_events.first_step && hero_stats.level == 1 && hero_stats.exp == 0 && hero_pos != _hero_pos){
		triggerEvent(EVENT_TYPE::FIRST_STEP);
	}




	_hero_stats = hero_stats;
	_hero_pos = hero_pos;

}

void EventsHandler::resetEvents()
{

	_events.start_of_game = false;
	_events.first_instructions = false;
	_events.first_step = false;
	_events.items_first_lookout = false;
	_events.items_instructions = false;
	_events.first_enemy_meet = false;
	_events.first_enemy_killed = false;

	_events.first_boss = false;
}
void EventsHandler::triggerStartOfGameEvent()
{

	std::string msg = "";

	msg += "\tYou slowly came back to your senses. You didn't even \nremember how many times you fainted. ";
	msg += "Hell, you didn't \neven know how long you were here, wandering aimlessly in \nthis labirynth. ";
	msg += "Like some kind of abomination with no need \nof food or water to live through another hours and days.";
	msg += "\n\tWhat was it...? It was swelling your mind from inside... \n\tRegret? Anger? Loneliness? \n\tMaybe awareness of long lost humanity?";
	msg += "\n\tHas everyone who entered this labirynth ended same as \nyou? One couldn't help but wonder. Was it fate? Was it curse? ";
	msg += "\n\tDeep inside of this monstrous construction should be \nsanctuary. Prohpecy said the Priestess will find solution \nto Kingdom's problems. ";
	msg += "But... \n\tWhat if? What if Kingdom's problem is this labirynth? \n\tWill she help you?";
	msg += "\n\tSince long ago you had none but one choice.";
	msg += "\n\tPry forward. To once again see the sun.";

	_eventMsg.setString(msg);
}


void EventsHandler::triggerFirstInstructionsEvent()
{
	std::string msg = "";

	msg += "\n\n\n\n\n                                 [INSTRUCTIONS]\n";
	msg += "\tTo move around character use arrow keys. Each step is \none turn. You can move only up, down, left or right.";
	msg += "\n\tTo move around camera use keypad. It's free action, you \ncan do it any moment without using turn. Use it to find \nexits or assess situation.";
	
	
	//msg += "\n\tThree bars in the upper left corner are your hit points, \nstamina and experience points indicators. You can find more \ndetails on character in [C]haracter Screen.";
	//msg += "\n\tIf your hit points drops to 0, your character dies and its \ngame over. To regenerate some health, rest a while, run around, \nor use item.";


	_eventMsg.setString(msg);


}

void EventsHandler::triggerFirstStepEvent()
{
	std::string msg = "";

	msg += "\n\tYou took a good look around. You noticed big, crumbled \nhole in the ceiling.";
	msg += "There was no way you could climb back, \nceiling was five or six meters high. \n\tYou suddenly remembered reason behind fainting. ";
	msg += "\n\tWhen you were checking one of rooms, floor suddenly \nstarted to crumble and finally colapsed with you. Last thing \nyou vaguely remember is slamming hard on cold, stone floor.";
	msg += "\n\tFeeling of unfamiliarity assaulted you from every side. It \nwasn't bad sign, however. You never was here and it seems \nlike nobody was here either.";
	msg += "\n\tYou found new path, a path you never saw before. Air was \nstrangely filled power, prickling subtly your skin. You didn't \nfelt this before. ";
	msg += "\n\tHope arose once more. \n\tSanctuary might be here, in this lower level of labirynth.";

	_eventMsg.setString(msg);
}

void EventsHandler::triggerItemsFirstLookoutEvent()
{
	std::string msg = "";

	msg += "\n\n\tYou noticed old, rusted sword laying few meters farther. \nIt looked chipped and dull, but it was a weapon nonetheless. \nA weapon you spent days with as only companion in your \nmisery. ";
	msg += "\n\tYou wielded many weapons in your past. It was natural \nfor soldier. You always felt strange sense of security with \none in hand or sheathed by waist. ";
	msg += "Now, without it, scary and \nsuffocating vulnerability was filling your body. \n\tYou needed it. \n\tA weapon. Any will do. \n\tAs it was part of your body.";

	_eventMsg.setString(msg);

}

void EventsHandler::triggerItemsInstructionEvent()
{
	std::string msg = "";

	msg += "\n\n\n\n\n                              [INSTRUCTIONS]\n";
	msg += "\tTo pick up item, walk on it and press [D] key. It will be \nplaced in your [I]nventory.";
	msg += "\n\tWhen in Inventory window, press [Return] to equip or use \nselected item. Press [Tab] to switch between your equipment \nand bag. When in equipment tab, [Return] will unequip item.";
	msg += "\n\tIf you want to drop item, press [D] while in Inventory. \nThat might prove useful since you can carry limited amout of \nitems.";
	

	_eventMsg.setString(msg);

}

void EventsHandler::triggerFirstEnemyEvent()
{
	std::string msg = "";

	msg += "\n\n\n\n\tIt was something unholy. Abomination you never met \nbefore in your short life.";
	msg += "\n\tIt's rattling bones made blood-chilling noise. Yet it didn't \nnoticed you yet. Or maybe it didn't want to notice you?";
	msg += "\n\tThe skeleton was on your way, on the only path on your \nholy mission. You didn't meet previously any enemy in this \nlabirynth. ";
	msg += "\n\tThat could mean something. Down there could be either \nSanctuary you need to find or your demise.";
	msg += "\n\tBut still, only option for you was to fight.";

	_eventMsg.setString(msg);
}

void EventsHandler::triggerKilledFirstEnemyEvent()
{
	std::string msg = "";

	msg += "\n\n\n\n\tIt was strange feeling. Very different from fighting flesh \nand blood humans, as you did in academy.";
	msg += "\n\tThe living dead made no noise besides rattling, it didn't \nscreamed from pain nor agony. It was so unsettling, you \nhad troubles with concentrating on fight.";
	msg += "\n\tYet stranger was the feeling of power which came after \nturning skeleton to pile of bones. You felt a little stronger.";
	msg += "\nNot much. Only by a bit. But you certainly felt it. Where did \nthat power came from?";
	msg += "\n\tAnd again, was it curse or blessing?";

	_eventMsg.setString(msg);
}
void EventsHandler::triggerFirstBossEvent()
{
	std::string msg = "";


	_eventMsg.setString(msg);
}


