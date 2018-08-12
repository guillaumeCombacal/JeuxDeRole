import QtQuick 2.0

Image
{
    id: markerBtn

    property string urlImage: ""
    property string idMarker: ""

    source: urlImage

    signal markerBtnSelected()// Selectionne le marker

    MouseArea
    {
        width: parent.width
        height: parent.height
        anchors.fill: parent
        onPressed:
        {
            markerBtn.markerBtnSelected();
        }
    }
}
