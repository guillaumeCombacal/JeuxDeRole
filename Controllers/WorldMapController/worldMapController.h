#ifndef WORLDMAPCONTROLLER_H
#define WORLDMAPCONTROLLER_H

#include"worldMapWidget.h"

class WorldMapController
{

private:
    WorldMapWidget *m_pWorldMapWidget;

public:
    WorldMapController();
    ~WorldMapController();

    WorldMapWidget *getWorldMapWidget();
};

#endif // WORLDMAPCONTROLLER_H
