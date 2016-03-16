#include "GameTienLenMNScene.h"

USING_NS_CC;

Scene* GameTienLenMNScene::createScene() {
	auto scene = Scene::create();
	auto layer = create();
	scene->addChild(layer);
	return scene;
}

GameTienLenMNScene* GameTienLenMNScene::loadScene(std::function<void()> onCompleted) {
	onCompleted;
	return nullptr;
}

GameTienLenMNScene::GameTienLenMNScene() {
	
}


GameTienLenMNScene::~GameTienLenMNScene() {
}
