import QtQuick 2.0

Rectangle
{
    id: marker

    color: "transparent"

    z: 1

    property string urlImage: ""
    property string idMarker: ""

    state: "DEFAULT"
    states:
        [
            State
            {
                name: "DEFAULT"
            },
            State
            {
                name: "HOVERED"
            }
        ]

    signal deleteMarker(string idMarker, int x, int y)// Return data to identify the marker

    Image
    {
        id: markerImg

        width: parent.width
        height: parent.height

        source: marker.urlImage
    }

    // Lorsque l'on clique sur le marker on a des info et la possibilité de le supprimer
    MouseArea
    {
        id:mouseAreaMarker

        width: parent.width
        height: parent.height
        anchors.fill: parent

        hoverEnabled: true // Allow to cath event callback onEntered & onExited

        acceptedButtons: Qt.LeftButton | Qt.RightButton

        onPressed:
        {

            if (mouseAreaMarker.pressedButtons & Qt.RightButton)// ClickDroit
            {
                // Destroy the Marker Component
                marker.destroy();

                // Destroy the Marker Obj
                var markerXPos = marker.x;
                var markerYPos = marker.y;

                // Calcule the offset
                if(marker.state === "HOVERED")
                {
                    var offsetX = (marker.width - (marker.width / 1.5)) / 2;
                    var offsetY = (marker.width - (marker.width / 1.5)) / 2;

                    markerXPos = markerXPos + offsetX;
                    markerYPos = markerYPos + offsetY;
                }

                deleteMarker(marker.idMarker, markerXPos, markerYPos);
            }
            else if (mouseAreaMarker.pressedButtons === Qt.LeftButton)
            {
                        console.log("left-button pressed")
            }
        }


        onDoubleClicked:
        {
            infoMarkerTitle.visible = false
            infoMarker.visible = true;
        }

        onEntered:
        {
            // Get current width and height
            var offsetX = marker.width;
            var offsetY = marker.height;

            // Grow up the Marker
            marker.width = marker.width * 1.5;
            marker.height = marker.height * 1.5;

            offsetX = (marker.width - offsetX) / 2;
            offsetY = (marker.height - offsetY) / 2;

            marker.x = marker.x - offsetX;
            marker.y = marker.y - offsetY;

            // Title is visible
            infoMarkerTitle.visible = true;

            marker.state = "HOVERED";
        }
        onExited:
        {
            // Get current width and height
            var offsetX = marker.width;
            var offsetY = marker.height;

            // Reduce the Marker size
            marker.width = marker.width / 1.5;
            marker.height = marker.height / 1.5;

            offsetX = (offsetX - marker.width) / 2;
            offsetY = (offsetY - marker.height) / 2;

            marker.x = marker.x + offsetX;
            marker.y = marker.y + offsetY;

            // Infos are not visible anymore
            infoMarkerTitle.visible = false;

            // Disable Edit Info
            if(infoMarker.visible === true)
            {
                infoMarker.visible = false;
            }

            marker.state = "DEFAULT";
        }

        InfoMarker
        {
            id:infoMarker

            x: parent.x - (infoMarker.width / 2) + (parent.width / 2)
            y: parent.y - infoMarker.height

            visible: false

        }

        Rectangle
        {
            id: infoMarkerTitle

            width:100
            height: 20

            x: parent.x - infoMarkerTitle.width / 4
            y: parent.y - infoMarkerTitle.height

            color:"white"
            opacity: 0.7

            Text
            {
                FontLoader
                {
                        id: textTitle
                        source: "file:///" + ressourcesDirPath + "/Ressources/qmlRessources/WorldMap/MORPHEUS.ttf"
                }

                font.family: textTitle.name

                text: infoMarker.title
            }

        }
    }

}
