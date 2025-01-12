#pragma once

// 渲染目标类，绘图后端绘制好后，可以将缓冲区中的图像渲染到gui相关的窗口或者文件中
// 不同的渲染目标实现不同的子类即可，这样context和设备无关
class lsRenderTarget
{
public:
    virtual ~lsRenderTarget() = default;

    virtual void render(const unsigned char *buffer, int width, int height, int stride) = 0;

    virtual int get_height() = 0;
    virtual int get_width() = 0;
};
