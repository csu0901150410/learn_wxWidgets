#include "lsUtils.h"

#ifdef LS_USE_CV
wxBitmap GetBitmap(const wxString &name)
{
    wxImage image(name, wxBITMAP_TYPE_PNG);
    return wxBitmap(image);
}

bool ocv_grayscale(cv::Mat &image)
{
    if (image.empty())
        return false;

    cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);
    cv::cvtColor(image, image, cv::COLOR_GRAY2BGR);
    return true;
}
#endif
