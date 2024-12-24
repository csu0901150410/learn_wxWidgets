#include "lsDrawPanel.h"

#include <wx/wx.h>
#include <cairo.h>
#include <string>

#include "tinyxml2.h"

lsDrawPanel::lsDrawPanel(wxWindow *parent)
    : wxScrolledCanvas(parent)
{
    m_context = new lsContext(this);

    m_view = new lsView(this);
    // m_view->add(lsLine(100, 200, 200, 300));
    m_view->m_painter->set_context(m_context);

    Bind(wxEVT_PAINT, &lsDrawPanel::OnPaint, this);
    Bind(wxEVT_SIZE, &lsDrawPanel::OnSize, this);
    Bind(wxEVT_IDLE, &lsDrawPanel::OnIdle, this);
}

lsDrawPanel::~lsDrawPanel()
{
    delete m_view;
    delete m_context;
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
    auto random_line = [&random_float](float xmin, float xmax, float ymin, float ymax) {
        lsLine line;
        line.sx = random_float(xmin, xmax);
        line.sy = random_float(ymin, ymax);
        line.ex = random_float(xmin, xmax);
        line.ey = random_float(ymin, ymax);
        return line;
    };

    wxSize clientSize = GetClientSize();
    float xmin = 0;
    float xmax = clientSize.x;
    float ymin = 0;
    float ymax = clientSize.y;

    for (int i = 0; i < 100; i++)
    {
        m_view->add(random_line(xmin, xmax, ymin, ymax));
    }
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
    m_context->resize_screen(clientSize.x, clientSize.y);
}

void lsDrawPanel::OnIdle(wxIdleEvent &event)
{
    event.Skip();
}

void lsDrawPanel::do_repaint()
{
    // 先beginpaint，不然context没申请就gg
    m_context->begin_paint();

    m_view->redraw();

    m_context->end_paint();
}
