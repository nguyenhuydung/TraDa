#include "GameListScene.h"

USING_NS_CC;

GameListScene::GameListScene() {
}


GameListScene::~GameListScene() {
}

Scene* GameListScene::createScene() {
	auto scene = Scene::create();
	auto layer = create();
	scene->addChild(layer);
	return scene;
}

bool GameListScene::init() {
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
	return true;
}
