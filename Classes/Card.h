#ifndef __CARD_SPRITE_H__
#define __CARD_SPRITE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

#define XAP false
#define NGUA true

class Card : public cocos2d::Sprite {
	public:
	static Texture2D* cardsImage;
	static int cardWidth;
	static int cardHeight;

	Card();
	~Card();
	static Card* create(int index, int element, bool state);
	//Sprite
	//void initOptions();
	void addTouchEvents();
	//Bai
	int cardIndex = 0, cardElement = 0;
	int zIndex = 1;
	__declspec(property(get = getprop, put = putprop)) bool cardState;
	//Method
	bool _state = false;
	void putprop(bool j) {
		_state = j;
		if (!_state) {
			

		}else {
			
		}
	}

	bool getprop() {
		return _state;
	}
	private:
	
};

class Cards {
	public:
	static Card* allCard[52];
	static void LoadData();
};
#endif
