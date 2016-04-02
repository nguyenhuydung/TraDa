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
bool Card::loadedData = false;


Card* Card::create(int index, int element) {
	auto pSprite = new Card();
	pSprite->cardIndex = index;
	pSprite->cardElement = element;
	pSprite->ChangeState(CARD_STATE_NORM);
	//pSprite->seTe
	pSprite->addTouchEvents();
	//pSprite->initWithFile("", Rect(0, 0, 11, 11));
	return pSprite;
}

void Card::addTouchEvents() {
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [&](Touch* touch, Event* event) {
		auto p = touch->getLocation();
		auto rect = this->getBoundingBox();
		if (rect.containsPoint(p) && (this->cardState != CARD_STATE_DOWN)) {
			//this->zIndex = this->getGlobalZOrder();
			//this->setGlobalZOrder(100);
			//this->ChangeState(!this->cardState);
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
		this->ChangeState(this->cardState == CARD_STATE_SELT ? CARD_STATE_NORM : CARD_STATE_SELT);
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);
}

void Card::ChangeState(cardstate state) { 
	cardState = state;
	if (cardState == CARD_STATE_NORM) {
		this->setTextureRect(Rect(cardIndex * cardWidth, cardElement * cardHeight, cardWidth, cardHeight));
		this->setVisible(true);
	}
	if (cardState == CARD_STATE_DOWN) {
		this->setTextureRect(Rect(0, cardHeight * 4, cardWidth, cardHeight));
		this->setVisible(true);
	}
	if (cardState == CARD_STATE_SELT) {
		this->setTextureRect(Rect(cardIndex * cardWidth, (cardElement + 5) * cardHeight, cardWidth, cardHeight));
		this->setVisible(true);
	}
	if (cardState == CARD_STATE_HIDE) {
		this->setVisible(false);
	}
}

/*
* Tai file allcard vao cache sprite
*/
void Card::loadData() {
	if (loadedData) return;
	cardsImage = Director::getInstance()->getTextureCache()->addImage("cardall.png");
	cardWidth = cardsImage->getContentSize().width / 13;
	cardHeight = cardsImage->getContentSize().height / 10;
	if (cardsImage) {
		for (auto i = 0; i < 52; i++) {
			allCard[i] = create(i % 13, i / 13);
			allCard[i]->initWithTexture(cardsImage, Rect(0, cardHeight * 4, cardWidth, cardHeight));
		}
	}
	loadedData = true;
}

