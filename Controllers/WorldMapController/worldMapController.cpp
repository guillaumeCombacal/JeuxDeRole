#include "worldMapController.h"

WorldMapController::WorldMapController()
{
    m_pWorldMapWidget = new WorldMapWidget();
}

WorldMapController::~WorldMapController()
{
    if(m_pWorldMapWidget != NULL)
    {
        delete m_pWorldMapWidget;
    }
}

WorldMapWidget *WorldMapController::getWorldMapWidget()
{
    return m_pWorldMapWidget;
}
