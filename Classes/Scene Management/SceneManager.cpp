#include "SceneManager.h"
#include "LoadingScene.h"

SceneManager::SceneManager()
{
	sceneToLoad = nullptr;
}

SceneManager::~SceneManager()
{
}

void SceneManager::ReplaceScene(cocos2d::Scene * scene)
{
	cocos2d::Director::getInstance()->replaceScene(scene);
}

void SceneManager::ReplaceScene(cocos2d::Scene* scene, std::vector<std::string> resourcesToLoad_)
{
	//if(sceneToLoad != nullptr)
	//	sceneToLoad->release();
	resourcesToLoad = resourcesToLoad_;
	sceneToLoad = scene;
	//sceneToLoad->retain();
	cocos2d::Director::getInstance()->replaceScene(LoadingScene::createScene());
}

std::vector<std::string> SceneManager::GetResourcesToLoad()
{
	return resourcesToLoad;
}

cocos2d::Scene * SceneManager::GetSceneToLoad()
{
	return sceneToLoad;
}
