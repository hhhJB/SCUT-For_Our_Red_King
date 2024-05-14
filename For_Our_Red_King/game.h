#ifndef GAME_H
#define GAME_H

#include <QObject>
#include "gameobject.h"

class GameObject;
class spriteComponent;
class Player;

class Game: public QObject
{
    Q_OBJECT
public:
    explicit Game(QObject *parent = nullptr);
    virtual ~Game();

    bool Initialize();//!初始化
    void Shutdown();  //!游戏结束
    void Loop();      //!主循环


    void createGameObject(GameObject*);  //!创建gameObject
    void removeGameObject(GameObject*);  //!移除gameObject
    void createSprite(spriteComponent* sprite);//!创建并按绘制顺序存储精灵
    void removeSprite(spriteComponent* sprite);//!移除精灵


private:
    std::vector<GameObject*> mGameObjects;        //!<    游戏物体容器
    std::vector<GameObject*> mPendingObjects;        //!<    等待状态的游戏物体容器
    std::vector<spriteComponent*>mSprites;          //!<   精灵容器

    bool    mIsUpdating;                    //!<    是否在更新状态
    bool    mIsRuning;                      //!<    运行状态
    Player* mPlayer;                  //!<    玩家角色

    void Update();                       //!更新
    void Draw();                         //!绘制
    void Tick(int fps);                         //!设置帧率
    void loadData();                     //!加载数据
    void unloadData();                   //!释放数据



signals:
};

#endif // GAME_H
