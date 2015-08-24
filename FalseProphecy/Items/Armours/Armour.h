#ifndef ITEM_ARMOURS_ARMOUR
#define ITEM_ARMOURS_ARMOUR



#include "../Item.h"
#include "../../StructsEnums.h"

class Armour : public Item{


public:

	void getItemStats();
	Armour_struct getStatsStruct();

	Armour();
	Armour(Armour_struct stats);
	~Armour();

private:

	Armour_struct _stats;



	//////////////////
	//Magic Numbers!//
	//////////////////


	std::string __DEFAULT_CHAINMAIL_BODY_IMAGE__ = "data\\img\\armour\\chainmailbodydefault.png";
private:


};


#endif //!ITEM_ARMOURS_ARMOUR