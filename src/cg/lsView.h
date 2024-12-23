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

    // 太麻烦了这样，要通过父窗口操作绘图后端就得定义这些重复的函数，后续有父窗口持有一个绘图后端的指针
    void recreate_buffer(int width, int height);

private:
    void draw(const lsLine *line);

public:
    std::vector<lsLine> m_entitys;
    lsPainter *m_painter;
};
