#pragma once

#include "lsPoint.h"

#include "lsContext.h"
#include "lsEntity.h"

class lsArc : public lsEntity
{
public:
    lsArc();

    lsArc(const lsPoint& s, const lsPoint& e, const lsPoint& c, bool ccw);

    ~lsArc() = default;

// 实现接口
public:
    virtual void draw(lsContext *context) override;

public:
    lsPoint s;
    lsPoint e;
    lsPoint c;
    bool ccw;
};
