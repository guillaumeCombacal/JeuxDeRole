import QtQuick 2.0

// Pour Le composant Slider
import QtQuick.Controls 1.4

// Pour le composant fileDialog
import QtQuick.Dialogs 1.0


Rectangle
{
    id: optionBoard

    color: "black"
    opacity: 0.5

    signal zoomLevelChange(double zoomLevel)// Zoom the worldMap
    signal closeOptionBoard()// Close the option board
    signal markerSelected(string idMarker, string urlImage)// Propage vers WorldMap qu'un marker a été sélectionné
    signal loadImgWorldMap(string urlImg)// Load Url Img  for the WorldMap


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
              markerBoard.allMarkerUnselected();
              markerBoard.isMarkerSelected = false;
            }
        }

        Image
        {
            height: parent.height
            width: parent.width
            rotation: 180
            source: "file:///" + applicationDirPath + "/../../JeuDeRole/Ressources/qmlRessources/arrow.svg"
        }
    }

    // Label Slider - Zoom Level
    Label
    {
        FontLoader
        {
                id: labelFont
                source: "file:///" + applicationDirPath + "/../../JeuDeRole/Ressources/qmlRessources/MORPHEUS.ttf"
        }

        id: labelZoomLevel
        text: "Zoom Level"
        font.pixelSize: 22
        font.family: labelFont.name
        color: "white"

        x: parent.width / 2 - zoomSlider.width / 2
    }

    // The Zoom Slider
    Slider
    {
        id: zoomSlider;

        minimumValue: 1;
        maximumValue: 3;

        anchors.margins: 10
        //anchors.bottom: scale.top
        //anchors.top: parent.top

        x: parent.width / 2 - zoomSlider.width / 2
        y: labelZoomLevel.height

        orientation : Qt.Horizontal

        onValueChanged: {
            if (value >= 0)
            {
                optionBoard.zoomLevelChange(value);
            }

        }

    }

    // Btn Load Img Map
    Rectangle
    {
        id:btnLoadMap

        x: parent.width/2 - btnLoadMap.width/2
        y: parent.height / 5

        width: 200
        height: 30


        Text
        {
            id: textBtnLoadMap
            text: "Charger une Map"
            font.pixelSize: 22
            font.family: textFont.name
            color: "black"

            anchors.horizontalCenter: parent.horizontalCenter

            FontLoader
            {
                    id: textFont
                    source: "file:///" + applicationDirPath + "/../../JeuDeRole/Ressources/qmlRessources/MORPHEUS.ttf"
            }
        }

        MouseArea
        {
            width: parent.width
            height: parent.height
            anchors.fill: parent

            hoverEnabled: true // Allow to cath event callback onEntered & onExited

            onPressed:
            {
                console.log("onPressed");
                //fileDialog.visible = true;
                fileDialog.open();
            }

            onEntered:
            {
                btnLoadMap.color = "palegoldenrod"
            }
            onExited:
            {
                btnLoadMap.color = "white"
            }
        }
    }

    FileDialog
    {
        id: fileDialog
        title: "Please choose a file"
        folder: shortcuts.home
        nameFilters: [ "Image files (*.jpg *.png)", "All files (*)" ]

        onAccepted:
        {
            console.log("You chose: " + fileDialog.fileUrls)
            optionBoard.loadImgWorldMap(fileDialog.fileUrls);
            Qt.quit()
        }
        onRejected:
        {
            console.log("Canceled")
            Qt.quit()
        }
        Component.onCompleted: visible = false
    }

    // The Marker Menu
    MarkerBoard
    {
        id: markerBoard

        width: parent.width - 2 * arrowClosingOptnBoard.width
        height: parent.height / 2 - arrowClosingOptnBoard.width

        y: parent.height /2
        x: arrowClosingOptnBoard.width + 5

        onMarkerSelected:
        {
            if(markerBoard.isMarkerSelected)
            {
                optionBoard.markerSelected(idMarker, urlImage);
            }
        }
    }

}
