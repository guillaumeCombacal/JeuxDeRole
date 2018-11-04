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

    property string title: ""

    MouseArea
    {
        width: parent.width
        height: parent.height
        anchors.fill: parent
        hoverEnabled: true // Allow to cath event callback onEntered & onExited

        onEntered:
        {
            infoMarker.visible = true;
        }
    }

    Rectangle
    {
        id: infoMarkerTitle

        width: parent.width
        height: parent.height / 5

        color: "white"

        TextEdit
        {
            id: textEditTitle

            anchors.fill:parent
            width:parent.width;
            height:parent.height

            FontLoader
            {
                    id: textEditTitleFont
                    source: "file:///" + ressourcesDirPath + "/Ressources/qmlRessources/WorldMap/MORPHEUS.ttf"
            }

            font.family: textEditTitleFont.name

            // Save the title text
            onTextChanged:
            {
                infoMarker.title = textEditTitle.text;
            }

            wrapMode: TextEdit.Wrap
        }
    }

    // Description Marker
        Rectangle
        {
            id: infoMarkerResume

            width: parent.width
            height: (parent.height / 5) * 4

            y: infoMarkerTitle.height

            color: "orange"

            Flickable
            {
                 id: flick

                 width: parent.width
                 height: parent.height
                 anchors.fill:parent

                 // Avoid to see the text out of the infoMarkerResume area
                 clip: true

                 // Allow to follow the cursor and set the area visible
                 function ensureVisible(r)
                 {
                     if (contentX >= r.x)
                     {
                         contentX = r.x;
                     }
                     else if (contentX+width <= r.x+r.width)
                     {
                        contentX = r.x+r.width-width;
                     }

                     if (contentY >= r.y)
                     {
                        contentY = r.y;
                     }
                     else if (contentY+height <= r.y+r.height)
                     {
                        contentY = r.y+r.height-height;
                     }

                 }

                TextEdit
                {
                    id: textEditResume

                    anchors.fill:parent
                    width:parent.width;
                    height:parent.height

                    focus: true

                    wrapMode: TextEdit.Wrap
                    onCursorRectangleChanged: flick.ensureVisible(cursorRectangle)
                }
            }
        }
}
