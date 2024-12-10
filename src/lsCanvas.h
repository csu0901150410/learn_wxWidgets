#pragma once

#include "wx/wx.h"

class lsFrame;

class lsCanvas : public wxScrolledWindow
{
public:
    lsCanvas(wxFrame *parent);

    void LoadImage(const wxString& path);
    bool HasImage() const { return !m_bitmap.IsNull(); }
	bool SaveImage(const wxString& path);

    bool Binarize(int threshold);

    void OnDraw(wxDC& dc) override;
    void OnSize(wxSizeEvent& event);

private:
    void CenterImage();

private:
    wxBitmap m_bitmap;
};
