#ifndef __TIENLENMN_SCENE_H__
#define __TIENLENMN_SCENE_H__

#include "cocos2d.h"
#include "Card.h"
#include <SimpleAudioEngine.h>
#include "ui/CocosGUI.h"
#include "GPlayer.h"

const Vec2 PP0 = Vec2(45, 110);
const Vec2 PP1 = Vec2(940, 375);
const Vec2 PP2 = Vec2(940, 560);
const Vec2 PP3 = Vec2(335, 560);
static float scaleX = 0.0f;
static float scaleY = 0.0f;

static float scaleXL = 0.0f;
static float scaleYL = 0.0f;






class DanhDauXapBo {
public:
	KieuXapBo DanhDau[13];
	static DanhDauXapBo* Create(int p) {
		auto x = new DanhDauXapBo();
		for (auto i = 0; i < 13; i++) {
			x->DanhDau[i] = BO_RAC; // { BO_RAC, BO_RAC, BO_RAC, BO_RAC, BO_RAC, BO_RAC, BO_RAC, BO_RAC, BO_RAC, BO_RAC, BO_RAC, BO_RAC, BO_RAC };
		}
		return x;
	}
};

class GameTienLenMNScene : public Layer {
	public:
	GameTienLenMNScene();
	~GameTienLenMNScene();
	static Scene* createScene();
	///create:
	static GameTienLenMNScene* create() {
		auto pRet = new(std::nothrow) GameTienLenMNScene();
		if (pRet && pRet->init()) {
			pRet->autorelease();
			return pRet;
		}
		delete pRet;
		return nullptr;
	};

	//------------------------------------------------------------------
	bool init() override;
	///Bai bac
	int chiaBaiIndex = 0;
	void chiaBai(Node* sender);
	void chiaBaiAnimation(Node* sender);
	///danh bai
	int logDanhBaiIndex = -1; //Trận đầu tiên
	LogLuotDanhBai* logDanhBai[104]; ///Log lại các lượt đánh ra

	void danhBai();
	void danhBaiAnimationDone(Node* sender);
	void danhBaiAnimation();

	void drawInitPlayerStatus();
	void drawUpdatePlayerStatus();
	int danhBaiKhoiTaoLog(); //retun player đánh tiếp theo		
	bool danhBaiKiemTraHopLe(BaiDanhRa *baidanhra); ///kiem tra xem bai danh có đúng không
	void danhBaiBoLuot(int player);

	private://------------------------------------------------------------------
	///UI:
	ui::Button *btnConfig = nullptr, *btnBack = nullptr, *btnUserPlay = nullptr, *btnUserThoi = nullptr, *btnUserXep = nullptr, *btnUserBoChon = nullptr;
	///Message and S
	Label* messageBox = nullptr, *lblP1CardCount = nullptr, *lblP2CardCount = nullptr, *lblP3CardCount = nullptr;
	///Bỏ lượt overlay icon:
	Sprite *iconSkipPlayer[4], *iconWinner = nullptr;
	void EnableControls(bool state);
	///Audio:
	CocosDenshion::SimpleAudioEngine* audio = CocosDenshion::SimpleAudioEngine::getInstance();
};

#endif

