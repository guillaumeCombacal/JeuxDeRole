import QtQuick 2.0

// Pour Le composant Slider
import QtQuick.Controls 1.4


Rectangle
{
    id: optionBoard

    color: "black"
    opacity: 0.5

    signal zoomLevelChange(double zoomLevel)// Zoom the worldMap
    signal closeOptionBoard()// Close the option board


    // The Arrow To Disable The OptionBoard
    Rectangle
    {
        id: arrowClosingOptnBoard

        color: "transparent"
        height: 25
        width: 25
        anchors.margins: 5
        anchors.left: parent.left
        y:parent.height /2

        MouseArea
        {
            width: parent.width
            height: parent.height
            anchors.fill: parent

            onPressed:
            {
              optionBoard.closeOptionBoard();
            }
        }

        Image
        {
            height: parent.height
            width: parent.width
            rotation: 180
            source: "file:///" + applicationDirPath + "/../../JeuDeRole/Ressources/ImgTest/arrow.svg"
        }
    }

    // The Zoom Slider
    Slider
    {
        id: zoomSlider;

        minimumValue: 1;
        maximumValue: 3;

        anchors.margins: 10
        anchors.bottom: scale.top
        anchors.top: parent.top

        x: parent.width / 2 - zoomSlider.width / 2

        orientation : Qt.Horizontal

        onValueChanged: {
            if (value >= 0)
            {
                optionBoard.zoomLevelChange(value);
            }

        }

    }

    // The Marker Menu
    MarkerBoard
    {
        id: markerBoard

        width: parent.width - 2 * arrowClosingOptnBoard.width
        height: parent.width - arrowClosingOptnBoard.width

        y: parent.height /2
        x: arrowClosingOptnBoard.width + 5
    }

}
