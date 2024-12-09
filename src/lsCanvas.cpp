#include "lsCanvas.h"

lsCanvas::lsCanvas(wxFrame *parent)
    : wxScrolledWindow(parent)
{
    SetBackgroundColour(*wxBLACK);
    SetScrollRate(5, 5);
}

void lsCanvas::LoadImage(const wxString& path)
{
    wxImage image;
    if (image.LoadFile(path))
    {
        m_bitmap = wxBitmap(image);
        SetVirtualSize(m_bitmap.GetSize()); // 设置虚拟大小以支持滚动
        Refresh(); // 重绘面板
    }
}

void lsCanvas::OnDraw(wxDC& dc)
{
    if (m_bitmap.IsOk())
    {
        // 获取当前滚动位置
        int x, y;
        GetViewStart(&x, &y);
        x *= 5; // 滚动单位转换为像素
        y *= 5;

        // 绘制位图
        dc.DrawBitmap(m_bitmap, x, y, true);
    }
}
