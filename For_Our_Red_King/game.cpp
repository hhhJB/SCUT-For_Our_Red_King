#include "game.h"
#include "spritecomponent.h"
#include "player.h"

Game::Game(QObject *parent):
    mIsRuning(true),
    mIsUpdating(false),
    mPlayer(nullptr)
{
    Initialize();
}

//!初始化
bool Game::Initialize()
{

}

//!主循环
void Game::Loop()
{
    while(mIsRuning)
    {
        // Event();
        Update();
        Draw();
    }
}

void Game::Shutdown()
{
    unloadData();
}


void Game::createGameObject(GameObject* gameObject)
{
    // 如果当前正在更新，将该对象加入等待区
    if (mIsUpdating)
    {
        mPendingObjects.emplace_back(gameObject);
    }
    else
    {
        mGameObjects.emplace_back(gameObject);
    }
}

void Game::removeGameObject(GameObject* gameObject)
{
    // 先在等待区中寻找并移除物体
    auto iter = std::find(mPendingObjects.begin(), mPendingObjects.end(), gameObject);
    if (iter != mPendingObjects.end())
    {
        std::iter_swap(iter, mPendingObjects.end() - 1);
        mPendingObjects.pop_back();
    }

    // 在正式物体区中寻找并移除物体
    iter = std::find(mGameObjects.begin(), mGameObjects.end(), gameObject);
    if (iter != mGameObjects.end())
    {
        std::iter_swap(iter, mGameObjects.end() - 1);
        mGameObjects.pop_back();
    }
}

void Game::Update()
{
    //设置帧率
    Tick(60);

    // 更新开始
    mIsUpdating = true;
    // 遍历并执行所有物体的更新函数
    for (auto gameObject : mGameObjects)
    {
        gameObject->Update();
    }
    // 更新结束
    mIsUpdating = false;

    // 将所有等待区物体移动至正式的物体区
    for (auto pendingObject : mPendingObjects)
    {
        mGameObjects.emplace_back(pendingObject);
    }
    // 清空等待区
    mPendingObjects.clear();

    // 将所有状态为EDead的物体添加至死亡区
    std::vector<GameObject*> deadObjects;
    for (auto deadObject : mGameObjects)
    {
        if (deadObject->getState() == GameObject::State::EDead)
        {
            deadObjects.emplace_back(deadObject);
        }
    }
    // 释放掉所有死亡区的物体
    for (auto deadObject : deadObjects)
    {
        delete deadObject;
    }
}

//!绘制精灵
void Game::Draw()
{
    for (auto sprite:mSprites)
    {
        sprite->Draw();
    }
}

//!创建精灵并按绘画顺序插入
void Game::createSprite(spriteComponent* sprite)
{
    int order = sprite->getDrawOrder();
    // 按照绘制顺序插入
    auto iter = mSprites.begin();
    for (; iter != mSprites.end(); ++iter)
    {
        if (order < (*iter)->getDrawOrder())
        {
            break;
        }
    }
    mSprites.insert(iter, sprite);
}

//!移除精灵
void Game::removeSprite(spriteComponent* sprite)
{
    auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
    mSprites.erase(iter);
}

//!设置帧率
void Game::Tick(int fps)
{
    // 根据设置的帧率计算每帧至少的时间
    int fpsTime = 1000 / fps;
    //...
}

//!释放数据
void Game::unloadData()
{
    while (!mGameObjects.empty())
    {
        delete mGameObjects.back();
    }
}
