import QtQuick 2.0

Rectangle{

    id: markerBtn

    opacity: 0.5
    border.color : "mediumturquoise"
    border.width: 0

    property string urlImage: ""
    property string idMarker: ""

    Image
    {
        id: markerBtnImg

        width: parent.width
        height: parent.height

        source: markerBtn.urlImage
    }

    signal markerBtnSelected()// Selectionne le marker

    MouseArea
    {
        width: parent.width
        height: parent.height
        anchors.fill: parent
        hoverEnabled: true // Allow to cath event callback onEntered & onExited

        onPressed:
        {
            markerBtn.markerBtnSelected();
        }

        onEntered:
        {
            markerBtn.color = "palegoldenrod"
        }
        onExited:
        {
            markerBtn.color = "white"
        }
    }
}
