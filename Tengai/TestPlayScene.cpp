#include "stdafx.h"
#include "TestPlayScene.h"
#include "Monster.h"
#include "MainGame.h"
#include "PauseBox.h"
#include "GameOverBox.h"
PlayScene::PlayScene():
    pCurrentShowBox{nullptr}
{
    time = 0.f;
    oldTime = 0.0f;
}
void PlayScene::OnLoaded()
{
    time = 0.f;
    oldTime = 0.0f;
    ObjectManager::CreateObject(ObjectType::PLAYER);
    timeline = {
        /*{ 1  ,Monster::Initialize(ObjectManager::CreateObject(ObjectType::MONSTER),MonsterType::BOSS, Transform{ WINDOW_WIDTH + 32, WINDOW_HEIGHT / 2 }) }*/
        { 0 ,Monster::Initialize(ObjectManager::CreateObject(ObjectType::MONSTER),MonsterType::MOB01, Transform{ WINDOW_WIDTH + 32, WINDOW_HEIGHT / 2 }) },
        { 2 ,Monster::Initialize(ObjectManager::CreateObject(ObjectType::MONSTER),MonsterType::MOB01, Transform{ WINDOW_WIDTH + 32, WINDOW_HEIGHT / 2 }) },
        { 4 ,Monster::Initialize(ObjectManager::CreateObject(ObjectType::MONSTER),MonsterType::MOB01, Transform{ WINDOW_WIDTH + 32, WINDOW_HEIGHT / 2 }) },
        { 4 ,Monster::Initialize(ObjectManager::CreateObject(ObjectType::MONSTER),MonsterType::MOB02, Transform{ WINDOW_WIDTH + 32, WINDOW_HEIGHT / 2 }) },
        { 6 ,Monster::Initialize(ObjectManager::CreateObject(ObjectType::MONSTER),MonsterType::MOB01, Transform{ WINDOW_WIDTH + 32, WINDOW_HEIGHT / 2 }) },
        { 8 ,Monster::Initialize(ObjectManager::CreateObject(ObjectType::MONSTER),MonsterType::MOB01, Transform{ WINDOW_WIDTH + 32, WINDOW_HEIGHT / 2 }) },
        { 9 ,Monster::Initialize(ObjectManager::CreateObject(ObjectType::MONSTER),MonsterType::MOB02, Transform{ WINDOW_WIDTH + 32, WINDOW_HEIGHT / 2 + 100 }) },
        { 10 ,Monster::Initialize(ObjectManager::CreateObject(ObjectType::MONSTER),MonsterType::MOB01, Transform{ WINDOW_WIDTH + 32, WINDOW_HEIGHT }) },
        { 11 ,Monster::Initialize(ObjectManager::CreateObject(ObjectType::MONSTER),MonsterType::MOB01, Transform{ WINDOW_WIDTH + 32, WINDOW_HEIGHT  }) },
        { 16 ,Monster::Initialize(ObjectManager::CreateObject(ObjectType::MONSTER),MonsterType::MOB01, Transform{ WINDOW_WIDTH + 32, WINDOW_HEIGHT  }) },
        { 20 ,Monster::Initialize(ObjectManager::CreateObject(ObjectType::MONSTER),MonsterType::MOB02, Transform{ WINDOW_WIDTH + 32, 100 }) },
        { 24 ,Monster::Initialize(ObjectManager::CreateObject(ObjectType::MONSTER),MonsterType::MOB02, Transform{ WINDOW_WIDTH + 32, 200 }) },
        { 28 ,Monster::Initialize(ObjectManager::CreateObject(ObjectType::MONSTER),MonsterType::MOB02, Transform{ WINDOW_WIDTH + 32, 300 }) },
        { 32  ,Monster::Initialize(ObjectManager::CreateObject(ObjectType::MONSTER),MonsterType::MOB02, Transform{ WINDOW_WIDTH + 32, 400 }) },
        { 35 ,Monster::Initialize(ObjectManager::CreateObject(ObjectType::MONSTER),MonsterType::MOB01, Transform{ WINDOW_WIDTH + 32, WINDOW_HEIGHT }) },
        { 37 ,Monster::Initialize(ObjectManager::CreateObject(ObjectType::MONSTER),MonsterType::MOB01, Transform{ WINDOW_WIDTH + 32, WINDOW_HEIGHT  }) },
        { 39 ,Monster::Initialize(ObjectManager::CreateObject(ObjectType::MONSTER),MonsterType::MOB01, Transform{ WINDOW_WIDTH + 32, WINDOW_HEIGHT  }) },
        { 41 ,Monster::Initialize(ObjectManager::CreateObject(ObjectType::MONSTER),MonsterType::MOB01, Transform{ WINDOW_WIDTH + 32, WINDOW_HEIGHT }) },
        { 45 ,Monster::Initialize(ObjectManager::CreateObject(ObjectType::MONSTER),MonsterType::MOB01, Transform{ WINDOW_WIDTH + 32, WINDOW_HEIGHT }) },
        { 47 ,Monster::Initialize(ObjectManager::CreateObject(ObjectType::MONSTER),MonsterType::MOB02, Transform{ WINDOW_WIDTH + 32, WINDOW_HEIGHT / 2 + 100 }) },
        { 47 ,Monster::Initialize(ObjectManager::CreateObject(ObjectType::MONSTER),MonsterType::MOB01, Transform{ WINDOW_WIDTH + 32, WINDOW_HEIGHT  }) },
        { 49 ,Monster::Initialize(ObjectManager::CreateObject(ObjectType::MONSTER),MonsterType::MOB01, Transform{ WINDOW_WIDTH + 32, WINDOW_HEIGHT  }) },
         { 50 ,Monster::Initialize(ObjectManager::CreateObject(ObjectType::MONSTER),MonsterType::MOB02, Transform{ WINDOW_WIDTH + 32, WINDOW_HEIGHT / 2 - 100 }) },
        { 50 ,Monster::Initialize(ObjectManager::CreateObject(ObjectType::MONSTER),MonsterType::MOB01, Transform{ WINDOW_WIDTH + 32, WINDOW_HEIGHT  }) },
        { 51 ,Monster::Initialize(ObjectManager::CreateObject(ObjectType::MONSTER),MonsterType::MOB01, Transform{ WINDOW_WIDTH + 32, WINDOW_HEIGHT }) },
        { 60  ,Monster::Initialize(ObjectManager::CreateObject(ObjectType::MONSTER),MonsterType::BOSS, Transform{ WINDOW_WIDTH + 32, WINDOW_HEIGHT / 2 }) }
    };
    iter = timeline.begin();
    MainGame::Resume();
}

void PlayScene::OnUnloaded()
{
    ObjectManager::DestroyAll();
}
//#1 백그라운드가 플레이어나 몬스터나 유닛보다 아래에 있어야 한다.
//#2 백그라운드가 이벤트를 받아서
void PlayScene::Update()
{
    if (MainGame::GetInstance()->isPause == false)
    {
        float currentTime = time + TimeManager::DeltaTime();
        float prevTime = oldTime;
        time = currentTime;
        if (currentTime == prevTime)
        {
            return;
        }
        for (; iter != timeline.end(); ++iter)
        {
            if (prevTime <= iter->first && iter->first <= currentTime)
            {
                oldTime = time;
                EventManager::Broadcast< TimePassedEvent>(iter->second, currentTime);
            }
            else
            {
                break;
            }
        }
    }
    else if (pCurrentShowBox != nullptr)
    {
        pCurrentShowBox->Update();
    }
    if (InputManager::GetKeyDown(VK_ESCAPE))
    {
        if (MainGame::GetInstance()->isPause == false)
        {
            MainGame::Pause();
            auto box = (UI*)ObjectManager::CreateObject<PauseBox>(ObjectType::UI);
            if (ShowBox(box))
            {
                box->Show();
            }
            else
            {
                box->Die();
            }
        }
        else if(dynamic_cast<PauseBox*>(pCurrentShowBox) != nullptr)
        {
            HideBox();
        }
    }
}

bool PlayScene::ShowBox(UI* ptr)
{
    if (pCurrentShowBox == nullptr)
    {
        pCurrentShowBox = ptr;
        return true;
    }
    return false;
}

bool PlayScene::HideBox()
{
    if (pCurrentShowBox != nullptr)
    {
        pCurrentShowBox->Hide();
    }
    pCurrentShowBox = nullptr;
    return true;
}
