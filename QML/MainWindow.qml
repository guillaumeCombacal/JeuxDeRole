import QtQuick 2.0

import "CommonMenu/SettingMenu"
import "CommonMenu/MusicPlayer"
import "CommonMenu/NavMenu"

import "WorldMap"
import "HeroMenu"
import "BattleMap"


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
                    battleMap.visible = false;
                    worldMap.visible = true;
                    worldMap.restartHeroSprite();
                }
                else if(component === "HeroMenu")
                {
                    worldMap.visible = false;
                    battleMap.visible = false;
                    heroMenu.visible = true;
                    //worldMap.restartHeroSprite();
                }
                else if(component === "BattleMenu")
                {
                    worldMap.visible = false;
                    heroMenu.visible = false;
                    battleMap.visible = true;
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

        BattleMap
        {
            id: battleMap
            visible: false
        }

    }
}

