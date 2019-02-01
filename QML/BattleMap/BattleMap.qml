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

    OpenGLView
    {
        id: openGLRenderer
        anchors.fill: parent
    }
}
