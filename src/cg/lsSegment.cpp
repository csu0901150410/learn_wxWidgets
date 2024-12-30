#include "lsSegment.h"

#include "lsBoundbox.h"


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

lsBoundbox lsSegment::get_boundbox() const
{
    lsBoundbox box;
    box.left = std::min(s.x, e.x);
    box.right = std::max(s.x, e.x);
    box.bottom = std::min(s.y, e.y);
    box.top = std::max(s.y, e.y);
    return box;
}
