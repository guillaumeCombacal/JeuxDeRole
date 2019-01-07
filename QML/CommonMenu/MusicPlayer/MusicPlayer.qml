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

    color: "white"

    x: parent.width - launcherMusicPlayer.width

    Image
    {
        id: launcherMusicPlayerImg

        width: parent.width
        height: parent.height

        source: "file:///" + ressourcesDirPath + "/Ressources/qmlRessources/MusicPlayer/MusicPlayer.png"
    }

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

        property int indexSelectedPlaylist: 0
        property int indexPlayingPlaylist: 0
        property int indexSelectedMusic: 0

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

            // ****
            // NOTE :
            // PlaylistMenu, MusicMenu, PlayerMenu have to be inside the MouseArea because they all have child MouseArea,
            // This is necessary to avoid interaction problem between parent / child MouseArea

            // COMPONENT PLAYLIST MENU
            // ***********************
            PlaylistMenu
            {
                id: playlistMenu

                // Create a new Playlist
                function createPlaylistInModel(playlistName)
                {
                    var playlistNameExist = false;
                    var vecSize = MusicPlayerData.vecPlaylist.length;
                    for(var i = 0; i<vecSize; i++)
                    {
                        // If the default name already exist => change it
                        if(MusicPlayerData.vecPlaylist[i].getNamePlaylist() === playlistName)
                        {
                            playlistMenu.createPlaylistInModel(playlistName + MusicPlayerData.vecPlaylist.length);
                            playlistNameExist = true;
                            break;
                        }
                    }

                    // The default name doesn't exist => create the playlist
                    if(playlistNameExist === false)
                    {
                        // Create a new Playlist add it in a vector
                        var newPlaylist = new MusicPlayerData.Playlist(playlistName);
                        MusicPlayerData.vecPlaylist.push(newPlaylist);

                        // Add the playlist inside the listModel to update the view
                        playlistMenu.addPlaylistInListModel(playlistName);
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
                    musicMenu.changeCurrentSelectedPlaylist(selectedPlaylistName);

                    // Remove all music from listView
                    musicMenu.removeAllMusicsFromListview();

                    // Add all the musics from the new playlist to the list view
                    for(var i = 0; i<MusicPlayerData.vecPlaylist.length; i++)
                    {
                        // Get all musics from the new playlist
                        if(MusicPlayerData.vecPlaylist[i].getNamePlaylist() === selectedPlaylistName)
                        {
                            // Save index to avoid for looping (for the next function)
                            musicPlayer.indexSelectedPlaylist = i;

                            // Get all musics from the selected playlist
                            var vecMusic = MusicPlayerData.vecPlaylist[i].getAllMusicInPlaylist();

                            // Remove all old musics from the old playlist inside the playerMenu
                            //playerMenu.removeAllMusicsInPlaylist();

                            // Add Musics in music view menu
                            for(var j = 0; j < vecMusic.length; j++)
                            {
                                // Add the music inside the list view of the music menu
                                musicMenu.addMusicInListView(vecMusic[j].getKeyMusic());

                                // Add the music inside the player menu current Playlist
                                //playerMenu.addMusicInPlaylist(vecMusic[j].getUrlMusic())
                            }
                            break;
                        }
                    }

                    // If the selected Playlist is the currently playing playlist, the music playing display selected
                    if(musicPlayer.indexSelectedPlaylist === musicPlayer.indexPlayingPlaylist)
                    {
                        musicMenu.selectMusic(musicPlayer.indexSelectedMusic);
                    }
                }

                onSignalRemoveCurrentPlaylist:
                {
                    // REMOVE ELEMENTS
                    // Remove the playlist from the model
                    MusicPlayerData.vecPlaylist.splice(musicPlayer.indexSelectedPlaylist, 1);
                    // Remove all old musics from the musicMenu
                    musicMenu.removeAllMusicsFromListview();

                    // If the playlist removed is the playing playlist
                    if(musicPlayer.indexPlayingPlaylist === musicPlayer.indexSelectedPlaylist)
                    {
                        // Remove all old musics from the old playlist inside the playerMenu
                        playerMenu.removeAllMusicsInPlaylist();

                        // RESET THE PLAYER MENU STATE
                        playerMenu.resetPlayerMenu();
                    }

                    //CHANGE THE NAME OF THE SELECTED PLAYLIST    
                    // Save the name
                    musicPlayer.currentPlaylist = selectedPlaylistName;
                    // Change the title of the current playlist
                    musicMenu.changeCurrentSelectedPlaylist(selectedPlaylistName);

                    // Change the index of the playing playlist if it's necessary
                    if(musicPlayer.indexSelectedPlaylist < musicPlayer.indexPlayingPlaylist)
                    {
                        musicPlayer.indexPlayingPlaylist = musicPlayer.indexPlayingPlaylist - 1;
                    }


                    // RELOAD MUSICS OF THE NEW SELECTED PLAYLIST
                    // Save index to avoid for looping (for the next function)
                    musicPlayer.indexSelectedPlaylist = indexNewSelectedPlaylist;
                    if(musicPlayer.indexSelectedPlaylist === musicPlayer.indexPlayingPlaylist)
                    {
                        musicPlayer.indexPlayingPlaylist = musicPlayer.indexSelectedPlaylist;
                    }

                    if(indexSelectedPlaylist >= 0 && selectedPlaylistName !== "")
                    {
                        // Get all musics from the selected playlist
                        var vecMusic = MusicPlayerData.vecPlaylist[indexNewSelectedPlaylist].getAllMusicInPlaylist();
                        // Add Musics in player and music menu
                        for(var j = 0; j < vecMusic.length; j++)
                        {
                            // Add the music inside the list view of the music menu
                            musicMenu.addMusicInListView(vecMusic[j].getKeyMusic());
                        }

                        // Change the selection in the ListView of playlistMenu
                        playlistMenu.changeCurrentSelectedPlaylist(MusicPlayerData.vecPlaylist[indexNewSelectedPlaylist].getNamePlaylist());
                    }
                }

            }

            // COMPONENT MUSIC MENU
            // ********************
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

                    // Add the music in the right playlist Model and add it in the list view
                    MusicPlayerData.vecPlaylist[musicPlayer.indexSelectedPlaylist].addMusic(newMusic);
                    musicMenu.addMusicInListView(filenameMusic);
                    playerMenu.addMusicInPlaylist(filenameMusic);
                }

                // When the user select a music in MusicMenu's list
                // Arg: musicName -> the label display in the MusicMenu view
                onChangeSelectedMusic:
                {
                    // Change Playing Playlist
                    if(musicPlayer.indexPlayingPlaylist !== musicPlayer.indexSelectedPlaylist)
                    {
                        // playing playlist becomes selected playlist
                        musicPlayer.indexPlayingPlaylist = musicPlayer.indexSelectedPlaylist

                        // Get all musics from the selected playlist
                        var vecMusicPlaying = MusicPlayerData.vecPlaylist[musicPlayer.indexPlayingPlaylist].getAllMusicInPlaylist();

                        // Remove all old musics from the old playlist inside the playerMenu
                        playerMenu.removeAllMusicsInPlaylist();

                        // Add Musics in playlist player menu
                        for(var j = 0; j < vecMusicPlaying.length; j++)
                        {
                            // Add the music inside the player menu current Playlist
                            playerMenu.addMusicInPlaylist(vecMusicPlaying[j].getUrlMusic())
                        }
                    }

                    // Find the filename
                    var vecMusic = MusicPlayerData.vecPlaylist[musicPlayer.indexSelectedPlaylist].getAllMusicInPlaylist()
                    for(var index = 0; index < vecMusic.length; index++)
                    {
                        // If the music is found
                        if(vecMusic[index].getKeyMusic() === musicName)
                        {
                            musicPlayer.indexSelectedMusic = index;
                            musicPlayer.currentMusicUrl = vecMusic[index].getUrlMusic();
                            playerMenu.changeSelectedMusic(musicName);

                            playerMenu.playMusic(musicPlayer.indexSelectedMusic);
                            break;
                        }
                        else
                        {
                            //console.log("not found !");
                        }
                    }
                }

                // When loading the music name in the listview it can be too long, so it's cut, and a key is saved to find it later
                onSetKeyMusic:
                {
                    var vecMusic = MusicPlayerData.vecPlaylist[musicPlayer.indexSelectedPlaylist].getAllMusicInPlaylist()
                    for(var j = 0; j < vecMusic.length; j++)
                    {
                        // At beginning url and key are the same (see constructor), so we can compare
                        if(vecMusic[j].getKeyMusic() === urlMusic)
                        {
                            vecMusic[j].setKeyMusic(keyMusic);
                            break;
                        }
                    }
                }

                // Remove music from the Model
                onSignalRemoveCurrentMusic:
                {
                    MusicPlayerData.vecPlaylist[musicPlayer.indexSelectedPlaylist].removeMusicInPlaylist(musicPlayer.indexSelectedMusic);

                    playerMenu.removeSelectedMusic(musicPlayer.indexSelectedMusic);

                    playerMenu.changeSelectedMusic(musicNameNextMusic);

                    musicPlayer.indexSelectedMusic = indexNewSelectedMusic;
                }
            }

            // COMPONENT PLAYER MENU
            // *********************
            PlayerMenu
            {
                id: playerMenu

                onSignalPushPlayMusicBtn:
                {
                    playerMenu.playMusic(musicPlayer.indexSelectedMusic);
                }

                onSignalBtnPreviousMusic:
                {
                    // Find the Playlist
                    // Get Musics and find the previous one
                    var vecMusic = MusicPlayerData.vecPlaylist[musicPlayer.indexPlayingPlaylist].getAllMusicInPlaylist();

                    // Get the size of the music array
                    var vecLength = Object.keys(vecMusic).length;

                    // If the current music is the first one we go to the last one
                    var newIndex = -1;
                    if(musicPlayer.indexSelectedMusic === 0)
                    {
                        newIndex = vecLength - 1
                    }
                    else
                    {
                        newIndex = musicPlayer.indexSelectedMusic - 1;
                    }

                    if(newIndex !== -1)
                    {
                        musicPlayer.indexSelectedMusic = newIndex;
                        musicPlayer.currentMusicUrl = vecMusic[newIndex].getUrlMusic();

                        // View is refreshed only if the user watched the playing playlist
                        if(musicPlayer.indexPlayingPlaylist === musicPlayer.indexSelectedPlaylist)
                        {
                            musicMenu.changeCurrentSelectedMusic(vecMusic[newIndex].getKeyMusic());
                        }
                        // If it's not the case the playerMenu title has to be refresh anyway
                        else
                        {
                            playerMenu.changeSelectedMusic(vecMusic[newIndex].getKeyMusic());
                        }

                        playerMenu.playMusic(musicPlayer.indexSelectedMusic);
                    }
                }

                onSignalBtnNextMusic:
                {
                    // Find the Playlist
                    // Get Musics and find the next one
                    var vecMusic = MusicPlayerData.vecPlaylist[musicPlayer.indexPlayingPlaylist].getAllMusicInPlaylist();

                    // Get the size of the music array
                    var vecLength = Object.keys(vecMusic).length;

                    // If the current music is the last one we go to the first one
                    var newIndex = -1;
                    if(musicPlayer.indexSelectedMusic === vecLength-1)
                    {
                        newIndex = 0
                    }
                    else
                    {
                        newIndex = musicPlayer.indexSelectedMusic + 1;
                    }

                    if(newIndex !== -1)
                    {
                        musicPlayer.indexSelectedMusic = newIndex;
                        musicPlayer.currentMusicUrl = vecMusic[newIndex].getUrlMusic();

                        // View is refreshed only if the user watched the playing playlist
                        if(musicPlayer.indexPlayingPlaylist === musicPlayer.indexSelectedPlaylist)
                        {
                            musicMenu.changeCurrentSelectedMusic(vecMusic[newIndex].getKeyMusic());
                        }
                        // If it's not the case the playerMenu title has to be refresh anyway
                        else
                        {
                            playerMenu.changeSelectedMusic(vecMusic[newIndex].getKeyMusic());
                        }

                        playerMenu.playMusic(musicPlayer.indexSelectedMusic);
                    }
                }

                onSignalBtnNextRandomMusic:
                {
                    // Get Musics and find the next one
                    var vecMusic = MusicPlayerData.vecPlaylist[musicPlayer.indexPlayingPlaylist].getAllMusicInPlaylist();

                    musicPlayer.indexSelectedMusic = randomIndex;
                    musicPlayer.currentMusicUrl = vecMusic[randomIndex].getUrlMusic();

                    // View is refreshed only if the user watched the playing playlist
                    if(musicPlayer.indexPlayingPlaylist === musicPlayer.indexSelectedPlaylist)
                    {
                        musicMenu.changeCurrentSelectedMusic(vecMusic[randomIndex].getKeyMusic());
                    }
                    // If it's not the case the playerMenu title has to be refresh anyway
                    else
                    {
                        playerMenu.changeSelectedMusic(vecMusic[randomIndex].getKeyMusic());
                    }

                    playerMenu.playMusic(musicPlayer.indexSelectedMusic);
                }

            }
        }


    }
}
