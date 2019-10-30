import QtQuick 2.6
import QtQuick.Window 2.2


import FrameBufferObject_OpenGL 1.0

//import "QML"

//import classAnchor 1.0 // Pemet d'importer la déclaration de la classe Anchor pour créer une référence dans le QML

Rectangle
{
    id: battleMapCanvas
    height: parent.height
    width : parent.width
    //color : "red"
    visible: true

    focus : true
    Keys.onPressed:
    {
        switch (event.key)
        {
            case Qt.Key_Return :
                interfaceComQML.eventKeyboardFromQML(0);
                break;
            case Qt.Key_Backspace:
                interfaceComQML.eventKeyboardFromQML(1);
                break;
            case Qt.Key_Left:
                interfaceComQML.eventKeyboardFromQML(2);
                break;
            case Qt.Key_Right:
                interfaceComQML.eventKeyboardFromQML(3);
                break;
            case Qt.Key_Up :
                interfaceComQML.eventKeyboardFromQML(4);
                break;
            case Qt.Key_Down :
                interfaceComQML.eventKeyboardFromQML(5);
                break;
            default:
            break;
        }

    }


    Rectangle
    {
        id: timeline
        width: 2*(parent.width/4)
        height: parent.height/10
        x: parent.width/4
        y: parent.height - parent.height/10
        color: "red"
        z : 1

        MouseArea
        {
            id:mouseAreaTimeline
            width: parent.width
            height: parent.height
            anchors.fill: parent
            hoverEnabled: true // Allow to cath event callback onEntered & onExited
            acceptedButtons: Qt.LeftButton | Qt.RightButton
            onPressed:
            {
                console.log("Click MouseArea");
            }
        }
    }

    Rectangle
    {
        id: heroTimelineMenu
        width: parent.width/4
        height: parent.width/6
        x: 0
        y: parent.height - parent.width/6
        color: "blue"
        z : 1

        MouseArea
        {
            id:mouseAreaheroTimelineMenu
            width: parent.width
            height: parent.height
            anchors.fill: parent
            hoverEnabled: true // Allow to cath event callback onEntered & onExited
            acceptedButtons: Qt.LeftButton | Qt.RightButton
            onPressed:
            {
                console.log("Click heroTimelineMenu");
            }
        }
    }

    OpenGLView
    {
        id: openGLRenderer
        anchors.fill: parent
    }
}
