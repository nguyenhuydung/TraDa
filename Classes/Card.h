﻿#ifndef __CARD_SPRITE_H__
#define __CARD_SPRITE_H__

#include "cocos2d.h"

USING_NS_CC;

///Hiển thị của Card:
enum cardstate { 
	CARD_STATE_NORM, //Hiện bình thường
	CARD_STATE_SELT, //Hiện đang được select
	CARD_STATE_DOWN, //Bài đang úp
	CARD_STATE_HIDE  //Đã bỏ khỏi bàn
};

enum KieuXapBo {
	BO_FALSE,
	BO_RAC,
	BO_DOI,
	BO_BA,
	BO_SANH3,
	BO_SANH4,
	BO_SANH5,
	BO_SANH6,
	BO_TUQUY,
	BO_SANH7,
	BO_SANH8,
	BO_SANH9,
	BO_SANH10,
	BO_SANH11,
	BO_SANH12,
	BO_SANH13,
	BO_DOITHONG3,
	BO_DOITHONG4,
	BO_DOITHONG5,
	BO_DOITHONG6, //20 kiểu sắp bộ
};

class Card : public Sprite {
	public:
	static Texture2D* cardsImage;
	static Texture2D* cardsImageSelected;
	static float cardWidth;
	static float cardHeight;
	static Card* allCard[52];
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

