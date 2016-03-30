﻿#ifndef __CARD_SPRITE_H__
#define __CARD_SPRITE_H__

#include "cocos2d.h"

USING_NS_CC;

///Hiển thị của Card:
enum cardstate { 
	CARD_STATE_NORM, //Hiện bình thường
	CARD_STATE_SELT, //Hiện đang được select
	CARD_STATE_DOWN, //Bài đang úp
};

class Card : public Sprite {
	public:
	static Texture2D* cardsImage;
	static Texture2D* cardsImageSelected;
	static float cardWidth;
	static float cardHeight;
	static Card* allCard[52];
	//Tải thông tin dữ liệu ảnh cho các quan bài và khởi tạo Sprite
	static void loadData();
	static bool loadedData;

	Card();
	~Card();
	static Card* create(int index, int element);
	//Sprite
	void addTouchEvents();
	//Quan bài
	int cardIndex = 0, cardElement = 0;
	//Hiển thị
	cardstate cardState = CARD_STATE_NORM; 
	int zIndex = 1;
	//Dùng cho chia bài
	bool daChia = false;
	//Dùng cho đánh
	bool daDanh = false;
	//Dùng để đổi trạng thái hiển thị
	void ChangeState(cardstate state);
};

#endif

