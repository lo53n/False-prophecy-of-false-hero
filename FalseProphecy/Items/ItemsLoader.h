#ifndef ITEMS_ITEMSLOADER
#define ITEMS_ITEMSLOADER



#include "Weapons\WeaponsLoader.h"
#include "Armours\ArmoursLoader.h"

class ItemsLoader {

public:
	void loadResources();
	void loadWeapons();
	void loadArmours();

	ItemsLoader(std::shared_ptr<ErrorHandler> handler);

private:

	std::shared_ptr<ErrorHandler> _errorHandler;
};


#endif //!ITEMS_ITEMSLOADER