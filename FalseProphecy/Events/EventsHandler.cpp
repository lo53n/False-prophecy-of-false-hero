#include "EventsHandler.h"

EventsHandler::EventsHandler()
{
	_renderTexture.setSmooth(true);
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
	//if (isPressed){
	//	switch (key){
	//	/*case sf::Keyboard::Return:
	//		refreshEventWindow();
	//		break;*/
	//	case sf::Keyboard::Return:
	//		_messages.clear();
	//		isEventMessage = false;

	//		if (_events.start_of_game && !_events.first_instructions){
	//			triggerEvent(EVENT_TYPE::FIRST_INSTRUCTIONS);
	//		}
	//		if (_events.first_step && !_events.items_first_lookout){
	//			triggerEvent(EVENT_TYPE::ITEMS_FIRST_LOOKOUT);
	//		}
	//		if (_events.items_first_lookout && !_events.items_instructions && !isEventMessage){
	//			triggerEvent(EVENT_TYPE::ITEMS_INSTRUCTIONS);
	//		}

	//		break;

	//	default:break;
	//	}
	//}
	if (isPressed){
				_messages.clear();
				isEventMessage = false;

				if (_events.start_of_game && !_events.first_instructions){
					triggerEvent(EVENT_TYPE::FIRST_INSTRUCTIONS);
				}
				//first items lookout
				if (_events.first_step && !_events.items_first_lookout){
					triggerEvent(EVENT_TYPE::ITEMS_FIRST_LOOKOUT);
				}
				if (_events.items_first_lookout && !_events.items_instructions && !isEventMessage){
					triggerEvent(EVENT_TYPE::ITEMS_INSTRUCTIONS);
				}
				//first enemy stuff
				if (_events.first_enemy_meet && !_events.first_enemy_meet_second && !isEventMessage){
					triggerEvent(EVENT_TYPE::FIRST_ENEMY_MEET_SECOND);
				}
				if (_events.first_enemy_meet_second && !_events.enemy_instructions && !isEventMessage){
					triggerEvent(EVENT_TYPE::ENEMY_INSTRUCTIONS);
				}
				//hero dies
				if (_events.hero_dies && !_events.hero_dies_second && !isEventMessage){
					triggerEvent(EVENT_TYPE::HERO_DIES_SECOND);
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

void EventsHandler::centerText()
{
	sf::Vector2f pos = _eventMsg.getPosition();
	pos.y = static_cast<int>(_eventWindow.getPosition().y + _eventWindow.getGlobalBounds().height / 2 - _eventMsg.getGlobalBounds().height / 2) - 5;
	_eventMsg.setPosition(pos);
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

	case EVENT_TYPE::FIRST_ENEMY_MEET_SECOND:
		_events.first_enemy_meet_second = true;
		isEventMessage = true;
		triggerFirstEnemySecondEvent();

		break;

	case EVENT_TYPE::ENEMY_INSTRUCTIONS:
		_events.enemy_instructions = true;
		isEventMessage = true;
		triggerEnemyInstructionsEvent();

		break;

	case EVENT_TYPE::FIRST_ENEMY_KILLED:
		_events.first_enemy_killed = true;
		isEventMessage = true;
		triggerKilledFirstEnemyEvent();

		break;

	case EVENT_TYPE::HALFWAY_TO_BOSS:
		_events.halfway_to_boss = true;
		isEventMessage = true;
		triggerHalfwayToBossEvent();

		break;

		//first boss
	case EVENT_TYPE::FIRST_BOSS:
		_events.first_boss = true;
		isEventMessage = true;
		triggerFirstBossEvent();

		break;

	case EVENT_TYPE::FIRST_BOSS_KILLED:
		_events.first_boss_killed = true;
		isEventMessage = true;
		triggerFirstBossKilledEvent();

		break;

		//priestess

	case EVENT_TYPE::PRIESTESS_FOUND_TOO_WEAK:
		_events.priestess_found_too_weak = true;
		isEventMessage = true;
		triggerPriestessFoundHeroWeakEvent();

		break;

	case EVENT_TYPE::PRIESTESS_FOUND:
		_events.priestess_found = true;
		isEventMessage = true;
		triggerPriestessFoundEvent();

		break;

	case EVENT_TYPE::PRIESTESS_KILLED:
		_events.priestess_killed = true;
		isEventMessage = true;
		triggerPriestessKilledEvent();

		break;


		//hero is killed
		//by priestess
	case EVENT_TYPE::PRIESTESS_FOUND_HERO_LOST:
		_events.priestess_found_hero_lost = true;
		isEventMessage = true;
		triggerPriestessFoundHeroLostEvent();

		break;

		//by normal mob
	case EVENT_TYPE::HERO_DIES:
		_events.hero_dies = true;
		isEventMessage = true;
		triggerHeroDiesEvent();

		break;

	case EVENT_TYPE::HERO_DIES_SECOND:
		_events.hero_dies_second = true;
		isEventMessage = true;
		triggerHeroDiesSecondEvent();

		break;
	
	}
	centerText();
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
	_events.first_enemy_meet_second = false;
	_events.enemy_instructions = false;
	_events.first_enemy_killed = false;
	_events.halfway_to_boss = false;

	_events.first_boss = false;
	_events.first_boss_killed = false;

	_events.priestess_found_too_weak = false;
	_events.priestess_found_hero_lost = false;
	_events.priestess_found = false;
	_events.priestess_killed = false;

	_events.hero_dies = false;
	_events.hero_dies_second = false;
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

	msg += "                                 [INSTRUCTIONS]\n";
	msg += "\n\tTo move around character use arrow keys. Each step is \none turn. You can move only up, down, left or right.";
	msg += "\n\tTo move around camera use keypad. It's free action, you \ncan do it any moment without using turn. Use it to find \nexits or assess situation.";
	
	
	//msg += "\n\tThree bars in the upper left corner are your hit points, \nstamina and experience points indicators. You can find more \ndetails on character in [C]haracter Screen.";
	//msg += "\n\tIf your hit points drops to 0, your character dies and its \ngame over. To regenerate some health, rest a while, run around, \nor use item.";


	_eventMsg.setString(msg);


}

void EventsHandler::triggerFirstStepEvent()
{
	std::string msg = "";

	msg += "\tYou took a good look around. You noticed big, crumbled \nhole in the ceiling.";
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

	msg += "\tYou noticed old, rusted sword laying few meters farther. \nIt looked chipped and dull, but it was a weapon nonetheless. \nA weapon you spent days with as only companion in your \nmisery. ";
	msg += "\n\tYou wielded many weapons in your past. It was natural \nfor soldier. You always felt strange sense of security with \none in hand or sheathed by waist. ";
	msg += "Now, without it, scary and \nsuffocating vulnerability was filling your body. \n\tYou needed it. \n\tA weapon. Any will do. \n\tAs it was part of your body.";

	_eventMsg.setString(msg);

}

void EventsHandler::triggerItemsInstructionEvent()
{
	std::string msg = "";

	msg += "                              [INSTRUCTIONS]\n";
	msg += "\n\tTo pick up item, walk on it and press [D] key. It will be \nplaced in your [I]nventory.";
	msg += "\n\tWhen in Inventory window, press [Return] to equip or use \nselected item. Press [Tab] to switch between your equipment \nand bag. When in equipment tab, [Return] will unequip item.";
	msg += "\n\tIf you want to drop item, press [D] while in Inventory. \nThat might prove useful since you can carry limited amout of \nitems.";
	

	_eventMsg.setString(msg);

}

void EventsHandler::triggerFirstEnemyEvent()
{
	std::string msg = "";

	msg += "\tYou opened doors and walked through long, very long \ncorridor. \n\tDespite being underground, everything was luminated by \nstrange light with no any visible source. ";
	msg += "Upper labirynth was \ndarker than Hell itself and torches weren't of any use there. \nThis otherwordly light bothered you more and more with \nevery passing moment.";
	msg += "\n\tYou turned right and left, marching steadily forward. After \nfew more turns you finally found another doors. You opened \nthem to find only something like passage.";
	msg += "\n\tOr so you thought. Something was there. Even before you \nsaw it, you felt it's presence.";
	msg += "\n\tShivers ran all over your body.";

	_eventMsg.setString(msg);
}

void EventsHandler::triggerFirstEnemySecondEvent()
{
	std::string msg = "";

	msg += "\tSomething unholy. Abomination you never met before in \nyour short life.";
	msg += "\n\tIt's rattling bones made blood-chilling noise. Yet it didn't \nnoticed you yet. Or maybe it didn't want to notice you?";
	msg += "\n\tThe skeleton was on your way, on the only path on your \nholy mission. You didn't meet previously any enemy in this \nlabirynth.";
	msg += "\n\tThat could mean something. Down there could be either \nSanctuary you need to find or your demise.";
	msg += "\n\tBut still, only option for you was to fight.";
	msg += "\n\tDespite of fear, you knew it shouldn't have a chance.";

	_eventMsg.setString(msg);
}

void EventsHandler::triggerEnemyInstructionsEvent()
{

	std::string msg = "";

	msg += "                                 [INSTRUCTIONS]\n";
	msg += "\n\tWalk into enemy to attack him. With every attack you use \na portion of stamina. When you deplete it, you deal reduced \ndamage and stop gaining proficiences.";
	msg += "\n\tUpper left corner contains three bars, each show current \nhealth, stamina and experience. More detailed info is in \n[C]haracter screen. Once your HP drops to 0, hero dies and \ngame ends.";
	msg += "\n\tIn addition to natural regeneration, you can [r]est a turn to \nrestore some stamina and health. Better option is using items, because \nenemies respawns and get stronger after few turns.";
	msg += "\n\tRemember that not every monster is aggresive, but others \nwill chase you relentlessly until one side dies.";
	msg += "";
	msg += "";


	_eventMsg.setString(msg);
}


void EventsHandler::triggerKilledFirstEnemyEvent()
{
	std::string msg = "";

	msg += "\tIt was a strange feeling. Very different from fighting flesh \nand blood humans, as you did in academy.";
	msg += "\n\tThe living dead made no noise besides rattling, it didn't \nscream from pain nor agony. It was so unsettling, you had \ntroubles with concentrating on fight.";
	msg += "\n\tYet stranger was the feeling of power which came after \nturning skeleton into a pile of bones. \n\tYou felt a little stronger.";
	msg += "Not much. Only by a bit. But you \ncertainly felt it. Where did that power came from?";
	msg += "\n\tAnd again, was it curse or blessing?";

	_eventMsg.setString(msg);
}

void EventsHandler::triggerHalfwayToBossEvent()
{
	std::string msg = "";

	msg += "\tMost of rooms started to look similar. Many times you \nthought you already was in room, but after some inspections \nyou were proven wrong.";
	msg += "\n\tAnd now, in one of the corridors, you noticed a writing on a \nwall made of blood. It was really smudgy, but you were able \nto discern two words.";
	msg += "\n\t\"CURSE\" and \"PRIESTESS\". Those words wasn't in same \nverse or column.";
	msg += "\n\tMaybe Priestess could cure curses? Or the Kingdom was \ncursed...?";
	msg += "\n\tAnd one was sure - someone was here. Blood wasn't fresh, \nso maybe many days have passed since then...";
	msg += "\n\tThat could mean that Priestess is here.";
	msg += "\n\tFilled with hope and determination, you pressed forward.";


	_eventMsg.setString(msg);
}

void EventsHandler::triggerFirstBossEvent()
{
	std::string msg = "";
	msg += "\tAfter you stepped forward, the doors closed with clicking \nsound. Before you stood a knight clad in silvery armour.";
	msg += "\n\t\"Cease your nonsense, fool!\" - he shouted, his voice filled \nwith anger. - \"You shall not threat my Lady any longer!";
	msg += "\n\tYou felt relieved despite situation. You told him you are \nsearching Priestess by the king's order.";
	msg += "\n\t\"Yes, I know that. But I can't let you pass. She is Cebil's \nvoice. Her presence shouldn't be tainted by the likes of you.\"";
	msg += "\n\tYou stared at him speechless. What was meaning of this?!";
	msg += "\n\tYou took few steps forward, trying to explan everything, \nbut... it seemed meaningless";
	msg += "\n\t\"You are not Cebil's servant. You shall not come any \ncloser, nonbeliever\" - he said with disguist.";
	msg += "\n\tHe took step forward, pulling sword out of his sheath.";
	msg += "\n\tNo words were able to solve this situation...";


	_eventMsg.setString(msg);
}

void EventsHandler::triggerFirstBossKilledEvent()
{
	std::string msg = "";
	msg += "\tHe coughed blood while lying on the cold floor.";
	msg += "\n\t\"You... are stronger than I... thought... \" - he \nsaid with weak voice. \"But... with no will...\"";
	msg += "\n\tA loud clicking sound filled room. Doors were once again \nopen.";
	msg += "\n\t\"Ah... so clear... my mind...\" - he whispered. - \"Your... your \ndetermination and willpower... are all that matter before her...\"";
	msg += "\n\tYou nodded at knight's words. He changed, just like that. \nLike something left his mind.";
	msg += "\n\tYou closed his eyes with hand and moved forward. In your \nmind one question has been born.";
	msg += "\n\tAre you doing the right thing...?";


	_eventMsg.setString(msg);
}

void EventsHandler::triggerPriestessFoundHeroWeakEvent()
{
	std::string msg = "";
	msg += "\tShe was dazzingly beautiful. Her looks gave strange, holy \nfeeling.";
	msg += "\n\t\"Ah, and so you came, young one\" - she said with bright \nsmile.";
	msg += "You could only nod with your head and watch as \nentranced. - \"Welcome to my palace. I hope you like it.\nFrom now on... you will serve here.\"";
	msg += "\n\tShe came closer, gently caresing your face with slender \narms. Bad feelings arose in your chest, but you bruised them \naside.";
	msg += "\n\t\"It's too bad. Oracles aren't exacly what they should be. \nYou are simply not strong enough for it.\"";
	msg += "\n\tYou froze in place, filled with dread. Something was in \nyour mind.";
	msg += "\n\t\"Your will... haha!\" - she laughed heartely. - \"What is it? \nYou are so weak-willed, you never could fullfill destiny, \nyou fool!\"";


	_eventMsg.setString(msg);
}

void EventsHandler::triggerPriestessFoundEvent()
{

	std::string msg = "";
	msg += "\tShe was surrounded in sinister aura you never felt.";
	msg += "\n\tThough she was clad in white dress, it looked pitch black \nfor you. She gave off some kind of unholy aura.";
	msg += "\n\tAnd yet... you knew. She was the Priestess.";
	msg += "\n\tThe one you were looking so hard for so long.";
	msg += "\n\tAnd it looks like she was responsible for everything.";
	msg += "\n\t\"So... you came, little hero. Is it... all?\" - she asked. - \"You \nknow everything, right? That's why you are here.And that's \nwhy I see this... sheen in your eyes.\"";
	msg += "\n\tYou prepared your weapon. She musn't live any second \nlonger.";
	msg += "\n\t\"Then... so be it, little hero\" - she said with sad voice.";


	_eventMsg.setString(msg);
}

void EventsHandler::triggerPriestessKilledEvent()
{

	std::string msg = "";
	msg += "\tIn the last moment you noticed.";
	msg += "\n\tShe was smiling in a relief. Her pale lips parted as if she \nwanted to say something, but no sound came out.";
	msg += "\n\tShe just fell on the ground, her body covered with wounds \nand blood. On her face was only smile with no shade of hate \nor regret.";
	msg += "\n\tThe light in the room dimmed a little for a second and you \nfelt something crawling into your soul. Something cold as \ndeath, something hot as hellish flames.";
	msg += "\n\tThe power, the curse grew stronger within you.";
	msg += "\n\tThe Priestess was dead. Everyone was doomed sooner or \nlater.";
	msg += "\n\tAnd you were trapped here, in this cursed labirynth, with \nno way to tell that to anybody.";
	msg += "\n\tIn the end, you never knew anything...";


	_eventMsg.setString(msg);
}



void EventsHandler::triggerPriestessFoundHeroLostEvent()
{
	std::string msg = "";
	msg += "\tYou felt strength leaving your body, unable to do anything \nmeaningful. ";
	msg += "\n\tShe knew that and beacuse of that she smiled menacingly. \nHer enitre beauty vanished in a split second as if it was mere \nillusion.";
	msg += "You were staring at her, terrified so much it was \ndriving you crazy.";
	msg += "\n\tShe took ornate, ceremonial knife and slashed open your \nthroat. Blood droplets gathered at her hand and started to \nfloat near her head.";
	msg += "\n\t\"Go, my dear slave\" - she said with cold smile. - \"Go and \nfight for me. Go and die for me. Go and create a world of my \ndreams.\"";
	msg += "\n\tAnd so your body moved with your mind in her hands.";


	_eventMsg.setString(msg);

}

void EventsHandler::triggerHeroDiesEvent()
{
	std::string msg = "";

	msg += "\tThe light flickered few times and everything went dark.";
	msg += "\n\tPain. Hate. Hope. Love. Dreams. Eveything... seems now \nso small and insignificant.";
	msg += "\n\tBesides that last ounce of despair. You failed.";
	msg += "\n\tYour body fell limply on the floor. Strength was leaving \nfaster and faster and your body was getting stiffer and colder.";
	msg += "\n\tAnd... it twitched. Your body moved without your control.";
	msg += "\n\tIt grabbed something, maybe weapon, maybe shield. Took \na step forward. Step to the side. It was roaming.";
	msg += "\n\tJust like all other living dead, your body was influenced \nby foreign will. \n\tAnd so your body relentlessly searched for something.";

	_eventMsg.setString(msg);
}

void EventsHandler::triggerHeroDiesSecondEvent()
{
	std::string msg = "";

	msg += "\t                 BUT IT NEVER FOUND HER.";

	_eventMsg.setString(msg);
}