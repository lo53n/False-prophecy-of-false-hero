#ifndef MAP_BUILDERPATTERN_MAPBUILDER
#define MAP_BUILDERPATTERN_MAPBUILDER

#include "LandBuilderPattern.h"

class MapBuilder{

private:
	LandBuilder *_landbuilder;


public:
	MapBuilder();
	~MapBuilder();

	void setLandBuilder(LandBuilder* lb);

	LandBuilder* getLandBuilder();
	Map& getMap();

	void buildMap(std::vector<std::vector<char>> *mapTemplate);


};



#endif //!MAP_BUILDERPATTERN_MAPBUILDER