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
    Bind(EventId::COLLISION_OBJ, &Item::OnCollision);
}

GameObject* Item::Initialize(GameObject* const obj, ItemType _type, const Transform& pos)
{
    if (obj->type == ObjectType::ITEM)
    {
        const auto uid = obj->uid;
        obj->~GameObject();
        new(obj) Item(_type, pos);
        obj->uid = uid;
    }
    return obj;
}
Item::~Item()
{

}

void Item::Update()
{

}

void Item::Render()
{

}

void Item::OnCollision(const CollisionEvent& event)
{

}
