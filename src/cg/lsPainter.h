#pragma once

#include <wx/wx.h>
#include <cairo.h>

#include "lsSegment.h"
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

    void draw(const lsSegment& seg);

private:
    lsContext *m_context;
};
