import QtQuick 2.0

Rectangle
{
    id: infoMarker

    width:100
    height: 100

    x: parent.x - (infoMarker.width / 4)
    y: parent.y - infoMarker.height - (parent.height / 4)

    color:"white"
    opacity: 0.5

    Rectangle
    {
        id: infoMarkerTitle

        width: parent.width
        height: parent.height / 5

        color: "white"

        state: "DISPLAYING"
        states:
            [
                State

                {
                    name: "DISPLAYING"
                },
                State
                {
                    name: "EDITING"
                }
            ]

        TextEdit
        {
            id: textEditTitle

            anchors.fill:parent
            width:parent.width;
            height:parent.height

            //enabled: false

            FontLoader
            {
                    id: textEditTitleFont
                    source: "file:///" + ressourcesDirPath + "/Ressources/qmlRessources/WorldMap/MORPHEUS.ttf"
            }

            font.family: textEditTitleFont.name

            wrapMode: TextEdit.Wrap
        }

        /*MouseArea
        {
            id: mouseAreaInfoTitle

            anchors.fill:parent
            width:parent.width
            height:parent.height

            onPressed:
            {
                console.log("mouseAreaInfoTitle Pressed");

                //if
            }
        }*/
    }

    // Description Marker
    Rectangle
    {
        id: infoMarkerResume

        width: parent.width
        height: (parent.height / 5) * 4

        y: infoMarkerTitle.height

        color: "orange"

        TextEdit
        {
            id: textEditResume

            anchors.fill:parent
            width:parent.width;
            height:parent.height

            //color:"white"
            //focus: true

            //wrapMode: TextEdit.Wrap

            //onCursorRectangleChanged: flickArea.ensureVisible(cursorRectangle)
        }
    }


}
