#include "lsScreenRenderTarget.h"

lsScreenRenderTarget::lsScreenRenderTarget(wxWindow *window)
    : m_window(window)
{
}

void lsScreenRenderTarget::render(const unsigned char *buffer, int width, int height, int stride)
{
    unsigned char *_buffer = const_cast<unsigned char *>(buffer);
    wxImage img(width, height, _buffer, true);
    wxBitmap bmp(img);
    wxMemoryDC mdc(bmp);
    wxClientDC clientDC(m_window);

    // 绘制到ClientDC
    clientDC.Blit(0, 0, width, height, &mdc, 0, 0, wxCOPY);
}

int lsScreenRenderTarget::get_width()
{
    return m_window->GetClientSize().GetWidth();
}

int lsScreenRenderTarget::get_height()
{
    return m_window->GetClientSize().GetHeight();
}
