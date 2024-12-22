#pragma once

#include <wx/wx.h>

#include "lsLine.h"

class lsPainter
{
public:
    lsPainter(wxWindow *parent) : m_parent(parent)
    {
        m_dc = new wxClientDC(parent);
        m_dc->SetPen(wxPen(wxColour(255, 255, 255), 5));
    }
    ~lsPainter()
    {
        delete m_dc;
    }

    // 统一的绘制接口，lsLine可以理解为后续的基类lsEntity
    void draw(const lsLine* line);

// 这些具体的绘制方法可以抽象成绘制接口
private:
    // Drawing methods
    void draw_line(float sx, float sy, float ex, float ey);

private:
    wxWindow *m_parent;
    wxClientDC *m_dc;
};
