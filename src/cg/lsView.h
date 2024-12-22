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
    lsView(wxWindow *parent)
    {
        m_painter = new lsPainter(parent);
    }

    ~lsView()
    {
        delete m_painter;
    }

    void add(const lsLine& line);

    void redraw();

    void init_context_info(bool force = false);

private:
    void draw(const lsLine *line);

public:
    std::vector<lsLine> m_entitys;
    lsPainter *m_painter;
};
