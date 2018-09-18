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
            source: "file:///" + ressourcesDirPath + "/Ressources/qmlRessources/WorldMap/arrow.svg"
        }
    }

    // ZOOM ///////////////////////////////////////////////////////////////////////////////////////////////
    //*****************************************************************************************************

    // Label Slider - Zoom Level
    Label
    {
        FontLoader
        {
                id: labelFont
                source: "file:///" + ressourcesDirPath + "/Ressources/qmlRessources/WorldMap/MORPHEUS.ttf"
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

        onValueChanged:
        {
            if (value >= 0)
            {
                optionBoard.zoomLevelChange(value);
            }

            // Set the text value
            var newValue = Math.round(value * 100)/100;
            labelZoomLevelValue.text = newValue;

            // Label value following the cursor with %
            var purcentValue = (value - 1) / (zoomSlider.maximumValue - 1);
            labelZoomLevelValue.x = zoomSlider.width * purcentValue;


            //var sliderWidth = zoomSlider.width - (zoomSlider.width / 3);
            //var offsetX = zoomSlider.width * (value / zoomSlider.maximumValue);
            //labelZoomLevelValue.x = offsetX - ((zoomSlider.width / 3) * (value / zoomSlider.maximumValue));// because zoom begin at 1
        }

        // Info bulle zoomLevel Label
        Label
        {
            id: labelZoomLevelValue
            text: ""
            font.pixelSize: 22
            font.family: labelZoomLevelValueFont.name
            color: "white"

            y: zoomSlider.height

            FontLoader
            {
                    id: labelZoomLevelValueFont
                    source: "file:///" + ressourcesDirPath + "/Ressources/qmlRessources/WorldMap/MORPHEUS.ttf"
            }
        }

        // INfo Bulle
        /*ToolTip
        {
            parent: zoomSlider.handle
            visible: zoomSlider.pressed
            text: zoomSlider.value.toFixed(1)
        }*/

    }
    //*****************************************************************************************************

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
                    source: "file:///" + ressourcesDirPath + "/Ressources/qmlRessources/WorldMap/MORPHEUS.ttf"
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
