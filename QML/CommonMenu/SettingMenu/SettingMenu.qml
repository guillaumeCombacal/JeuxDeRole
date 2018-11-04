import QtQuick 2.0

// Pour Le composant Label
import QtQuick.Controls 1.4


Rectangle
{
    id: settingMenu

    width: 50
    height: 50

    color: "red"

    MouseArea
    {
        width: parent.width
        height: parent.height
        anchors.fill: parent

        onPressed:
        {
            if(settings.visible === false)
            {
                // Setting become visible
                settings.visible = true;
            }
        }
    }

    // Setting Btn Layout
    Rectangle
    {
        id: settings

        width: 100
        height: 200

        //color: "blue"

        visible: false

        MouseArea
        {
            width: parent.width
            height: parent.height
            anchors.fill: parent
            hoverEnabled: true // Allow to cath event callback onEntered & onExited

            // When the user get out of the area, it becomes invisible
            onExited:
            {
                settings.visible = false;
            }
        }

        // Btn Save Game
        Rectangle
        {
            id: btnSaveGame

            width: parent.width
            height: parent.height / 3

            color: "blue"

            Label
            {
                text: "Save Game"
            }

            MouseArea
            {
                width: parent.width
                height: parent.height
                anchors.fill: parent

                onPressed:
                {
                    console.log("Save Game !!!");

                }
            }
        }

        // Btn Load Game
        Rectangle
        {
            id: btnLoadGame

            width: parent.width
            height: parent.height / 3

            y : parent.height / 3

            color: "green"

            Label
            {
                text: "Load Game"
            }

            MouseArea
            {
                width: parent.width
                height: parent.height
                anchors.fill: parent

                onPressed:
                {
                    console.log("Load Game !!!");

                }
            }
        }

        // Btn Quit
        Rectangle
        {
            id: btnQuitAppli

            width: parent.width
            height: parent.height / 3

            y : 2 * (parent.height / 3)

            color: "grey"

            Label
            {
                text: "Quit"
            }

            MouseArea
            {
                width: parent.width
                height: parent.height
                anchors.fill: parent

                onPressed:
                {
                    console.log("Quit Game !!!");
                    Qt.quit();

                }
            }
        }

    }

}
