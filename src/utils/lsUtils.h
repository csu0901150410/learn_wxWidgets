#pragma once

#include <wx/wx.h>

#ifdef LS_USE_CV
#include "opencv2/opencv.hpp"
#endif

#ifdef LS_USE_CV
wxBitmap GetBitmap(const wxString& name);

bool ocv_grayscale(cv::Mat& image);
#endif
