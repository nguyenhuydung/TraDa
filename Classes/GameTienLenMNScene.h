#ifndef __TIENLENMN_SCENE_H__
#define __TIENLENMN_SCENE_H__

#include "cocos2d.h"

class GameTienLenMNScene : public cocos2d::Layer {
	public:
	GameTienLenMNScene();
	~GameTienLenMNScene();

	static cocos2d::Scene* createScene();
	bool init() override;
	
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
