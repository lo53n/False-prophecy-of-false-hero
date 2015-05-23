#ifndef MAP_BUILDERPATTERN_LANDBUILDER
#define MAP_BUILDERPATTERN_LANDBUILDER

#include <vector>

#include "Map.h"


class LandBuilder{

protected:
	Map *_map;

public:
	LandBuilder();
	~LandBuilder();

	void setMap(Map* map);

	Map& getMap();

	virtual void putCommon(int *i, int *j, int *maptile) = 0;
	virtual void putRock(int *i, int *j, int *maptile) = 0;
	virtual void putSpecial(int *i, int *j, int *maptile) = 0;
	//virtual void endBuilding(){ map_->setMapLayer(); }

};






#endif //!MAP_BUILDERPATTERN_LANDBUILDER