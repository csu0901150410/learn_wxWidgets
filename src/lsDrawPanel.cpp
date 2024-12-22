#include "lsDrawPanel.h"

#include <wx/wx.h>
#include <cairo.h>

lsDrawPanel::lsDrawPanel(wxWindow *parent)
    : wxScrolledCanvas(parent)
{
    SetBackgroundColour(*wxBLACK);

    m_view = new lsView(this);
    m_view->add(lsLine(0, 0, 200, 300));

    Bind(wxEVT_PAINT, &lsDrawPanel::OnPaint, this);
}

lsDrawPanel::~lsDrawPanel()
{
    delete m_view;
}

void lsDrawPanel::OnPaint(wxPaintEvent &event)
{
    // cairo backend
    // https://www.cairographics.org/
    // https://github.com/preshing/cairo-windows

    // 获取绘图尺寸
    wxPaintDC dc(this);
    wxSize screen_size = dc.GetSize();

    // 申请绘图buffer
    int stride = cairo_format_stride_for_width(CAIRO_FORMAT_RGB24, screen_size.x);
    unsigned int buffer_size = stride * screen_size.y;
    unsigned char *bitmap_buffer = new unsigned char[buffer_size];
    unsigned char *wx_output = new unsigned char[screen_size.x * 3 * screen_size.y];

    // 初始化绘图surface/context
    cairo_surface_t *surface = cairo_image_surface_create_for_data(bitmap_buffer, CAIRO_FORMAT_ARGB32, screen_size.x, screen_size.y, stride);
    cairo_t *context = cairo_create(surface);

    // 设置背景色
    cairo_set_source_rgba(context, 0.0, 0.0, 0.0, 1.0);
    cairo_rectangle(context, 0, 0, screen_size.x, screen_size.y);
    cairo_fill(context);

    // 绘制线段
    cairo_set_source_rgba(context, 255, 0.0, 0.0, 1.0);
    cairo_move_to(context, 100, 100);
    cairo_line_to(context, 500, 100);
    cairo_set_line_width(context, 5.0);
    cairo_stroke(context);

    // 绘制结束，将cairo绘制的数据组织成wxImage的格式
    int height = screen_size.y;
    unsigned char* srcRow = bitmap_buffer;
    unsigned char* dst = wx_output;

    for( int y = 0; y < height; y++ )
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

    wxImage    img(screen_size.x, screen_size.y, wx_output, true);
    wxBitmap   bmp(img);
    wxMemoryDC mdc(bmp);
    wxClientDC clientDC(this);

    // 绘制到ClientDC
    clientDC.Blit( 0, 0, screen_size.x, screen_size.y, &mdc, 0, 0, wxCOPY );

    // 释放cairo资源
    cairo_destroy(context);
    context = nullptr;
    cairo_surface_destroy(surface);
    surface = nullptr;

    // 释放申请的内存
    delete[] bitmap_buffer;
    bitmap_buffer = nullptr;
    delete[] wx_output;
    wx_output = nullptr;

    // 走view绘制的一套
    do_repaint();
}

void lsDrawPanel::do_repaint()
{
    m_view->redraw();
}
