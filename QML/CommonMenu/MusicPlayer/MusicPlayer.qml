import QtQuick 2.0

// Music Data
import "ModelMusicPlayer.js" as MusicPlayerData;

Rectangle
{
    id: launcherMusicPlayer

    width: 50
    height: 50

    property int parentWidth
    property int parentHeight

    color: "green"

    x: parent.width - launcherMusicPlayer.width

    MouseArea
    {
        width: parent.width
        height: parent.height
        anchors.fill: parent

        onPressed:
        {
            if(musicPlayer.visible === false)
            {
                // Setting become visible
                musicPlayer.visible = true;
            }
        }
    }

    Rectangle
    {
        id: musicPlayer

        visible: false

        width: 2 * (parentWidth / 3)
        height: 200

        x: - musicPlayer.width + launcherMusicPlayer.width

        color: "black"

        property string currentPlaylist: ""
        property string currentMusicUrl: ""

        MouseArea
        {
            id: mouseAreaMusicPlayer

            width: parent.width
            height: parent.height
            anchors.fill: parent
            hoverEnabled: true // Allow to cath event callback onEntered & onExited

            // When the user get out of the area, it becomes invisible
            onExited:
            {
                musicPlayer.visible = false;
                playlistMenu.disableFocus();
            }

            onEntered:
            {
                //playlistMenu.onOpenPlaylistMenu();// enabled the all the playlist element in the listView
            }

            // PlaylistMenu, MusicMenu, PlayerMenu have to be inside the MouseArea because they all have child MouseArea,
            // This is necessary to avoid interaction problem between parent / child MouseArea
            PlaylistMenu
            {
                id: playlistMenu

                // Create a new Playlist
                function createPlaylistInModel(playlistName)
                {
                    var vecSize = MusicPlayerData.vecPlaylist.length;
                    for(var i = 0; i<vecSize; i++)
                    {
                        // If the default name already exist => change it
                        if(MusicPlayerData.vecPlaylist[i].getNamePlaylist() === playlistName)
                        {
                            playlistMenu.createPlaylistInModel(playlistName + MusicPlayerData.vecPlaylist.length);
                        }
                        else // the default name doesn't exist => create the playlist
                        {
                            // Create a new Playlist add it in a vector
                            var newPlaylist = new MusicPlayerData.Playlist(playlistName);
                            MusicPlayerData.vecPlaylist.push(newPlaylist);

                            // Add the playlist inside the listModel to update the view
                            playlistMenu.addPlaylistInListModel(playlistName);
                            break;
                        }
                    }

                    // Handle the fisrt creation of the playlist
                    if(MusicPlayerData.vecPlaylist.length === 0)
                    {
                        // Create a new Playlist add it in a vector
                        var newPlaylist = new MusicPlayerData.Playlist(playlistName);
                        MusicPlayerData.vecPlaylist.push(newPlaylist);

                        // Add the playlist inside the listModel to update the view
                        playlistMenu.addPlaylistInListModel(playlistName);
                    }
                }

                // change the playlist name
                function changeNamePlaylist(oldPlaylistName, newPlaylistName)
                {
                    var isNameExist = 0;

                    for(var i = 0; i<MusicPlayerData.vecPlaylist.length; i++)
                    {
                        // Check if the new name already exist
                        if(MusicPlayerData.vecPlaylist[i].getNamePlaylist() === newPlaylistName)
                        {
                            changeNamePlaylist(oldPlaylistName, newPlaylistName + MusicPlayerData.vecPlaylist.length);
                            isNameExist = 1;
                            break;// Stop the loop
                        }
                    }

                    // the new name does not still exist
                    if(isNameExist === 0)
                    {
                        for(var j = 0; j<MusicPlayerData.vecPlaylist.length; j++)
                        {
                            if(MusicPlayerData.vecPlaylist[j].getNamePlaylist() === oldPlaylistName)
                            {
                                // Change the name in the data
                                MusicPlayerData.vecPlaylist[j].setNamePlaylist(newPlaylistName);

                                // Change the name in the listModel
                                playlistMenu.changePlaylistNameInListModel(oldPlaylistName, newPlaylistName);
                            }
                        }
                    }
                }

                // Create a new playlist with a default name
                // playlistName is the argument
                onCreatePlaylist:
                {
                    playlistMenu.createPlaylistInModel(playlistName);
                }


                // Changing the Playlist Name when user edit the name
                onChangePlaylistName:
                {
                    changeNamePlaylist(oldPlaylistName, newPlaylistName)
                }

                // Change the current selected playlist
                onChangeSelectedPlaylist:
                {
                    // Save the name
                    musicPlayer.currentPlaylist = selectedPlaylistName;

                    // Change the title of the current playlist
                    musicMenu.changeCurrentPlaylistName(selectedPlaylistName);

                    // Remove all music from listView
                    musicMenu.removeAllMusicsFromListview();

                    // Add all the musics from the new playlist to the list view
                    for(var i = 0; i<MusicPlayerData.vecPlaylist.length; i++)
                    {
                        // Get all musics from the new playlist
                        if(MusicPlayerData.vecPlaylist[i].getNamePlaylist() === selectedPlaylistName)
                        {
                            var vecMusic = MusicPlayerData.vecPlaylist[i].getAllMusicInPlaylist();

                            for(var j = 0; j < vecMusic.length; j++)
                            {
                                musicMenu.addMusicInListView(vecMusic[j].getKeyMusic());
                            }
                        }
                    }
                }
            }

            MusicMenu
            {
                id: musicMenu

                // Loading songs using fileDialog close the MusicPlayer, so it's set visible again after closing the fileDialog
                /*onDisplayMusicPlayer:
                {
                    musicPlayer.visible = true;
                }
                */

                // Create music for model and listView one by one
                onAddNewMusic:
                {
                    // Create the new music
                    var newMusic = new MusicPlayerData.Music(filenameMusic);

                    var posPlaylist = -1;

                    // Add the music in the right playlist Model and add it in the list view
                    for(var i = 0; i < MusicPlayerData.vecPlaylist.length; i++)
                    {
                        if(MusicPlayerData.vecPlaylist[i].getNamePlaylist() === currentPlaylistName)
                        {
                            MusicPlayerData.vecPlaylist[i].addMusic(newMusic);
                            musicMenu.addMusicInListView(filenameMusic);
                            posPlaylist = i;
                            break;
                        }
                    }
                }

                // When the user click on an unselected music
                onChangeSelectedMusic:
                {
                    playerMenu.changeCurrentMusicName(musicName);

                    // Find the filename
                    for(var i = 0; i < MusicPlayerData.vecPlaylist.length; i++)
                    {
                        if(MusicPlayerData.vecPlaylist[i].getNamePlaylist() === musicPlayer.currentPlaylist)
                        {
                            var vecMusic = MusicPlayerData.vecPlaylist[i].getAllMusicInPlaylist()
                            for(var j = 0; j < vecMusic.length; j++)
                            {
                                if(vecMusic[j].getKeyMusic() === musicName)
                                {
                                    console.log("FOUND IT !!!");
                                    musicPlayer.currentMusicUrl = vecMusic[j].getUrlMusic();
                                    break;
                                }
                                else
                                {
                                    console.log("not found !");
                                }
                            }
                            break;
                        }
                    }
                }

                // When loading the music name in the listview it can be too long, so it's cut, and a key is saved to find it later
                onSetKeyMusic:
                {
                    for(var i = 0; i < MusicPlayerData.vecPlaylist.length; i++)
                    {
                        if(MusicPlayerData.vecPlaylist[i].getNamePlaylist() === musicPlayer.currentPlaylist)
                        {
                            var vecMusic = MusicPlayerData.vecPlaylist[i].getAllMusicInPlaylist()
                            for(var j = 0; j < vecMusic.length; j++)
                            {
                                // At beginning url and key are the same (see constructor), so we can compare
                                if(vecMusic[j].getKeyMusic() === urlMusic)
                                {
                                    vecMusic[j].setKeyMusic(keyMusic);
                                    break;
                                }
                            }
                            break;
                        }
                    }
                }
            }

            PlayerMenu
            {
                id: playerMenu

                onPushPlayMusicBtn:
                {
                    console.log("Play currentMusic" + musicPlayer.currentMusicUrl);

                    playerMenu.setUrlMusic(musicPlayer.currentMusicUrl);
                    playerMenu.playMusic();
                }
            }
        }



    }
}
