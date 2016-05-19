#include "cocos2d.h"
#include "RankingScene.h"
#include "ui/CocosGUI.h"
#include "GameTienLenMNScene.h"
#include "HelloWorldScene.h"
#include "GridViewGlobal.h"
#ifdef SDKBOX_ENABLED
#include "PluginFacebook/PluginFacebook.h"
#endif

USING_NS_CC;
using namespace ui;

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
	button->setScaleX(visibleSize.width / sprite->getContentSize().width);
	button->setScaleY(visibleSize.height / sprite->getContentSize().height);
	button->setTitleText("Chơi ngay");
	button->setTitleFontSize(20);
	button->setTitleColor(Color3B(33, 33, 33));
	button->setPosition(Vec2(visibleSize.width * 1180.0f / sprite->getContentSize().width, visibleSize.height * 670.0f / sprite->getContentSize().height));
	button->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type) {
			case Widget::TouchEventType::BEGAN:
				break;
			case Widget::TouchEventType::ENDED:
				Director::getInstance()->replaceScene(TransitionFade::create(1, GameTienLenMNScene::createScene(), Color3B(0, 0, 0)));
				break;
			default:
				break;
		}
	});
	this->addChild(button);

	//Nut dis connect facebook:
	auto disConnectFace = Button::create("score.play.button.nor.png", "score.play.button.prd.png", "score.play.button.dis.png");
	disConnectFace->setScaleX(visibleSize.width / sprite->getContentSize().width);
	disConnectFace->setScaleY(visibleSize.height / sprite->getContentSize().height);
#ifdef SDKBOX_ENABLED
	if (sdkbox::PluginFacebook::isLoggedIn()) {
		disConnectFace->setTitleText("Out Facebook");
	} else {
		disConnectFace->setTitleText("Connect Facebook");
	}
#else
	disConnectFace->setTitleText("Facebook");
	disConnectFace->setEnabled(false);
#endif
	disConnectFace->setTitleFontSize(20);
	disConnectFace->setTitleColor(Color3B(33, 33, 33));
	disConnectFace->setPosition(Vec2(visibleSize.width * 1020 / sprite->getContentSize().width, visibleSize.height * 670.0f / sprite->getContentSize().height));
	disConnectFace->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type) {
			case Widget::TouchEventType::BEGAN:
				break;
			case Widget::TouchEventType::ENDED:
			#ifdef SDKBOX_ENABLED
				if (sdkbox::PluginFacebook::isLoggedIn()) {
					sdkbox::PluginFacebook::logout();
				} else {
					sdkbox::PluginFacebook::login();
				}
			#endif
				break;
			default:
				break;
		}
	});
	this->addChild(disConnectFace);

	auto touchListener = EventListenerKeyboard::create();
	touchListener->onKeyReleased = [](EventKeyboard::KeyCode keyCode, Event *event) {
		if (keyCode == EventKeyboard::KeyCode::KEY_BACK) {
			Director::getInstance()->end();
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	userdata = UserDefault::sharedUserDefault();
	auto name = userdata->getStringForKey("PLAYER_NAME");
	auto lblName = Label::create(name, "Arial", 20);
	lblName->setPosition(Vec2(visibleSize.width * 115.0f / sprite->getContentSize().width, visibleSize.height * 505.0f / sprite->getContentSize().height));
	this->addChild(lblName);

	/// test reset data
	///Nut dis connect facebook:
	auto resetData = Button::create("score.play.button.nor.png", "score.play.button.prd.png", "score.play.button.dis.png");
	resetData->setScaleX(visibleSize.width / sprite->getContentSize().width);
	resetData->setScaleY(visibleSize.height / sprite->getContentSize().height);
	resetData->setTitleText("Flush User");
	resetData->setTitleFontSize(20);
	resetData->setTitleColor(Color3B(33, 33, 33));
	resetData->setPosition(Vec2(visibleSize.width * 860 / sprite->getContentSize().width, visibleSize.height * 670.0f / sprite->getContentSize().height));
	resetData->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type) {
			case Widget::TouchEventType::BEGAN:
				break;
			case Widget::TouchEventType::ENDED:
				//u = UserDefault::sharedUserDefault();
				userdata->flush();
				Director::getInstance()->replaceScene(TransitionFade::create(1, HelloWorld::createScene(), Color3B(0, 0, 0)));
				break;
			default:
				break;
		}
	});
	this->addChild(resetData);

	auto layer = GridViewTestLayer::create();
	this->addChild(layer);
	
	return true;
}


Scene* RankingScene::createScene() {
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	// 'layer' is an autorelease object
	auto layer = create();
	// add layer as a child to scene
	scene->addChild(layer);
	// return the scene
	return scene;
}