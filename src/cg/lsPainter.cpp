#include "lsPainter.h"

void lsPainter::draw(const lsSegment& seg)
{
    // 确定entity类型之后，分发到具体的绘制任务
    m_context->draw_segment(seg);
}
