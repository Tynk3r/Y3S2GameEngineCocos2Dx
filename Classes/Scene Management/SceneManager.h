#pragma once
#include <iostream>
#include "SingletonTemplate.h"
#include "cocos2d.h"

class SceneManager : public Singleton<SceneManager>
{
	friend Singleton<SceneManager>;
public:
	SceneManager();
	~SceneManager();

	void ReplaceScene(cocos2d::Scene* scene);
	void ReplaceScene(cocos2d::Scene* scene, std::vector<std::string> resourcesToLoad_);

	std::vector<std::string> GetResourcesToLoad();
	cocos2d::Scene* GetSceneToLoad();

	enum SCENE_NAMES
	{
		HelloWorld,
		Test
	};

private:
	std::vector<std::string> resourcesToLoad;
	cocos2d::Scene* sceneToLoad;
};

