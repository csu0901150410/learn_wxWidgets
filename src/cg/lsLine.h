#pragma once

#include "lsPoint.h"

class lsLine
{
public:
    lsLine();

    lsLine(const lsReal& sx, const lsReal& sy, const lsReal& ex, const lsReal& ey);

    lsLine(const lsPoint& s, const lsPoint& e);

    lsLine(const lsLine& other);

    ~lsLine() = default;

public:
    lsPoint s;
    lsPoint e;
};
