#pragma once

#include <wx/wx.h>

#include "opencv2/opencv.hpp"

wxBitmap GetBitmap(const wxString& name);

bool ocv_grayscale(cv::Mat& image);
