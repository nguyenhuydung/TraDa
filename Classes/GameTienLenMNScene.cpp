#include "GameTienLenMNScene.h"
#include "Card.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* GameTienLenMNScene::createScene() {
	auto scene = Scene::create();
	auto layer = GameTienLenMNScene::create();
	scene->addChild(layer);
	return scene;
}

//GameTienLenMNScene* GameTienLenMNScene::loadScene(std::function<void()> onCompleted) {
//	onCompleted();
//
//	
//	return nullptr;
//}

bool GameTienLenMNScene::init() {
	if (!Layer::init()) {
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto sprite = Sprite::create("board.png");
	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	sprite->setScaleX(visibleSize.width / sprite->getContentSize().width);
	sprite->setScaleY(visibleSize.height / sprite->getContentSize().height);
	// add the sprite as a child to this layer
	this->addChild(sprite, 0);
	//khoi tao 52 quan bai
	for (auto i = 0; i < 52; i++) {
		Cards::allCard[i]->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		Cards::allCard[i]->ChangeState(false);
		Cards::allCard[i]->setScaleX(visibleSize.width / sprite->getContentSize().width);
		Cards::allCard[i]->setScaleY(visibleSize.height / sprite->getContentSize().height);
		addChild(Cards::allCard[i], 1);
	}
	//Vẽ nút quit và nut Config
	auto btnConfig = ui::Button::create("play.back.nor.png", "play.back.put.png", "play.back.dis.png");
	btnConfig->setPosition(Vec2(visibleSize.width - btnConfig->getContentSize().width - btnConfig->getContentSize().width, visibleSize.height - btnConfig->getContentSize().height));
	btnConfig->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type) {
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED:
				//Director::getInstance()->replaceScene(TransitionFade::create(1, GameTienLenMNScene::createScene(), Color3B(0, 0, 0)));
				break;
			default:
				break;
		}
	});
	this->addChild(btnConfig);

	auto btnBack = ui::Button::create("play.back.nor.png", "play.back.put.png", "play.back.dis.png");
	btnBack->setPosition(Vec2(visibleSize.width - btnConfig->getContentSize().width, visibleSize.height - btnConfig->getContentSize().height));
	btnBack->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type) {
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED:
				//Director::getInstance()->replaceScene(TransitionFade::create(1, GameTienLenMNScene::createScene(), Color3B(0, 0, 0)));
				break;
			default:
				break;
		}
	});
	this->addChild(btnBack);
	//Vẽ nút điều khiển đánh bài
	do {


		//Chia bai

		//Chọn người đánh đầu tiên:

		//
		return true;
	} while (true);
	return true;
}

GameTienLenMNScene::GameTienLenMNScene() {
	
}


GameTienLenMNScene::~GameTienLenMNScene() {
}
