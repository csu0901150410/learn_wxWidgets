#pragma once

#include <wx/wx.h>
#include <cairo.h>

#include "lsLine.h"
#include "lsContext.h"

class lsPainter
{
public:
    lsPainter(wxWindow *parent)
        : m_context(nullptr)
    {
        // m_context = new lsContext(parent);
    }

    ~lsPainter()
    {
    }

    void set_context(lsContext *context)
    {
        m_context = context;
    }

    // 统一的绘制接口，lsLine可以理解为后续的基类lsEntity
    void draw(const lsLine* line);

private:
    lsContext *m_context;
};
