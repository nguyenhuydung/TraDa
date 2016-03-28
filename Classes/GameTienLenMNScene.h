#ifndef __TIENLENMN_SCENE_H__
#define __TIENLENMN_SCENE_H__

#include "cocos2d.h"
#include "Card.h"

const Vec2 PP0 = Vec2(45, 110);
const Vec2 PP1 = Vec2(940, 375);
const Vec2 PP2 = Vec2(940, 560);
const Vec2 PP3 = Vec2(335, 560);
static float scaleX = 0.0f;
static float scaleY = 0.0f;

static float scaleXL = 0.0f;
static float scaleYL = 0.0f;

class GameTienLenMNScene : public Layer {
	public:
	GameTienLenMNScene();
	~GameTienLenMNScene();
	int chiaBaiIndex = 0;

	int lopBaiDanhRa = 0, lopBaiDanhRaCuoi = 0;
	Card* baiDanhRa[100][13];
	int baiDanhRaCount[100];
	static int stepDanhBai; //Cai bien nay chi ra ai dang danh, ai bo luot

	static Scene* createScene();
	bool init() override;
	
	void chiaBai();
	void chiaBaiAnimation(Node* sender);
	void newGameStart(int lastWinPlayer);
	void danhBaiAnimation();
	//CPU playing:
	bool tlmnValid(int state);
	void tlmnCpuSelect(int player, int step);

	//static GameTienLenMNScene* loadScene(std::function<void ()> onCompleted);
	static GameTienLenMNScene* create() {
		auto pRet = new(std::nothrow) GameTienLenMNScene();
		if (pRet && pRet->init()) {
			pRet->autorelease(); return pRet;
		}
		delete pRet;
		return nullptr;
	};
};

#endif
