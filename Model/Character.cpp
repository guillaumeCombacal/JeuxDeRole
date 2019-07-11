#include "Character.h"

#include "QDebug"

#include <QJsonArray>
#include <QVector2D>

Character::Character():
    m_bIsReadyToRender(false),
    m_iCountRender(0),
    m_iTotalCountRender(0),
    m_orientation(0.0f)
{
}

Character::~Character()
{
}

void Character::saveCharacterData(QJsonObject &json)const
{
    json["orientation"] = m_orientation;
    //json["height"] = m_height;
    json["imgTilesheetFilePath"] = m_strImgTilesheetFilePath;
    json["sizeSide"] = m_iSizeSide;

    QJsonArray l_arrayJsonIndexTileArea;
    for(int i=0; i<m_vecIndexTileArea.size(); i++)
    {
        QJsonObject indexObject;
        indexObject["index"] = m_vecIndexTileArea[i];
        l_arrayJsonIndexTileArea.append(indexObject);
    }
    json["indexTileArea"] = l_arrayJsonIndexTileArea;

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


void Character::loadCharacterData(const QJsonObject &json)
{
    m_orientation = json["orientation"].toDouble();
    //m_height = json["height"].toDouble();
    m_strImgTilesheetFilePath = json["imgTilesheetFilePath"].toString();

    m_iSizeSide = json["sizeSide"].toInt();

    _initTotalCountRender();

    m_vecIndexTileArea.clear();
    QJsonArray indexTileAreaArray = json["indexTileArea"].toArray();
    for (int itIndex = 0; itIndex < indexTileAreaArray.size(); itIndex++)
    {
        QJsonObject indexObject = indexTileAreaArray[itIndex].toObject();
        m_vecIndexTileArea.append(indexObject["index"].toInt());
    }

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

bool Character::isReadyToRender()
{
    m_iCountRender++;

    if(m_iCountRender == m_iTotalCountRender)
    {
        m_bIsReadyToRender = true;
        return true;
    }
    else if(m_iCountRender == m_iSizeSide*m_iSizeSide)
    {
        m_bIsReadyToRender = false;
        m_iCountRender = 0;
        return false;
    }
    else
    {
        m_bIsReadyToRender = false;
        return false;
    }
}

void Character::_initTotalCountRender()
{
    if(m_iSizeSide > 0)
    {
        // Number Tiles it's necessary to count to know when the character have to be render
        if(m_iSizeSide%2 == 0)// Pair
        {
            m_iTotalCountRender = ((m_iSizeSide/2)*(m_iSizeSide+1)) - (m_iSizeSide-1);
        }
        else// Impair
        {
            m_iTotalCountRender = (((m_iSizeSide+1)/2)*m_iSizeSide) - (m_iSizeSide-1);
        }
    }
}
