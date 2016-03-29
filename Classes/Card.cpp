#include "Card.h"

USING_NS_CC;

Card* Card::allCard[52];

Card::Card() {
}

Card::~Card() {
}

Texture2D* Card::cardsImage = nullptr;
float Card::cardWidth = 0;
float Card::cardHeight = 0;



Card* Card::create(int index, int element, std::function<void()> on_select, std::function<void()> on_select_ok) {
	auto pSprite = new Card();
	pSprite->cardIndex = index;
	pSprite->cardElement = element;
	pSprite->ChangeState(CARD_STATE_NORM);
	//pSprite->seTe
	pSprite->addTouchEvents(on_select, on_select_ok);
	//pSprite->initWithFile("", Rect(0, 0, 11, 11));
	return pSprite;
}

void Card::addTouchEvents(std::function<void ()> on_select, std::function<void ()> on_select_ok) {
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [&](Touch* touch, Event* event) {
		auto p = touch->getLocation();
		auto rect = this->getBoundingBox();
		if (rect.containsPoint(p) && (this->cardState != CARD_STATE_DOWN)) {
			//this->zIndex = this->getGlobalZOrder();
			//this->setGlobalZOrder(100);
			//this->ChangeState(!this->cardState);
			CCLOG("Begin touch card: %d - %d", this->cardIndex, this->cardElement);
			on_select();
			return true; // to indicate that we have consumed it.
		}
		return false; // we did not consume this event, pass thru.
	};

	listener->onTouchMoved = [=](Touch* touch, Event* event) {
		//this->setPosition(this->getPosition() + touch->getDelta());
	};

	listener->onTouchEnded = [=](Touch* touch, Event* event) {
		// card
		//this->setPosition(this->getPosition() + touch->getDelta());
		//this->setGlobalZOrder(this->zIndex);
		//Snap bai vao vị trí bàn user:
		CCLOG("End touch card: %d - %d", this->cardIndex, this->cardElement);
		on_select_ok();
		this->ChangeState(this->cardState == CARD_STATE_SELT ? CARD_STATE_NORM : CARD_STATE_SELT);
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);
}

void Card::ChangeState(cardstate state) {
	cardState = state;
	if ((cardState == CARD_STATE_NORM) || (cardState == CARD_STATE_DROP)) {
		//Set RECT vao ảnh quân bài
		this->setTextureRect(Rect(cardIndex * cardWidth, cardElement * cardHeight, cardWidth, cardHeight));
	}
	if (cardState == CARD_STATE_DOWN) {
		//Bài đang xấp
		this->setTextureRect(Rect(0, cardHeight * 4, cardWidth, cardHeight));
	}
	if (cardState == CARD_STATE_SELT) {
		//Set RECT vao ảnh quân bài
		this->setTextureRect(Rect(cardIndex * cardWidth, (cardElement + 5) * cardHeight, cardWidth, cardHeight));
	}
}

/*
* Tai file allcard vao cache sprite
*/
void Card::loadData(std::function<void()> on_select, std::function<void()> on_select_ok) {
	cardsImage = Director::getInstance()->getTextureCache()->addImage("cardall.png");
	cardWidth = cardsImage->getContentSize().width / 13;
	cardHeight = cardsImage->getContentSize().height / 10;
	if (cardsImage) {
		for (auto i = 0; i < 52; i++) {
			allCard[i] = create(i % 13, i / 13, on_select, on_select_ok);
			allCard[i]->initWithTexture(cardsImage, Rect(0, cardHeight * 4, cardWidth, cardHeight));
		}
	}
}

