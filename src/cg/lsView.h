#pragma once

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <vector>
#include <memory>

#include "lsLine.h"
#include "lsSegment.h"

#include "lsPainter.h"

class lsView
{
public:
    lsView(wxWindow *parent)
    {
        m_painter = new lsPainter(parent);
    }

    ~lsView()
    {
        delete m_painter;
    }

    void add(const lsSegment& seg);

    void redraw();

private:
    void draw(const lsSegment& seg);

public:
    std::vector<lsSegment> m_entitys;
    lsPainter *m_painter;
};
