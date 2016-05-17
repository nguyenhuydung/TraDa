#ifndef __RANKING_SCENE_H__
#define __RANKING_SCENE_H__

#include "cocos2d.h"

class RankingScene : public cocos2d::Layer {
	public:
	RankingScene();
	~RankingScene();
	cocos2d::UserDefault* userdata;

	static cocos2d::Scene* createScene();
	bool init() override;
	// implement the "static create()" method manually
	static RankingScene* create() {
		auto pRet = new(std::nothrow) RankingScene();
		if (pRet && pRet->init()) {
			pRet->autorelease(); return pRet;
		}
		delete pRet;
		return nullptr;
	};
};
#endif
