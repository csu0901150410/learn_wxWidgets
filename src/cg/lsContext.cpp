#include "lsContext.h"

#include <assert.h>

lsContext::lsContext(wxWindow *parent)
    : m_parent(parent)
    , m_bitmapBuffer(nullptr)
    , m_wximageBuffer(nullptr)
    , m_initialized(false)
{
}

lsContext::~lsContext()
{
    release_buffer();
}

void lsContext::resize_screen(int width, int height)
{
    // 设置好窗口尺寸后，重建绘图缓冲区
    m_screenWidth = width;
    m_screenHeight = height;

    release_buffer();
    allocate_buffer();
}

void lsContext::clear_screen()
{
    cairo_set_source_rgb(m_context, 0, 0, 0);
    cairo_rectangle(m_context, 0.0, 0.0, m_screenWidth, m_screenHeight);
    cairo_fill(m_context);
}

void lsContext::begin_paint()
{
    init_surface();

    clear_screen();

    // 设置线宽和颜色
    cairo_set_line_width(m_context, 1.0);
    cairo_set_source_rgba(m_context, 255, 0.0, 0.0, 1.0);
}

void lsContext::end_paint()
{
    // 绘制结束，将cairo绘制的数据组织成wxImage的格式
    int stride = m_stride;
    int screenWidth = m_screenWidth;
    int screenHeight = m_screenHeight;
    unsigned char* srcRow = m_bitmapBuffer;
    unsigned char* dst = m_wximageBuffer;

    for( int y = 0; y < screenHeight; y++ )
    {
        for( int x = 0; x < stride; x += 4 )
        {
            const unsigned char* src = srcRow + x;

            // BGRX
            dst[0] = src[2];
            dst[1] = src[1];
            dst[2] = src[0];

            dst += 3;
        }

        srcRow += stride;
    }

    wxImage img(screenWidth, screenHeight, m_wximageBuffer, true);
    wxBitmap bmp(img);
    wxMemoryDC mdc(bmp);
    wxClientDC clientDC(m_parent);

    // 绘制到ClientDC
    clientDC.Blit(0, 0, screenWidth, screenHeight, &mdc, 0, 0, wxCOPY);

    deinit_surface();
}

void lsContext::draw_line(const lsReal& x1, const lsReal& y1, const lsReal& x2, const lsReal& y2)
{
    // 使用cairo绘制
    cairo_move_to(m_context, x1, y1);
    cairo_line_to(m_context, x2, y2);
    cairo_stroke(m_context);
}

void lsContext::draw_line(const lsPoint &p1, const lsPoint &p2)
{
    draw_line(p1.x, p1.y, p2.x, p2.y);
}

void lsContext::draw_line(const lsLine &line)
{
    draw_line(line.s, line.e);
}

void lsContext::draw_segment(const lsSegment &seg)
{
    cairo_move_to(m_context, seg.s.x, seg.s.y);
    cairo_line_to(m_context, seg.e.x, seg.e.y);
    cairo_stroke(m_context);
}

void lsContext::allocate_buffer()
{
    // 根据窗口尺寸申请绘图缓冲区
    m_stride = cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, m_screenWidth);
    m_bufferSize = m_stride * m_screenHeight;

    // 申请绘图缓冲区内存和转换缓冲区内存
    assert(m_bitmapBuffer == nullptr);
    m_bitmapBuffer = new unsigned char[m_bufferSize];
    assert(m_wximageBuffer == nullptr);
    m_wximageBuffer = new unsigned char[m_screenWidth * 3 * m_screenHeight];
}

void lsContext::release_buffer()
{
    // 释放申请的内存
    delete[] m_bitmapBuffer;
    m_bitmapBuffer = nullptr;
    delete[] m_wximageBuffer;
    m_wximageBuffer = nullptr;
}

void lsContext::init_surface()
{
    if (m_initialized)
        return;

    // 创建cairo对象
    m_surface = cairo_image_surface_create_for_data(m_bitmapBuffer, CAIRO_FORMAT_ARGB32, m_screenWidth,
                                                    m_screenHeight, m_stride);
    m_context = cairo_create(m_surface);

    m_initialized = true;
}

void lsContext::deinit_surface()
{
    if (!m_initialized)
        return;

    // 释放cairo资源
    cairo_destroy(m_context);
    m_context = nullptr;
    cairo_surface_destroy(m_surface);
    m_surface = nullptr;

    m_initialized = false;
}
