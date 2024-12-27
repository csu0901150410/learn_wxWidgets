#pragma once

#include <cairo.h>

#include <wx/wx.h>
// #include <wx/image.h>
// #include <wx/dcmemory.h>
// #include <wx/dcclient.h>
// #include <wx/msw/window.h>
// #include <wx/msw/bitmap.h>

#include "lsPoint.h"
#include "lsLine.h"
#include "lsSegment.h"

class lsContext
{
public:
    lsContext(wxWindow *parent);
    ~lsContext();

    // 屏幕尺寸变换，需要重新申请缓冲区
    void resize_screen(int width, int height);

    void clear_screen();

    void begin_paint();
    void end_paint();

// 绘图接口
public:
    void draw_line(const lsReal& x1, const lsReal& y1, const lsReal& x2, const lsReal& y2);
    void draw_line(const lsPoint& p1, const lsPoint& p2);
    void draw_line(const lsLine& line);

    void draw_segment(const lsSegment& seg);

private:
    void allocate_buffer();
    void release_buffer();

    void init_surface();
    void deinit_surface();

private:
    cairo_t *m_context;
    cairo_surface_t *m_surface;

    int m_screenWidth;// 屏幕宽度
    int m_screenHeight;// 屏幕高度

    // buffer
    unsigned char *m_bitmapBuffer;// 绘图缓冲区
    unsigned char *m_wximageBuffer;// 转换缓冲区
    int m_bufferSize;// 缓冲区尺寸
    int m_stride;// 对齐后的缓冲区宽度

    bool m_initialized;// 标记cairo对象是否创建，保证不重复创建和释放

    wxWindow *m_parent;
};
