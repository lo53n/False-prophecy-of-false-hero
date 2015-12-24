#ifndef EVENTS_EVENTSHANDLER
#define EVENTS_EVENTSHANDLER


#include <vector>

#include "SFML/Graphics.hpp"

#include "../LoadFromResource.h"
#include "../UIResource.h"

#include "../StructsEnums.h"

class EventsHandler : public sf::Drawable{

public:

	bool getEventStatus();

	void resizeByGameWindow(sf::Vector2f center);

	void handleInput(int key, bool isPressed);

	void showMessage();

	EventsHandler();
	~EventsHandler();
	 
	void refreshEventWindow();

	void triggerEvent(int event_number);

	void updateEventTracker(Hero_Profile hero_stats, sf::Vector2i hero_pos, int curr_map = -1);

	enum EVENT_TYPE{
		START_OF_GAME,		//start of plot
		FIRST_INSTRUCTIONS, //about movement
		FIRST_STEP,			//info about laying items
		ITEMS_FIRST_LOOKOUT,//lookout for items
		ITEMS_INSTRUCTIONS	//instuctions about items



	};
	struct GameEvents{
		bool start_of_game = false;
		bool first_instructions = false;
		bool first_step = false;
		bool items_first_lookout = false;
		bool items_instructions = false;


	};

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
	int errorNumber = 0;


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


};





#endif //!EVENTS_EVENTSHANDLER