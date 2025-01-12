#pragma once

#include "lsRenderTarget.h"

#include <wx/wx.h>

// 渲染到wx的窗口
class lsScreenRenderTarget : public lsRenderTarget
{
public:
    explicit lsScreenRenderTarget(wxWindow *window);

    void render(const unsigned char *buffer, int width, int height, int stride) override;

    int get_width() override;
    int get_height() override;

private:
    wxWindow *m_window;
};
