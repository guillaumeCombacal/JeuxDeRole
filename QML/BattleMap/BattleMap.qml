import QtQuick 2.6
import QtQuick.Window 2.2


import FrameBufferObject_OpenGL 1.0

// Pour Le composant GridLayout
import QtQuick.Layouts 1.1

// Component QLabel
import QtQuick.Controls 1.4

Rectangle
{
    id: battleMapCanvas
    height: parent.height
    width : parent.width
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

    Connections
    {
        target: interfaceComQML
        onCursorOnCharacter:
        {
            tileMenu.visible = interfaceComQML.isCursorOnCharacter;
        }
        onFeaturesCharacterChanged:
        {
            //Load the character face inside the menu
            tileImgMenu.changeImg(interfaceComQML.featuresCharacter["UrlImg"]);
            tileStatsMenu.changeStats(interfaceComQML.featuresCharacter["Name"],
                                      interfaceComQML.featuresCharacter["PV"], interfaceComQML.featuresCharacter["MaxPV"],
                                      interfaceComQML.featuresCharacter["PA"], interfaceComQML.featuresCharacter["MaxPA"],
                                      interfaceComQML.featuresCharacter["PM"],
                                      interfaceComQML.featuresCharacter["Xp"]);
        }

        onListCharacterToAddInBattleMapChanged:
        {
            listModelCharacter.append({"characterNameData": interfaceComQML.characterToAddInBattleMap[0], "color":"orange"})
            listModelCharacter.append({"characterNameData": interfaceComQML.characterToAddInBattleMap[1], "color":"orange"})
            listModelCharacter.append({"characterNameData": interfaceComQML.characterToAddInBattleMap[2], "color":"orange"})
        }
    }

    Rectangle
    {
        id: addCharacter
        width: parent.width/16
        height: parent.height/10
        x: parent.width - width
        y: parent.height - height
        color: "black"
        z: 1

        MouseArea
        {
            width: parent.width
            height: parent.height
            anchors.fill: parent

            onPressed:
            {
                if(addCharacterMenu.visible === false)
                {
                    // Setting become visible
                    addCharacterMenu.visible = true;
                }
            }
        }
    }

    Rectangle
    {
        id: addCharacterMenu
        width: parent.width/10
        height: parent.height/2
        x: parent.width - width
        y: parent.height - height
        color: "red"
        z: 1
        visible: false

        MouseArea
        {
            id:mouseListView
            width: parent.width
            height: parent.height
            anchors.fill: parent
            hoverEnabled: true // Allow to cath event callback onEntered & onExited
            acceptedButtons: Qt.LeftButton | Qt.RightButton

            onClicked:
            {
                addCharacterMenu.visible = false;
            }
        }

        Component
        {
            id: delegateComponentListCharacter

            Rectangle
            {
                id: characterElement

                width: parent.width
                height: addCharacterMenu.height / 6
                color: "white"

                Text
                {
                    id: characterNameTxt
                    property string characterName : characterNameData
                    text: characterNameData
                }

                MouseArea
                {
                    id:mouseSelectCharacter
                    width: parent.width
                    height: parent.height
                    anchors.fill: parent
                    hoverEnabled: true // Allow to cath event callback onEntered & onExited
                    acceptedButtons: Qt.LeftButton | Qt.RightButton

                    onPressed:
                    {
                        interfaceComQML.selectCharacterToAddInBattle(characterNameData);
                    }

                    onEntered:
                    {
                        characterElement.color = "palegoldenrod"
                    }
                    onExited:
                    {
                        characterElement.color = "white"
                    }
                }

            }
        }

        ListModel
        {
          id: listModelCharacter
        }

        Rectangle{
            id: containerListView
            width: parent.width
            height: parent.height - 40
            y: 40
            clip: true
            color: "black"

            ListView
            {
                width: parent.width
                height: parent.height
                model: listModelCharacter
                delegate: delegateComponentListCharacter
            }
        }



    }

    Rectangle
    {
        id: tileMenu
        width: parent.width/4
        height: parent.width/6
        x: 0
        y: parent.height - parent.width/6
        color: "transparent"
        visible : false
        z : 1

        Rectangle
        {
            id: tileImgMenu
            width: parent.width/2
            height: parent.height/2
            x: 0
            y: 0
            color: "transparent"

            function changeImg(urlImg)
            {
                imgTileImgMenu.source = "file:///" + ressourcesDirPath +  urlImg;
            }

            Image
            {
                id: imgTileImgMenu

                width: parent.width
                height: parent.height
            }
        }

        Rectangle
        {
            id: tileStatsMenu
            width: parent.width/2
            height: parent.height/2
            x: 0
            y: parent.height/2
            color: "orange"
            z : 1

            function changeStats(name, pv, maxPv, pa, maxPa, pm, xp)
            {
                labelNameCharacter.text = name;
                labelPVCharacter.pv = pv;
                labelPVCharacter.maxPv = maxPv;
                labelPACharacter.pa = pa;
                labelPACharacter.maxPa = maxPa;
                labelPMCharacter.pm = pm;
                labelXPCharacter.xp = xp;
            }

            Label
            {
                id: labelNameCharacter
                text: "Name"
                font.pixelSize: 22
                color: "black"
            }


            Label
            {
                id: labelPVCharacter
                text: "PV : "+ pv + " / " + maxPv
                font.pixelSize: 11
                color: "black"
                property string pv: ""
                property string maxPv: ""
                y: labelNameCharacter.height
            }
//            ProgressBar
//            {
//                id: progressBarPV
//                width: parent.width/3
//                height: parent.height/20
//                x: labelPVCharacter.x + labelPVCharacter.width
//                y: labelPVCharacter.y + height/2
//            }


            Label
            {
                id: labelPACharacter
                text: "PA : " + pa + " / " + maxPa
                font.pixelSize: 11
                color: "black"
                property string pa: ""
                property string maxPa: ""
                y: labelPVCharacter.height + labelNameCharacter.height
            }
//            ProgressBar
//            {
//                id: progressBarPA
//                width: parent.width/3
//                height: parent.height/20
//                x: labelPACharacter.x + labelPACharacter.width
//                y: labelPACharacter.y + height/2
//            }


            Label
            {
                id: labelPMCharacter
                text: "PM : " + pm
                font.pixelSize: 11
                color: "black"
                property string pm: ""
                y: labelPVCharacter.height + labelNameCharacter.height + labelPACharacter.height
            }

            Label
            {
                id: labelXPCharacter
                text: "XP : " + xp
                font.pixelSize: 11
                color: "black"
                property string xp: ""
                y: labelPVCharacter.height + labelNameCharacter.height + labelPACharacter.height + labelPMCharacter.height
            }
        }

        Rectangle
        {
            id: tileActionMenu
            width: parent.width/2
            height: parent.height/2
            x: parent.width/2
            y: 0
            color: "blue"
            z : 1

            GridLayout
            {
                id: gridActionMenu
                anchors.fill: parent
                rows: 2
                columns: 2

                Rectangle
                {
                    id:btnMove

                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.columnSpan: 1
                    Layout.rowSpan: 1
                    Layout.row: 0
                    Layout.column: 0
                    color: "green"

                    //urlImage: "file:///" + ressourcesDirPath + "/Ressources/qmlRessources/WorldMap/Marker/MarkerQuest.png"

//                    onMarkerBtnSelected:
//                    {
//                        markerBoard.onMarkerSelected(idMarker, urlImage);
//                    }
                }

                Rectangle
                {
                    id:btnFight

                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.columnSpan: 1
                    Layout.rowSpan: 1
                    Layout.row: 0
                    Layout.column: 1
                    color: "white"

                    Label
                    {
                        id: labelBtnFight
                        text: "Fight"
                        font.pixelSize: 22
                        color: "black"
                    }

                    MouseArea
                    {
                        id:mouseAreaFight
                        width: parent.width
                        height: parent.height
                        anchors.fill: parent
                        hoverEnabled: true // Allow to cath event callback onEntered & onExited
                        acceptedButtons: Qt.LeftButton | Qt.RightButton
                        onPressed:
                        {
                            interfaceComQML.fightRequest();
                        }
                    }
                }

                Rectangle
                {
                    id:btnOrientation

                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.columnSpan: 1
                    Layout.rowSpan: 1
                    Layout.row: 1
                    Layout.column: 0
                    color: "grey"

                    Label
                    {
                        id: labelBtnOrientation
                        text: "Orientation"
                        font.pixelSize: 22
                        color: "black"
                    }

                    MouseArea
                    {
                        id:mouseAreaOrientation
                        width: parent.width
                        height: parent.height
                        anchors.fill: parent
                        hoverEnabled: true // Allow to cath event callback onEntered & onExited
                        acceptedButtons: Qt.LeftButton | Qt.RightButton
                        onPressed:
                        {
                            interfaceComQML.orientationRequest();
                        }
                    }
                }
           }
        }

        Rectangle
        {
            id: tileListActionMenu
            width: parent.width/2
            height: parent.height/2
            x: parent.width/2
            y: parent.height/2
            color: "black"
            z : 1

            MouseArea
            {
                id:mouseAreaTileMenu
                width: parent.width
                height: parent.height
                anchors.fill: parent
                hoverEnabled: true // Allow to cath event callback onEntered & onExited
                acceptedButtons: Qt.LeftButton | Qt.RightButton
                onPressed:
                {
                    console.log("Click tileListActionMenu");
                }
            }
        }
    }

    OpenGLView
    {
        id: openGLRenderer
        anchors.fill: parent
    }
}
