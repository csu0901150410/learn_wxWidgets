#pragma once

#include <wx/window.h>
#include <wx/scrolwin.h>

// 图形绘图面板
class lsDrawPanel : public wxScrolledCanvas
{
public:
    lsDrawPanel(wxWindow* parent);

    ~lsDrawPanel();

    void OnPaint(wxPaintEvent& event);

    void Redraw();

private:
    void render(wxDC& dc);
};
