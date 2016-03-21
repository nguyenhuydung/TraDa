#include "cocos2d.h"
#include "RankingScene.h"
#include "ui/CocosGUI.h"
#include "GameTienLenMNScene.h"

USING_NS_CC;
using namespace cocos2d::ui;

RankingScene::RankingScene() {
}


RankingScene::~RankingScene() {
}

bool RankingScene::init() {
	//////////////////////////////
	// 1. super init first
	if (!Layer::init()) {
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	// add "HelloWorld" splash screen"
	auto sprite = Sprite::create("ranking.png");
	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	sprite->setScaleX(visibleSize.width / sprite->getContentSize().width);
	sprite->setScaleY(visibleSize.height / sprite->getContentSize().height);
	// add the sprite as a child to this layer
	this->addChild(sprite, 0);
	//Nut play:
	auto button = Button::create("score.play.button.nor.png", "score.play.button.prd.png", "score.play.button.dis.png");
	button->setPosition(Vec2(visibleSize.width - button->getContentSize().width, visibleSize.height - button->getContentSize().height));
	button->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type) {
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED:
				Director::getInstance()->replaceScene(TransitionFade::create(1, GameTienLenMNScene::createScene(), Color3B(0, 0, 0)));
				break;
			default:
				break;
		}
	});
	this->addChild(button);

	auto touchListener = EventListenerKeyboard::create();
	touchListener->onKeyReleased = [](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event) {
		if (keyCode == EventKeyboard::KeyCode::KEY_BACK) {
			Director::getInstance()->end();
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	return true;
}


Scene* RankingScene::createScene() {
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	// 'layer' is an autorelease object
	auto layer = RankingScene::create();
	// add layer as a child to scene
	scene->addChild(layer);
	// return the scene
	return scene;
}