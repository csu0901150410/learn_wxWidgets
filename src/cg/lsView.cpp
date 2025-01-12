#include "lsView.h"

#include "lsContext.h"
#include "lsDocument.h"

#include "lsBoundbox.h"

#include "lsScreenRenderTarget.h"

lsView::lsView(wxWindow *parent)
{
    m_context = new lsContext(new lsScreenRenderTarget(parent));

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

    // 设置视口，通过屏幕观察场景中的box区域
    lsBoundbox viewbox = box;
    viewbox.scale(1.1, 1.1);
    set_viewport(viewbox);

    m_factor = 1.0;
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
    // 假设屏幕原点和矩形左下角重合
    lsPoint origin(box.left, box.bottom);
    m_context->set_origin(origin);
    m_context->update_matrix();
}

void lsView::zoom(lsReal factor, lsReal screenx, lsReal screeny)
{
    // 计算新的缩放值
    m_factor *= factor;
    if (m_factor < 0.1)
    {
        m_factor = 0.1;
    }
    else if (m_factor > 10)
    {
        m_factor = 10;
    }

    m_context->set_scale(lsPoint(screenx, screeny), m_factor);
    
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
