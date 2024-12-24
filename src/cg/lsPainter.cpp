#include "lsPainter.h"

void lsPainter::draw(const lsLine *line)
{
    // 确定entity类型之后，分发到具体的绘制任务
    m_context->draw_line(line->sx, line->sy, line->ex, line->ey);
}
