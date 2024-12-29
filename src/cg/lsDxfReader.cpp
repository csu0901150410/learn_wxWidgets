#include "lsDxfReader.h"

#include "lsPoint.h"
#include "lsSegment.h"

#include "lsDocument.h"

bool lsDxfReader::import(lsDocument *document, const std::string &filepath)
{
    LS_DEBUG->print("[lsDxfReader::import] Importing file : %s", filepath.c_str());

    m_document = document;

    bool success = m_dxf.in(filepath.c_str(), this);
    if (!success)
    {
        LS_DEBUG->print("Cannot open DXF file : %s", filepath.c_str());
        return false;
    }

    return true;
}

void lsDxfReader::addLine(const DL_LineData &data)
{
    lsReal scale = 10000 * 0.5;
    lsReal offsetx = 1500;
    lsReal offsety = 1000;

    lsPoint s(data.x1 * scale + offsetx, data.y1 * scale + offsety);
    lsPoint e(data.x2 * scale + offsetx, data.y2 * scale + offsety);
    lsSegment *pseg = new lsSegment(s, e);
    m_document->add(pseg);
}