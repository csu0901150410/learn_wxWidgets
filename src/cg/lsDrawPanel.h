#pragma once

#include <wx/window.h>
#include <wx/scrolwin.h>

#include "lsView.h"

// 图形绘图面板
class lsDrawPanel : public wxScrolledCanvas
{
public:
    lsDrawPanel(wxWindow* parent);

    ~lsDrawPanel();

// Event handlers
private:
    void OnPaint(wxPaintEvent& event);

private:
    void do_repaint();

public:
    lsView* m_view;
};

// 绘图改造。在frame中添加一个canvas，canvas中存在view，view中存在painter和entity，painter中存在绘图接口指针
// 绘制的时候，view中的entity表示绘制数据，painter中的绘图接口指针指向具体的绘图后端
// view还记录缩放、视口等信息
// 在canvas的PaintEvent中，通过view绘制所有entity
