#include "lsDrawPanel.h"

#include <wx/wx.h>
#include <cairo.h>

lsDrawPanel::lsDrawPanel(wxWindow *parent)
    : wxScrolledCanvas(parent)
{
    SetBackgroundColour(*wxBLACK);

    m_view = new lsView(this);
    m_view->add(lsLine(0, 0, 200, 300));

    Bind(wxEVT_PAINT, &lsDrawPanel::OnPaint, this);
    Bind(wxEVT_SIZE, &lsDrawPanel::OnSize, this);
}

lsDrawPanel::~lsDrawPanel()
{
    delete m_view;
}

void lsDrawPanel::init_context_info(bool force)
{
    m_view->init_context_info(force);
}

void lsDrawPanel::OnPaint(wxPaintEvent &event)
{
    // cairo backend
    // https://www.cairographics.org/
    // https://github.com/preshing/cairo-windows

    // 获取绘图尺寸
    wxPaintDC dc(this);
    wxSize screen_size = dc.GetSize();

    // bug - 窗口发生变化的时候，painter里边的buffer信息就对不上了，操作图像数据会出错
    // 还是得独立一个绘图后端的类出来
    // 暂时尝试在OnSize事件中通知painter修改绘图buffer，还是不行，可能OnSize的时候，绘图还未完成，此时不能修改buffer
    init_context_info();

    // 走view绘制的一套
    do_repaint();
}

void lsDrawPanel::OnSize(wxSizeEvent &event)
{
    // init_context_info(true);
}

void lsDrawPanel::do_repaint()
{
    m_view->redraw();
}
