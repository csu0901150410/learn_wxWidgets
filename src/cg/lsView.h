#pragma once

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <vector>
#include <memory>

#include <wx/wx.h>

#include "lsEntity.h"

class lsContext;

// 视图类，负责在窗口内绘图的逻辑，比如平移、缩放等
class lsView
{
public:
    lsView(wxWindow *parent);

    ~lsView();

    void add(const lsEntity *entity);

    void redraw();

    void resize_screen(int width, int height);

private:
    void draw(const lsEntity *entity);

public:

    // 暂时由view管理图元数据
    std::vector<const lsEntity *> m_entitys;// 相当于是由view去管理entity的生命周期

    // 由view管理绘制上下文
    lsContext *m_context;
};
