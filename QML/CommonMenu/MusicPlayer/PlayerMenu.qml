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

    color: "black"

    signal pushPlayMusicBtn(string musicName)
    signal signalBtnNextMusic(int currentIndex)
    signal signalBtnPreviousMusic(int currentIndex)

    // Change the label for the current music played
    // Set the index of the music played for the playlist
    function changeSelectedMusic(musicName, index)
    {
        labelCurrentMusicName.text = musicName;
        currentPlaylist.currentIndex = index;
    }

    // Add a music in the media player's playlist
    function addMusicInPlaylist(musicName)
    {
        currentPlaylist.addItem(musicName);
        console.log(currentPlaylist.itemCount);
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
    function playMusic()
    {
        // Calcul index of the music selected
        // By default all musics inside the playlist will be play from this one

        mediaPlayer.source = currentPlaylist.itemSource(currentPlaylist.currentIndexMusicPlayed)

        console.log(mediaPlayer.source);
        console.log(currentPlaylist.itemCount);

        if(mediaPlayer.source !== "")
        {
            mediaPlayer.play();
        console.log("PlayMusic");
            console.log(mediaPlayer.source);
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

        playlist: Playlist
                  {
                      id: currentPlaylist

                      property int currentIndexMusicPlayed: 0
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

    // BTN RANDOM READING
    Rectangle
    {
        id: btnRandomReading

        height: 50
        width: parent.width / 7

        x: ((parent.width / 7) / 7)
        y: (parent.height / 2) - (btnPreviousMusic.height / 2)

        property bool isRandomReadingActivated: false

        MouseArea
        {
            height: parent.height
            width: parent.width

            onClicked:
            {
                // When user push the random reading btn
                if(isRandomReadingActivated)
                {
                    isRandomReadingActivated = false;
                }
                else
                {
                    isRandomReadingActivated = true
                }
                console.log("RANDOM READING activated")
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

        MouseArea
        {
            height: parent.height
            width: parent.width

            onClicked:
            {
                signalBtnPreviousMusic(currentPlaylist.currentIndex);
                console.log("PREVIOUS Music")
/*
                // If the current music is the first one we go to the last one
                if(currentPlaylist.currentIndexMusicPlayed === 0)
                {
                    currentPlaylist.currentIndexMusicPlayed = currentPlaylist.itemCount;
                }
                else
                {
                    currentPlaylist.currentIndexMusicPlayed -= 1;
                    playerMenu.playMusic();
                }
                */
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

        MouseArea
        {
            height: parent.height
            width: parent.width

            onClicked:
            {
                mediaPlayer.stop();
                console.log("STOP Music")
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
                        pushPlayMusicBtn(labelCurrentMusicName.text);
                        btnPlayPause.state = "PAUSE_VISIBLE";
                        btnPlayPause.color = "blue";
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

        MouseArea
        {
            height: parent.height
            width: parent.width

            onClicked:
            {
                signalBtnNextMusic(currentPlaylist.currentIndex);
                console.log("NEXT Music")
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

        property bool isLoopReadingActivated: false

        color: "grey"

        MouseArea
        {
            height: parent.height
            width: parent.width

            onClicked:
            {
                // When user push the loops reading btn
                if(btnLoopingReading.isLoopReadingActivated)
                {
                    btnLoopingReading.isLoopReadingActivated = false;
                    btnLoopingReading.color = "grey"
                    console.log("LOOPING READING deactivated")
                }
                else
                {
                    btnLoopingReading.isLoopReadingActivated = true
                    mediaPlayer.Infinite
                    btnLoopingReading.color = "black"
                    console.log("LOOPING READING activated = " + btnLoopingReading.isLoopReadingActivated)
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
            //console.log("valueChanged !!!")
        }

        onPressedChanged:
        {
            if(!sliderProgressionMusic.pressed)
            {
                console.log("mediaPlayer.position = " + mediaPlayer.position);
                console.log("sliderProgressionMusic.value = " + sliderProgressionMusic.value);
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
