#include "stdafx.h"
#include "TestPlayScene.h"
#include "Monster.h"
#include "MainGame.h"
void PlayScene::OnLoaded()
{
    time = 0.f;
    oldTime = 0.0f;
    ObjectManager::CreateObject(ObjectType::PLAYER);
    timeline = {
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
}

void PlayScene::OnUnloaded()
{
    ObjectManager::DestroyAll();
}
//#1 ��׶��尡 �÷��̾ ���ͳ� ���ֺ��� �Ʒ��� �־�� �Ѵ�.
//#2 ��׶��尡 �̺�Ʈ�� �޾Ƽ�
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
}