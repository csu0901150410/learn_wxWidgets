#pragma once

#include <wx/window.h>
#include <wx/scrolwin.h>

#include <mutex>

#include "lsView.h"

// 图形绘图面板。负责窗口的管理，如显示、尺寸调整、鼠标事件
class lsDrawPanel : public wxScrolledCanvas
{
public:
    lsDrawPanel(wxWindow* parent);

    ~lsDrawPanel();

    void parse_svg();

// Event handlers
private:
    void OnPaint(wxPaintEvent& event);
    void OnSize(wxSizeEvent& event);
    void OnIdle(wxIdleEvent& event);

private:
    void do_repaint();

public:
    lsView* m_view;
};
