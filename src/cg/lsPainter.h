#pragma once

#include <wx/wx.h>
#include <cairo.h>

#include "lsLine.h"

class lsPainter
{
public:
    lsPainter(wxWindow *parent)
        : m_parent(parent)
        , m_context(nullptr)
        , m_initialized(false)
    {
    }

    ~lsPainter()
    {
        release_buffer();
    }

    // 统一的绘制接口，lsLine可以理解为后续的基类lsEntity
    void draw(const lsLine* line);

    void init_context_info(bool force = false);
    bool is_initialized() const { return m_initialized; }

    void begin_paint();
    void end_paint();

    // 重建绘图缓冲区，由外部调用
    void recreate_buffer(int width, int height);

    // 申请绘图缓存
    void allocate_buffer();

    // 释放绘图缓存
    void release_buffer();

// 这些具体的绘制方法可以抽象成绘制接口
private:
    // Drawing methods
    void draw_line(float sx, float sy, float ex, float ey);

private:
    wxWindow *m_parent;

    // 绘图相关的部分，可以抽象成接口或者定义成一个新类
    cairo_t *m_context;// 绘图上下文，直接指定使用cairo作为绘图后端
    cairo_surface_t *m_surface;// 绘图表面，即绘制到的地方

    wxSize m_screenSize;// 绘图窗口大小
    
    unsigned char *m_bitmapBuffer;// cairo绘图缓冲区
    unsigned int m_bufferSize;// 绘图缓冲区大小
    int m_stride;// 绘图缓冲区实际宽度，有时候窗口宽度比如说是奇数，cairo会进行填充类似内存对齐

    unsigned char *m_wximageBuffer;// wxImage转换缓冲区，cairo绘制的数据转换之后存储在这里

    bool m_initialized;
};
