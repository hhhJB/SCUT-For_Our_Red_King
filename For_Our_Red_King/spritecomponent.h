#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include "component.h"

class spriteComponent : public Component
{
public:
    explicit spriteComponent(class GameObject* gameObject=nullptr,int drawOrder=100);//100order为最底层
    ~spriteComponent();

    //! 绘制函数
    virtual void Draw();
    //! 设置贴图
    virtual void SetTexture(QString imageLocation);

    //! 贴图宽度的get
    int		getTexWidth() const;
    //! 贴图高度的get
    int		getTexHeight() const;
    //! 绘制顺序的get和set
    int		getDrawOrder() const;
    void	setDrawOrder(int order);
protected:
    int		mDrawOrder;		//!<	绘制顺序
    int		mTexWidth;		//!<	贴图宽
    int		mTexHeight;		//!<	贴图高
signals:
};

#endif // SPRITECOMPONENT_H
