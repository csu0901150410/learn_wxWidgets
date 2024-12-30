#pragma once

#include "lsPoint.h"

#include "lsContext.h"
#include "lsEntity.h"

class lsBoundbox;

class lsLine : public lsEntity
{
public:
    lsLine();

    lsLine(const lsReal& sx, const lsReal& sy, const lsReal& ex, const lsReal& ey);

    lsLine(const lsPoint& s, const lsPoint& e);

    lsLine(const lsLine& other);

    ~lsLine() = default;

// 实现接口
public:
    virtual void draw(lsContext *context) override;

    virtual lsBoundbox get_boundbox() const override;

public:
    lsPoint s;
    lsPoint e;
};
