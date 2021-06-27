#ifndef FLOODFILL_H
#define FLOODFILL_H

#include "datamanager.h"

class FloodFill
{
public:
    FloodFill();

    static void FillRegions(DataManager* dataManager);

};

#endif // FLOODFILL_H
