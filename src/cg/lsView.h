#pragma once

#include <wx/wx.h>

#include "lsCommon.h"
#include "lsPoint.h"
#include "lsBoundbox.h"

class lsContext;
class lsDocument;
class lsEntity;

// 视图类，负责在窗口内绘图的逻辑，比如平移、缩放等
class lsView : public wxEvtHandler
{
public:
    lsView(wxWindow *parent);

    ~lsView();

    void redraw();

    void resize_screen(int width, int height);

    void set_offset(const lsPoint &pos);
    lsPoint get_offset() const;

    void set_viewport(const lsBoundbox &box);

    void view_all();

// events
private:
    enum MOUSE_STATE
    {
        MOUSE_IDLE = 0,
        MOSUE_PANNING,// 按下鼠标中键拖动
        MOUSE_MOVING,
    };
    MOUSE_STATE m_state;
    lsPoint m_dragStartPos;

    void OnMouseButton(wxMouseEvent& event);

public:
    void zoom(lsReal scale, lsReal screenx, lsReal screeny);
    void zoom_in(lsReal cx, lsReal cy);
    void zoom_out(lsReal cx, lsReal cy);

    lsPoint screen2world(lsPoint pos, bool abs = true);
    lsPoint world2screen(lsPoint pos, bool abs = true);

private:
    void draw(const lsEntity *entity);

public:

    lsDocument *m_document;

    // 由view管理绘制上下文
    lsContext *m_context;

public:
    lsPoint m_offset;
};
