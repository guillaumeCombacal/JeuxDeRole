#include "Tile.h"

#include "QDebug"

#include <QJsonArray>
#include <QVector2D>

Tile::Tile():
    m_iIndexTexture(0),
    m_iNbSquareUp(0),
    m_iNbSquareDown(0),
    m_orientation(0.0f)
{
}

Tile::~Tile()
{
}

void Tile::saveTileData(QJsonObject &json)const
{
    json["orientation"] = m_orientation;
    json["imgTilesheetFilePath"] = m_strImgTilesheetFilePath;
    json["nbSquareUp"] = m_iNbSquareUp;
    json["nbSquareDown"] = m_iNbSquareDown;


    QJsonArray l_arrayJsonCoordText;
    for(int i=0; i<m_coordTexture.size(); i++)
    {
        QJsonObject coordObject;
        coordObject["coordX"] = m_coordTexture[i].x();
        coordObject["coordY"] = m_coordTexture[i].y();
        l_arrayJsonCoordText.append(coordObject);
    }
    json["textureCoords"] = l_arrayJsonCoordText;
}


void Tile::loadTileData(const QJsonObject &json)
{
    m_orientation = json["orientation"].toDouble();
    m_strImgTilesheetFilePath = json["imgTilesheetFilePath"].toString();
    m_iNbSquareUp = json["nbSquareUp"].toInt();
    m_iNbSquareDown = json["nbSquareDown"].toInt();

    m_coordTexture.clear();
    QJsonArray coordArray = json["textureCoords"].toArray();
    for (int itCoord = 0; itCoord < coordArray.size(); itCoord++)
    {
        QJsonObject coordObject = coordArray[itCoord].toObject();
        QVector2D l_vecCoord;
        l_vecCoord.setX(coordObject["coordX"].toDouble());
        l_vecCoord.setY(coordObject["coordY"].toDouble());
        m_coordTexture.append(l_vecCoord);
    }
}
