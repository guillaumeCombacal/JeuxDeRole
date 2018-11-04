import QtQuick 2.0

Rectangle
{
    id: heroMenu

    width: parent.width
    height: parent.height

    color:"pink"

    FeatureHero
    {
        id: featureHero
    }

    StatsHero
    {
        id: statsHero
    }

    EquipmentHero
    {
        id: equipmentHero
    }

    BagHero
    {
        id: bagHero
    }

}
