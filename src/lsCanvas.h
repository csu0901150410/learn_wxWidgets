#pragma once

#include "wx/wx.h"
#include "opencv2/opencv.hpp"

class lsFrame;

class lsCanvas : public wxScrolledWindow
{
public:
    lsCanvas(wxFrame *parent);

    void LoadImage(const wxString& path);
    bool HasImage() const { return !m_image.empty(); }
	bool SaveImage(const wxString& path);

    bool Binarize(int threshold);

    void OnDraw(wxDC& dc) override;
    void OnSize(wxSizeEvent& event);

private:
    void CenterImage();
    wxBitmap ConvertToBitmap() const;

private:
    cv::Mat m_image;
    wxBitmap m_cachedBitmap;// 缓存，用于显示
     bool m_needUpdate { false };// 标记是否需要更新缓存的位图
};
