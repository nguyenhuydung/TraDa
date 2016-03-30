#include "GameTienLenMNScene.h"
#include "Card.h"
#include "ui/CocosGUI.h"
#include "GPlayer.h"
#include "RankingScene.h"
#include "HelloWorldScene.h"
#include "FrozaxShake/FShake.h"
#include <SimpleAudioEngine.h>

USING_NS_CC;

auto visibleSize = Director::getInstance()->getVisibleSize();
GPlayer* player[4];

int GameTienLenMNScene::stepDanhBai = 0;

GameTienLenMNScene::GameTienLenMNScene(): messageBox(nullptr) {

}

GameTienLenMNScene::~GameTienLenMNScene() {
}

Scene* GameTienLenMNScene::createScene() {
	auto scene = Scene::create();
	auto layer = create();
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

	//Create scale
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	scaleX = visibleSize.width / sprite->getContentSize().width;
	scaleY = visibleSize.height / sprite->getContentSize().height;

	scaleXL = scaleX * 94 / 56;
	scaleYL = scaleY * 120 / 75;

	sprite->setScaleX(scaleX);
	sprite->setScaleY(scaleY);
	// add the sprite as a child to this layer
	this->addChild(sprite, 0);

	//Vẽ nút quit và nut Config
	auto btnConfig = ui::Button::create("play.cfg.nor.png", "play.cfg.put.png", "play.cfg.nor.png");
	btnConfig->setPosition(Vec2(175.0f * scaleX, 50.0f * scaleY));
	btnConfig->setScaleX(scaleX);
	btnConfig->setScaleY(scaleY);
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
	btnBack->setPosition(Vec2(64.0f * scaleX, 50.0f * scaleY));
	btnBack->setScaleX(scaleX);
	btnBack->setScaleY(scaleY);
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
	auto btnUserPlay = ui::Button::create("button.nor.png", "button.put.png", "button.dis.png");
	btnUserPlay->setTitleText("Đánh");
	btnUserPlay->setTitleFontSize(24);
	btnUserPlay->setTitleColor(Color3B(33, 33, 33));
	btnUserPlay->setScaleX(scaleX);
	btnUserPlay->setScaleY(scaleY);
	btnUserPlay->setPosition(Vec2(1200.0f * scaleX, 50.0f * scaleY));
	btnUserPlay->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type) {
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED:
				if (tlmnValid(0)) {
					danhBaiAnimation();
				} else {
					auto shake = FShake::actionWithDuration(0.03f, 10.0f);
					this->runAction(shake);
					messageBox->setString("Bài chọn không hợp lệ");
				}
				break;
			default:
				break;
		}
	});
	//NUT THOI
	this->addChild(btnUserPlay);
	auto btnUserThoi = ui::Button::create("button.nor.png", "button.put.png", "button.dis.png");
	btnUserThoi->setTitleText("Thôi");
	btnUserThoi->setScaleX(scaleX);
	btnUserThoi->setScaleY(scaleY);
	btnUserThoi->setTitleFontSize(24);
	btnUserThoi->setTitleColor(Color3B(33, 33, 33));
	btnUserThoi->setPosition(Vec2(1060.0f * scaleX, 50.0f * scaleY));
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
	auto btnUserXep = ui::Button::create("button.nor.png", "button.put.png", "button.dis.png");
	btnUserXep->setTitleText("Xếp bài");
	btnUserXep->setScaleX(scaleX);
	btnUserXep->setScaleY(scaleY);
	btnUserXep->setTitleFontSize(24);
	btnUserXep->setTitleColor(Color3B(33, 33, 33));
	btnUserXep->setPosition(Vec2(920.0f * scaleX, 50.0f * scaleY));
	btnUserXep->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type) {
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED:
				for (auto i = 0; i < 13; i++) {
					for (auto j = i + 1; j < 13; j++) {
						if ((player[0]->Bai[i]->cardIndex > player[0]->Bai[j]->cardIndex) || (player[0]->Bai[i]->cardIndex == player[0]->Bai[j]->cardIndex && player[0]->Bai[i]->cardElement > player[0]->Bai[j]->cardElement)) {
							auto tmp = player[0]->Bai[i];
							player[0]->Bai[i] = player[0]->Bai[j];
							player[0]->Bai[j] = tmp;
						}
					}
				}
				for (auto i = 0; i < 13; i++) {
					if (!player[0]->Bai[i]->daDanh) {
						auto actionMove = MoveTo::create(0.5, Vec2(Vec2(scaleXL * (PP0.x + i * Card::cardWidth), scaleYL * PP0.y)));
						auto actionMoveDone = CallFunc::create(player[0]->Bai[i], SEL_CallFunc());
						player[0]->Bai[i]->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
					}
				}
				break;
			default:
				break;
		}
	});
	this->addChild(btnUserXep);
	//THONG BAO
	messageBox = Label::create();
	messageBox->setTextColor(Color4B(0, 0, 0, 255));
	messageBox->setSystemFontSize(24);
	messageBox->setPosition(Vec2(455.0f * scaleX, 60.0f * scaleY));
	messageBox->setString("Đang chia bai...");
	this->addChild(messageBox);

	Card::loadData();

	//khoi tao 52 quan bai
	for (auto i = 0; i < 52; i++) {
		Card::allCard[i]->setPosition(Vec2(visibleSize.width / 2, scaleY * 450.0f));
		Card::allCard[i]->ChangeState(CARD_STATE_DOWN);
		Card::allCard[i]->setScaleX(scaleX);
		Card::allCard[i]->setScaleY(scaleY);
		addChild(Card::allCard[i], 1);
	}

	newGameStart(-1);
	return true;
}

void GameTienLenMNScene::chiaBai() {
	//reset allcard
	for (auto i = 0; i < 52; i++) {
		Card::allCard[i]->daChia = false;
		Card::allCard[i]->setPosition(Vec2(visibleSize.width / 2, scaleY * 450.0f));
		Card::allCard[i]->setScaleX(scaleX);
		Card::allCard[i]->setScaleY(scaleY);
		Card::allCard[i]->ChangeState(CARD_STATE_DOWN);
	}

	player[0] = new GPlayer();
	for (auto i = 0; i < 13; i++) {
		auto inx = RandomHelper::random_int(0, 51);
		while (Card::allCard[inx]->daChia) {
			inx = RandomHelper::random_int(0, 51);
		}
		Card::allCard[inx]->daChia = true;
		player[0]->Bai[i] = Card::allCard[inx];
	}
	player[1] = new GPlayer();
	for (auto i = 0; i < 13; i++) {
		auto inx = RandomHelper::random_int(0, 51);
		while (Card::allCard[inx]->daChia) {
			inx = RandomHelper::random_int(0, 51);
		}
		Card::allCard[inx]->daChia = true;
		player[1]->Bai[i] = Card::allCard[inx];
	}
	player[2] = new GPlayer();
	for (auto i = 0; i < 13; i++) {
		auto inx = RandomHelper::random_int(0, 51);
		while (Card::allCard[inx]->daChia) {
			inx = RandomHelper::random_int(0, 51);
		}
		Card::allCard[inx]->daChia = true;
		player[2]->Bai[i] = Card::allCard[inx];
	}
	player[3] = new GPlayer();
	auto inx = 0;
	for (auto i = 0; i < 52; i++) {
		if (!Card::allCard[i]->daChia) {
			player[3]->Bai[inx] = Card::allCard[i];
			Card::allCard[i]->daChia = true;
			inx ++;
		}
	}
	//create animation:
	chiaBaiIndex = 0;
	chiaBaiAnimation(nullptr);
	return;
}

//auto audio = CocosDenshion::SimpleAudioEngine::getInstance();

void GameTienLenMNScene::chiaBaiAnimation(Node* sender) {
	if (chiaBaiIndex >= 52) return;
	if (chiaBaiIndex % 4 == 0) {
		//Chia cho nguoi choi
		auto baiso = static_cast<int>(chiaBaiIndex / 4);
		auto actionMove = CCMoveTo::create(0.05, Vec2(scaleX * PP1.x, scaleY * PP1.y));
		auto actionMoveDone = CallFuncN::create(this, callfuncN_selector(GameTienLenMNScene::chiaBaiAnimation));
		player[1]->Bai[baiso]->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
	}
	if (chiaBaiIndex % 4 == 1) {
		//Chia cho CPU phai PP1
		auto baiso = static_cast<int>(chiaBaiIndex / 4);
		auto actionMove = CCMoveTo::create(0.05, Vec2(scaleX * PP2.x, scaleY * PP2.y));
		auto actionMoveDone = CallFuncN::create(this, callfuncN_selector(GameTienLenMNScene::chiaBaiAnimation));
		player[2]->Bai[baiso]->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
	}
	if (chiaBaiIndex % 4 == 2) {
		//Chia cho CPU tren PP2
		auto baiso = static_cast<int>(chiaBaiIndex / 4);
		auto actionMove = CCMoveTo::create(0.05, Vec2(scaleX * PP3.x, scaleY * PP3.y));
		auto actionMoveDone = CallFuncN::create(this, callfuncN_selector(GameTienLenMNScene::chiaBaiAnimation));
		player[3]->Bai[baiso]->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
	}
	if (chiaBaiIndex % 4 == 3) {
		//Chia cho CPU trai PP3
		auto baiso = static_cast<int>(chiaBaiIndex / 4);
		player[0]->Bai[baiso]->ChangeState(CARD_STATE_NORM);
		player[0]->Bai[baiso]->setScaleX(scaleXL);
		player[0]->Bai[baiso]->setScaleY(scaleYL);

		auto actionScale = ScaleTo::create(0.08, scaleXL, scaleYL);
		auto actionMove = MoveTo::create(0.08, Vec2(scaleXL * (PP0.x + baiso * Card::cardWidth), scaleYL * PP0.y));
		auto actionRotate = RotateBy::create(0.08, 360);
		auto actionMoveDone = CallFuncN::create(this, callfuncN_selector(GameTienLenMNScene::chiaBaiAnimation));
		player[0]->Bai[baiso]->runAction(CCSequence::create(actionMove, NULL));
		player[0]->Bai[baiso]->runAction(CCSequence::create(actionRotate, NULL));
		player[0]->Bai[baiso]->runAction(CCSequence::create(actionScale, actionMoveDone, NULL));
		audio->playEffect("Sound/add.mp3", false, 1.0f, 1.0f, 1.0f);
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
		if (Card::allCard[i]->cardState == CARD_STATE_SELT) {
			baiDanhRa[lopBaiDanhRa][soBaiDanhRa] = Card::allCard[i];
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
		auto cWidth = baiDanhRaCount[lopBaiDanhRa] * Card::cardWidth / 2;
		auto actionMove = MoveTo::create(0.5, Vec2(Vec2(scaleX * 660 + i * Card::cardWidth - cWidth, scaleY * 500 - donCount * 30)));
		auto actionScale = ScaleTo::create(0.5, scaleX, scaleY);
		auto actionRotate = RotateBy::create(0.5, 360);

		baiDanhRa[lopBaiDanhRa][i]->runAction(Sequence::create(actionMove, NULL));
		baiDanhRa[lopBaiDanhRa][i]->runAction(Sequence::create(actionScale, NULL));
		baiDanhRa[lopBaiDanhRa][i]->runAction(Sequence::create(actionRotate, NULL));

		baiDanhRa[lopBaiDanhRa][i]->ChangeState(CARD_STATE_NORM);
		baiDanhRa[lopBaiDanhRa][i]->daDanh = true;
		baiDanhRa[lopBaiDanhRa][i]->setLocalZOrder(lopBaiDanhRa);
	}
	lopBaiDanhRa++;
}

void GameTienLenMNScene::danhBaiDone() {
	//auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("Sound/add.mp3", false, 1.0f, 1.0f, 1.0f);
}

///Kiem tra card selected co dung khong
bool GameTienLenMNScene::tlmnValid(int step) {
	Card* selectedCrad[13];
	auto selectedCradLen = 0;
	for (auto i = 0; i < 52; i++) {
		if (Card::allCard[i]->cardState == CARD_STATE_SELT) {
			selectedCrad[selectedCradLen] = Card::allCard[i];
			selectedCradLen++;
		}
	}
	if (isValidSelected(selectedCrad, selectedCradLen)) return true;
	return false;
}

///CPU chon quan de danh
void GameTienLenMNScene::tlmnCpuSelect(int player, int step, int level) {
	//Chon quan đánh


	//Update lại Step
}

//Private for Tien Len Mien Nam:

bool GameTienLenMNScene::isValidSelected(Card* selectedCrad[13], int selectedCradLen) {
	if (selectedCradLen == 1) {
		//Rác:
		return true;
	}
	if (selectedCradLen == 2) {
		//Đôi
		if (selectedCrad[0]->cardIndex == selectedCrad[1]->cardIndex) {
			return true;
		}
		return false;
	}
	if (selectedCradLen == 3) {
		//Sám
		if (selectedCrad[0]->cardIndex == selectedCrad[1]->cardIndex && selectedCrad[1]->cardIndex == selectedCrad[2]->cardIndex) {
			return true;
		}
		//return false;
	}
	if (selectedCradLen == 4) {
		//Tứ quý
		if (selectedCrad[0]->cardIndex == selectedCrad[1]->cardIndex && selectedCrad[1]->cardIndex == selectedCrad[2]->cardIndex && selectedCrad[2]->cardIndex == selectedCrad[3]->cardIndex) {
			return true;
		}
		//return false;
	}
	//Kiểm tra sảnh:

	Card* tmpar[13];
	for (auto i = 0; i < selectedCradLen; i++) {
		tmpar[i] = selectedCrad[i];
	}
	//sort teamp
	for (auto i = 0; i < selectedCradLen; i++) {
		for (auto j = i + 1; j < selectedCradLen; j++) {
			if ((tmpar[i]->cardIndex > tmpar[j]->cardIndex) || (tmpar[i]->cardIndex == tmpar[j]->cardIndex && tmpar[i]->cardElement > tmpar[j]->cardElement)) {
				auto tmpx = tmpar[i];
				tmpar[i] = tmpar[j];
				tmpar[j] = tmpx;
			}
		}
	}
	///dây
	auto i = 1;
	auto isValid = true;
	do {
		if (tmpar[0]->cardIndex != tmpar[i]->cardIndex - i) {
			isValid = false;
		}
		i++;
	} while (isValid && i < selectedCradLen);
	if (isValid) return true;
	///Đôi thông
	if (selectedCradLen == 6 || selectedCradLen == 8 || selectedCradLen == 10 || selectedCradLen == 12) {
		i = 0;
		do {
			if ((tmpar[i]->cardIndex != tmpar[i + 1]->cardIndex) && (tmpar[i]->cardIndex != tmpar[i + 2]->cardIndex - 1) && (tmpar[i + 1]->cardIndex != tmpar[i + 3]->cardIndex - 1)) {
				isValid = false;
			}
			i = i + 2;
		} while (isValid && i < selectedCradLen - 4);
	}
	return false;
}

