#include "EnterYourName.h"
#include "GameTienLenMNScene.h"
#include "RankingScene.h"
#ifdef SDKBOX_ENABLED
#include "PluginFacebook/PluginFacebook.h"
#endif
USING_NS_CC;

Scene* EnterYourName::createScene() {
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
bool EnterYourName::init() {
	//////////////////////////////
	// 1. super init first
	if (!Layer::init()) {
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	// add "HelloWorld" splash screen"
	auto sprite = Sprite::create("EnterName.png");
	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	sprite->setScaleX(visibleSize.width / sprite->getContentSize().width);
	sprite->setScaleY(visibleSize.height / sprite->getContentSize().height);
	// add the sprite as a child to this layer
	this->addChild(sprite, 0);

	scaleX = visibleSize.width / sprite->getContentSize().width;
	scaleY = visibleSize.height / sprite->getContentSize().height;

	auto _editName = ui::EditBox::create(cocos2d::Size(340.f * scaleX, 45.f * scaleY), ui::Scale9Sprite::create("frame_img.png"), nullptr, nullptr);
	_editName->setPosition(Vec2(420.0f * scaleX, 280.0f * scaleY));
	_editName->setFontSize(25);
	_editName->setFontColor(Color3B::BLACK);
	_editName->setPlaceHolder("  Name:");
	_editName->setPlaceholderFontColor(Color3B::GRAY);
	_editName->setMaxLength(8);
	_editName->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	//_editName->setDelegate(this);
	this->addChild(_editName);

	//Button login
	auto btnLogin = ui::Button::create("btn.square.nor.png", "btn.square.put.png", "btn.square.dis.png");
	btnLogin->setPosition(Vec2(542.0f * scaleX, 212.0f * scaleY));
	btnLogin->setScaleX(scaleX * 0.25f);
	btnLogin->setScaleY(scaleY* 0.25f);
	btnLogin->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type) {
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED:
			{
				auto u = UserDefault::sharedUserDefault();
				u->setStringForKey("PLAYER_NAME", _editName->getText());
				Director::getInstance()->replaceScene(TransitionFade::create(1, RankingScene::createScene(), Color3B(0, 0, 0)));
			}
				break;
			default:
				break;
		}
	});
	this->addChild(btnLogin, 0);
	auto spritel = Sprite::create("check.png");
	spritel->setPosition(Vec2(542.0f * scaleX, 212.0f * scaleY));
	spritel->setScaleX(scaleX * 0.25f);
	spritel->setScaleY(scaleY * 0.25f);
	this->addChild(spritel, 0);
	///Social Facebook
	auto btnLoginFace = ui::Button::create("btn.square.nor.png", "btn.square.put.png", "btn.square.dis.png");
	btnLoginFace->setPosition(Vec2(442.0f * scaleX, 212.0f * scaleY));
	btnLoginFace->setScaleX(scaleX * 0.25f);
	btnLoginFace->setScaleY(scaleY * 0.25f);
	btnLoginFace->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type) {
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED:
			#ifdef SDKBOX_ENABLED
				sdkbox::PluginFacebook::login();
			#endif
				break;
			default:
				break;
		}
	});
	this->addChild(btnLoginFace, 0);
	auto spritef = Sprite::create("faceicon.png");
	spritef->setPosition(Vec2(442.0f * scaleX, 212.0f * scaleY));
	spritef->setScaleX(scaleX * 0.25f);
	spritef->setScaleY(scaleY * 0.25f);
	this->addChild(spritef, 0);

	///Social G++
	auto btnLoginGplus = ui::Button::create("btn.square.nor.png", "btn.square.put.png", "btn.square.dis.png");
	btnLoginGplus->setPosition(Vec2(342.0f * scaleX, 212.0f * scaleY));
	btnLoginGplus->setScaleX(scaleX* 0.25f);
	btnLoginGplus->setScaleY(scaleY* 0.25f);
	btnLoginGplus->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type) {
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED:
			#ifdef SDKBOX_ENABLED
				sdkbox::PluginFacebook::logout();
			#endif
				break;
			default:
				break;
		}
	});
	this->addChild(btnLoginGplus, 0);
	auto spriteg = Sprite::create("google.png");
	spriteg->setPosition(Vec2(342.0f * scaleX, 212.0f * scaleY));
	spriteg->setScaleX(scaleX * 0.25f);
	spriteg->setScaleY(scaleY * 0.25f);
	this->addChild(spriteg, 0);
	


	//-----
	return true;
}
