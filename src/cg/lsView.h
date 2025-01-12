#pragma once

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

public:
    void zoom(lsReal factor, lsReal screenx, lsReal screeny);
    void zoom_in(lsReal cx, lsReal cy);
    void zoom_out(lsReal cx, lsReal cy);

private:
    void draw(const lsEntity *entity);

public:

    lsDocument *m_document;

    // 由view管理绘制上下文
    lsContext *m_context;

private:
    lsReal m_offsetx;// 屏幕坐标系原点相对于世界坐标系的偏移量，用世界坐标距离描述
    lsReal m_offsety;// 屏幕坐标系原点相对于世界坐标系的偏移量，用世界坐标距离描述
    lsReal m_factor;// 缩放比例 屏幕坐标/世界坐标
};
