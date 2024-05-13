#include "gameobject.h"
#include "game.h"

GameObject::GameObject(QObject *parent,Game *game):
    QObject{parent},
    mGame(game),
    mState(State::EActive)
{
    mGame->createGameObject(this);
}

GameObject::~GameObject()
{
    mGame->removeGameObject(this);
    while (!mComponents.empty())
    {
        delete mComponents.back();
    }
}

void GameObject::addComponent(Component* component)
{
    // 获取该组件的更新顺序
    int order = component->getUpdateOrder();
    auto iter = mComponents.begin();
    // 新组件需要按顺序插入到对应位置
    for (; iter != mComponents.end(); ++iter)
    {
        if (order < (*iter)->getUpdateOrder())
        {
            break;
        }
    }
    mComponents.insert(iter, component);
}

void GameObject::removeComponent(Component* component)
{
    auto iter = std::find(mComponents.begin(), mComponents.end(), component);
    if (iter != mComponents.end())
    {
        mComponents.erase(iter);
    }
}

//!获取当前状态
GameObject::State GameObject::getState()
{
    return this->mState;
}

//!获取Game对象
Game* GameObject::getGame()
{
    return this->mGame;
}
