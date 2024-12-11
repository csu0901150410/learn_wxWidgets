﻿#include "lsCanvas.h"

#include <opencv2/opencv.hpp>

// See https://github.com/PBfordev/wxopencvtest
#include "convertmattowxbmp.h"

lsCanvas::lsCanvas(wxFrame *parent)
    : wxScrolledWindow(parent)
{
    SetBackgroundColour(*wxBLACK);
    SetScrollRate(0, 0); // 初始时禁用滚动条

    Bind(wxEVT_SIZE, &lsCanvas::OnSize, this);
}

void lsCanvas::LoadImage(const wxString& path)
{
    // 使用OpenCV直接加载图像
    std::string stdPath(path.mb_str());
    m_image = cv::imread(stdPath);
    if (!m_image.empty())
    {
        // 确保图像格式为BGR CV_8UC3
        if (m_image.type() != CV_8UC3) {
            cv::Mat temp;
            m_image.convertTo(temp, CV_8UC3);
            m_image = temp;
        }

        m_needUpdate = true;
        CenterImage();
        Refresh();
    }
}

bool lsCanvas::SaveImage(const wxString &path)
{
    if (!HasImage())
        return false;
    
    std::string stdPath(path.mb_str());
    return cv::imwrite(stdPath, m_image);
}

bool lsCanvas::Binarize(int threshold)
{
    if (!HasImage())
        return false;

    // 转换为灰度图
    cv::Mat gray_image;
    cv::cvtColor(m_image, gray_image, cv::COLOR_BGR2GRAY);
    
    // 执行二值化
    cv::Mat binary_image;
    cv::threshold(gray_image, binary_image, threshold, 255, cv::THRESH_BINARY);
    
    // 转换回BGR图像
    cv::cvtColor(binary_image, m_image, cv::COLOR_GRAY2BGR);
    
    m_needUpdate = true;
    Refresh();
    return true;
}

void lsCanvas::OnDraw(wxDC& dc)
{
    if (m_image.empty())
        return;

    // 如果需要更新缓存的位图
    if (m_needUpdate)
    {
        m_cachedBitmap = ConvertToBitmap();
        m_needUpdate = false;
    }

    // 获取面板和图片的尺寸
    int panelWidth, panelHeight;
    GetSize(&panelWidth, &panelHeight);
    int bmpWidth = m_cachedBitmap.GetWidth();
    int bmpHeight = m_cachedBitmap.GetHeight();

    // 计算居中位置
    int x = (panelWidth - bmpWidth) / 2;
    int y = (panelHeight - bmpHeight) / 2;

    // 如果图片大于面板，需要考虑滚动位置
    if (bmpWidth > panelWidth || bmpHeight > panelHeight)
    {
        int scrollX, scrollY;
        GetViewStart(&scrollX, &scrollY);
        int ppuX, ppuY;
        GetScrollPixelsPerUnit(&ppuX, &ppuY);
        x = (GetVirtualSize().x - bmpWidth) / 2 - scrollX * ppuX;
        y = (GetVirtualSize().y - bmpHeight) / 2 - scrollY * ppuY;
    }

    // 确保x和y不会为负值
    x = wxMax(0, x);
    y = wxMax(0, y);

    dc.DrawBitmap(m_cachedBitmap, x, y, true);
}

void lsCanvas::OnSize(wxSizeEvent &event)
{
    if (!m_image.empty())
    {
        CenterImage();
    }
    event.Skip();
}

void lsCanvas::CenterImage()
{
    if (m_image.empty())
        return;

    // 获取面板和图片的尺寸
    int panelWidth, panelHeight;
    GetSize(&panelWidth, &panelHeight);
    int bmpWidth = m_image.cols;
    int bmpHeight = m_image.rows;

    // 设置虚拟大小
    // 当图片小于面板时，使用面板大小作为虚拟大小
    // 当图片大于面板时，使用图片大小作为虚拟大小
    int virtualWidth = wxMax(panelWidth, bmpWidth);
    int virtualHeight = wxMax(panelHeight, bmpHeight);
    
    SetVirtualSize(virtualWidth, virtualHeight);
    
    // 禁用滚动条（当图片小于面板时）
    if (bmpWidth <= panelWidth && bmpHeight <= panelHeight)
    {
        SetScrollRate(0, 0);
    }
    else
    {
        SetScrollRate(5, 5);
    }

    Refresh();  // 强制重绘
}

wxBitmap lsCanvas::ConvertToBitmap() const
{
    if (m_image.empty())
        return wxBitmap();

    // wxBitmap的宽高应该初始化为和Mat一致，且深度为24
    wxBitmap bitmap(m_image.cols, m_image.rows, 24);
    bool bSuccess = ConvertMatBitmapTowxBitmap(m_image, bitmap);
    if (!bSuccess)
        return wxBitmap();
    
    // 返回wxBitmap
    return bitmap;
}
