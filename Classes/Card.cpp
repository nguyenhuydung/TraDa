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
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [&](Touch* touch, Event* event) {
		auto p = touch->getLocation();
		auto rect = this->getBoundingBox();
		if (rect.containsPoint(p)) {
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
		//this->setPosition(this->getPosition() + touch->getDelta());
		//this->setGlobalZOrder(this->zIndex);
		//Snap bai vao vị trí bàn user:
		if (this->cardState) {
			if (!this->selected) {
				this->setPositionY(this->getPositionY() + 5);
				this->selected = true;
			} else {
				this->setPositionY(this->getPositionY() - 5);
				this->selected = false;
			}
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 30);
}
/*-----*/

Card* Cards::allCard[52];

void Card::ChangeState(bool state) {
	cardState = state;
	if (cardState) {
		//Set RECT vao ảnh quân bài
		if (this->getTexture() == nullptr) {
			this->initWithTexture(cardsImage, Rect(cardIndex* cardWidth, cardElement* cardHeight, cardWidth, cardHeight));
		} else {
			this->setTextureRect(Rect(cardIndex* cardWidth, cardElement* cardHeight, cardWidth, cardHeight));
		}
	} else {
		//Bài đang xấp
		if (this->getTexture() != nullptr) {
			this->setTextureRect(Rect(0, cardHeight * 4, cardWidth, cardHeight));
		} else {
			this->initWithTexture(cardsImage, Rect(0, cardHeight * 4, cardWidth, cardHeight));
		}

	}
}

void Cards::loadData() {
	Card::cardsImage = Director::getInstance()->getTextureCache()->addImage("cardall.png");
	Card::cardWidth = Card::cardsImage->getContentSize().width / 13;
	Card::cardHeight = Card::cardsImage->getContentSize().height / 5;
	if (Card::cardsImage) {
		for (auto i = 0; i < 52; i++) {
			allCard[i] = Card::create(i % 13, i / 13, RandomHelper::random_int(0, 1) == 0);
		}
	}
}

