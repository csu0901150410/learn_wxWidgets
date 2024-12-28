#pragma once

class lsContext;

class lsEntity
{
public:
    explicit lsEntity();// 强制显式使用构造函数

    virtual ~lsEntity() = default;

    void init();// 初始化流程，仅由基类指定

    virtual void init_id();// 初始化id，子类可选覆盖指定自己的初始化策略

    unsigned long long get_id() const
    {
        return m_id;
    }

    // 接口，纯虚函数，子类必须实现
    virtual void draw(lsContext *context) = 0;

protected:
    unsigned long long m_id;// 声明为protected，仅子类可访问
};
