#include "component.h"
#include "gameobject.h"

Component::Component(QObject *parent,GameObject* gameObject):
    QObject{parent},
    mGameObject(gameObject),
    mUpdateOrder(100)
{
    mGameObject->addComponent(this);
}

Component::~Component()
{
    mGameObject->removeComponent(this);
}

int Component::getUpdateOrder()
{
    return this->mUpdateOrder;
}


