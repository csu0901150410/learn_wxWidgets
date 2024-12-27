#include "lsLine.h"

lsLine::lsLine()
    : s(lsPoint())
    , e(lsPoint())
{
}

lsLine::lsLine(const lsReal &sx, const lsReal &sy, const lsReal &ex, const lsReal &ey)
    : s(lsPoint(sx, sy))
    , e(lsPoint(ex, ey))
{
}

lsLine::lsLine(const lsPoint &s, const lsPoint &e)
    : s(s)
    , e(e)
{
}

lsLine::lsLine(const lsLine &other)
    : s(other.s)
    , e(other.e)
{
}
