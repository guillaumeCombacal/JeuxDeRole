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
    height: 150
    width: 100

    color:"white"
    opacity: 0.8

    function markerSelected(idMarker)
    {
        console.log(idMarker + " Pressed");
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
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.columnSpan: 1
                Layout.rowSpan: 1
                Layout.row: 0
                Layout.column: 0

                urlImage: "file:///" + applicationDirPath + "/../../JeuDeRole/Ressources/ImgTest/Marker/MarkerQuest.png"
                idMarker: "MarkerQuest"

                onMarkerBtnSelected:
                {
                    markerBoard.markerSelected(idMarker);
                }
            }

            MarkerBtn
            {
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.columnSpan: 1
                Layout.rowSpan: 1
                Layout.row: 0
                Layout.column: 1

                urlImage: "file:///" + applicationDirPath + "/../../JeuDeRole/Ressources/ImgTest/Marker/MarkerTown.png"
                idMarker: "MarkerTown"

                onMarkerBtnSelected:
                {
                    markerBoard.markerSelected(idMarker);
                }
            }

            MarkerBtn
            {
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.columnSpan: 1
                Layout.rowSpan: 1
                Layout.row: 1
                Layout.column: 0

                urlImage: "file:///" + applicationDirPath + "/../../JeuDeRole/Ressources/ImgTest/Marker/MarkerEnnemy.png"
                idMarker: "MarkerEnnemy"

                onMarkerBtnSelected:
                {
                    markerBoard.markerSelected(idMarker);
                }
            }

            MarkerBtn
            {
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.columnSpan: 1
                Layout.rowSpan: 1
                Layout.row: 1
                Layout.column: 1

                urlImage: "file:///" + applicationDirPath + "/../../JeuDeRole/Ressources/ImgTest/Marker/MarkerDungeon.png"
                idMarker: "MarkerDungeon"

                onMarkerBtnSelected:
                {
                    markerBoard.markerSelected(idMarker);
                }
            }

            MarkerBtn
            {
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.columnSpan: 1
                Layout.rowSpan: 1
                Layout.row: 2
                Layout.column: 0

                urlImage: "file:///" + applicationDirPath + "/../../JeuDeRole/Ressources/ImgTest/Marker/MarkerHolyPlace.png"
                idMarker: "MarkerHolyPlace"

                onMarkerBtnSelected:
                {
                    markerBoard.markerSelected(idMarker);
                }
            }

            MarkerBtn
            {
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.columnSpan: 1
                Layout.rowSpan: 1
                Layout.row: 2
                Layout.column: 1

                urlImage: "file:///" + applicationDirPath + "/../../JeuDeRole/Ressources/ImgTest/Marker/MarkerMountain.png"
                idMarker: "MarkerMountain"

                onMarkerBtnSelected:
                {
                    markerBoard.markerSelected(idMarker);
                }
            }

    }
}
