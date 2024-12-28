#include "lsLine.h"

lsLine::lsLine()
    : lsEntity()
    , s(lsPoint())
    , e(lsPoint())
{
}

lsLine::lsLine(const lsReal &sx, const lsReal &sy, const lsReal &ex, const lsReal &ey)
    : lsEntity()
    , s(lsPoint(sx, sy))
    , e(lsPoint(ex, ey))
{
}

lsLine::lsLine(const lsPoint &s, const lsPoint &e)
    : lsEntity()
    , s(s)
    , e(e)
{
}

lsLine::lsLine(const lsLine &other)
    : lsEntity()
    , s(other.s)
    , e(other.e)
{
}

void lsLine::draw(lsContext *context)
{
    context->draw_line(s.x, s.y, e.x, e.y);
}
