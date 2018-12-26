import QtQuick 2.0

// Component QLabel
import QtQuick.Controls 1.4

// Component SliderStyle
import QtQuick.Controls.Styles 1.4

// Component MediaPlayer
import QtMultimedia 5.8

Rectangle
{
    id: playerMenu

    width: parent.width / 3
    height: parent.height

    x: 2 * (parent.width / 3)

    color: "white"

    signal signalPushPlayMusicBtn()
    signal signalBtnNextMusic()
    signal signalBtnNextRandomMusic(int randomIndex)
    signal signalBtnPreviousMusic()

    // Change the label for the current music played
    // Set the index of the music played for the playlist
    function changeSelectedMusic(musicName, index)
    {
        labelCurrentMusicName.text = musicName;
        //currentPlaylist.currentIndex = index;

        // If a music was playing, it's stopped to play the new selected music
        if(mediaPlayer.isMusicPlaying)
        {
            mediaPlayer.stop();
        }
    }

    // Add a music in the media player's playlist
    function addMusicInPlaylist(musicName)
    {
        currentPlaylist.addItem(musicName);
    }

    // Remove all music from the playlist, used when we change the playlist to reset the media player's playlist
    function removeAllMusicsInPlaylist()
    {
        currentPlaylist.removeItems(0, currentPlaylist.itemCount)
    }


    function setUrlMusic(urlMusic)
    {
        if(mediaPlayer.source !== urlMusic)
        {
            //mediaPlayer.source = urlMusic;
        }
    }

    // Play the source frome url currentPlaylistIndex
    function playMusic(indexMusicSelected)
    {
        currentPlaylist.currentIndexMusicPlayed = indexMusicSelected;

        mediaPlayer.source = currentPlaylist.itemSource(currentPlaylist.currentIndexMusicPlayed)

        if(mediaPlayer.source !== "")
        {
            mediaPlayer.play();
        }
    }

    // Pause the music, and change the state of the button
    function pauseMusic()
    {
        if(mediaPlayer.source !== "")
        {
            mediaPlayer.pause();
        }
    }

    // MEDIA PLAYER
    MediaPlayer
    {
        id: mediaPlayer

        property bool isMusicPlaying: false
        property bool isLoopReadingActivated: false
        property bool isRandomReadingActivated: false

        playlist: Playlist
                  {
                      id: currentPlaylist

                      property int currentIndexMusicPlayed: 0
                  }

        // Event received when the music is playing
        onPlaying:
        {
            mediaPlayer.isMusicPlaying = true;
        }

        // Event received when the music is finished or the user push the stop btn
        onStopped:
        {
            mediaPlayer.isMusicPlaying = false;

            // Means it's the end of the music
            if(mediaPlayer.position === mediaPlayer.duration)
            {
                // Set the cursor position to 0
                sliderProgressionMusic.value = 0;

                // Read the next music randomly
                if(mediaPlayer.isRandomReadingActivated)
                {
                    var randomIndex = Math.floor(Math.random() * Math.floor(currentPlaylist.itemCount))

                    // Loading the next music by default
                    signalBtnNextRandomMusic(randomIndex);
                    mediaPlayer.play();

                }
                else
                {
                    // Loading the next music by default
                    signalBtnNextMusic();
                    mediaPlayer.play();
                }
            }
            // Means the user stopped the current music
            else
            {
                // Set the cursor position to 0
                sliderProgressionMusic.value = 0;

                if(btnPlayPause.state === "PAUSE_VISIBLE")
                {
                    btnPlayPause.state = "PLAY_VISIBLE";
                    btnPlayPause.color = "green";

                    btnPlayPauseImg.source = "file:///" + ressourcesDirPath + "/Ressources/qmlRessources/MusicPlayer/btnPlayMusic.png"
                }
            }
        }

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

    // BTN RANDOM / CONTINUE READING
    Rectangle
    {
        id: btnRandomReading

        height: 50
        width: parent.width / 7

        x: ((parent.width / 7) / 7)
        y: (parent.height / 2) - (btnPreviousMusic.height / 2)

        color: "grey"

        Image
        {
            id: btnRandomReadingImg

            width: parent.width
            height: parent.height

            source: "file:///" + ressourcesDirPath + "/Ressources/qmlRessources/MusicPlayer/btnContinueReading.png"
        }

        MouseArea
        {
            height: parent.height
            width: parent.width

            onClicked:
            {
                // When user push the random reading btn
                if(mediaPlayer.isRandomReadingActivated)
                {
                    mediaPlayer.isRandomReadingActivated = false;
                    btnRandomReading.color = "grey"

                    btnRandomReadingImg.source = "file:///" + ressourcesDirPath + "/Ressources/qmlRessources/MusicPlayer/btnContinueReading.png"
                }
                else
                {
                    mediaPlayer.isRandomReadingActivated = true
                    btnRandomReading.color = "white"

                    btnRandomReadingImg.source = "file:///" + ressourcesDirPath + "/Ressources/qmlRessources/MusicPlayer/btnRandomReading.png"
                }
            }
        }
    }

    // BTN PREVIOUS MUSIC
    Rectangle
    {
        id: btnPreviousMusic

        height: 50
        width: parent.width / 7

        x: parent.width / 7 + 2 * ((parent.width / 7) / 7)
        y: (parent.height / 2) - (btnPreviousMusic.height / 2)

        color: "orange"

        Image
        {
            id: btnPreviousMusicImg

            width: parent.width
            height: parent.height

            source: "file:///" + ressourcesDirPath + "/Ressources/qmlRessources/MusicPlayer/btnNextPreviousMusic.png"
        }

        MouseArea
        {
            height: parent.height
            width: parent.width

            onClicked:
            {
                signalBtnPreviousMusic();
            }
        }
    }

    // BTN STOP
    Rectangle
    {
        id: btnStop

        height: 50
        width: parent.width / 7

        x: 2 * (parent.width / 7) + 3 * ((parent.width / 7) / 7)
        y: (parent.height / 2) - (btnStop.height / 2)

        color: "red"

        Image
        {
            id: btnStopImg

            width: parent.width
            height: parent.height

            source: "file:///" + ressourcesDirPath + "/Ressources/qmlRessources/MusicPlayer/btnStopMusic.png"
        }

        MouseArea
        {
            height: parent.height
            width: parent.width

            onClicked:
            {
                mediaPlayer.stop();
            }
        }
    }

    // BTN PLAY / PAUSE
    Rectangle
    {
        id: btnPlayPause

        color: "green"

        height: 50
        width: parent.width / 7

        x: 3 * (parent.width / 7) + 4 * ((parent.width / 7) / 7)
        y: (parent.height / 2) - (btnPlayPause.height / 2)

        state: "PLAY_VISIBLE"
        states:
            [
                State
                {
                    name: "PLAY_VISIBLE"
                },
                State
                {
                    name: "PAUSE_VISIBLE"
                }
            ]

        Image
        {
            id: btnPlayPauseImg

            width: parent.width
            height: parent.height

            source: "file:///" + ressourcesDirPath + "/Ressources/qmlRessources/MusicPlayer/btnPlayMusic.png"
        }

        MouseArea
        {
            height: parent.height
            width: parent.width

            onClicked:
            {
                // If the user pushed the play btn
                if(btnPlayPause.state === "PLAY_VISIBLE")
                {
                    if(labelCurrentMusicName.text !== "")
                    {
                        playerMenu.signalPushPlayMusicBtn();
                        btnPlayPause.state = "PAUSE_VISIBLE";
                        btnPlayPause.color = "blue";

                        btnPlayPauseImg.source = "file:///" + ressourcesDirPath + "/Ressources/qmlRessources/MusicPlayer/btnPauseMusic.png"
                    }
                }
                // If the user pushed the pause btn
                else if(btnPlayPause.state === "PAUSE_VISIBLE")
                {
                    if(labelCurrentMusicName.text !== "")
                    {
                        pauseMusic();
                        btnPlayPause.state = "PLAY_VISIBLE";
                        btnPlayPause.color = "green";

                        btnPlayPauseImg.source = "file:///" + ressourcesDirPath + "/Ressources/qmlRessources/MusicPlayer/btnPlayMusic.png"
                    }

                }

            }
        }
    }

    // BTN NEXT MUSIC
    Rectangle
    {
        id: btnNextMusic

        height: 50
        width: parent.width / 7

        x: 4 * (parent.width / 7) + 5 * ((parent.width / 7) / 7)
        y: (parent.height / 2) - (btnPreviousMusic.height / 2)

        color: "orange"

        Image
        {
            id: btnNextMusicImg

            width: parent.width
            height: parent.height
            rotation: 180

            source: "file:///" + ressourcesDirPath + "/Ressources/qmlRessources/MusicPlayer/btnNextPreviousMusic.png"
        }

        MouseArea
        {
            height: parent.height
            width: parent.width

            onClicked:
            {
                signalBtnNextMusic();
            }
        }
    }

    // BTN LOOPING READING
    Rectangle
    {
        id: btnLoopingReading

        height: 50
        width: parent.width / 7

        x: 5 * (parent.width / 7) + 6 * ((parent.width / 7) / 7)
        y: (parent.height / 2) - (btnPreviousMusic.height / 2)

        color: "grey"

        Image
        {
            id: btnLoopingReadingImg

            width: parent.width
            height: parent.height

            source: "file:///" + ressourcesDirPath + "/Ressources/qmlRessources/MusicPlayer/btnLoopReading.png"
        }

        MouseArea
        {
            height: parent.height
            width: parent.width

            onClicked:
            {
                // When user push the loops reading btn
                if(mediaPlayer.isLoopReadingActivated)
                {
                    mediaPlayer.isLoopReadingActivated = false;
                    mediaPlayer.loops = 0;
                    btnLoopingReading.color = "grey"
                }
                else
                {
                    mediaPlayer.isLoopReadingActivated = true
                    mediaPlayer.loops = MediaPlayer.Infinite
                    btnLoopingReading.color = "purple"
                }
            }
        }
    }

    // PROGRESSION MUSIC SLIDER
    Slider
    {
        id: sliderProgressionMusic;

        //minimumValue: 1;
        maximumValue: mediaPlayer.duration

        //anchors.margins: 10
        //anchors.bottom: scale.top
        //anchors.top: parent.top

        width: parent.width - (parent.width / 7)

        x: (parent.width - sliderProgressionMusic.width) / 2
        y: parent.height - 30

        orientation : Qt.Horizontal

        style: SliderStyle
        {
            handle: Rectangle
                    {
                        anchors.centerIn: parent
                        color: control.pressed ? "white" : "lightgray"
                        border.color: "gray"
                        border.width: 2
                        implicitHeight: 15
                        implicitWidth: 15
                        radius: 8
                    }
        }

        onValueChanged:
        {
        }

        onPressedChanged:
        {
            if(!sliderProgressionMusic.pressed)
            {
                mediaPlayer.seek(sliderProgressionMusic.value);
            }
        }

        Binding
        {
            target: sliderProgressionMusic
            property: "value"
            value: mediaPlayer.position
            when: !sliderProgressionMusic.pressed
        }
    }

}
