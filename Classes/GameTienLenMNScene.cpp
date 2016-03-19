#include "GameTienLenMNScene.h"
#include "Card.h"
#include "ui/CocosGUI.h"
#include "GPlayer.h"

USING_NS_CC;

auto visibleSize = Director::getInstance()->getVisibleSize();
GPlayer* player[4];

GameTienLenMNScene::GameTienLenMNScene() {

}

GameTienLenMNScene::~GameTienLenMNScene() {
}

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
	visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto sprite = Sprite::create("board.png");
	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	scaleX = visibleSize.width / sprite->getContentSize().width;
	scaleY = visibleSize.height / sprite->getContentSize().height;
	sprite->setScaleX(scaleX);
	sprite->setScaleY(scaleY);
	// add the sprite as a child to this layer
	this->addChild(sprite, 0);
	//khoi tao 52 quan bai
	for (auto i = 0; i < 52; i++) {
		Cards::allCard[i]->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		Cards::allCard[i]->ChangeState(true);
		Cards::allCard[i]->setScaleX(scaleX);
		Cards::allCard[i]->setScaleY(scaleY);
		addChild(Cards::allCard[i], 1);
	}
	//Vẽ nút quit và nut Config
	auto btnConfig = ui::Button::create("play.cfg.nor.png", "play.cfg.put.png", "play.cfg.dis.png");
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
		chiaBai();

		//Chọn người đánh đầu tiên:

		//
		return true;
	} while (true);
	return true;
}

void GameTienLenMNScene::chiaBai() {
	//reset allcard
	for (auto i = 0; i < 52; i++) {
		Cards::allCard[i]->daChia = false;
		Cards::allCard[i]->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		Cards::allCard[i]->ChangeState(false);
	}
	player[0] = new GPlayer();
	for (auto i = 0; i < 13; i++) {
		auto inx = cocos2d::RandomHelper::random_int(0, 51);
		while (Cards::allCard[inx]->daChia) {
			inx = cocos2d::RandomHelper::random_int(0, 51);
		}
		Cards::allCard[i]->daChia = true;
		player[0]->Bai[i] = Cards::allCard[inx];
	}
	player[1] = new GPlayer();
	for (auto i = 0; i < 13; i++) {
		auto inx = cocos2d::RandomHelper::random_int(0, 51);
		while (Cards::allCard[inx]->daChia) {
			inx = cocos2d::RandomHelper::random_int(0, 51);
		}
		Cards::allCard[i]->daChia = true;
		player[1]->Bai[i] = Cards::allCard[inx];
	}
	player[2] = new GPlayer();
	for (auto i = 0; i < 13; i++) {
		auto inx = cocos2d::RandomHelper::random_int(0, 51);
		while (Cards::allCard[inx]->daChia) {
			inx = cocos2d::RandomHelper::random_int(0, 51);
		}
		Cards::allCard[i]->daChia = true;
		player[2]->Bai[i] = Cards::allCard[inx];
	}
	player[3] = new GPlayer();
	auto inx = 0;
	for (auto i = 0; i < 52; i++) {
		if (!Cards::allCard[i]->daChia) {
			player[3]->Bai[inx] = Cards::allCard[i];
			Cards::allCard[i]->daChia = true;
			inx ++;
		}
	}
	//create animation:
	chiaBaiIndex = 0;
	FiniteTimeAction* actionMove = MoveTo::create(0.1, Vec2(scaleX * PP0.x, scaleY * PP0.y));
	FiniteTimeAction* actionMoveDone = CallFuncN::create(this, callfuncN_selector(GameTienLenMNScene::chiaBaiAnimation));
	player[0]->Bai[0]->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
}

void GameTienLenMNScene::chiaBaiAnimation(Node* sender) {
	if (chiaBaiIndex >= 52) return;
	if (chiaBaiIndex % 4 == 0) {
		//Chia cho nguoi choi
		auto baiso = static_cast<int>(chiaBaiIndex / 4);
		FiniteTimeAction* actionMove = MoveTo::create(0.1, Vec2(scaleX * PP1.x, scaleY * PP1.y));
		FiniteTimeAction* actionMoveDone = CallFuncN::create(this, callfuncN_selector(GameTienLenMNScene::chiaBaiAnimation));
		player[0]->Bai[baiso]->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
	}
	if (chiaBaiIndex % 4 == 1) {
		//Chia cho CPU phai PP1
		auto baiso = static_cast<int>(chiaBaiIndex / 4);
		FiniteTimeAction* actionMove = MoveTo::create(0.1, Vec2(scaleX * PP2.x, scaleY * PP2.y));
		FiniteTimeAction* actionMoveDone = CallFuncN::create(this, callfuncN_selector(GameTienLenMNScene::chiaBaiAnimation));
		player[1]->Bai[baiso]->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
	}
	if (chiaBaiIndex % 4 == 2) {
		//Chia cho CPU tren PP2
		auto baiso = static_cast<int>(chiaBaiIndex / 4);
		FiniteTimeAction* actionMove = MoveTo::create(0.1, Vec2(scaleX * PP3.x, scaleY * PP3.y));
		FiniteTimeAction* actionMoveDone = CallFuncN::create(this, callfuncN_selector(GameTienLenMNScene::chiaBaiAnimation));
		player[2]->Bai[baiso]->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
	}
	if (chiaBaiIndex % 4 == 3) {
		//Chia cho CPU trai PP3
		auto baiso = static_cast<int>(chiaBaiIndex / 4);
		FiniteTimeAction* actionMove = MoveTo::create(0.1, Vec2(scaleX * PP0.x, scaleY * PP0.y));
		FiniteTimeAction* actionMoveDone = CallFuncN::create(this, callfuncN_selector(GameTienLenMNScene::chiaBaiAnimation));
		player[3]->Bai[baiso]->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
	}
	chiaBaiIndex++;

}

