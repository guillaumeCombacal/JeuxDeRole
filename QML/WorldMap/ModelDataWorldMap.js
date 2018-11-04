
var vectMarker = [];

function Marker (posX, posY, idMarker, urlImg)
{
    this.m_posX = posX;
    this.m_posY = posY;
    this.m_idMarker = idMarker;
    this.m_urlImg = urlImg;
}

Marker.prototype.getMarkerXPosition = function()
{
    return this.m_posX;
}

Marker.prototype.getMarkerYPosition = function()
{
    return this.m_posY;
}

Marker.prototype.getIdMarker = function()
{
    return this.m_idMarker;
}

