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

    void init_context_info(bool force = false);

// Event handlers
private:
    void OnPaint(wxPaintEvent& event);
    void OnSize(wxSizeEvent& event);

private:
    void do_repaint();

public:
    lsView* m_view;
};

// 绘图改造。在frame中添加一个canvas，canvas中存在view，view中存在painter和entity，painter中存在绘图接口指针
// 绘制的时候，view中的entity表示绘制数据，painter中的绘图接口指针指向具体的绘图后端
// view还记录缩放、视口等信息
// 在canvas的PaintEvent中，通过view绘制所有entity

// 实现一个绘图后端。view->painter->interface执行绘制，interface是图形绘制接口（基类指针），指向
// 具体的绘图后端，比方说cairo，每一次PaintEvent绘制，都创建cairo对象进行绘制，绘制结束后销毁对象，
// 类似win32 api的BeginPaint/EndPaint，在BeginPaint中创建对象，在EndPaint中销毁对象，可以将其
// 设计到一个类的构造和析构函数中，PaintEvent响应时创建这么个局部对象，在这个局部对象的生命周期内，通
// view去调用具体的绘图后端进行绘制就是有效的了。
