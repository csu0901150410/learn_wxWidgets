#pragma once

// 设计一个类用来输出日志，这个类要是单例的
// 后续要扩展到输出日志到文件

#define LS_DEBUG lsDebug::instance()

class lsDebug
{
public:
    ~lsDebug();
    lsDebug(const lsDebug &) = delete;            // 删除复制构造函数 不允许 lsDebug debug2(debug1);
    lsDebug &operator=(const lsDebug &) = delete; // 删除赋值操作符 不允许 lsDebug debug2 = debug1;
    lsDebug(lsDebug &&) = delete;                 // 删除移动构造函数 不允许 lsDebug debug2(std::move(debug1));
    lsDebug &operator=(lsDebug &&) = delete;      // 删除移动赋值操作符 不允许 lsDebug debug2 = std::move(debug1);

    static lsDebug *instance(); // 静态函数，获取单例指针

public:
    void print(const char *format...); // 类似printf格式化输出接口

private:
    lsDebug(); // 私有化构造函数 不允许 lsDebug debug1;

    class lsGaobo // 它的唯一工作就是在析构函数中删除单例实例
    {
    public:
        ~lsGaobo()
        {
            if (lsDebug::instance())
                delete lsDebug::instance();
        }
    };
    static lsGaobo garbo; // 定义一个静态成员，在程序结束时，系统会调用它的析构函数
};
