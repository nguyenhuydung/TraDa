#ifndef __TIENLENMN_SCENE_H__
#define __TIENLENMN_SCENE_H__

#include "cocos2d.h"
#include "Card.h"
#include <SimpleAudioEngine.h>
#include "ui/CocosGUI.h"

const Vec2 PP0 = Vec2(45, 110);
const Vec2 PP1 = Vec2(940, 375);
const Vec2 PP2 = Vec2(940, 560);
const Vec2 PP3 = Vec2(335, 560);
static float scaleX = 0.0f;
static float scaleY = 0.0f;

static float scaleXL = 0.0f;
static float scaleYL = 0.0f;

enum XapBo {
	BO_RAC,
	BO_DOI,
	BO_BA,
	BO_TUQUY,
	BO_DAY,
	BO_DOITHONG,
	BO_FALSE
};

struct LuotDanh {
	int nguoiDangDanh = -1;
	int nguoiDaBoVong[4] = {0,0,0,0};
	int nguoiDanhSang = 0;
	XapBo baiDanhSang = BO_RAC;

	LuotDanh() {
		nguoiDangDanh = -1;
		nguoiDanhSang = -1;
		nguoiDaBoVong[0] = 0;
		nguoiDaBoVong[0] = 0;
		nguoiDaBoVong[0] = 0;
		baiDanhSang = BO_RAC;
	}
};

class GameTienLenMNScene : public Layer {
public:
	GameTienLenMNScene();
	~GameTienLenMNScene();
	static Scene* createScene();
	bool init() override;
	///Bai bac
	int chiaBaiIndex = 0;
	void chiaBai();
	void chiaBaiAnimation(Node* sender);
	void newGameStart();
	///danh bai
	int lopBaiDanhRa = 0, lopBaiDanhRaCuoi = 0;
	Card* baiDanhRa[100][13];
	int baiDanhRaCount[100];

	void danhBai();
	void danhBaiAnimation();
	void danhBaiDone(Node* sender);
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

private:
	XapBo isSelectedType(Card* selectedCrad[13], int selectedCradLen);
	//CPU playing:
	LuotDanh* stepDanhBai; //Cai bien nay chi ra ai dang danh, ai bo luot
	bool tlmnValid(int state);
	void tlmnCpuSelect(int player, int step, int level);
	///UI
	ui::Button *btnConfig, *btnBack, *btnUserPlay, *btnUserThoi, *btnUserXep;
	Label* messageBox;
	void EnableControls(bool state);
	
	//bool 
	CocosDenshion::SimpleAudioEngine* audio = CocosDenshion::SimpleAudioEngine::getInstance();
};

#endif

