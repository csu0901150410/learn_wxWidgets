#include "lsView.h"

void lsView::add(const lsLine &line)
{
    m_entitys.push_back(line);
}

void lsView::redraw()
{
    // 先beginpaint，不然context没申请就gg
    m_painter->begin_paint();

    for (const auto& entity : m_entitys)
    {
        draw(&entity);
    }

    m_painter->end_paint();
}

void lsView::init_context_info(bool force)
{
    m_painter->init_context_info(force);
}

void lsView::draw(const lsLine *line)
{
    m_painter->draw(line);
}
