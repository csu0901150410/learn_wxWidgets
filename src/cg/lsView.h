#pragma once

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <vector>
#include <memory>

#include "lsPainter.h"
#include "lsEntity.h"

class lsView
{
public:
    lsView(wxWindow *parent)
    {
        m_painter = new lsPainter(parent);
    }

    ~lsView()
    {
        for (auto ent : m_entitys)
            delete ent;
        delete m_painter;
    }

    void add(const lsEntity *entity);

    void redraw();

private:
    void draw(const lsEntity *entity);

public:
    std::vector<const lsEntity *> m_entitys;// 相当于是由view去管理entity的生命周期
    lsPainter *m_painter;
};
