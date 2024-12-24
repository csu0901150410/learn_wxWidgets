#pragma once

#include <wx/window.h>
#include <wx/scrolwin.h>

#include <mutex>

#include "lsView.h"
#include "lsContext.h"

// 图形绘图面板
class lsDrawPanel : public wxScrolledCanvas
{
public:
    lsDrawPanel(wxWindow* parent);

    ~lsDrawPanel();

    void parse_svg();

    void generate_random_entitys();

// Event handlers
private:
    void OnPaint(wxPaintEvent& event);
    void OnSize(wxSizeEvent& event);
    void OnIdle(wxIdleEvent& event);

private:
    void do_repaint();

public:
    lsView* m_view;

    lsContext *m_context;
};
