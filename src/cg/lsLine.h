#pragma once

class lsLine
{
public:
    lsLine() {}

    lsLine(float x0, float y0, float x1, float y1)
        : sx(x0), sy(y0), ex(x1), ey(y1)
    {
    }

public:
    float sx;
    float sy;
    float ex;
    float ey;
};
