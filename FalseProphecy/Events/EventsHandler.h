#ifndef EVENTS_EVENTSHANDLER
#define EVENTS_EVENTSHANDLER


#include <vector>

#include "SFML/Graphics.hpp"

#include "../LoadFromResource.h"
#include "../UIResource.h"

#include "../StructsEnums.h"

class EventsHandler : public sf::Drawable{

public:
	GameEvents getEventsStructure();
	void restoreEventData(GameEvents &events);
	
	void printStruct();

	bool getEventStatus();

	void centerText();


	void resizeByGameWindow(sf::Vector2f center);

	void handleInput(int key, bool isPressed);

	void showMessage();

	EventsHandler();
	~EventsHandler();
	 
	void refreshEventWindow();

	void triggerEvent(int event_number);

	void resetEvents();

	void updateEventTracker(Hero_Profile hero_stats, sf::Vector2i hero_pos, int curr_map = -1);


private:

	std::vector<std::string> _messages;

	sf::RenderTexture _renderTexture;
	sf::Sprite _sprite;

	sf::RectangleShape _eventWindow;

	sf::Font _font;
	sf::Text _eventMsg;
	sf::Text _eventConfirmUpper;
	sf::Text _eventConfirmLower;

	int _messageState;

	bool isEventMessage = false;


	GameEvents _events;
	Hero_Profile _hero_stats;
	sf::Vector2i _hero_pos;



private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;



	//NAME: trigger<NAME_OF_EVENT>Event
	//should be in chronological order
	//start of the game
	void triggerStartOfGameEvent();
	//first instructions about movement
	void triggerFirstInstructionsEvent();
	//trigger after taking a first step
	void triggerFirstStepEvent();
	//trigger looking for items in room
	void triggerItemsFirstLookoutEvent();
	//trigger instructions for inventory
	void triggerItemsInstructionEvent();
	//trigger meeting the first enemy (bones?)
	void triggerFirstEnemyEvent();
	//trigger meeting the first enemy (bones?) second part
	void triggerFirstEnemySecondEvent();
	//trigger instructions about enemies
	void triggerEnemyInstructionsEvent();
	//trigger killing the first enemy (bones?)
	void triggerKilledFirstEnemyEvent();
	//trigger after reaching 20th room, half way to boss
	void triggerHalfwayToBossEvent();
	//trigger first boss
	void triggerFirstBossEvent();
	//trigger after killing first boss
	void triggerFirstBossKilledEvent();

	//trigger finding priestess when hero is too weak
	void triggerPriestessFoundHeroWeakEvent();
	//trigger when priestess if found
	void triggerPriestessFoundEvent();
	//trigget killing priestess aka winning game
	void triggerPriestessKilledEvent();

	//trigger when hero died to priestess
	void triggerPriestessFoundHeroLostEvent();
	//trigger after dying
	void triggerHeroDiesEvent();
	//trigger after dying part two
	void triggerHeroDiesSecondEvent();

};





#endif //!EVENTS_EVENTSHANDLER