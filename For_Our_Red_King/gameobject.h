#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QObject>
#include <QVector2D>
#include <vector>
#include "component.h"

class GameObject : public QObject
{
    Q_OBJECT
public:

    explicit GameObject(QObject *parent = nullptr,class Game* game = nullptr);
    virtual ~GameObject();

    enum class State{EActive,EDead};   //物体状态

    void Update();        //每帧更新

    void	addComponent(class Component* component);//添加组件
    void	removeComponent(class Component* component);//移除组件

    //! 获取特定类型的组件，并得到该组件类型的指针
    template<typename T> T* GetComponent()
    {
        for (auto com : mComponents)
        {
            T* component = dynamic_cast<T*>(com);
            if (component != nullptr)
            {
                return component;
            }
        }
        return nullptr;
    }

    State getState();          //获取当前状态
    Game* getGame();           //获取Game对象

private:
    class Game* mGame;   //从属Game类
    State mState;        //当前状态
    QVector2D mPosition;   //当前位置坐标
    QVector2D mScale;      //缩放
    float mRotation;     //旋转

protected:
    std::vector<class Component*> mComponents;    //组件数组


signals:
};

#endif // GAMEOBJECT_H
