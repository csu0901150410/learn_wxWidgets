#pragma once

#include "lsPoint.h"

#include "lsContext.h"
#include "lsEntity.h"

class lsSegment : public lsEntity
{
public:
    lsSegment();

    lsSegment(const lsReal& sx, const lsReal& sy, const lsReal& ex, const lsReal& ey);

    lsSegment(const lsPoint& s, const lsPoint& e);

    ~lsSegment() = default;

// 实现接口
public:
    virtual void draw(lsContext *context) override;

public:
    lsPoint s;
    lsPoint e;
};
