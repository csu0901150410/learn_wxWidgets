#include "lsSegment.h"

lsSegment::lsSegment()
    : lsEntity()
    , e(0, 0)
    , s(0, 0)
{
}

lsSegment::lsSegment(const lsReal &sx, const lsReal &sy, const lsReal &ex, const lsReal &ey)
    : lsEntity()
    , e(ex, ey)
    , s(sx, sy)
{
}

lsSegment::lsSegment(const lsPoint &s, const lsPoint &e)
    : lsEntity()
    , e(e)
    , s(s)
{
}

void lsSegment::draw(lsContext *context)
{
    context->draw_segment(s.x, s.y, e.x, e.y);
}
