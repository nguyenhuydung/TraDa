#include "Card.h"

USING_NS_CC;

Card::Card() {
}

Card::~Card() {
}

Texture2D* Card::cardsImage = nullptr;
int Card::cardWidth = 0;
int Card::cardHeight = 0;

Card* Card::create(int index, int element, bool state) {
	auto pSprite = new Card();
	pSprite->cardIndex = index;
	pSprite->cardElement = element;
	pSprite->cardState = state;
	pSprite->addTouchEvents();
	return pSprite;
}

void Card::addTouchEvents() {
	auto listener = cocos2d::EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event) {
		auto p = touch->getLocation();
		auto rect = this->getBoundingBox();
		if (rect.containsPoint(p)) {
			this->zIndex = this->getGlobalZOrder();
			this->setGlobalZOrder(100);
			return true; // to indicate that we have consumed it.
		}
		return false; // we did not consume this event, pass thru.
	};

	listener->onTouchMoved = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
		this->setPosition(this->getPosition() + touch->getDelta());
	};

	listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
		this->setPosition(this->getPosition() + touch->getDelta());
		this->setGlobalZOrder(this->zIndex);
		//Snap bai vao vị trí bàn user:

	};
	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 30);
}

/*-----*/
Card* Cards::allCard[52];

void Cards::LoadData() {
	auto* image = new Image();
	image->initWithImageFile("Cards.png");
	Card::cardsImage = new Texture2D();
	Card::cardsImage->initWithImage(image);

	for (auto i = 0; i < 52; i++) {
		allCard[i] = Card::create(i % 13, i / 13, false);
	}
}

