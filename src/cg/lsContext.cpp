#include "lsContext.h"

#include <assert.h>

lsContext::lsContext(wxWindow *window)
    : m_window(window)
    , m_bitmapBuffer(nullptr)
    , m_wximageBuffer(nullptr)
    , m_initialized(false)
{
    cairo_matrix_init_identity(&m_matrixWorld2Screen);
    cairo_matrix_init_identity(&m_matrixScreen2World);

    m_viewportOffset = lsPoint(0, 0);
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

    update_matrix();
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

    // 渲染到具体的设备上
    wxImage img(screenWidth, screenHeight, m_wximageBuffer, true);
    wxBitmap bmp(img);
    wxMemoryDC mdc(bmp);
    wxClientDC clientDC(m_window);

    // 绘制到ClientDC
    clientDC.Blit(0, 0, screenWidth, screenHeight, &mdc, 0, 0, wxCOPY);

    deinit_surface();
}

int lsContext::get_screen_width() const
{
    return m_screenWidth;
}

int lsContext::get_screen_height() const
{
    return m_screenHeight;
}

cairo_matrix_t lsContext::get_world2screen_matrix() const
{
    return m_matrixWorld2Screen;
}

cairo_matrix_t lsContext::get_screen2world_matrix() const
{
    cairo_matrix_t mat = m_matrixWorld2Screen;
    cairo_matrix_invert(&mat);
    return mat;
}

lsPoint lsContext::screen2world(lsPoint pos)
{
    lsPoint ret = pos;
    cairo_matrix_transform_point(&m_matrixScreen2World, &ret.x, &ret.y);
    return ret;
}

lsPoint lsContext::world2screen(lsPoint pos)
{
    lsPoint ret = pos;
    cairo_matrix_transform_point(&m_matrixWorld2Screen, &ret.x, &ret.y);
    return ret;
}

// 重新计算变换矩阵
void lsContext::update_matrix()
{
    // 计算世界坐标系到屏幕坐标系的变换矩阵，再求逆得到screen -> world

    // 将视口映射到屏幕
    cairo_matrix_t translation;
    cairo_matrix_init_translate(&translation, -m_viewportOffset.x, -m_viewportOffset.y);

    cairo_matrix_t matrix;
    cairo_matrix_init_identity(&matrix);
    cairo_matrix_multiply(&matrix, &translation, &matrix);

    m_matrixWorld2Screen = matrix;
    m_matrixScreen2World = matrix;
    cairo_matrix_invert(&m_matrixScreen2World);
}

void lsContext::set_viewport_offset(const lsPoint &pos)
{
    m_viewportOffset = pos;
}

void lsContext::draw_segment(const lsReal &x1, const lsReal &y1, const lsReal &x2, const lsReal &y2)
{
    lsPoint p1 = transform(lsPoint(x1, y1));
    lsPoint p2 = transform(lsPoint(x2, y2));

    cairo_move_to(m_context, p1.x, p1.y);
    cairo_line_to(m_context, p2.x, p2.y);
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

// see https://www.cairographics.org/manual/cairo-cairo-matrix-t.html Description
lsPoint lsContext::transform(const lsPoint &point)
{
    lsPoint ret;
    ret.x = m_matrixWorld2Screen.xx * point.x + m_matrixWorld2Screen.xy * point.y + m_matrixWorld2Screen.x0;
    ret.y = m_matrixWorld2Screen.yx * point.x + m_matrixWorld2Screen.yy * point.y + m_matrixWorld2Screen.y0;
    return ret;
}
