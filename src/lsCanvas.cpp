#include "lsCanvas.h"

lsCanvas::lsCanvas(wxFrame *parent)
    : wxScrolledWindow(parent)
{
    SetBackgroundColour(*wxBLACK);
    SetScrollRate(0, 0); // 初始时禁用滚动条

    Bind(wxEVT_SIZE, &lsCanvas::OnSize, this);
}

void lsCanvas::LoadImage(const wxString& path)
{
    wxImage image;
    if (image.LoadFile(path))
    {
        m_bitmap = wxBitmap(image);
        CenterImage();
        Refresh(); // 重绘面板
    }
}

void lsCanvas::OnDraw(wxDC& dc)
{
    if (!m_bitmap.IsOk())
        return;

    // 获取面板和图片的尺寸
    int panelWidth, panelHeight;
    GetSize(&panelWidth, &panelHeight);
    int bmpWidth = m_bitmap.GetWidth();
    int bmpHeight = m_bitmap.GetHeight();

    // 计算居中位置
    int x = (panelWidth - bmpWidth) / 2;
    int y = (panelHeight - bmpHeight) / 2;

    // 如果图片大于面板，需要考虑滚动位置
    if (bmpWidth > panelWidth || bmpHeight > panelHeight)
    {
        int scrollX, scrollY;
        GetViewStart(&scrollX, &scrollY);
        int ppuX, ppuY;
        GetScrollPixelsPerUnit(&ppuX, &ppuY);
        x = (GetVirtualSize().x - bmpWidth) / 2 - scrollX * ppuX;
        y = (GetVirtualSize().y - bmpHeight) / 2 - scrollY * ppuY;
    }

    // 确保x和y不会为负值
    x = wxMax(0, x);
    y = wxMax(0, y);

    dc.DrawBitmap(m_bitmap, x, y, true);
}

void lsCanvas::OnSize(wxSizeEvent &event)
{
    if (m_bitmap.IsOk())
    {
        CenterImage();
    }
    event.Skip();
}

void lsCanvas::CenterImage()
{
    if (!m_bitmap.IsOk())
        return;

    // 获取面板和图片的尺寸
    int panelWidth, panelHeight;
    GetSize(&panelWidth, &panelHeight);
    int bmpWidth = m_bitmap.GetWidth();
    int bmpHeight = m_bitmap.GetHeight();

    // 设置虚拟大小
    // 当图片小于面板时，使用面板大小作为虚拟大小
    // 当图片大于面板时，使用图片大小作为虚拟大小
    int virtualWidth = wxMax(panelWidth, bmpWidth);
    int virtualHeight = wxMax(panelHeight, bmpHeight);
    
    SetVirtualSize(virtualWidth, virtualHeight);
    
    // 禁用滚动条（当图片小于面板时）
    if (bmpWidth <= panelWidth && bmpHeight <= panelHeight)
    {
        SetScrollRate(0, 0);
    }
    else
    {
        SetScrollRate(5, 5);
    }

    Refresh();  // 强制重绘
}
