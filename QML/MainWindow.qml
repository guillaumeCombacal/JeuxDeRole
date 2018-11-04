import QtQuick 2.0

import "CommonMenu/SettingMenu"
import "CommonMenu/MusicPlayer"
import "CommonMenu/NavMenu"

import "WorldMap"

import "HeroMenu"

Item
{
    id: mainWindow

    height: parent.height
    width : parent.width

    visible: true

    signal quit()

    Rectangle
    {
        id: gameView

        height: parent.height
        width : parent.width
        //color : "green"

        SettingMenu
        {
            id: settingMenu
            z: 1
        }

        NavMenu
        {
            id: navMenu
            z: 1

            onSwitchMenu:
            {
                if(component === "WorldMap")
                {
                    heroMenu.visible = false;
                    worldMap.visible = true;
                    worldMap.restartHeroSprite();
                }
                else if(component === "HeroMenu")
                {
                    worldMap.visible = false;
                    heroMenu.visible = true;
                    worldMap.restartHeroSprite();
                }
                else if(component === "QuestMenu")
                {

                }

            }
        }

        MusicPlayer
        {
            id: musicPlayer

            parentWidth: parent.width
            parentHeight: parent.height

            z: 1
        }

        HeroMenu
        {
            id: heroMenu

            visible: false
        }

        WorldMap
        {
            id: worldMap

            visible: true
        }

    }
}

