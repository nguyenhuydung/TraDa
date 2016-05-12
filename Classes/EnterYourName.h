#pragma once
#include "cocos2d.h"

class EnterYourName : public cocos2d::Layer {
public:
	static cocos2d::Scene* createScene();
	static std::string* playerName;
	bool init() override;

	static EnterYourName* create() {
		auto pRet = new(std::nothrow) EnterYourName();
		if (pRet && pRet->init()) {
			pRet->autorelease(); return pRet;
		}
		delete pRet;
		return nullptr;
	};
};

