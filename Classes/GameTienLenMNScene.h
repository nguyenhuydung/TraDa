#ifndef __TIENLENMN_SCENE_H__
#define __TIENLENMN_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

typedef void(*functiontype)();

class GameTienLenMNScene : public Layer {
	public:
	static Scene* createScene();
	static GameTienLenMNScene* loadScene(std::function<void ()> onCompleted);
	GameTienLenMNScene();
	~GameTienLenMNScene();
};

#endif
