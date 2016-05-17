#include "HelloWorldScene.h"
#include "RankingScene.h"
#include "Card.h"
#include "GameTienLenMNScene.h"
#include "EnterYourName.h"

#ifdef SDKBOX_ENABLED
#include "PluginFacebook/PluginFacebook.h"
#endif
USING_NS_CC;

std::string* HelloWorld::playerName = nullptr;

Scene* HelloWorld::createScene() {
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	// 'layer' is an autorelease object
	auto layer = create();
	// add layer as a child to scene
	scene->addChild(layer);
	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init() {
	//////////////////////////////
	// 1. super init first
	if (!Layer::init()) {
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	// add "HelloWorld" splash screen"
	auto sprite = Sprite::create("splash.png");
	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	sprite->setScaleX(visibleSize.width / sprite->getContentSize().width);
	sprite->setScaleY(visibleSize.height / sprite->getContentSize().height);
	// add the sprite as a child to this layer
	this->addChild(sprite, 0);

	return true;
}

void HelloWorld::onEnter() {
	Layer::onEnter();
	this->scheduleOnce(schedule_selector(HelloWorld::finishSplash), 0.5f);
}

void HelloWorld::finishSplash(float dt) {
	auto u = UserDefault::sharedUserDefault();
	//Director::getInstance()->replaceScene(TransitionFade::create(1, EnterYourName::createScene(), Color3B(0, 0, 0)));
#ifdef SDKBOX_ENABLED
	if (sdkbox::PluginFacebook::isLoggedIn()) {
		Director::getInstance()->replaceScene(TransitionFade::create(1, RankingScene::createScene(), Color3B(0, 0, 0)));
	}
#endif

	//Director::getInstance()->replaceScene(TransitionFade::create(1, EnterYourName::createScene(), Color3B(0, 0, 0)));
	//return;
	if (u->getStringForKey("PLAYER_NAME").length() != 0) {
		Director::getInstance()->replaceScene(TransitionFade::create(1, RankingScene::createScene(), Color3B(0, 0, 0)));
	} else {
		/// Chuyển đến hỏi tên
		Director::getInstance()->replaceScene(TransitionFade::create(1, EnterYourName::createScene(), Color3B(0, 0, 0)));
	}
	
}

void HelloWorld::menuCloseCallback(Ref* pSender) {
    Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
