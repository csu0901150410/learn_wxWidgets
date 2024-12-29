#include "lsView.h"

#include "lsContext.h"
#include "lsDocument.h"

lsView::lsView(wxWindow *parent)
{
    m_context = new lsContext(parent);

    m_document = new lsDocument();
    m_document->open("resources/models/bridge.dxf");
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

    std::vector<const lsEntity *> entitys;
    m_document->get_entitys(entitys);
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

void lsView::draw(const lsEntity *entity)
{
    // 去掉const限定，进行多态调用
    lsEntity *ptr = const_cast<lsEntity *>(entity);
    ptr->draw(m_context);
}
