#pragma once

#include <wx/wx.h>

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

private:
    void draw(const lsEntity *entity);

public:

    lsDocument *m_document;

    // 由view管理绘制上下文
    lsContext *m_context;
};
