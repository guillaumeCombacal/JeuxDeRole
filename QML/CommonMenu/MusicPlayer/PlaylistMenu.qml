import QtQuick 2.6

// Component QLabel
import QtQuick.Controls 1.4



Rectangle
{
    id: playlistMenu

    width: parent.width / 3
    height: parent.height

    signal changePlaylistName(string oldPlaylistName, string newPlaylistName)// Change the playlist Name
    signal createPlaylist(string playlistName)// Create a new playlist
    signal changeSelectedPlaylist(string selectedPlaylistName);

    // Create a Playlist and add it to the listModel
    function addPlaylistInListModel(playlistName)
    {
        // Create a new playlist for the listView
        listModelPlaylist.append({"playlistNameData" : playlistName, "enabledTextEdit" : false, "visibleLabel" : true,"selectedPlaylist": false, "currentColor": "orange"})
    }

    // Change the playlist name inside the listModel
    function changePlaylistNameInListModel(oldPlaylistName, newPlaylistName)
    {
        for(var i = 0; i<listModelPlaylist.count; i++)
        {
            if(listModelPlaylist.get(i).playlistNameData === oldPlaylistName)
            {
                listModelPlaylist.get(i).playlistNameData = newPlaylistName
            }
        }
    }

    // When the menu is closed
    function disableFocus()
    {
        for(var i = 0; i<listModelPlaylist.count; i++)
        {
            listModelPlaylist.get(i).enabledTextEdit = false;// Call onEditingFinished() and set visibleLabel = true
        }
    }

    // When the menu is opened
    /*function onOpenPlaylistMenu()
    {
        for(var i = 0; i<listModelPlaylist.count; i++)
        {
            listModelPlaylist.get(i).enabledTextEdit = true;
        }
    }*/

    // When the selected playlist change, at the end the signal changeSelectedPlaylist() is sent
    function changeCurrentSelectedPlaylist(selectedPlaylistName)
    {
        var posPlaylist = 0;// Position of the selected playlist

        // All elements are test to find the current selected playlist and set at false the old playlist selected
        for(var i = 0; i<listModelPlaylist.count; i++)
        {
            // posPlaylist is set to the index of the selected playlist
            if(listModelPlaylist.get(i).playlistNameData === selectedPlaylistName)
            {
                posPlaylist = i;
            }

            // If there is a playlist selected already, its selected state become false
            if(listModelPlaylist.get(i).selectedPlaylist === true)
            {
                listModelPlaylist.get(i).selectedPlaylist = false;
                listModelPlaylist.get(i).currentColor = "orange";
                listModelPlaylist.get(i).enabledTextEdit = false;// Call onEditingFinished() and set visibleLabel = true
            }
        }

        // Then the selected state of the selected playlist become true
        listModelPlaylist.get(posPlaylist).selectedPlaylist = true;
        listModelPlaylist.get(posPlaylist).currentColor = "turquoise";
        changeSelectedPlaylist(listModelPlaylist.get(posPlaylist).playlistNameData);
    }


    // LABEL FOR THE TITLE OF THE PLAYLIST SECTION
    Rectangle
    {
        id: titlePlaylistMenu

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

            id: labelTitlePlaylistMenu
            text: "Playlists"
            font.pixelSize: 22
            //font.family: labelFont.name
            color: "black"

            x: parent.width / 2 - labelTitlePlaylistMenu.width / 2
        }
    }


    // RECTANGLE CONTAINING THE LIST OF THE PLAYLIST COMPONENTS
    Rectangle
    {
        id: listPlaylist

        width: parent.width
        height: 4 * (parent.height / 6)

        y: parent.height / 6

        color: "orange" 

        // Data Model, containing the data which will transfert from the callback function to the component
        ListModel
        {
            id: listModelPlaylist
        }

        // Component used as delegate item for the listView, it contains the behavior of the playlist component
        Component
        {
            id: delegateComponent
            Rectangle
             {
                 id: delegatePlaylistName

               width: parent.width
               height: listPlaylist.height / 4

               //Keys.onPressed:
               //{
               //    console.log("-- Key EVENT --");

                //if(event.key === Qt.Key_Enter)
                //{
                //    console.log("-- Key Enter --");
                //}
               //}

               //id: playlistName

               color: currentColor

               property bool playlistSelected: selectedPlaylist

                   MouseArea
                   {
                       hoverEnabled: true // Allow to cath event callback onEntered & onExited

                       width: parent.width
                       height: parent.height

                       onPressed:
                       {
                           playlistMenu.changeCurrentSelectedPlaylist(playlistNameData);
                       }

                       onEntered:
                       {
                           if(delegatePlaylistName.playlistSelected == false)
                           {
                                currentColor = "blue"
                           }
                       }
                       onExited:
                       {
                           if(delegatePlaylistName.playlistSelected == false)
                           {
                                currentColor = "orange"
                           }

                       }

                       onDoubleClicked:
                       {
                           enabledTextEdit = true;
                           playlistNameEdit.visible = true;
                           labelNamePlaylist.visible = false;
                       }

                       Label
                       {
                           /*FontLoader
                           {
                                   id: labelFont
                                   source: "file:///" + ressourcesDirPath + "/Ressources/qmlRessources/WorldMap/MORPHEUS.ttf"
                           }*/

                           id: labelNamePlaylist
                           text: playlistNameData
                           font.pixelSize: 22
                           //font.family: labelFont.name
                           color: "black"

                           x: parent.width / 2 - labelNamePlaylist.width / 2

                           visible : visibleLabel
                       }

                       // Playlist Name, during init step  playlistName and text equal the default name
                       TextEdit
                       {
                           id: playlistNameEdit

                           property string playlistName : playlistNameData

                           x: parent.width / 2 - width / 2

                           text: playlistNameData

                           font.pixelSize: 22

                           enabled: enabledTextEdit
                           visible: enabledTextEdit

                           // Update the playlist name with edition
                           onEditingFinished:
                           {
                               if(playlistNameEdit.playlistName !== playlistNameEdit.text)
                               {
                                   // Limit the text size to avoid overbounding
                                   if(playlistNameEdit.text.length > 20)
                                   {
                                       playlistNameEdit.text = playlistNameEdit.text.substr(0, 20);
                                   }

                                   playlistMenu.changePlaylistName(playlistNameEdit.playlistName, playlistNameEdit.text);
                               }
                               labelNamePlaylist.visble = true;// the name label is visble

                           }
                       }

                   }
             }
        }


       // Template for a new playlist component : model -> data / delegate -> visual component
       ListView
       {
           width: parent.width
           height: parent.height

           model: listModelPlaylist
           delegate: delegateComponent
       }
    }

    // BUTTON TO CREATE A NEW PLAYLIST
    Rectangle
    {
        id: btnCreatePlaylist

        width: parent.width
        height: parent.height / 6

        y: 5 * (parent.height / 6)

        z: 1

        Label
        {
            /*FontLoader
            {
                    id: labelFont
                    source: "file:///" + ressourcesDirPath + "/Ressources/qmlRessources/WorldMap/MORPHEUS.ttf"
            }*/

            id: labelBtnCreatePlaylist
            text: "+ Create Playlists"
            font.pixelSize: 22
            //font.family: labelFont.name
            color: "black"

            x: parent.width / 2 - labelBtnCreatePlaylist.width / 2
        }

        MouseArea
        {
            width: parent.width
            height: parent.height
            anchors.fill: parent
            hoverEnabled: true // Allow to cath event callback onEntered & onExited

            // Add a new playlist
            onPressed:
            {
                // Update the Model, and whenit will be finished, the model will send a signal to create a new playlist in the ListModel
                // This has to be the first step because listModelPlaylist.count will be increased,
                // because the name can still change in the "playlistMenu.createPlaylist" step
                playlistMenu.createPlaylist("Playlist " + listModelPlaylist.count);

            }

            onEntered:
            {
                btnCreatePlaylist.color = "turquoise"
            }
            onExited:
            {
                btnCreatePlaylist.color = "white"
            }
        }
    }

}
