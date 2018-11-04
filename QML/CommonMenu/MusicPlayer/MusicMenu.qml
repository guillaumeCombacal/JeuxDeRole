import QtQuick 2.6

// Pour le composant fileDialog
import QtQuick.Dialogs 1.0

// Component QLabel
import QtQuick.Controls 1.4


Rectangle
{
    id: musicMenu

    width: parent.width / 3
    height: parent.height

    x: parent.width / 3

    color: "silver"

    //signal displayMusicPlayer()
    signal addNewMusic(string filenameMusic, string currentPlaylistName)

    signal changeSelectedMusic(string musicName)

    signal setKeyMusic(string urlMusic, string keyMusic)

    function changeCurrentPlaylistName(playlistName)
    {
        labelCurrentPlaylistName.text = playlistName;

        if(btnAddMusic.visible === false)
        {
            btnAddMusic.visible = true;
        }
    }

    function removeAllMusicsFromListview()
    {
        var nbElement = listModelMusic.count;

        // When an element is removed in listview,
        // another one takes its place in index,
        // so it's just necessary to remove the index 0 element each time to remove the whole list !
        for(var i = 0; i<nbElement; i++)
        {
            listModelMusic.remove(0);
        }
    }

    function addMusicInListView(musicName)
    {
        // Get only the musicName in the fileName
        var musicTitleTab = musicName.split('/');
        var musicTitle = musicTitleTab[musicTitleTab.length - 1];

        // Limit the name to avoid overbounding
        if(musicTitle.length > 35)
        {
            musicTitle = musicTitle.substr(0, 35);
        }

        // Create a new music for the listView
        listModelMusic.append({"musicNameData" : musicTitle, "selectedMusic": false, "currentColor": "orange"})

        // Set the music model with its key
        musicMenu.setKeyMusic(musicName, musicTitle);
    }

    // When the selected music change, at the end the signal changeSelectedMusic() is sent
    function changeCurrentSelectedMusic(selectedMusicName)
    {
        var posMusic = 0;// Position of the selected music

        // All elements are test to find the current selected music and set at false the old music selected
        for(var i = 0; i<listModelMusic.count; i++)
        {
            // posMusic is set to the index of the selected music
            if(listModelMusic.get(i).musicNameData === selectedMusicName)
            {
                posMusic = i;
            }

            // If there is already a music selected, its selected state become false
            if(listModelMusic.get(i).selectedMusic === true)
            {
                listModelMusic.get(i).selectedMusic = false;
                listModelMusic.get(i).currentColor = "orange";
            }
        }

        // Then the selected state of the selected music become true
        listModelMusic.get(posMusic).selectedMusic = true;
        listModelMusic.get(posMusic).currentColor = "turquoise";

        changeSelectedMusic(listModelMusic.get(posMusic).musicNameData);
    }

    // LABEL NAME OF THE SELECTED PLAYLIST NAME
    Rectangle
    {
        id: currentPlaylistName

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

            id: labelCurrentPlaylistName
            text: ""
            font.pixelSize: 22
            //font.family: labelFont.name
            color: "black"

            //width: parent.width

            x: parent.width / 2 - labelCurrentPlaylistName.width / 2
        }
    }


    // RECTANGLE CONTAINING THE LIST OF THE MUSICS COMPONENTS
    Rectangle
    {
        id: listMusic

        width: parent.width
        height: 4 * (parent.height / 6)

        y: parent.height / 6

        color: "red"

        // Data Model, containing the data which will transfert from the callback function to the component
        ListModel
        {
            id: listModelMusic
        }

        // Component used as delegate item for the listView, it contains the behavior of the music component
        Component
        {
            id: delegateComponent
            Rectangle
             {
                 id: delegateMusicName

               width: parent.width
               height: listMusic.height / 4

               //Keys.onPressed:
               //{
               //    console.log("-- Key EVENT --");

                //if(event.key === Qt.Key_Enter)
                //{
                //    console.log("-- Key Enter --");
                //}
               //}

               color: currentColor

               property bool musicSelected: selectedMusic

                   MouseArea
                   {
                       hoverEnabled: true // Allow to cath event callback onEntered & onExited

                       width: parent.width
                       height: parent.height

                       onPressed:
                       {
                           musicMenu.changeCurrentSelectedMusic(musicNameData);
                       }

                       onEntered:
                       {
                           if(delegateMusicName.musicSelected == false)
                           {
                                currentColor = "blue"
                           }
                       }
                       onExited:
                       {
                           if(delegateMusicName.musicSelected == false)
                           {
                                currentColor = "orange"
                           }

                       }

                       Label
                       {
                           /*FontLoader
                           {
                                   id: labelFont
                                   source: "file:///" + ressourcesDirPath + "/Ressources/qmlRessources/WorldMap/MORPHEUS.ttf"
                           }*/

                           id: labelNameMusic
                           text: musicNameData
                           font.pixelSize: 15
                           //font.family: labelFont.name
                           color: "black"

                           x: parent.width / 2 - labelNameMusic.width / 2
                       }
                   }
             }
        }

        // Template for a new music component : model -> data / delegate -> visual component
        ListView
        {
            width: parent.width
            height: parent.height

            model: listModelMusic
            delegate: delegateComponent
        }
    }

    // BUTTON TO ADD NEW MUSICS INSIDE THE SELECTED PLAYLIST
    Rectangle
    {
        id: btnAddMusic

        width: parent.width
        height: parent.height / 6

        y: 5 * (parent.height / 6)

        z: 1

        Component.onCompleted:
        {
            if(labelCurrentPlaylistName.text !== "")
            {
                console.log("Some text !!! ");
            }
            else
            {
                console.log("No text");
                btnAddMusic.visible = false;
            }
        }

        Label
        {
            /*FontLoader
            {
                    id: labelFont
                    source: "file:///" + ressourcesDirPath + "/Ressources/qmlRessources/WorldMap/MORPHEUS.ttf"
            }*/

            id: labelBtnAddMusic
            text: "+ Add Music"
            font.pixelSize: 22
            //font.family: labelFont.name
            color: "black"

            x: parent.width / 2 - labelBtnAddMusic.width / 2
        }

        MouseArea
        {
            width: parent.width
            height: parent.height
            anchors.fill: parent
            hoverEnabled: true // Allow to cath event callback onEntered & onExited

            // Add new musics
            onPressed:
            {
                fileDialogLoadSong.open();
            }

            onEntered:
            {
                btnAddMusic.color = "turquoise"
            }
            onExited:
            {
                btnAddMusic.color = "white"
            }
        }
    }



    // DIALOG TO OPEN THE WINDOWS EXPLORER
    FileDialog
    {
        id: fileDialogLoadSong

        title: "Choose your songs"
        folder: shortcuts.home
        selectMultiple: true
        nameFilters: [ "Image files (*.mp3)", "All files (*)" ]

        onAccepted:
        {

            for (var i = 0; i < fileUrls.length; ++i)
            {
                // Send signal to add the music fileName in the current Playlist model, one by one
                musicMenu.addNewMusic(fileUrls[i], labelCurrentPlaylistName.text);
            }

            Qt.exit(1)
        }
        onRejected:
        {
            Qt.exit(1)
        }

    }

}


