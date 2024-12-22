#include "lsDrawPanel.h"

#include <wx/wx.h>

lsDrawPanel::lsDrawPanel(wxWindow *parent)
    : wxScrolledCanvas(parent)
{
    SetBackgroundColour(*wxBLACK);

    m_view = new lsView(this);
    m_view->add(lsLine(0, 0, 200, 300));

    Bind(wxEVT_PAINT, &lsDrawPanel::OnPaint, this);
}

lsDrawPanel::~lsDrawPanel()
{
    delete m_view;
}

void lsDrawPanel::OnPaint(wxPaintEvent &event)
{
    wxPaintDC dc(this);

    do_repaint();
}

void lsDrawPanel::do_repaint()
{
    m_view->redraw();
}
