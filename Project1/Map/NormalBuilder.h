#ifndef MAP_NORMALBUILDER
#define MAP_NORMALBUILDER

#include "LandBuilderPattern.h"

class NormalBuilder : public LandBuilder{

public:

	NormalBuilder(){}
	~NormalBuilder(){}

	//void initializeTiles();
	void putCommon(int *i, int *j, int *maptile){};
	void putRock(int *i, int *j, int *maptile){};
	void putSpecial(int *i, int *j, int *maptile){};




};


#endif //!MAP_NORMALBUILDER