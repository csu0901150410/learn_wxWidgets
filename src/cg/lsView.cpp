#include "lsView.h"

void lsView::add(const lsEntity *entity)
{
    m_entitys.push_back(entity);
}

void lsView::redraw()
{
    for (const auto& entity : m_entitys)
    {
        draw(entity);
    }
}

void lsView::draw(const lsEntity *entity)
{
    m_painter->draw(entity);
}
