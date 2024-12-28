#include "lsPainter.h"

void lsPainter::draw(const lsEntity *entity)
{
    // 去掉const限定，进行多态调用
    lsEntity *ptr = const_cast<lsEntity *>(entity);
    ptr->draw(m_context);
}
