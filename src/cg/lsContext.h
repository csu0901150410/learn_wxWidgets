﻿#pragma once

#include <cairo.h>

#include "lsPoint.h"
#include "lsLine.h"
#include "lsSegment.h"

class lsRenderTarget;

// 绘图上下文，负责具体绘图后端的实现，在绘图目标（窗口）上进行绘制动作
class lsContext
{
public:
    lsContext(lsRenderTarget *target);
    ~lsContext();

    // 屏幕尺寸变换，需要重新申请缓冲区
    void resize_screen(int width, int height);

    void clear_screen();

    void begin_paint();
    void end_paint();

// 变换接口
public:
    void set_world2screen_matrix(const cairo_matrix_t &matrix);
    cairo_matrix_t get_world2screen_matrix() const;
    cairo_matrix_t get_screen2world_matrix() const;

    lsPoint screen2world(lsPoint pos);
    lsPoint world2screen(lsPoint pos);

    void update_matrix();
    void set_scale(lsPoint anchor, lsReal scale);

// 绘图接口
public:
    void draw_segment(const lsReal& x1, const lsReal& y1, const lsReal& x2, const lsReal& y2);

private:
    void allocate_buffer();
    void release_buffer();

    void init_surface();
    void deinit_surface();

    lsPoint transform(const lsPoint& point);

private:
    cairo_t *m_context;
    cairo_surface_t *m_surface;

    int m_screenWidth;// 屏幕宽度
    int m_screenHeight;// 屏幕高度

    // buffer
    unsigned char *m_bitmapBuffer;// 绘图缓冲区
    unsigned char *m_wximageBuffer;// 转换缓冲区
    int m_bufferSize;// 缓冲区尺寸
    int m_stride;// 对齐后的缓冲区宽度

    bool m_initialized;// 标记cairo对象是否创建，保证不重复创建和释放

    // 坐标系变换
    lsPoint m_origin;// 屏幕坐标系原点在世界坐标系下的坐标
    lsReal m_scale;// 世界坐标系到屏幕坐标系的缩放比例 屏幕距离/世界距离
    lsReal m_rotation;// 世界坐标系到屏幕坐标系的旋转弧度 单位为弧度
    bool m_flipx;
    bool m_flipy;// 一般来说，转换到屏幕坐标系，要对y进行翻转
    cairo_matrix_t m_matrixWorld2Screen;// 世界坐标系到屏幕坐标系的变换矩阵
    cairo_matrix_t m_matrixScreen2World;// 屏幕坐标系到世界坐标系的变换矩阵

    lsRenderTarget *m_target;
};
