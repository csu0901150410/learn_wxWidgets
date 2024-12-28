#include "lsEntity.h"

lsEntity::lsEntity()
{
    init();
}

void lsEntity::init()
{
    init_id();
}

void lsEntity::init_id()
{
    static unsigned long long idCounter=0;
    m_id = idCounter++;
}
