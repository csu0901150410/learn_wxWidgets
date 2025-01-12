#include "lsDrawPanel.h"

#include <wx/wx.h>
#include <cairo.h>
#include <string>

#include "tinyxml2.h"

#include "lsPoint.h"
#include "lsSegment.h"

lsDrawPanel::lsDrawPanel(wxWindow *parent)
    : wxScrolledCanvas(parent)
{
    m_view = new lsView(this);

    Bind(wxEVT_PAINT, &lsDrawPanel::OnPaint, this);
    Bind(wxEVT_SIZE, &lsDrawPanel::OnSize, this);
    Bind(wxEVT_IDLE, &lsDrawPanel::OnIdle, this);

    Bind(wxEVT_MOUSEWHEEL, &lsDrawPanel::OnMouseWheel, this);
}

lsDrawPanel::~lsDrawPanel()
{
    delete m_view;
}

void lsDrawPanel::parse_svg()
{
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile("resources/images/test_render.svg") != tinyxml2::XML_SUCCESS)
    {
        return;
    }

    tinyxml2::XMLElement *root = doc.RootElement();
    for (tinyxml2::XMLElement *element = root->FirstChildElement();
        nullptr != element;
        element = element->NextSiblingElement())
    {
        const char *tag = element->Name();
        std::string strtag(tag);
        if ("rect" == strtag)
        {

        }
    }
}

void lsDrawPanel::OnPaint(wxPaintEvent &event)
{
    wxSize clientSize = GetClientSize();
    int a = 100;

    // cairo backend
    // https://www.cairographics.org/
    // https://github.com/preshing/cairo-windows
    do_repaint();
}

void lsDrawPanel::OnSize(wxSizeEvent &event)
{
    // 窗口尺寸变化的时候，重建绘图后端的缓冲区
    wxSize clientSize = GetClientSize();
    m_view->resize_screen(clientSize.x, clientSize.y);
}

void lsDrawPanel::OnIdle(wxIdleEvent &event)
{
    wxSize clientSize = GetClientSize();

    event.Skip();
}

void lsDrawPanel::OnMouseWheel(wxMouseEvent &event)
{
    int delta = event.GetWheelRotation();
    int x = event.GetX();
    int y = event.GetY();

    if (delta > 0)
    {
        m_view->zoom_in(x, y);
    }
    else
    {
        m_view->zoom_out(x, y);
    }
}

void lsDrawPanel::do_repaint()
{
    m_view->redraw();
}
