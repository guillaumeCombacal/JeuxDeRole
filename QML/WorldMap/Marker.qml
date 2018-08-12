import QtQuick 2.0

Image
{

    property string urlImage: ""
    property string typeMarker: ""

    source: urlImage

    // Lorsque l'on clique sur le marker on a des info et la possibilité de le supprimer
    MouseArea
    {
        width: parent.width
        height: parent.height
        anchors.fill: parent
        onPressed:
        {
          console.log("Marker " + typeMarker);
        }
    }
}
