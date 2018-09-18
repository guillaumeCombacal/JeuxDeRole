import QtQuick 2.6
import QtQuick.Window 2.2

// Pour Le composant Map
import QtQuick.Controls 1.4
import QtLocation 5.6
import QtPositioning 5.5

//import classAnchor 1.0 // Permet d'importer la déclaration de la classe Anchor pour créer une référence dans le QML

import "ModelDataWorldMap.js" as MarkerData;

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

            // Init x and y offset
            var xOffset = imgWorldMap.width;
            var yOffset = imgWorldMap.height;

            // Change la dimension de la flickable area contenant l'image
            flickMapArea.contentHeight = imgWorldMap.height * zoomLevel
            flickMapArea.contentWidth = imgWorldMap.width * zoomLevel
        }

        onCloseOptionBoard:
        {
            launcherMarkerBoard.opacity = 1;
            launcherMarkerBoard.enabled = true;

            optionBoard.x = parent.width

            flickMapArea.state = "FOCUS_ON_MAP";
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
        state: "FOCUS_ON_MAP"
        states:
            [
                State
                {
                    name: "FOCUS_ON_MAP"
                },
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
            // Create a new Marker component
            var component;
            var sprite;
            component = Qt.createComponent("Marker.qml");
            sprite = component.createObject(imgWorldMap, {"width": imgWorldMap.width/50, "height": imgWorldMap.width/50, urlImage: urlImageMarker, idMarker: flickMapArea.idMarker});

            // Set the position of the Marker component
            sprite.x = xPos / zoomLevel - sprite.width /2;
            sprite.y = yPos / zoomLevel - sprite.height /2;

            // Create a Marker object and add it in a vector
            var newMarker = new MarkerData.Marker(Math.floor(sprite.x), Math.floor(sprite.y), flickMapArea.idMarker, urlImageMarker);
            MarkerData.vectMarker.push(newMarker);

            // Connect the destruction of the Marker with the callback
            sprite.deleteMarker.connect(onDeleteMarker);

        }

        // Destroy the Marker from the vector
        function onDeleteMarker(idMarker, x, y)
        {
            for(var i = 0; i<MarkerData.vectMarker.length; i++)
            {
                if(idMarker === MarkerData.vectMarker[i].getIdMarker())
                {
                    if(x === Math.floor(MarkerData.vectMarker[i].getMarkerXPosition()))
                    {
                        MarkerData.vectMarker.splice(i, 1);// Destroy 1 element from element i

                        console.log("Victory");
                        console.log("*******");
                    }
                };
            }

        }

        Image
        {
            id: imgWorldMap

            // z = 1 for image allows at all sprites on image to get the focus
            z:1

            source: "file:///" + ressourcesDirPath + "/Ressources/qmlRessources/WorldMap/Oriense_World_Map.png"

            transform: Scale{xScale: worldMap.zoomLevel; yScale: worldMap.zoomLevel}

            SpriteHero
            {
                id: spriteAnimation
                width : imgWorldMap.width / 25
                height : imgWorldMap.width / 25 + ((imgWorldMap.width / 25) / 3)
            }
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
                    // Move the sprite
                    spriteAnimation.moveHero(mouse.x, mouse.y, worldMap.zoomLevel);
                }
                if(flickMapArea.state === "FOCUS_ON_MARKER")
                {
                    flickMapArea.createMarkerObjects(mouse.x, mouse.y);
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

            source: "file:///" + ressourcesDirPath + "/Ressources/qmlRessources/WorldMap/arrow.png"

        }
    }

}
