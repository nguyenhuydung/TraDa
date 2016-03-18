#include "cocos2d.h"
#include "RankingScene.h"
#include "Card.h"

USING_NS_CC;

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
	auto sprite = Sprite::create("board.png");

	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	sprite->setScaleX(visibleSize.width / sprite->getContentSize().width);
	sprite->setScaleY(visibleSize.height / sprite->getContentSize().height);
	// add the sprite as a child to this layer
	this->addChild(sprite, 0);
	for (auto i = 0; i < 52; i++) {
		Cards::allCard[i]->setPosition(Vec2(RandomHelper::random_int<int>(0, 1280), RandomHelper::random_int<int>(0, 720)));
		Cards::allCard[i]->ChangeState(i < 30);
		Cards::allCard[i]->setScaleX(visibleSize.width / sprite->getContentSize().width);
		Cards::allCard[i]->setScaleY(visibleSize.height / sprite->getContentSize().height);
		addChild(Cards::allCard[i], 1);
	}
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