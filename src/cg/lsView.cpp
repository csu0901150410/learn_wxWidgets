#include "lsView.h"

#include "lsContext.h"
#include "lsDocument.h"

#include "lsBoundbox.h"

#include "lsScreenRenderTarget.h"

lsView::lsView(wxWindow *parent)
{
    m_context = new lsContext(new lsScreenRenderTarget(parent));

    m_document = new lsDocument();
    m_document->open("resources/models/bridge.dxf");

    // 计算一个box显示出来
    lsBoundbox box;
    std::vector<const lsEntity *> entitys = m_document->get_entitys();
    for (const auto& entity : entitys)
    {
        box.combine(entity->get_boundbox());
    }
    m_document->add(new lsSegment(lsPoint(box.left, box.bottom), lsPoint(box.left, box.top)));
    m_document->add(new lsSegment(lsPoint(box.left, box.top), lsPoint(box.right, box.top)));
    m_document->add(new lsSegment(lsPoint(box.right, box.top), lsPoint(box.right, box.bottom)));
    m_document->add(new lsSegment(lsPoint(box.right, box.bottom), lsPoint(box.left, box.bottom)));

    m_factor = 1.0;
}

lsView::~lsView()
{
    delete m_context;
    delete m_document;
}

void lsView::redraw()
{
    // 先beginpaint，不然context没申请就gg
    m_context->begin_paint();

    std::vector<const lsEntity *> entitys = m_document->get_entitys();
    for (const auto& entity : entitys)
    {
        draw(entity);
    }

    m_context->end_paint();
}

void lsView::resize_screen(int width, int height)
{
    m_context->resize_screen(width, height);
}

void lsView::zoom(lsReal factor, lsReal screenx, lsReal screeny)
{
    // 计算出新的变换矩阵设置给context

    // 计算屏幕坐标对应的世界坐标
    lsPoint oldpt(screenx, screeny);
    cairo_matrix_t mats2w = m_context->get_screen2world_matrix();
    cairo_matrix_transform_point(&mats2w, &oldpt.x, &oldpt.y);

    // 计算新的缩放值
    m_factor *= factor;
    if (m_factor < 0.1)
    {
        m_factor = 0.1;
    }
    else if (m_factor > 10)
    {
        m_factor = 10;
    }

    // 偏移不变，改变缩放值，计算屏幕坐标点对应的世界坐标
    // 注意，上边可以直接get_screen2world_matrix获取screen -> world变换矩阵
    // 这里要自己根据新的缩放值组装，太tm麻烦了，后续得考虑个办法
    cairo_matrix_t matscal;
    cairo_matrix_init_identity(&matscal);
    cairo_matrix_init_scale(&matscal, m_factor, m_factor);

    cairo_matrix_t mattran;
    cairo_matrix_init_identity(&mattran);
    cairo_matrix_translate(&mattran, m_offsetx, m_offsety);

    cairo_matrix_t mattmp;
    cairo_matrix_init_identity(&mattmp);
    cairo_matrix_multiply(&mattmp, &mattran, &matscal);

    // 因为m_factor/m_offsetx/m_offsety参数是描述world -> screen变换矩阵的
    // 所以组装好后要invert求screen -> world变换矩阵
    cairo_matrix_invert(&mattmp);
    lsPoint newpt(screenx, screeny);
    cairo_matrix_transform_point(&mattmp, &newpt.x, &newpt.y);

    // 不同缩放比例下，同一个屏幕坐标点对应的新旧两个世界点之差就是新旧两个屏幕坐标系的偏移
    m_offsetx += newpt.x - oldpt.x;
    m_offsety += newpt.y - oldpt.y;

    // 计算新的  world -> screen 变换矩阵
    cairo_matrix_t matscale;
    cairo_matrix_init_identity(&matscale);
	cairo_matrix_init_scale(&matscale, m_factor, m_factor);

    cairo_matrix_t mattranslation;
    cairo_matrix_init_identity(&mattranslation);
	cairo_matrix_translate(&mattranslation, m_offsetx, m_offsety);

    cairo_matrix_t matw2s;
    cairo_matrix_init_identity(&matw2s);
    cairo_matrix_multiply(&matw2s, &mattranslation, &matscale);

    m_context->set_world2screen_matrix(matw2s);

    redraw();
}

void lsView::zoom_in(lsReal cx, lsReal cy)
{
    zoom(1.1, cx, cy);
}

void lsView::zoom_out(lsReal cx, lsReal cy)
{
    zoom(0.9, cx, cy);
}

void lsView::draw(const lsEntity *entity)
{
    // 去掉const限定，进行多态调用
    lsEntity *ptr = const_cast<lsEntity *>(entity);
    ptr->draw(m_context);
}
