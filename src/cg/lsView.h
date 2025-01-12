﻿#pragma once

#include <wx/wx.h>

#include "lsCommon.h"
#include "lsPoint.h"
#include "lsBoundbox.h"

class lsContext;
class lsDocument;
class lsEntity;

// 视图类，负责在窗口内绘图的逻辑，比如平移、缩放等
class lsView
{
public:
    lsView(wxWindow *parent);

    ~lsView();

    void redraw();

    void resize_screen(int width, int height);

    void set_viewport(const lsBoundbox &box);

    void set_center(const lsPoint &pos);
    void set_scale(lsReal scale);

    void view_all();

public:
    void zoom(lsReal scale, lsReal screenx, lsReal screeny);
    void zoom_in(lsReal cx, lsReal cy);
    void zoom_out(lsReal cx, lsReal cy);

private:
    void draw(const lsEntity *entity);

public:

    lsDocument *m_document;

    // 由view管理绘制上下文
    lsContext *m_context;

private:
    lsPoint m_center;
    lsReal m_scale;
};
