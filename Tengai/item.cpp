#include "stdafx.h"
#include "item.h"

Item::Item():
    itemType{ItemType::NONE}
{
    type = ObjectType::ITEM;
}

Item::Item(ItemType _type, const Transform& pos):
    itemType{_type}
{
    type = ObjectType::ITEM;
    this->position = pos;
    this->pState = nullptr;
    this->simpleCollider = RECT{ -15, -15, 15, 15 };
    this->colliders.push_back(this->simpleCollider);
    this->speed = 100;
    MakeNewDest();


    Bind(EventId::COLLISION_OBJ, &Item::OnCollision);
}

GameObject* Item::Initialize(GameObject* const obj, ItemType _type, const Transform& pos)
{
    if (obj->type == ObjectType::ITEM)
    {
        const auto uid = obj->uid;
        obj->~GameObject();
        switch (_type)
        {
        case ItemType::HEAL:
            new(obj) HealItem{ _type, pos };
            break;
        case ItemType::SKILL:
            new(obj) SkillItem{ _type, pos };
            break;
        }
        obj->uid = uid;
    }
    return obj;
}
Item::~Item()
{

}

void Item::Update()
{
    if (pState->Update())
    {
        MakeNewDest();
    }
}
void Item::OnCollision(const CollisionEvent& event)
{
    if (event.other->type == ObjectType::PLAYER)
    {
        Die();
    }
}

void Item::MakeNewDest()
{
    Transform pos{ position };
    Transform center{ rand() % (WINDOW_WIDTH * 10) / 10.f , rand() % (WINDOW_HEIGHT * 10) / 10.f };
    Transform dest{ rand() % (WINDOW_WIDTH * 10) / 10.f , rand() % (WINDOW_HEIGHT * 10) / 10.f };
    //Character* const _pCharecter, const Transform& _start, const Transform& _center, const Transform& _dest
    if (pState != nullptr)
    {
        delete pState;
        pState = nullptr;
    }
    pState = new BezierCurveMoveToState{this, pos, center, dest};
    pState->Reset();
}

HealItem::HealItem(ItemType _type, const Transform& pos):
    Item{ _type, pos }
{
}

HealItem::~HealItem()
{
}

void HealItem::Render()
{
    RenderManager::DrawRect(simpleCollider + position, RGB(128, 255, 128));
}

SkillItem::SkillItem(ItemType _type, const Transform& pos):
    Item{ _type, pos }
{
}

SkillItem::~SkillItem()
{

}

void SkillItem::Render()
{
    RenderManager::DrawRect(simpleCollider + position, RGB(255, 128, 128));
}
