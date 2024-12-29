﻿#include "lsDrawPanel.h"

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
    // cairo backend
    // https://www.cairographics.org/
    // https://github.com/preshing/cairo-windows
    do_repaint();
}

void lsDrawPanel::OnSize(wxSizeEvent &event)
{
    // 窗口尺寸变化的时候，重建绘图后端的缓冲区
    // 初始化的时候要有好几个OnSize才变为最终的尺寸
    // 这里相当于依赖了先到来的消息是OnSize并重建（创建）了缓冲区
    wxSize clientSize = GetClientSize();
    m_view->resize_screen(clientSize.x, clientSize.y);
}

void lsDrawPanel::OnIdle(wxIdleEvent &event)
{
    event.Skip();
}

void lsDrawPanel::do_repaint()
{
    m_view->redraw();
}
