#include "spritecomponent.h"
#include "gameobject.h"
#include "game.h"

spriteComponent::spriteComponent(GameObject* gameObject,int drawOrder):
    Component(gameObject),
    mTexWidth(0),
    mTexHeight(0),
    mDrawOrder(drawOrder)
{
    mGameObject->getGame()->createSprite(this);
}

spriteComponent::~spriteComponent()
{
    mGameObject->getGame()->removeSprite(this);
}

void spriteComponent::Draw()
{
    //to be written
}


