#include "GameTienLenMNScene.h"
#include "Card.h"
#include "ui/CocosGUI.h"
#include "GPlayer.h"
#include "RankingScene.h"
#include "HelloWorldScene.h"
#include <complex>

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
				Director::getInstance()->replaceScene(TransitionFade::create(1, HelloWorld::createScene(), Color3B(0, 0, 0)));
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
				Director::getInstance()->replaceScene(TransitionFade::create(1, RankingScene::createScene(), Color3B(0, 0, 0)));
				break;
			default:
				break;
		}
	});
	this->addChild(btnBack);
	//return true;
	//Vẽ nút điều khiển đánh bài
	auto btnUserPlay = ui::Button::create("play.danh.nor.png", "play.danh.put.png", "play.danh.dis.png");
	btnUserPlay->setPosition(Vec2(1145 * scaleX, 110 * scaleY));
	btnUserPlay->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type) {
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED:
				danhBaiAnimation();
				break;
			default:
				break;
		}
	});
	//NUT THOI
	this->addChild(btnUserPlay);
	auto btnUserThoi = ui::Button::create("play.thoi.nor.png", "play.thoi.put.png", "play.thoi.dis.png");
	btnUserThoi->setPosition(Vec2(1210 * scaleX, 40 * scaleY));
	btnUserThoi->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type) {
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED:
				//Director::getInstance()->replaceScene(TransitionFade::create(1, RankingScene::createScene(), Color3B(0, 0, 0)));
				break;
			default:
				break;
		}
	});
	this->addChild(btnUserThoi);
	//NUT XEP BAI
	auto btnUserXep = ui::Button::create("play.xep.nor.png", "play.xep.put.png", "play.xep.dis.png");
	btnUserXep->setPosition(Vec2(1080 * scaleX, 40 * scaleY));
	btnUserXep->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type) {
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED:
				for (auto i = 0; i < 13;i++) {
					for (auto j = i + 1; j < 13;j++) {
						if ((player[0]->Bai[i]->cardIndex > player[0]->Bai[j]->cardIndex) || (player[0]->Bai[i]->cardIndex == player[0]->Bai[j]->cardIndex && player[0]->Bai[i]->cardElement > player[0]->Bai[j]->cardElement)) {
							auto tmp = player[0]->Bai[i];
							player[0]->Bai[i] = player[0]->Bai[j];
							player[0]->Bai[j] = tmp;
						}
					}
				}
				for (auto i = 0; i < 13;i++) {
					auto actionMove = MoveTo::create(0.5, Vec2(Vec2(scaleX * (PP0.x + i * Card::cardWidth), scaleY * PP0.y)));
					auto actionMoveDone = CallFunc::create(player[0]->Bai[i], SEL_CallFunc());
					player[0]->Bai[i]->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
				}
				break;
			default:
				break;
		}
	});
	this->addChild(btnUserXep);
	// -- NUT XEP BAI
	newGameStart(-1);
	return true;
}

void GameTienLenMNScene::chiaBai() {
	//reset allcard
	for (auto i = 0; i < 52; i++) {
		Cards::allCard[i]->daChia = false;
		Cards::allCard[i]->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		Cards::allCard[i]->ChangeState(false);
		Cards::allCard[i]->selected = false;
	}

	player[0] = new GPlayer();
	for (auto i = 0; i < 13; i++) {
		auto inx = cocos2d::RandomHelper::random_int(0, 51);
		while (Cards::allCard[inx]->daChia) {
			inx = cocos2d::RandomHelper::random_int(0, 51);
		}
		Cards::allCard[inx]->daChia = true;
		player[0]->Bai[i] = Cards::allCard[inx];
	}
	player[1] = new GPlayer();
	for (auto i = 0; i < 13; i++) {
		auto inx = cocos2d::RandomHelper::random_int(0, 51);
		while (Cards::allCard[inx]->daChia) {
			inx = cocos2d::RandomHelper::random_int(0, 51);
		}
		Cards::allCard[inx]->daChia = true;
		player[1]->Bai[i] = Cards::allCard[inx];
	}
	player[2] = new GPlayer();
	for (auto i = 0; i < 13; i++) {
		auto inx = cocos2d::RandomHelper::random_int(0, 51);
		while (Cards::allCard[inx]->daChia) {
			inx = cocos2d::RandomHelper::random_int(0, 51);
		}
		Cards::allCard[inx]->daChia = true;
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
	chiaBaiAnimation(nullptr);
	return;
}

void GameTienLenMNScene::chiaBaiAnimation(Node* sender) {
	if (chiaBaiIndex >= 52) return;
	if (chiaBaiIndex % 4 == 0) {
		//Chia cho nguoi choi
		auto baiso = static_cast<int>(chiaBaiIndex / 4);
		CCFiniteTimeAction* actionMove = CCMoveTo::create(0.05, Vec2(scaleX * PP1.x, scaleY * PP1.y));
		CCFiniteTimeAction* actionMoveDone = CallFuncN::create(this, callfuncN_selector(GameTienLenMNScene::chiaBaiAnimation));
		player[1]->Bai[baiso]->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
	}
	if (chiaBaiIndex % 4 == 1) {
		//Chia cho CPU phai PP1
		auto baiso = static_cast<int>(chiaBaiIndex / 4);
		CCFiniteTimeAction* actionMove = CCMoveTo::create(0.05, Vec2(scaleX * PP2.x, scaleY * PP2.y));
		CCFiniteTimeAction* actionMoveDone = CallFuncN::create(this, callfuncN_selector(GameTienLenMNScene::chiaBaiAnimation));
		player[2]->Bai[baiso]->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
	}
	if (chiaBaiIndex % 4 == 2) {
		//Chia cho CPU tren PP2
		auto baiso = static_cast<int>(chiaBaiIndex / 4);
		CCFiniteTimeAction* actionMove = CCMoveTo::create(0.05, Vec2(scaleX * PP3.x, scaleY * PP3.y));
		CCFiniteTimeAction* actionMoveDone = CallFuncN::create(this, callfuncN_selector(GameTienLenMNScene::chiaBaiAnimation));
		player[3]->Bai[baiso]->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
	}
	if (chiaBaiIndex % 4 == 3) {
		//Chia cho CPU trai PP3
		auto baiso = static_cast<int>(chiaBaiIndex / 4);
		player[0]->Bai[baiso]->ChangeState(true);
		CCFiniteTimeAction* actionMove = CCMoveTo::create(0.08, Vec2(scaleX * (PP0.x + baiso * Card::cardWidth), scaleY * PP0.y));
		CCFiniteTimeAction* actionMoveDone = CallFuncN::create(this, callfuncN_selector(GameTienLenMNScene::chiaBaiAnimation));
		player[0]->Bai[baiso]->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
	}
	chiaBaiIndex++;
}

void GameTienLenMNScene::newGameStart(int lastWinPlayer) {
	chiaBai();

}


void GameTienLenMNScene::danhBaiAnimation() {
	//tìm số lượng bài sẽ đánh
	auto soBaiDanhRa = 0;
	for (auto i = 0; i < 52; i++) {
		if (Cards::allCard[i]->selected) {
			baiDanhRa[lopBaiDanhRa][soBaiDanhRa] = Cards::allCard[i];
			soBaiDanhRa++;
		}
	}
	if (soBaiDanhRa == 0) {
		return;
	}

	baiDanhRaCount[lopBaiDanhRa] = soBaiDanhRa;
	//dồn bài cũ
	auto donCount = lopBaiDanhRa - lopBaiDanhRaCuoi;
	/*
	for (auto dong = lopBaiDanhRa - 1; dong >= lopBaiDanhRaCuoi; dong--) {
		for (auto j = 0; j < baiDanhRaCount[dong]; j++) {
			auto actionMove = MoveTo::create(0.5, Vec2(Vec2(baiDanhRa[dong][j]->getPositionX(), baiDanhRa[dong][j]->getPositionY() + 30)));
			baiDanhRa[dong][j]->runAction(CCSequence::create(actionMove, NULL, NULL));
		}
	}*/
	for (auto i = 0; i < baiDanhRaCount[lopBaiDanhRa]; i++) {
		auto actionMove = MoveTo::create(0.5, Vec2(Vec2(scaleX * 600 + i* Card::cardWidth, scaleY * 390 - donCount * 30)));
		auto actionMoveDone = CallFunc::create(player[0]->Bai[i], SEL_CallFunc());
		baiDanhRa[lopBaiDanhRa][i]->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
		baiDanhRa[lopBaiDanhRa][i]->selected = false;
		baiDanhRa[lopBaiDanhRa][i]->setLocalZOrder(lopBaiDanhRa);
	}
	lopBaiDanhRa++;
}
