#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
	bool init() override;
	void onEnter() override;
	void finishSplash(float dt);
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    static HelloWorld* create() {
		auto pRet = new(std::nothrow) HelloWorld(); 
		if (pRet && pRet->init()) {
			pRet->autorelease(); return pRet;
		}
	    delete pRet;
	    return nullptr;
    };
};

#endif // __HELLOWORLD_SCENE_H__
