#include "GameTienLenMNScene.h"
#include "Card.h"
#include "GPlayer.h"
#include "RankingScene.h"
#include "HelloWorldScene.h"
#include "FrozaxShake/FShake.h"
#include <SimpleAudioEngine.h>
#include <iostream>

USING_NS_CC;

auto visibleSize = Director::getInstance()->getVisibleSize();
GPlayer* CPplayer[4];

//LuotDanh *GameTienLenMNScene::stepDanhBai = new LuotDanh;

GameTienLenMNScene::GameTienLenMNScene() {
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
	btnConfig = ui::Button::create("play.cfg.nor.png", "play.cfg.put.png", "play.cfg.dis.png");
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

	btnBack = ui::Button::create("play.back.nor.png", "play.back.put.png", "play.back.dis.png");
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
	btnUserPlay = ui::Button::create("button.nor.png", "button.put.png", "button.dis.png");
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
			case ui::Widget::TouchEventType::ENDED: {///FILL LOG ĐÁNH BÀI: quet bai được chọn
				auto baiDanhRa = new BaiDanhRa();
				baiDanhRa->soLuong = 0;
				for (auto i = 0; i < 13; i++) {
					if (CPplayer[0]->Bai[i]->cardState == CARD_STATE_SELT) {
						baiDanhRa->danhSach[baiDanhRa->soLuong] = CPplayer[0]->Bai[i];
						baiDanhRa->soLuong ++;
					}
				}
				if (baiDanhRa->soLuong != 0) {
					baiDanhRa->kieuBai = tlmnTimKieuSapBo(baiDanhRa->danhSach, baiDanhRa->soLuong);
					if (baiDanhRa->kieuBai != BO_FALSE) {
						if (tlmnKiemTraBaiDanhRa(baiDanhRa, 0)) {
							///Đánh bài thành công
							CPplayer[0]->BaiCount -= baiDanhRa->soLuong;
							logDanhBai[logDanhBaiIndex]->baiDanh = baiDanhRa;
							EnableControls(false);
							///Goi đánh animation
							danhBaiAnimation();
							break;
						}
					}
				}
				///Faill: 
				auto shake = FShake::actionWithDuration(0.03f, 10.0f);
				this->runAction(shake);
				messageBox->setString("Bài chọn không hợp lệ, mời chọn lại");
			}
				break;
			case ui::Widget::TouchEventType::MOVED: break;
			case ui::Widget::TouchEventType::CANCELED: break;
			default: break;
		}
	});
	//NUT THOI
	this->addChild(btnUserPlay);
	btnUserThoi = ui::Button::create("button.nor.png", "button.put.png", "button.dis.png");
	btnUserThoi->setTitleText("Bỏ lượt");
	btnUserThoi->setScaleX(scaleX);
	btnUserThoi->setScaleY(scaleY);
	btnUserThoi->setTitleFontSize(24);
	btnUserThoi->setTitleColor(Color3B(33, 33, 33));
	btnUserThoi->setPosition(Vec2(1060.0f * scaleX, 50.0f * scaleY));
	btnUserThoi->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type) {
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED: {
				if (logDanhBai[logDanhBaiIndex - 1]->vongKetThuc) {
					messageBox->setString("Bạn đang được quyền đánh, không bỏ lượt được.");
					return;
				}
				tlmnBoLuot(0);
				danhBaiAnimation();
			}
				break;
			case ui::Widget::TouchEventType::MOVED: break;
			case ui::Widget::TouchEventType::CANCELED: break;
		}
	});
	this->addChild(btnUserThoi);
	//NUT XEP BAI
	btnUserXep = ui::Button::create("button.nor.png", "button.put.png", "button.dis.png");
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
						if ((CPplayer[0]->Bai[i]->cardIndex > CPplayer[0]->Bai[j]->cardIndex) || (CPplayer[0]->Bai[i]->cardIndex == CPplayer[0]->Bai[j]->cardIndex && CPplayer[0]->Bai[i]->cardElement > CPplayer[0]->Bai[j]->cardElement) || CPplayer[0]->Bai[j]->daDanh) {
							auto tmp = CPplayer[0]->Bai[i];
							CPplayer[0]->Bai[i] = CPplayer[0]->Bai[j];
							CPplayer[0]->Bai[j] = tmp;
						}
					}
				}

				for (auto i = 0; i < 13; i++) {
					if (!CPplayer[0]->Bai[i]->daDanh) {
						auto actionMove = MoveTo::create(0.5, Vec2(Vec2(scaleXL * (PP0.x + i * Card::cardWidth), scaleYL * PP0.y)));
						auto actionMoveDone = CallFunc::create(CPplayer[0]->Bai[i], SEL_CallFunc());
						CPplayer[0]->Bai[i]->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
					}
				}
				break;
			default:
				break;
		}
	});
	this->addChild(btnUserXep);
	///Nút bỏ chọn
	btnUserBoChon = ui::Button::create("button.nor.png", "button.put.png", "button.dis.png");
	btnUserBoChon->setTitleText("Bỏ chọn");
	btnUserBoChon->setScaleX(scaleX);
	btnUserBoChon->setScaleY(scaleY);
	btnUserBoChon->setTitleFontSize(24);
	btnUserBoChon->setTitleColor(Color3B(33, 33, 33));
	btnUserBoChon->setPosition(Vec2(780.0f * scaleX, 50.0f * scaleY));
	btnUserBoChon->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type) {
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED:
				for (auto i = 0; i < 13; i++) {
					CPplayer[0]->Bai[i]->ChangeState(CARD_STATE_NORM);
				}
				break;
			default:
				break;
		}
	});
	this->addChild(btnUserBoChon);
	//THONG BAO
	messageBox = Label::create();
	messageBox->setTextColor(Color4B(0, 0, 0, 255));
	messageBox->setSystemFontSize(24);
	messageBox->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	messageBox->setPosition(Vec2(240.0f * scaleX, 50.0f * scaleY));
	messageBox->setString("Đang chia bai...");
	this->addChild(messageBox);

	iconWinner = Sprite::create("winner.stamp.png");
	iconWinner->setScaleX(scaleX);
	iconWinner->setScaleY(scaleY);
	iconWinner->setVisible(false);
	this->addChild(iconWinner, 102);

	Card::loadData();

	//khoi tao 52 quan bai
	for (auto i = 0; i < 52; i++) {
		Card::allCard[i]->setPosition(Vec2(visibleSize.width / 2, scaleY * 450.0f));
		Card::allCard[i]->ChangeState(CARD_STATE_DOWN);
		Card::allCard[i]->setScaleX(scaleX);
		Card::allCard[i]->setScaleY(scaleY);
		addChild(Card::allCard[i], 1);
	}
	for (auto i = 0; i < 104; i++) {
		logDanhBai[i] = nullptr;
	}
	logDanhBaiIndex = -1;
	drawInitPlayerStatus();
	chiaBai(nullptr);
	return true;
}

void GameTienLenMNScene::chiaBai(Node* sender) {
	//Reset
	for (auto i = 0; i < 52; i++) {
		Card::allCard[i]->daChia = false;
		Card::allCard[i]->daDanh = false;
		Card::allCard[i]->setPosition(Vec2(visibleSize.width / 2, scaleY * 450.0f));
		Card::allCard[i]->setScaleX(scaleX);
		Card::allCard[i]->setScaleY(scaleY);
		Card::allCard[i]->ChangeState(CARD_STATE_DOWN);
	}
	iconWinner->setVisible(false);
	EnableControls(false);
	//Chia ngau nhien
	CPplayer[0] = new GPlayer();
	for (auto i = 0; i < 13; i++) {
		auto inx = RandomHelper::random_int(0, 51);
		while (Card::allCard[inx]->daChia) {
			inx = RandomHelper::random_int(0, 51);
		}
		Card::allCard[inx]->daChia = true;
		CPplayer[0]->Bai[i] = Card::allCard[inx];
	}
	CPplayer[0]->BaiCount = 13;

	CPplayer[1] = new GPlayer();
	for (auto i = 0; i < 13; i++) {
		auto inx = RandomHelper::random_int(0, 51);
		while (Card::allCard[inx]->daChia) {
			inx = RandomHelper::random_int(0, 51);
		}
		Card::allCard[inx]->daChia = true;
		CPplayer[1]->Bai[i] = Card::allCard[inx];
	}
	CPplayer[1]->BaiCount = 13;

	CPplayer[2] = new GPlayer();
	for (auto i = 0; i < 13; i++) {
		auto inx = RandomHelper::random_int(0, 51);
		while (Card::allCard[inx]->daChia) {
			inx = RandomHelper::random_int(0, 51);
		}
		Card::allCard[inx]->daChia = true;
		CPplayer[2]->Bai[i] = Card::allCard[inx];
	}
	CPplayer[2]->BaiCount = 13;

	CPplayer[3] = new GPlayer();
	auto inx = 0;
	for (auto i = 0; i < 52; i++) {
		if (!Card::allCard[i]->daChia) {
			CPplayer[3]->Bai[inx] = Card::allCard[i];
			Card::allCard[i]->daChia = true;
			inx ++;
		}
	}
	CPplayer[3]->BaiCount = 13;

	//create animation:
	chiaBaiIndex = 0;
	chiaBaiAnimation(nullptr);
}

//auto audio = CocosDenshion::SimpleAudioEngine::getInstance();

void GameTienLenMNScene::chiaBaiAnimation(Node* sender) {
	if (chiaBaiIndex >= 52) {
		//Chia bài xong:
		messageBox->setString("Chia bài xong.");

		if (logDanhBaiIndex == -1) {
			///tim player có 3 pic cho trận đầu tiên.
			auto player = 0; ///tự cho nó = 0 đã
			///Tạo cái log đầu tiên
			logDanhBaiIndex = 0;
			logDanhBai[logDanhBaiIndex] = new LuotDanh;
			logDanhBai[logDanhBaiIndex]->nguoiDangDanh = player;
			logDanhBai[logDanhBaiIndex]->vongKetThuc = true;
		}
		drawUpdatePlayerStatus();
		danhBai();
		return;
	}
	if (chiaBaiIndex % 4 == 0) {
		//Chia cho nguoi choi
		auto baiso = static_cast<int>(chiaBaiIndex / 4);
		auto actionMove = CCMoveTo::create(0.05, Vec2(scaleX * PP1.x, scaleY * PP1.y));
		auto actionMoveDone = CallFuncN::create(this, callfuncN_selector(GameTienLenMNScene::chiaBaiAnimation));
		CPplayer[1]->Bai[baiso]->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
	}
	if (chiaBaiIndex % 4 == 1) {
		//Chia cho CPU phai PP1
		auto baiso = static_cast<int>(chiaBaiIndex / 4);
		auto actionMove = CCMoveTo::create(0.05, Vec2(scaleX * PP2.x, scaleY * PP2.y));
		auto actionMoveDone = CallFuncN::create(this, callfuncN_selector(GameTienLenMNScene::chiaBaiAnimation));
		CPplayer[2]->Bai[baiso]->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
	}
	if (chiaBaiIndex % 4 == 2) {
		//Chia cho CPU tren PP2
		auto baiso = static_cast<int>(chiaBaiIndex / 4);
		auto actionMove = CCMoveTo::create(0.05, Vec2(scaleX * PP3.x, scaleY * PP3.y));
		auto actionMoveDone = CallFuncN::create(this, callfuncN_selector(GameTienLenMNScene::chiaBaiAnimation));
		CPplayer[3]->Bai[baiso]->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
	}
	if (chiaBaiIndex % 4 == 3) {
		//Chia cho CPU trai PP3
		auto baiso = static_cast<int>(chiaBaiIndex / 4);
		CPplayer[0]->Bai[baiso]->ChangeState(CARD_STATE_NORM);
		CPplayer[0]->Bai[baiso]->setScaleX(scaleXL);
		CPplayer[0]->Bai[baiso]->setScaleY(scaleYL);

		auto actionScale = ScaleTo::create(0.08, scaleXL, scaleYL);
		auto actionMove = MoveTo::create(0.08, Vec2(scaleXL * (PP0.x + baiso * Card::cardWidth), scaleYL * PP0.y));
		auto actionRotate = RotateBy::create(0.08, 360);
		auto actionMoveDone = CallFuncN::create(this, callfuncN_selector(GameTienLenMNScene::chiaBaiAnimation));
		CPplayer[0]->Bai[baiso]->runAction(CCSequence::create(actionMove, NULL));
		CPplayer[0]->Bai[baiso]->runAction(CCSequence::create(actionRotate, NULL));
		CPplayer[0]->Bai[baiso]->runAction(CCSequence::create(actionScale, actionMoveDone, NULL));
		audio->playEffect("Sound/add.mp3", false, 1.0f, 1.0f, 1.0f);
	}
	chiaBaiIndex++;
}

int GameTienLenMNScene::danhBaiTaoLog() {
	//Kiểm tra cái log trước: 1. Còn ai đánh không?
	int player;
	if (logDanhBai[logDanhBaiIndex]->vongKetThuc) {
		player = logDanhBai[logDanhBaiIndex]->nguoiDangDanh;
		logDanhBaiIndex++;
		if (logDanhBai[logDanhBaiIndex] == nullptr) {
			logDanhBai[logDanhBaiIndex] = new LuotDanh;
		}
		logDanhBai[logDanhBaiIndex]->nguoiDangDanh = player;
		logDanhBai[logDanhBaiIndex]->nguoiDaBoVongCount = 0;
		logDanhBai[logDanhBaiIndex]->nguoiDaBoVong[0] = false;
		logDanhBai[logDanhBaiIndex]->nguoiDaBoVong[1] = false;
		logDanhBai[logDanhBaiIndex]->nguoiDaBoVong[2] = false;
		logDanhBai[logDanhBaiIndex]->nguoiDaBoVong[3] = false;
		logDanhBai[logDanhBaiIndex]->vongKetThuc = false;

	} else {
		//tim nguoi danh tiep theo (chua bo vong)
		player = logDanhBai[logDanhBaiIndex]->nguoiDangDanh + 1;
		if (player >= 4) player = 0;
		while (logDanhBai[logDanhBaiIndex]->nguoiDaBoVong[player]) {
			player = player + 1;
			if (player >= 4) player = 0;
		}
		logDanhBaiIndex++;
		if (logDanhBai[logDanhBaiIndex] == nullptr) {
			logDanhBai[logDanhBaiIndex] = new LuotDanh;
		}
		logDanhBai[logDanhBaiIndex]->nguoiDangDanh = player;
		logDanhBai[logDanhBaiIndex]->nguoiDaBoVongCount = logDanhBai[logDanhBaiIndex - 1]->nguoiDaBoVongCount;
		logDanhBai[logDanhBaiIndex]->nguoiDaBoVong[0] = logDanhBai[logDanhBaiIndex - 1]->nguoiDaBoVong[0] ? true : false;
		logDanhBai[logDanhBaiIndex]->nguoiDaBoVong[1] = logDanhBai[logDanhBaiIndex - 1]->nguoiDaBoVong[1] ? true : false;
		logDanhBai[logDanhBaiIndex]->nguoiDaBoVong[2] = logDanhBai[logDanhBaiIndex - 1]->nguoiDaBoVong[2] ? true : false;
		logDanhBai[logDanhBaiIndex]->nguoiDaBoVong[3] = logDanhBai[logDanhBaiIndex - 1]->nguoiDaBoVong[3] ? true : false;
		logDanhBai[logDanhBaiIndex]->vongKetThuc = false;
	}
	//Tạo cái log cho lượt đánh mới:
	return player;
	///tiếp theo, player chọn quân đánh sẽ fill nốt các trường còn lại :))
}

void GameTienLenMNScene::danhBai() {
	auto player = danhBaiTaoLog();
	if (player == 0) {
		//Nguoi choi ddanhs
		EnableControls(true); // cho người chơi đánh
		///sau khi ấn đánh, kiemr tra so với log trước
	} else {
		///CPU danh
		tlmnCpuChonBaiDanhRa(player, 0);
		danhBaiAnimation();
	}
}

void GameTienLenMNScene::danhBaiAnimationDone(Node* sender) {
	//Kieem tra wwiner
	for (auto p = 0; p < 4; p++) {
		if (CPplayer[p]->BaiCount == 0) {
			iconWinner->setPosition(visibleSize.width / 2, visibleSize.height / 2);
			iconWinner->setVisible(true);
			auto shake = FShake::actionWithDuration(0.03f, 10.0f);
			this->runAction(shake);
			//Report điểm ở đây:
			auto actionDelay = DelayTime::create(5.0f);
			auto actionDone = CallFuncN::create(this, callfuncN_selector(GameTienLenMNScene::chiaBai));
			this->runAction(Sequence::create(actionDelay, actionDone, NULL));
			return;
		}
	}
	//Chua co danh tiep:
	danhBai();
}

void GameTienLenMNScene::danhBaiAnimation() {
	//Bỏ lượt: animation bỏ
	if (logDanhBai[logDanhBaiIndex]->baiDanh->soLuong == 0) {


	} else {
		//không bỏ, animation di chuyển quân bài:
		for (auto i = 0; i < logDanhBai[logDanhBaiIndex]->baiDanh->soLuong; i++) {
			auto cWidth = logDanhBai[logDanhBaiIndex]->baiDanh->soLuong * Card::cardWidth / 2;

			logDanhBai[logDanhBaiIndex]->baiDanh->danhSach[i]->ChangeState(CARD_STATE_NORM);
			logDanhBai[logDanhBaiIndex]->baiDanh->danhSach[i]->daDanh = true;
			logDanhBai[logDanhBaiIndex]->baiDanh->danhSach[i]->setLocalZOrder(logDanhBaiIndex);

			auto positiony = ((logDanhBaiIndex - 1) % 4) * 30;
			auto actionMove = MoveTo::create(0.5, Vec2(Vec2(scaleX * 660 + i * Card::cardWidth - cWidth, scaleY * (500 - positiony))));
			auto actionScale = ScaleTo::create(0.5, scaleX, scaleY);
			auto actionRotate = RotateBy::create(0.5, 360);
			logDanhBai[logDanhBaiIndex]->baiDanh->danhSach[i]->runAction(Sequence::create(actionMove, NULL));
			logDanhBai[logDanhBaiIndex]->baiDanh->danhSach[i]->runAction(Sequence::create(actionScale, NULL));
			logDanhBai[logDanhBaiIndex]->baiDanh->danhSach[i]->runAction(Sequence::create(actionRotate, NULL));
			audio->playEffect("Sound/add.mp3", false, 1.0f, 1.0f, 1.0f);
		}
	}
	drawUpdatePlayerStatus();
	auto actionDelay = DelayTime::create(1.0f);
	auto actionDone = CallFuncN::create(this, callfuncN_selector(GameTienLenMNScene::danhBaiAnimationDone));
	this->runAction(Sequence::create(actionDelay, actionDone, NULL));
}

void GameTienLenMNScene::drawInitPlayerStatus() {
	//Vẽ các thông tin Player:
	///Số quân bài còn lại:
	lblP1CardCount = Label::create();
	lblP1CardCount->setTextColor(Color4B::GREEN);
	lblP1CardCount->setSystemFontSize(24);
	lblP1CardCount->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	lblP1CardCount->setPosition(Vec2(scaleX * PP1.x, scaleY * (PP1.y + 10)));
	lblP1CardCount->enableOutline(Color4B::WHITE, 2);
	this->addChild(lblP1CardCount, 101);

	lblP2CardCount = Label::create();
	lblP2CardCount->setTextColor(Color4B::GREEN);
	lblP2CardCount->setSystemFontSize(24);
	lblP2CardCount->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	lblP2CardCount->setPosition(Vec2(scaleX * PP2.x, scaleY * (PP2.y + 10)));
	lblP2CardCount->enableOutline(Color4B::WHITE, 2);
	this->addChild(lblP2CardCount, 101);

	lblP3CardCount = Label::create();
	lblP3CardCount->setTextColor(Color4B::GREEN);
	lblP3CardCount->setSystemFontSize(24);
	lblP3CardCount->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	lblP3CardCount->setPosition(Vec2(scaleX * PP3.x, scaleY * (PP3.y + 10)));
	lblP3CardCount->enableOutline(Color4B::WHITE, 2);
	this->addChild(lblP3CardCount, 101);

	///Bỏ vòng:
	iconSkipPlayer[0] = Sprite::create("skip.png");
	iconSkipPlayer[0]->setPosition(Vec2(scaleX * 688, scaleY * 75));
	iconSkipPlayer[0]->setVisible(false);
	this->addChild(iconSkipPlayer[0], 101);

	iconSkipPlayer[1] = Sprite::create("skip.png");
	iconSkipPlayer[1]->setPosition(Vec2(scaleX * PP1.x, scaleY * (PP1.y - 10)));
	iconSkipPlayer[1]->setVisible(false);
	this->addChild(iconSkipPlayer[1], 101);

	iconSkipPlayer[2] = Sprite::create("skip.png");
	iconSkipPlayer[2]->setPosition(Vec2(scaleX * PP2.x, scaleY * (PP2.y - 10)));
	iconSkipPlayer[2]->setVisible(false);
	this->addChild(iconSkipPlayer[2], 101);

	iconSkipPlayer[3] = Sprite::create("skip.png");
	iconSkipPlayer[3]->setPosition(Vec2(scaleX * PP3.x, scaleY * (PP3.y - 10)));
	iconSkipPlayer[3]->setVisible(false);
	this->addChild(iconSkipPlayer[3], 101);
}

void GameTienLenMNScene::drawUpdatePlayerStatus() {
	//Số lượng quân bài
	std::ostringstream s1;
	s1 << "x" << CPplayer[1]->BaiCount;
	lblP1CardCount->setString(s1.str());

	std::ostringstream s2;
	s2 << "x" << CPplayer[2]->BaiCount;
	lblP2CardCount->setString(s2.str());

	std::ostringstream s3;
	s3 << "x" << CPplayer[3]->BaiCount;
	lblP3CardCount->setString(s3.str());
	//Trạng thái bỏ vòng
	for (auto i = 0; i < 4; i++) {
		iconSkipPlayer[i]->setVisible(logDanhBai[logDanhBaiIndex]->nguoiDaBoVong[i]);
	}
}

//De quy toi uu bai danh ra:
BaiDanhRa* GameTienLenMNScene::tlmnTryTimBaiDanhRa(Card* selectedCrad[13]) {
	//chonj bai de danh:
	auto soBai = RandomHelper::random_int(1, 3);

	auto i = 0;
	auto baiDanh = new BaiDanhRa();
	baiDanh->soLuong = 0;
	while (i < 13 && baiDanh->soLuong < soBai) {
		if (!selectedCrad[i]->daDanh) {
			selectedCrad[i]->cardState = CARD_STATE_SELT;
			baiDanh->danhSach[baiDanh->soLuong] = selectedCrad[i];
			baiDanh->soLuong++;
		}
		i++;
	}
	//logDanhBai[logDanhBaiIndex]->baiDanh = baiDanh;
	//z->BaiCount = CPplayer[player]->BaiCount - logDanhBai[logDanhBaiIndex]->baiDanh->soLuong;
	return baiDanh;
}

///Kiem tra Luot đánh ra có phù hợp với lượt trước đó không (dành kiểm tra người chơi thôi, máy đánh đã kiểm tra lúc chọn rồi)
bool GameTienLenMNScene::tlmnKiemTraBaiDanhRa(BaiDanhRa* baidanhra, int player) {

	return true;
}

//Danh abi
BaiDanhRa* GameTienLenMNScene::tlmnCpuTimBaiDanh(int player) {
	if (logDanhBai[logDanhBaiIndex - 1]->vongKetThuc) {
		auto baiDanhRa = tlmnTryTimBaiDanhRa({});
		logDanhBai[logDanhBaiIndex]->baiDanh = baiDanhRa;
		CPplayer[player]->BaiCount = CPplayer[player]->BaiCount - logDanhBai[logDanhBaiIndex]->baiDanh->soLuong;
		return baiDanhRa;
	}
	//Chonj bai de do~:
	auto baiDanhRa = tlmnCpuTimBaiDo(nullptr, 0);
	if (baiDanhRa->soLuong != 0) {
		logDanhBai[logDanhBaiIndex]->baiDanh = baiDanhRa;
		CPplayer[player]->BaiCount = CPplayer[player]->BaiCount - logDanhBai[logDanhBaiIndex]->baiDanh->soLuong;
	} else {
		tlmnBoLuot(player);
	}
	return baiDanhRa;
}

//Do bai
BaiDanhRa* GameTienLenMNScene::tlmnCpuTimBaiDo(BaiDanhRa* baidanh, int player) {

	return nullptr;
}

///CPU chon quan de danh 
bool GameTienLenMNScene::tlmnCpuChonBaiDanhRa(int player, int level) {
	//CPU Chon quan de đánh and Fill log:
	auto baidanh = tlmnCpuTimBaiDanh(player);
	return baidanh->soLuong != 0;
}

void GameTienLenMNScene::tlmnBoLuot(int player) {
	auto luotNguoiDanh = logDanhBai[logDanhBaiIndex];
	auto baiDanh = new BaiDanhRa();
	baiDanh->soLuong = 0;
	luotNguoiDanh->baiDanh = baiDanh;
	luotNguoiDanh->nguoiDangDanh = logDanhBai[logDanhBaiIndex - 1]->nguoiDangDanh; //chuyeen quyen cho nguoi truow do
	luotNguoiDanh->nguoiDaBoVong[player] = true;
	luotNguoiDanh->nguoiDaBoVongCount++;

	if (luotNguoiDanh->nguoiDaBoVongCount >= 3) {
		luotNguoiDanh->vongKetThuc = true;
	}
	if (player == 0) {
		EnableControls(false);
	}
}

void GameTienLenMNScene::EnableControls(bool state) {
	btnConfig->setEnabled(state);
	btnBack->setEnabled(state);

	btnUserPlay->setEnabled(state);
	btnUserThoi->setEnabled(state);
	btnUserXep->setEnabled(state);
	btnUserBoChon->setEnabled(state);
}

//Private for Tien Len Mien Nam:
KieuXapBo GameTienLenMNScene::tlmnTimKieuSapBo(Card* selectedCrad[13], int selectedCradLen) {
	if (selectedCradLen == 1) {
		///Rác:
		return BO_RAC;
	}
	if (selectedCradLen == 2) {
		///Đôi
		if (selectedCrad[0]->cardIndex == selectedCrad[1]->cardIndex) {
			return BO_DOI;
		}
		return BO_FALSE;
	}
	if (selectedCradLen == 3) {
		///Sám
		if (selectedCrad[0]->cardIndex == selectedCrad[1]->cardIndex && selectedCrad[1]->cardIndex == selectedCrad[2]->cardIndex) {
			return BO_BA;
		}
	}
	if (selectedCradLen == 4) {
		///Tứ quý
		if (selectedCrad[0]->cardIndex == selectedCrad[1]->cardIndex && selectedCrad[1]->cardIndex == selectedCrad[2]->cardIndex && selectedCrad[2]->cardIndex == selectedCrad[3]->cardIndex) {
			return BO_TUQUY;
		}
	}
	///Kiểm tra sảnh:
	Card* tmpar[13];
	for (auto i = 0; i < selectedCradLen; i++) {
		tmpar[i] = selectedCrad[i];
	}
	///sort teamp
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
	if (isValid) return BO_DAY;
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
	if (isValid) return BO_DOITHONG;
	return BO_FALSE;
}

