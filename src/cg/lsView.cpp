#include "lsView.h"

void lsView::add(const lsSegment &seg)
{
    m_entitys.push_back(seg);
}

void lsView::redraw()
{
    for (const auto& entity : m_entitys)
    {
        draw(entity);
    }
}

void lsView::draw(const lsSegment& seg)
{
    m_painter->draw(seg);
}
