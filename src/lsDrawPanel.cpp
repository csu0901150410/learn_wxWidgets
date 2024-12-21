#include "lsDrawPanel.h"

#include "wx/wx.h"

lsDrawPanel::lsDrawPanel(wxWindow *parent)
    : wxScrolledCanvas(parent)
{
    SetBackgroundColour(*wxBLACK);

    Bind(wxEVT_PAINT, &lsDrawPanel::OnPaint, this);
}

lsDrawPanel::~lsDrawPanel()
{
}

void lsDrawPanel::OnPaint(wxPaintEvent &event)
{
    // wxPaintDC 只能用在wxPaintEvent事件中
    wxPaintDC dc(this);
    render(dc);
}

void lsDrawPanel::Redraw()
{
    wxClientDC dc(this);
    render(dc);

    // 测试在wxPaintEvent外绘制
    dc.SetPen(wxPen(wxColour(0, 0, 255), 5));
    dc.DrawCircle(wxPoint(600, 400), 50);
}

void lsDrawPanel::render(wxDC &dc)
{
    dc.SetBrush(*wxGREEN_BRUSH);
    dc.SetPen(wxPen(wxColour(255, 0, 0), 5));

    dc.DrawCircle(wxPoint(300, 400), 50);
}
