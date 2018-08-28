import QtQuick 2.6
import QtQuick.Window 2.2

// Pour Le composant Map
import QtQuick.Controls 1.4
import QtLocation 5.6
import QtPositioning 5.5

//import classAnchor 1.0 // Permet d'importer la déclaration de la classe Anchor pour créer une référence dans le QML

//import "ModelDataWorldMap.js" as MarkerData;
//Components.utils.import//("resource://C:\Users\Yaku\Documents\DeveloppementCode\PROJECT\jeuxDeRole\JeuDeRole\QML\WorldMap\ModelDataWorldMap.js");


Item
{

    id: worldMap
    height: parent.height
    width : parent.width
    //color : "green"
    visible: true

    //zoomLevel: 1
    property double zoomLevel: 1

    // The Option Board
    OptionBoard
    {
        id: optionBoard

        width:parent.width / 4
        height: parent.height

        y:parent.height /2 - optionBoard.height / 2
        x:parent.width

        onZoomLevelChange:
        {
            // Zoom l image
            worldMap.zoomLevel = zoomLevel

            // Change la dimension de la flickable area contenant l'image
            flickMapArea.contentHeight = imgWorldMap.height * zoomLevel
            flickMapArea.contentWidth = imgWorldMap.width * zoomLevel
        }

        onCloseOptionBoard:
        {
            launcherMarkerBoard.opacity = 1;
            launcherMarkerBoard.enabled = true;

            optionBoard.x = parent.width

            flickMapArea.state = "FOCUS_ON_HERO";
        }

        onMarkerSelected:
        {
            if(flickMapArea.state !== "FOCUS_ON_MARKER")
            {
                flickMapArea.state = "FOCUS_ON_MARKER";
            }
            flickMapArea.urlImageMarker = urlImage;
            flickMapArea.idMarker = idMarker;
        }

        onLoadImgWorldMap:
        {
            imgWorldMap.source = urlImg;
        }
    }

// Component containing the image of the map
    Flickable
    {

        id: flickMapArea

        width: parent.width
        height: parent.height
        contentHeight: parent.width
        contentWidth: parent.height
        anchors.fill:parent
        interactive: true
        boundsBehavior: Flickable.StopAtBounds

        property string urlImageMarker: ""
        property string idMarker: ""

        // Tableau d'etat
        // Pour savoir ce que l'on fait sur la map (deplacement perso, ajout de marker, autre...)
        state: "FOCUS_ON_HERO"
        states:
            [
                State
                {
                    name: "FOCUS_ON_HERO"
                },
                State
                {
                    name: "FOCUS_ON_MARKER"
                }
            ]

        // Add Marker Component on the map
        function createMarkerObjects(xPos, yPos)
        {
            var component;
            var sprite;
            component = Qt.createComponent("Marker.qml");
            sprite = component.createObject(imgWorldMap, {"width": 50, "height": 50, urlImage: urlImageMarker, idMarker: idMarker});

            // Set the position of the image
            sprite.x = xPos / zoomLevel - sprite.width /2;
            sprite.y = yPos / zoomLevel - sprite.height /2;

            if (sprite === null)
            {
                // Error Handling
                console.log("Error creating object");
            }
        }

        Image
        {
            id: imgWorldMap

            source: "file:///" + applicationDirPath + "/../../JeuDeRole/Ressources/qmlRessources/Oriense_World_Map.png"
            transform: Scale{xScale: worldMap.zoomLevel; yScale: worldMap.zoomLevel}
        }

        MouseArea
        {
            width: parent.width
            height: parent.height
            anchors.fill: parent

            onPressed:
            {
                if(flickMapArea.state === "FOCUS_ON_HERO")
                {
                    console.log("Point = " + Qt.point(mouse.x, mouse.y));
                }
                if(flickMapArea.state === "FOCUS_ON_MARKER")
                {
                    console.log("Point = " + Qt.point(mouse.x, mouse.y));
                    flickMapArea.createMarkerObjects(mouse.x, mouse.y);
                    //console.log(MarkerData.currentIdMarker);
                }

            }
        }

    }

// Component to launch the marker Menu
    Rectangle
    {
        id: launcherMarkerBoard
        color: "transparent"
        height: 100
        width: 50
        anchors.margins: 5
        anchors.right: parent.right
        y:parent.height /2 - launcherMarkerBoard.height / 2

        MouseArea
        {
            width: parent.width
            height: parent.height
            anchors.fill: parent
            onPressed:
            {
              console.log("Open MARKER Menu !!! ")
                //Opacity 0 & disable
                launcherMarkerBoard.opacity = 0;
                launcherMarkerBoard.enabled = false;

                //Deplacement du menu d'option pour le faire apparaître
                optionBoard.x = worldMap.width - optionBoard.width;
                optionBoard.z = 1;
            }
        }

        Image
        {
            height: parent.height
            width: parent.width
            sourceSize.width: parent.width
            sourceSize.height: parent.height

            source: "file:///" + applicationDirPath + "/../../JeuDeRole/Ressources/ImgTest/arrow.svg"

        }
    }

}
