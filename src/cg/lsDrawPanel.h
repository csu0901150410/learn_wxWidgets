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

    void recreate_buffer(int width, int height);

// Event handlers
private:
    void OnPaint(wxPaintEvent& event);
    void OnSize(wxSizeEvent& event);

private:
    void do_repaint();

public:
    lsView* m_view;
};
