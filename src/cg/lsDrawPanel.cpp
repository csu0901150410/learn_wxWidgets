#include "lsDrawPanel.h"

#include <wx/wx.h>
#include <cairo.h>

lsDrawPanel::lsDrawPanel(wxWindow *parent)
    : wxScrolledCanvas(parent)
{
    SetBackgroundColour(*wxBLACK);

    m_view = new lsView(this);
    m_view->add(lsLine(100, 200, 200, 300));

    // 初始化绘图后端，即context，上下文
    m_view->init_context_info();

    Bind(wxEVT_PAINT, &lsDrawPanel::OnPaint, this);
    Bind(wxEVT_SIZE, &lsDrawPanel::OnSize, this);
}

lsDrawPanel::~lsDrawPanel()
{
    delete m_view;
}

void lsDrawPanel::recreate_buffer(int width, int height)
{
    m_view->recreate_buffer(width, height);
}

void lsDrawPanel::OnPaint(wxPaintEvent &event)
{
    // cairo backend
    // https://www.cairographics.org/
    // https://github.com/preshing/cairo-windows
    do_repaint();
}

void lsDrawPanel::OnSize(wxSizeEvent &event)
{
    // 窗口尺寸变化的时候，重建绘图后端的缓冲区
    // 初始化的时候要有好几个OnSize才变为最终的尺寸
    wxSize clientSize = GetClientSize();
    recreate_buffer(clientSize.x, clientSize.y);
}

void lsDrawPanel::do_repaint()
{
    m_view->redraw();
}
