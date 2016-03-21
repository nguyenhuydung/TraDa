#ifndef __TIENLENMN_SCENE_H__
#define __TIENLENMN_SCENE_H__

#include "cocos2d.h"
#include "Card.h"

const cocos2d::Vec2 PP0 = cocos2d::Vec2(310, 70);
const cocos2d::Vec2 PP1 = cocos2d::Vec2(950, 370);
const cocos2d::Vec2 PP2 = cocos2d::Vec2(640, 490);
const cocos2d::Vec2 PP3 = cocos2d::Vec2(320, 370);
static float scaleX = 0.0f;
static float scaleY = 0.0f;

class GameTienLenMNScene : public cocos2d::Layer {
	public:
	GameTienLenMNScene();
	~GameTienLenMNScene();
	int chiaBaiIndex = 0;

	int lopBaiDanhRa = 0, lopBaiDanhRaCuoi = 0;
	Card* baiDanhRa[100][13];
	int baiDanhRaCount[100];

	static cocos2d::Scene* createScene();
	bool init() override;
	
	void chiaBai();
	void chiaBaiAnimation(Node* sender);
	void newGameStart(int lastWinPlayer);
	void danhBaiAnimation();

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
