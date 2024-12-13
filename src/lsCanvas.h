#pragma once

#include "wx/wx.h"
#include "wx/timer.h"
#include "opencv2/opencv.hpp"

class lsFrame;

class lsCanvas : public wxScrolledWindow
{
public:
    lsCanvas(wxWindow* parent);
    ~lsCanvas();

    void LoadImage(const wxString& path);
    bool HasImage() const { return !m_image.empty(); }
	bool SaveImage(const wxString& path);

    bool Binarize(int threshold);

    void OnDraw(wxDC& dc) override;
    void OnSize(wxSizeEvent& event);
    void OnTimer(wxTimerEvent& event);

    bool OpenCamera(int deviceId = 0);
    void CloseCamera();
    bool IsCameraOpen() const { return m_camera.isOpened(); }

private:
    void CenterImage();
    wxBitmap ConvertToBitmap() const;

private:
    cv::Mat m_image;
    wxBitmap m_cachedBitmap;// 缓存，用于显示
    bool m_needUpdate { false };// 标记是否需要更新缓存的位图

    cv::VideoCapture m_camera;
    wxTimer *m_timer;
    bool m_isStreaming { false };
};
