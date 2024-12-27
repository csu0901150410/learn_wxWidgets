﻿#pragma once

#include "lsCommon.h"

class lsPoint
{
public:
    lsPoint();
    lsPoint(lsReal vx, lsReal vy);
    lsPoint(const lsPoint& other);
    ~lsPoint() = default;

public:
    lsReal x;
    lsReal y;
};
