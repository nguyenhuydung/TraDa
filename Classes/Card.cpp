#include "Card.h"

USING_NS_CC;

Card::Card() {
}

Card::~Card() {
}

Texture2D* Card::cardsImage = nullptr;
float Card::cardWidth = 0;
float Card::cardHeight = 0;

Card* Card::create(int index, int element, bool state) {
	auto pSprite = new Card();
	pSprite->cardIndex = index;
	pSprite->cardElement = element;
	pSprite->ChangeState(state);
	//pSprite->seTe
	pSprite->addTouchEvents();
	//pSprite->initWithFile("", Rect(0, 0, 11, 11));
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
			this->ChangeState(!this->cardState);
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

void Card::ChangeState(bool state) {
	cardState = state;
	if (cardState) {
		//Set RECT vao ảnh quân bài
		if (this->getTexture() == nullptr) {
			this->initWithTexture(Card::cardsImage, Rect(cardIndex* Card::cardWidth, cardElement* Card::cardHeight, Card::cardWidth, Card::cardHeight));
		} else {
			this->setTextureRect(Rect(cardIndex* Card::cardWidth, cardElement* Card::cardHeight, Card::cardWidth, Card::cardHeight));
		}
	} else {
		//Bài đang xấp
		if (this->getTexture() != nullptr) {
			this->setTextureRect(Rect(0, Card::cardHeight * 4, Card::cardWidth, Card::cardHeight));
		} else {
			this->initWithTexture(Card::cardsImage, Rect(0, Card::cardHeight * 4, Card::cardWidth, Card::cardHeight));
		}

	}
}

void Cards::loadData() {
	Card::cardsImage = Director::getInstance()->getTextureCache()->addImage("cards.png");
	Card::cardWidth = Card::cardsImage->getContentSize().width / 13;
	Card::cardHeight = Card::cardsImage->getContentSize().height / 5;
	if (Card::cardsImage) {
		for (auto i = 0; i < 52; i++) {
			allCard[i] = Card::create(i % 13, i / 13, RandomHelper::random_int(0, 1) == 0);
		}
	}
}

