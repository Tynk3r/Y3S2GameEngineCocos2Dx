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

	/** Replaces the running scene with a new one. The running scene is terminated.
	* Immediately goes to next scene.
	* ONLY call it if there is a running scene.
	*/
	void ReplaceScene(cocos2d::Scene* scene);

	/** Replaces the running scene with a new one. The running scene is terminated.
	* Goes to loading screen to load resources before going to next scene.
	* ONLY call it if there is a running scene.
	*/
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

