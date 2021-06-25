#include "polygonstruct.h"
#include <algorithm>

PolygonStruct::PolygonStruct(QPolygon* p)
{
    polygon = p;
}

QPolygon *PolygonStruct::GetPolygon()
{
    return polygon;
}

void PolygonStruct::SetTraversability(int value)
{
    traversability = std::clamp(value, 0, 100);
}

int PolygonStruct::GetTraversability()
{
    return traversability;
}
