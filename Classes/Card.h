#ifndef __CARD_SPRITE_H__
#define __CARD_SPRITE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class Card : public cocos2d::Sprite {
	public:
	static Texture2D* cardsImage;
	static float cardWidth;
	static float cardHeight;
	
	Card();
	~Card();
	static Card* create(int index, int element, bool state);
	//Sprite
	//void initOptions();
	void addTouchEvents();
	//Bai
	int cardIndex = 0, cardElement = 0;
	int zIndex = 1;
	bool cardState = false;
	void ChangeState(bool state);
};

class Cards {
	public:
	static Card* allCard[52];
	static void LoadData();
};
#endif
