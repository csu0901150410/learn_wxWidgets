﻿#pragma once

#include "lsCommon.h"
#include "lsPoint.h"

class lsBoundbox
{
public:
    lsBoundbox();
    lsBoundbox(const lsBoundbox &box);

    void init();

    bool is_valid() const;

    lsReal width() const;
    lsReal height() const;
    lsReal area() const;
    lsPoint center() const;

    bool is_in(const lsPoint &point);
    bool is_contain(const lsBoundbox &box);
    bool is_intersect(const lsBoundbox &box);

    void offset(lsReal dx, lsReal dy);
    void scale(lsReal sx, lsReal sy);

    void intersect(const lsBoundbox &box);
    void combine(const lsBoundbox &box);

    lsBoundbox intersect_with(const lsBoundbox &box) const;
    lsBoundbox combine_with(const lsBoundbox &box) const;

public:
    lsReal left;
    lsReal right;
    lsReal bottom;
    lsReal top;
};
