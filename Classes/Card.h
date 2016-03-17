#ifndef __CARD_SPRITE_H__
#define __CARD_SPRITE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class Card : public cocos2d::Sprite {
	public:
	Card();
	~Card();
	Card* create(std::string filename, Rect rect);
	//Sprite
	void initOptions();
	void addEvents();
	//Bai
	int cardIndex = 0, cardElement = 0;
	int zIndex = 1;

	//Method
	private:
};

#endif
