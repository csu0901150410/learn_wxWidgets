#pragma once

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <vector>
#include <memory>

#include "lsLine.h"
#include "lsPainter.h"

class lsView
{
public:
    lsView(wxWindow *parent) : m_painter(parent) {}
    ~lsView() {}

    void add(const lsLine& line);

    void redraw();

private:
    void draw(const lsLine *line);

public:
    std::vector<lsLine> m_entitys;
    lsPainter m_painter;
};
