#pragma once

#include "wx/wx.h"

class lsFrame;

class lsCanvas : public wxScrolledWindow
{
public:
    lsCanvas(wxFrame *parent);

    void LoadImage(const wxString& path);

    void OnDraw(wxDC& dc) override;

private:
    wxBitmap m_bitmap;
};
