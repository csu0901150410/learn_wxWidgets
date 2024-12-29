#pragma once

#include <string>
#include <vector>

class lsEntity;

class lsDocument
{
public:
    explicit lsDocument();

    ~lsDocument();

    void test_init_entitys();

    unsigned long long get_id() const;

    // 从文件加载图元数据
    void open(const std::string &filepath);

    // 释放占用的文件
    void release();

    // 添加图元
    void add(const lsEntity* entity);

    // 获取图元列表
    void get_entitys(std::vector<const lsEntity*>& entitys);

private:
    unsigned long long m_id;

    std::vector<const lsEntity*> m_entitys;
};
