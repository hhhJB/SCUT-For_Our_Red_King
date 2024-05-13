#ifndef COMPONENT_H
#define COMPONENT_H

#include <QObject>

class Component : public QObject
{
    Q_OBJECT
public:
    //! 构造函数
    explicit Component(QObject *parent = nullptr,class GameObject* gameObject=nullptr);
    //! 析构函数
    virtual ~Component();

    //! 每帧更新
    virtual void Update();

    //!获取mUpdateOrder
    int getUpdateOrder();

protected:
    class GameObject* mGameObject;        //!<    自身附着的游戏物体
    int mUpdateOrder;        //!<    更新顺序

signals:
};

#endif // COMPONENT_H
