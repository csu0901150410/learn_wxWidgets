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

void lsDrawPanel::generate_random_entitys()
{
    // 随机生成范围内的浮点数
    auto random_float = [](float min, float max) {
        return min + (max - min) * (static_cast<float>(rand()) / RAND_MAX);
    };

    // 生成随机线段
    auto random_segment = [&random_float](float xmin, float xmax, float ymin, float ymax) {
        lsSegment seg;
        seg.s.x = random_float(xmin, xmax);
        seg.s.y = random_float(ymin, ymax);
        seg.e.x = random_float(xmin, xmax);
        seg.e.y = random_float(ymin, ymax);
        return seg;
    };

    wxSize clientSize = GetClientSize();
    float xmin = 0;
    float xmax = clientSize.x;
    float ymin = 0;
    float ymax = clientSize.y;

    for (int i = 0; i < 10; i++)
    {
        lsSegment seg = random_segment(xmin, xmax, ymin, ymax);
        m_view->add(new lsSegment(seg));
    }

    lsSegment left(50, 50, 50, 200);
    lsSegment top(50, 200, 500, 200);
    lsSegment right(500, 200, 500, 50);
    lsSegment bottom(500, 50, 50, 50);
    m_view->add(new lsSegment(left));
    m_view->add(new lsSegment(top));
    m_view->add(new lsSegment(right));
    m_view->add(new lsSegment(bottom));
}

// ugly
static int g_repaint_count = 0;

void lsDrawPanel::OnPaint(wxPaintEvent &event)
{
    // cairo backend
    // https://www.cairographics.org/
    // https://github.com/preshing/cairo-windows

    if (0 == g_repaint_count)
    {
        g_repaint_count++;
        // 第一次OnPaint，窗口尺寸稳定了，生成随机线段
        generate_random_entitys();
    }

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
