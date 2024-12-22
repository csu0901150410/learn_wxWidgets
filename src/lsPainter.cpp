#include "lsPainter.h"

void lsPainter::draw(const lsLine *line)
{
    // 确定entity类型之后，分发到具体的绘制任务
    draw_line(line->sx, line->sy, line->ex, line->ey);
}

void lsPainter::draw_line(float sx, float sy, float ex, float ey)
{
    m_dc->DrawLine((int)sx, (int)sy, (int)ex, (int)ey);
}
