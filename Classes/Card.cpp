#include "Card.h"

USING_NS_CC;

Card::Card() {
}

Card::~Card() {
}

Card* Card::create(std::string filename, Rect rect) {
	auto img = new Image();
	img->initWithImageFile("cards.png");
	auto texture = new Texture2D();
	texture->initWithImage(img);
	auto pSprite = new Card();
	if (pSprite->initWithTexture(texture, rect)) {
		pSprite->autorelease();
		//pSprite->initOptions();
		//pSprite->addEvents();
		return pSprite;
	}
	CC_SAFE_DELETE(pSprite);
	return nullptr;
}

