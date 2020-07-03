#pragma once
#include"SceneManager.h"
#include<vector>
#include"GameObject.h"
#include"UI.h"
class PlayScene : public IScene
{
public:
    PlayScene();
    void OnLoaded() override;
    void OnUnloaded() override;
    void Update() override;
    virtual bool ShowBox(UI*) override;
    virtual bool HideBox() override;
    std::vector<std::pair<float, GameObject*> > timeline;
    std::vector<std::pair<float, GameObject*> >::const_iterator iter;
    UI* pCurrentShowBox;
    float time;
    float oldTime;
};