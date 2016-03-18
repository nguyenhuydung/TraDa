#pragma once
#ifndef __GAMESELECTING_SCENE_H__
#define __GAMESELECTING_SCENE_H__

#include "cocos2d.h"

class GameListScene : public cocos2d::Layer {
	public:
	GameListScene();
	~GameListScene();

	static cocos2d::Scene* createScene();
	bool init() override;

	static GameListScene* create() {
		auto pRet = new(std::nothrow) GameListScene();
		if (pRet && pRet->init()) {
			pRet->autorelease(); return pRet;
		}
		delete pRet;
		return nullptr;
	};
};
#endif
