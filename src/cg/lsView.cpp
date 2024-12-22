#include "lsView.h"

void lsView::add(const lsLine &line)
{
    m_entitys.push_back(line);
}

void lsView::redraw()
{
    for (const auto& entity : m_entitys)
    {
        draw(&entity);
    }
}

void lsView::draw(const lsLine *line)
{
    m_painter.draw(line);
}
