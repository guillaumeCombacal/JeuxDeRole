import QtQuick 2.0

// Component QLabel
import QtQuick.Controls 1.4

// Component MediaPlayer
import QtMultimedia 5.8

Rectangle
{
    id: playerMenu

    width: parent.width / 3
    height: parent.height

    x: 2 * (parent.width / 3)

    color: "black"

    signal pushPlayMusicBtn(string musicName)

    function changeCurrentMusicName(musicName)
    {
        labelCurrentMusicName.text = musicName;
    }

    function setUrlMusic(urlMusic)
    {
        if(mediaPlayer.source !== urlMusic)
        {
            mediaPlayer.source = urlMusic;
        }
    }

    function playMusic()
    {
        if(mediaPlayer.source !== "")
        {
            mediaPlayer.play();
        }
    }

    // The Media Player for music
    MediaPlayer
    {
        id: mediaPlayer

        source: ""
    }

    // LABEL NAME OF THE CURRENT MUSIC NAME
    Rectangle
    {
        id: currentMusicName

        width: parent.width
        height: parent.height / 6

        z: 1

        Label
        {
            /*FontLoader
            {
                    id: labelFont
                    source: "file:///" + ressourcesDirPath + "/Ressources/qmlRessources/WorldMap/MORPHEUS.ttf"
            }*/

            id: labelCurrentMusicName
            text: ""
            font.pixelSize: 15
            //font.family: labelFont.name
            color: "black"

            //width: parent.width

            x: parent.width / 2 - labelCurrentMusicName.width / 2
        }
    }

    // BTN PLAY
    Rectangle
    {
        id: playBtn

        height: 50
        width: 50

        x: (parent.width / 2) - (playBtn.width / 2)
        y: (parent.height / 2) - (playBtn.height / 2)

        MouseArea
        {
            height: parent.height
            width: parent.width

            onClicked:
            {
                if(labelCurrentMusicName.text !== "")
                {
                    pushPlayMusicBtn(labelCurrentMusicName.text);
                }
            }
        }
    }

}
