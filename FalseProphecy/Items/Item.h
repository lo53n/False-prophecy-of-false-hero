#ifndef ITEM_ITEM
#define ITEM_ITEM

#include <cstdlib>
#include <iostream>
#include <vector>

#include "SFML/Graphics.hpp"

#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/base_object.hpp>


class Item : public sf::Drawable{

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar  & _itemType;
	}
public:

	void setItemTexture();

	void setImagesPosition(sf::Vector2f newPosition);

	void getItemStats();
	int getItemType();

	Item();
	Item(int item_type);
	~Item();


	void restoreData();
	int _itemType;

public:

	bool _isItemVisible = false;
	bool _isBackgroundVisible = false;

	sf::Texture _itemTexture;
	sf::Texture _backgroundTexture;

	sf::RectangleShape _itemShape;
	sf::RectangleShape _backgroundShape;

	////////////////////////
	//Public Magic Numbers//
	////////////////////////

	std::string __TILE_IMAGE__ = "data\\img\\etc\\backtile.png";

private:






private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(Item)



#endif //!!ITEM_ITEM