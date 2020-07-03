#pragma once
#include"UI.h"
struct IScene
{
	virtual void OnLoaded() = 0;
	virtual void OnUnloaded() = 0;
	virtual void Update() = 0;
	virtual bool ShowBox(UI* ptr) { ptr->Die(); return false; };
	virtual bool HideBox() { return false; };
	virtual ~IScene() = default;
};
class SceneManager
{
private:
	SceneManager();
	~SceneManager();
	static void LoadScene(IScene * pScene);
public:
	static SceneManager* GetInstance();
	static void LastUpdate();
	//매개 인자가 없는 씬 생성자 호출
	template<typename SceneT>
	static void LoadScene();
	template<typename SceneT, typename ...ArgT>
	static void LoadScene(ArgT&& ...args);
	static void Release();
	IScene* pCurrentScene;
	IScene* pReadyScene;
};

template<typename SceneT>
inline void SceneManager::LoadScene()
{
	LoadScene(static_cast<IScene*>(new SceneT{}));
}

template<typename SceneT, typename ...ArgT>
inline void SceneManager::LoadScene(ArgT&& ...args)
{
	LoadScene(static_cast<IScene*>(new SceneT{std::forward<ArgT>(args) ... }));
}
