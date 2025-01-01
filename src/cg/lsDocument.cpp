#include "lsDocument.h"

#include "lsSegment.h"

#include "lsEntity.h"

#include "lsDxfReader.h"

lsDocument::lsDocument()
{
    static unsigned long long idCounter=0;
    m_id = idCounter++;

    // test_init_entitys();
}

lsDocument::~lsDocument()
{
    for (auto entity : m_entitys)
    {
        delete entity;
    }
}

void lsDocument::test_init_entitys()
{
    // 随机生成范围内的浮点数
    auto random_float = [](float min, float max) {
        return min + (max - min) * (static_cast<float>(rand()) / RAND_MAX);
    };

    // 生成随机线段
    auto random_segment = [&random_float](float xmin, float xmax, float ymin, float ymax) {
        lsSegment seg;
        seg.s.x = random_float(xmin, xmax);
        seg.s.y = random_float(ymin, ymax);
        seg.e.x = random_float(xmin, xmax);
        seg.e.y = random_float(ymin, ymax);
        return seg;
    };

    float xmin = 0;
    float xmax = 800;
    float ymin = 0;
    float ymax = 600;

    for (int i = 0; i < 10; i++)
    {
        lsSegment seg = random_segment(xmin, xmax, ymin, ymax);
        add(new lsSegment(seg));
    }

    lsSegment left(50, 50, 50, 200);
    lsSegment top(50, 200, 500, 200);
    lsSegment right(500, 200, 500, 50);
    lsSegment bottom(500, 50, 50, 50);
    add(new lsSegment(left));
    add(new lsSegment(top));
    add(new lsSegment(right));
    add(new lsSegment(bottom));
}

unsigned long long lsDocument::get_id() const
{
    return m_id;
}

bool lsDocument::open(const std::string &filepath)
{
    lsDxfReader dxfReader;
    bool success = dxfReader.import(this, filepath);
    return success;
}

void lsDocument::release()
{
}

void lsDocument::add(const lsEntity *entity)
{
    m_entitys.push_back(entity);
}

std::vector<const lsEntity*>& lsDocument::get_entitys()
{
    return m_entitys;
}
