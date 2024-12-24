#include "lsPainter.h"

void lsPainter::draw(const lsLine *line)
{
    // 确定entity类型之后，分发到具体的绘制任务
    draw_line(line->sx, line->sy, line->ex, line->ey);
}

void lsPainter::init_context_info(bool force)
{
    if (!force && m_initialized)
        return;
    m_initialized = true;

    // 获取父窗口大小，申请绘图缓冲区
    m_screenSize = m_parent->GetClientSize();
    allocate_buffer();
}

void lsPainter::begin_paint()
{
    // 创建cairo对象
    m_surface = cairo_image_surface_create_for_data(m_bitmapBuffer, CAIRO_FORMAT_ARGB32, m_screenSize.x,
                                                    m_screenSize.y, m_stride);
    m_context = cairo_create(m_surface);

    // 设置线宽和颜色
    cairo_set_line_width(m_context, 1.0);
    cairo_set_source_rgba(m_context, 255, 0.0, 0.0, 1.0);
}

void lsPainter::end_paint()
{
    // 绘制结束，将cairo绘制的数据组织成wxImage的格式
    int stride = m_stride;
    int screenWidth = m_screenSize.x;
    int screenHeight = m_screenSize.y;
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

    // 释放cairo资源
    cairo_destroy(m_context);
    m_context = nullptr;
    cairo_surface_destroy(m_surface);
    m_surface = nullptr;
}

void lsPainter::recreate_buffer(int width, int height)
{
    // 未初始化，跳过，主要是跳过未初始化时OnSize的重建，必须在初始化之后才能重建
    if (!m_initialized)
        return;

    // 设置好窗口尺寸后，重建绘图缓冲区
    m_screenSize = wxSize(width, height);

    release_buffer();
    allocate_buffer();
}

void lsPainter::allocate_buffer()
{
    // 根据窗口尺寸 m_screenSize 申请绘图缓冲区
    m_stride = cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, m_screenSize.x);
    m_bufferSize = m_stride * m_screenSize.y;

    // 申请绘图缓冲区内存和转换缓冲区内存
    wxASSERT(m_bitmapBuffer == nullptr);
    m_bitmapBuffer = new unsigned char[m_bufferSize];
    wxASSERT(m_wximageBuffer == nullptr);
    m_wximageBuffer = new unsigned char[m_screenSize.x * 3 * m_screenSize.y];
}

void lsPainter::release_buffer()
{
    // 释放申请的内存
    delete[] m_bitmapBuffer;
    m_bitmapBuffer = nullptr;
    delete[] m_wximageBuffer;
    m_wximageBuffer = nullptr;
}

void lsPainter::draw_line(float sx, float sy, float ex, float ey)
{
    // 使用cairo绘制
    cairo_move_to(m_context, sx, sy);
    cairo_line_to(m_context, ex, ey);
    cairo_stroke(m_context);
}
