#include "lsView.h"

#include "lsContext.h"
#include "lsDocument.h"

#include "lsBoundbox.h"

lsView::lsView(wxWindow *parent)
{
    m_context = new lsContext(parent);

    m_document = new lsDocument();
    m_document->open("resources/models/bridge.dxf");

    // 计算一个box显示出来
    lsBoundbox box;
    std::vector<const lsEntity *> entitys = m_document->get_entitys();
    for (const auto& entity : entitys)
    {
        box.combine(entity->get_boundbox());
    }
    m_document->add(new lsSegment(lsPoint(box.left, box.bottom), lsPoint(box.left, box.top)));
    m_document->add(new lsSegment(lsPoint(box.left, box.top), lsPoint(box.right, box.top)));
    m_document->add(new lsSegment(lsPoint(box.right, box.top), lsPoint(box.right, box.bottom)));
    m_document->add(new lsSegment(lsPoint(box.right, box.bottom), lsPoint(box.left, box.bottom)));
}

lsView::~lsView()
{
    delete m_context;
    delete m_document;
}

void lsView::redraw()
{
    // 先beginpaint，不然context没申请就gg
    m_context->begin_paint();

    std::vector<const lsEntity *> entitys = m_document->get_entitys();
    for (const auto& entity : entitys)
    {
        draw(entity);
    }

    m_context->end_paint();
}

void lsView::resize_screen(int width, int height)
{
    m_context->resize_screen(width, height);
}

// 设置场景中的一个矩形区域为屏幕显示的区域，暂时不考虑缩放，只考虑原点偏移
void lsView::set_viewport(const lsBoundbox &box)
{
    // 保持宽高比缩放
    lsReal scalex = box.width() / m_context->get_screen_width();
    lsReal scaley = box.height() / m_context->get_screen_height();

    // scalex/scaley取最大值，scale取到最小值，scale乘以box.width/box.height时，两者都不会超出屏幕
    lsReal scale = 1 / std::max(scalex, scaley);

    set_center(box.center());
    set_scale(1.1);

    redraw();
}

void lsView::set_center(const lsPoint &pos)
{
    m_center = pos;
    m_context->set_lookat(pos);
    m_context->update_matrix();
}

void lsView::set_scale(lsReal scale)
{
    m_scale = scale;
    m_context->set_scale(scale);
    m_context->update_matrix();
}

void lsView::view_all()
{
    lsBoundbox box;
    std::vector<const lsEntity *> entitys = m_document->get_entitys();
    for (const auto& entity : entitys)
    {
        box.combine(entity->get_boundbox());
    }

    // 设置视口，通过屏幕观察场景中的box区域
    lsBoundbox viewbox = box;
    // viewbox.scale(1.1, 1.1);
    set_viewport(viewbox);
}

void lsView::zoom(lsReal scale, lsReal screenx, lsReal screeny)
{
    // 计算新的缩放值
    m_scale *= scale;
    if (m_scale < 0.1)
    {
        m_scale = 0.1;
    }
    else if (m_scale > 10)
    {
        m_scale = 10;
    }

    
    
    redraw();
}

void lsView::zoom_in(lsReal cx, lsReal cy)
{
    zoom(1.1, cx, cy);
}

void lsView::zoom_out(lsReal cx, lsReal cy)
{
    zoom(0.9, cx, cy);
}

void lsView::draw(const lsEntity *entity)
{
    // 去掉const限定，进行多态调用
    lsEntity *ptr = const_cast<lsEntity *>(entity);
    ptr->draw(m_context);
}
