#include "lsView.h"

#include "lsContext.h"

lsView::lsView(wxWindow *parent)
{
    m_context = new lsContext(parent);
}

lsView::~lsView()
{
    for (auto ent : m_entitys)
        delete ent;
    delete m_context;
}

void lsView::add(const lsEntity *entity)
{
    m_entitys.push_back(entity);
}

void lsView::redraw()
{
    // 先beginpaint，不然context没申请就gg
    m_context->begin_paint();

    for (const auto& entity : m_entitys)
    {
        draw(entity);
    }

    m_context->end_paint();
}

void lsView::resize_screen(int width, int height)
{
    m_context->resize_screen(width, height);
}

void lsView::draw(const lsEntity *entity)
{
    // 去掉const限定，进行多态调用
    lsEntity *ptr = const_cast<lsEntity *>(entity);
    ptr->draw(m_context);
}
