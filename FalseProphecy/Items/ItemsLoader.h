#ifndef ITEMS_ITEMSLOADER
#define ITEMS_ITEMSLOADER



#include "Weapons\WeaponsLoader.h"

class ItemsLoader {

public:
	void loadResources();
	void loadWeapons();

private:
	std::vector<std::string> weapons;

};


#endif //!ITEMS_ITEMSLOADER