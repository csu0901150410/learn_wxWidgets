#include "lsArc.h"

lsArc::lsArc()
    : lsEntity()
    , c(0, 0), ccw(true), e(0, 0), s(0, 0)
{
}

lsArc::lsArc(const lsPoint &s, const lsPoint &e, const lsPoint &c, bool ccw)
    : lsEntity()
    , c(c), ccw(ccw), e(e), s(s)
{
}

void lsArc::draw(lsContext *context)
{
}
