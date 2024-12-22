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
        // bug - 这里的时候父窗口还未完全初始化，获取的尺寸是错的，要更改获取这些信息的时机
        // 由窗口去维护context会比较好
        // // 获取父窗口大小，计算绘图缓冲区参数
        // m_screenSize = parent->GetClientSize();
        // m_stride = cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, m_screenSize.x);
        // m_bufferSize = m_stride * m_screenSize.y;

        // // 申请绘图缓冲区内存和转换缓冲区内存
        // wxASSERT(m_bitmapBuffer == nullptr);
        // m_bitmapBuffer = new unsigned char[m_bufferSize];
        // wxASSERT(m_wximageBuffer == nullptr);
        // m_wximageBuffer = new unsigned char[m_screenSize.x * 3 * m_screenSize.y];
    }

    ~lsPainter()
    {
    }

    // 统一的绘制接口，lsLine可以理解为后续的基类lsEntity
    void draw(const lsLine* line);

    void init_context_info(bool force = false);
    void begin_paint();
    void end_paint();

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
