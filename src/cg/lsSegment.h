#pragma once

#include "lsPoint.h"

class lsSegment
{
public:
    lsSegment();

    lsSegment(const lsReal& sx, const lsReal& sy, const lsReal& ex, const lsReal& ey);

    lsSegment(const lsPoint& s, const lsPoint& e);

    ~lsSegment() = default;

public:
    lsPoint s;
    lsPoint e;
};
