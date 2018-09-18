import QtQuick 2.6
import QtQuick.Window 2.2

// Pour Le composant GridLayout
import QtQuick.Layouts 1.1

//import QtLocation 5.6
//import QtPositioning 5.5

//import classAnchor 1.0 // Permet d'importer la déclaration de la classe Anchor pour créer une référence dans le QML

Rectangle
{
    id: markerBoard
    //anchors.right: parent.right
    height: parent.height
    width: parent.width

    color:"white"
    opacity: 1

    property bool isMarkerSelected: false

    signal markerSelected(string idMarker, string urlImage)// Propage vers OptionBoard qu'un marker a été sélectionné

    function onMarkerSelected(idMarker, urlImage)
    {
        if(!markerBoard.isMarkerSelected)
        {
            markerBoard.isMarkerSelected = true;
        }

        markerSelected(idMarker, urlImage);

        // Change Opacity to see which marker is selected
        for (var i = 0; i < grid.children.length; ++i)
        {
            if(grid.children[i].idMarker === idMarker)
            {
                grid.children[i].opacity = 1;
                grid.children[i].border.width = 3;
            }
            else
            {
                grid.children[i].opacity = 0.5;
                grid.children[i].border.width = 0;
            }
        }
    }

    function allMarkerUnselected()
    {
        for (var i = 0; i < grid.children.length; ++i)
        {
            grid.children[i].opacity = 0.5;
            grid.children[i].border.width = 0;
        }
    }

    // Layout contenant tous les btn de marker
    GridLayout
    {
        id: grid
        anchors.fill: parent

        rows: 3
        columns: 2

            MarkerBtn
            {
                id:markerQuest

                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.columnSpan: 1
                Layout.rowSpan: 1
                Layout.row: 0
                Layout.column: 0

                urlImage: "file:///" + ressourcesDirPath + "/Ressources/qmlRessources/WorldMap/Marker/MarkerQuest.png"
                idMarker: "MarkerQuest"

                onMarkerBtnSelected:
                {
                    markerBoard.onMarkerSelected(idMarker, urlImage);
                }
            }

            MarkerBtn
            {
                id:markerTown

                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.columnSpan: 1
                Layout.rowSpan: 1
                Layout.row: 0
                Layout.column: 1

                urlImage: "file:///" + ressourcesDirPath + "/Ressources/qmlRessources/WorldMap/Marker/MarkerTown.png"
                idMarker: "MarkerTown"

                onMarkerBtnSelected:
                {
                    markerBoard.onMarkerSelected(idMarker, urlImage);
                }
            }

            MarkerBtn
            {
                id:markerEnnemy

                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.columnSpan: 1
                Layout.rowSpan: 1
                Layout.row: 1
                Layout.column: 0

                urlImage: "file:///" + ressourcesDirPath + "/Ressources/qmlRessources/WorldMap/Marker/MarkerEnnemy.png"
                idMarker: "MarkerEnnemy"

                onMarkerBtnSelected:
                {
                    markerBoard.onMarkerSelected(idMarker, urlImage);
                }
            }

            MarkerBtn
            {
                id:markerDungeon

                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.columnSpan: 1
                Layout.rowSpan: 1
                Layout.row: 1
                Layout.column: 1

                urlImage: "file:///" + ressourcesDirPath + "/Ressources/qmlRessources/WorldMap/Marker/MarkerDungeon.png"
                idMarker: "MarkerDungeon"

                onMarkerBtnSelected:
                {
                    markerBoard.onMarkerSelected(idMarker, urlImage);
                }
            }

            MarkerBtn
            {
                id:markerHolyPlace

                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.columnSpan: 1
                Layout.rowSpan: 1
                Layout.row: 2
                Layout.column: 0

                urlImage: "file:///" + ressourcesDirPath + "/Ressources/qmlRessources/WorldMap/Marker/MarkerHolyPlace.png"
                idMarker: "MarkerHolyPlace"

                onMarkerBtnSelected:
                {
                    markerBoard.onMarkerSelected(idMarker, urlImage);
                }
            }

            MarkerBtn
            {
                id:markerMountain

                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.columnSpan: 1
                Layout.rowSpan: 1
                Layout.row: 2
                Layout.column: 1

                urlImage: "file:///" + ressourcesDirPath + "/Ressources/qmlRessources/WorldMap/Marker/MarkerMountain.png"
                idMarker: "MarkerMountain"

                onMarkerBtnSelected:
                {
                    markerBoard.onMarkerSelected(idMarker, urlImage);
                }
            }

    }
}
