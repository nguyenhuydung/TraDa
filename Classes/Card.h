#ifndef __CARD_SPRITE_H__
#define __CARD_SPRITE_H__

#include "cocos2d.h"

USING_NS_CC;

enum cardstate {
	CARD_STATE_NORM, CARD_STATE_SELT, CARD_STATE_DOWN, CARD_STATE_DROP
};

class Card : public Sprite {
	public:
	static Texture2D* cardsImage;
	static Texture2D* cardsImageSelected;
	static float cardWidth;
	static float cardHeight;
	static Card* allCard[52];
	static void loadData(std::function<void()> on_select, std::function<void()> on_select_ok);

	Card();
	~Card();
	static Card* create(int index, int element, std::function<void()> on_select, std::function<void()> on_select_ok);
	//Sprite
	void addTouchEvents(std::function<void()> on_select, std::function<void()> on_select_ok);
	//Bai
	int cardIndex = 0, cardElement = 0;
	cardstate cardState = CARD_STATE_NORM;
	int zIndex = 1;
	///trang thai xap
	bool daChia = false;
	
	void ChangeState(cardstate state);
};

#endif

