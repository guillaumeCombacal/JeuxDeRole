import QtQuick 2.0

// Pour ouvrir Hero Menu ou quest Menu
Rectangle
{
    id: launcherNavMenu

    height: 30
    width: 100

    x: (parent.width / 2) - (launcherNavMenu.width / 2)

    color: "grey"

    signal switchMenu(string component)// Signal to switch on anothe Menu


    MouseArea
    {
        width: parent.width
        height: parent.height
        anchors.fill: parent
        hoverEnabled: true // Allow to cath event callback onEntered & onExited

        // When the user get in the area
        onEntered:
        {
            navMenu.visible = true;
        }
    }

    Rectangle
    {
        id: navMenu

        height: 50
        width: 200

        x: - ((navMenu.width - launcherNavMenu.width) / 2)// Center in function of the launcherNavMenu width

        visible: false

        color: "purple"

        MouseArea
        {
            width: parent.width
            height: parent.height
            anchors.fill: parent
            hoverEnabled: true // Allow to cath event callback onEntered & onExited

            // When the user get in the area
            onExited:
            {
                navMenu.visible = false;
            }
        }

        Rectangle
        {
            id: launchWorldMap

            width: parent.width / 3
            height: parent.height

            color: "yellow"

            MouseArea
            {
                width: parent.width
                height: parent.height
                anchors.fill: parent

                // Send the signal to switch on World Map
                onPressed:
                {
                    launcherNavMenu.switchMenu("WorldMap");
                }
            }

        }

        Rectangle
        {
            id: launchMenuHero

            width: parent.width / 3
            height: parent.height

            x: launchWorldMap.width // offset function of launchMenuHero

            color: "blue"

            MouseArea
            {
                width: parent.width
                height: parent.height
                anchors.fill: parent

                // Send the signal to switch on Hero Menu
                onPressed:
                {
                    launcherNavMenu.switchMenu("HeroMenu");
                }
            }

        }

        Rectangle
        {
            id: launchMenuQuest

            width: parent.width / 3
            height: parent.height

            x: launchWorldMap.width + launchMenuHero.width// offset function of launchMenuHero

            color: "green"

            MouseArea
            {
                width: parent.width
                height: parent.height
                anchors.fill: parent

                // Send the signal to switch on Quest Menu
                onPressed:
                {
                    launcherNavMenu.switchMenu("QuestMenu");
                }
            }

        }
    }
}
