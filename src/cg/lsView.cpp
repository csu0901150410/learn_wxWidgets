#include "lsView.h"

#include "lsContext.h"
#include "lsDocument.h"

#include "lsBoundbox.h"

lsView::lsView(wxWindow *parent)
    : m_state(MOUSE_IDLE)
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

    set_viewport(box);

    parent->Connect(wxEVT_MIDDLE_DOWN, wxMouseEventHandler(lsView::OnMouseButton), nullptr, this);
    parent->Connect(wxEVT_MIDDLE_UP, wxMouseEventHandler(lsView::OnMouseButton), nullptr, this);
    parent->Connect(wxEVT_MOVE, wxMouseEventHandler(lsView::OnMouseButton), nullptr, this);
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

void lsView::set_offset(const lsPoint &pos)
{
    m_offset = pos;
    m_context->set_viewport_offset(pos);
}

lsPoint lsView::get_offset() const
{
    return m_offset;
}

// 设置场景中的一个矩形区域为屏幕显示的区域，暂时不考虑缩放，只考虑原点偏移
void lsView::set_viewport(const lsBoundbox &box)
{
    // 保持宽高比缩放
    lsReal scalex = box.width() / m_context->get_screen_width();
    lsReal scaley = box.height() / m_context->get_screen_height();

    // scalex/scaley取最大值，scale取到最小值，scale乘以box.width/box.height时，两者都不会超出屏幕
    lsReal scale = 1 / std::max(scalex, scaley);

    set_offset(lsPoint(box.left, box.bottom));
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
    set_viewport(viewbox);

    redraw();
}

void lsView::OnMouseButton(wxMouseEvent &event)
{
    // 状态机
    switch (m_state)
    {
    case MOUSE_IDLE:
        // 空闲状态进入拖动状态
        if (event.MiddleDown())
        {
            m_dragStartPos.x = event.GetX();
            m_dragStartPos.y = event.GetY();
            m_state = MOSUE_PANNING;
        }
        break;

    case MOSUE_PANNING:
        // 拖动状态
        if (event.MiddleUp())
        {
            lsPoint screenDelta = lsPoint(event.GetX() - m_dragStartPos.x, event.GetY() - m_dragStartPos.y);
            lsPoint worldDelta = screen2world(screenDelta, false);
            lsPoint offset = get_offset();
            offset.x -= worldDelta.x;
            offset.y -= worldDelta.y;
            set_offset(offset);
            redraw();

            m_state = MOUSE_IDLE;
        }
        break;
    }

    event.Skip();
}

void lsView::zoom(lsReal scale, lsReal screenx, lsReal screeny)
{
}

void lsView::zoom_in(lsReal cx, lsReal cy)
{
    zoom(1.1, cx, cy);
}

void lsView::zoom_out(lsReal cx, lsReal cy)
{
    zoom(0.9, cx, cy);
}

lsPoint lsView::screen2world(lsPoint pos, bool abs)
{
    lsPoint ret = pos;
    cairo_matrix_t mat = m_context->get_screen2world_matrix();
    if (abs)
    {
        // 对点进行变换，变换到另一个点
        cairo_matrix_transform_point(&mat, &ret.x, &ret.y);
    }
    else
    {
        // 对向量进行变换，仅应用缩放
        ret.x *= mat.xx;
        ret.y *= mat.yy;
    }
    return ret;
}

lsPoint lsView::world2screen(lsPoint pos, bool abs)
{
    lsPoint ret = pos;
    cairo_matrix_t mat = m_context->get_world2screen_matrix();
    if (abs)
    {
        // 对点进行变换，变换到另一个点
        cairo_matrix_transform_point(&mat, &ret.x, &ret.y);
    }
    else
    {
        // 对向量进行变换，仅应用缩放
        ret.x *= mat.xx;
        ret.y *= mat.yy;
    }
    return ret;
}

void lsView::draw(const lsEntity *entity)
{
    // 去掉const限定，进行多态调用
    lsEntity *ptr = const_cast<lsEntity *>(entity);
    ptr->draw(m_context);
}
