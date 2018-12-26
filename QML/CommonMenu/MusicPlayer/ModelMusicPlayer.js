// Playlist Vector
var vecPlaylist = [];



// Class Music
function Music (urlMusic)
{
    this.m_urlMusic = urlMusic;// the full filename of the file
    this.m_keyMusic = urlMusic;// the key used to find the music when using loop
}

Music.prototype.getUrlMusic = function()
{
    return this.m_urlMusic;
}

Music.prototype.getKeyMusic = function()
{
    return this.m_keyMusic;
}

Music.prototype.setKeyMusic = function(newName)
{
    this.m_keyMusic = newName;
}




// Class Playlist
function Playlist (namePlaylist)
{
    this.m_vecMusic = [];
    this.m_namePlaylist= namePlaylist;
}

Playlist.prototype.getNamePlaylist = function()
{
    return this.m_namePlaylist;
}

Playlist.prototype.setNamePlaylist = function(newName)
{
    this.m_namePlaylist = newName;
}

Playlist.prototype.addMusic = function(music)
{
    this.m_vecMusic.push(music);
}

Playlist.prototype.getAllMusicInPlaylist = function()
{
    return this.m_vecMusic;
}

Playlist.prototype.removeMusicInPlaylist = function(index)
{
    this.m_vecMusic.splice(index, 1);
}

