#pragma once
#include"SceneManager.h"
#include<vector>
#include"GameObject.h"
class PlayScene : public IScene
{
public:

    void OnLoaded() override;
    void OnUnloaded() override;
    void Update() override;
    std::vector<std::pair<float, GameObject*> > timeline;
    std::vector<std::pair<float, GameObject*> >::const_iterator iter;
    float time;
    float oldTime;
};