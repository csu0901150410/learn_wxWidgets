#include "lsSegment.h"

lsSegment::lsSegment()
    : e(0, 0)
    , s(0, 0)
{
}

lsSegment::lsSegment(const lsReal &sx, const lsReal &sy, const lsReal &ex, const lsReal &ey)
    : e(ex, ey)
    , s(sx, sy)
{
}

lsSegment::lsSegment(const lsPoint &s, const lsPoint &e)
    : e(e)
    , s(s)
{
}
