#include "Character.h"

#include "QDebug"

#include <QJsonArray>
#include <QVector2D>

#define TIMEOUT_ANIMATION_CHARACTER 300// timeout in ms between changing state

Character::Character():
    m_bIsReadyToRender(false),
    m_iCountRender(0),
    m_iTotalCountRender(0),
    m_orientation(0.0f),
    m_iSizeSide(0)
{
    // Init inherited members
    m_currentStateFrame = STATE_WALK_1;
    m_timeoutSignal_ms = TIMEOUT_ANIMATION_CHARACTER;
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
    for(int i=0; i<NB_COORD_TEXTURE; i++)
    {
        QJsonObject coordObject;
        coordObject["coordX"] = m_tabCoordTexture[i].x();
        coordObject["coordY"] = m_tabCoordTexture[i].y();
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

    QJsonArray coordArray = json["textureCoords"].toArray();
    for (int itCoord = 0; itCoord < coordArray.size(); itCoord++)
    {
        QJsonObject coordObject = coordArray[itCoord].toObject();
        QVector2D l_vecCoord;
        l_vecCoord.setX(coordObject["coordX"].toDouble());
        l_vecCoord.setY(coordObject["coordY"].toDouble());
        m_tabCoordTexture[itCoord] = l_vecCoord;
    }

}

bool Character::isReadyToRender()
{   
    if(m_iSizeSide == 0)
    {
        qDebug()<<"Character has no size !!!";
        return false;
    }
    //TODO : correction size side


    // Handle the case with m_iSizeSide = 1
    if(m_iCountRender >= (m_iSizeSide*m_iSizeSide))
    {
       m_iCountRender = 0;
    }

    if(m_iCountRender == 0)
    {
        m_iCountRender++;
        return true;
    }
    else if(m_iCountRender == (m_iSizeSide*m_iSizeSide)-1)
    {
        m_iCountRender = 0;
        return false;
    }
    else
    {
        m_iCountRender++;
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

//TODO : changement des coords
void Character::updateCoordSprite(int i_stateFrame)
{
    switch(i_stateFrame)
    {
        case STATE_WALK_1 :
        m_tabCoordTexture[0] = QVector2D(0.0f,1.0f);
        m_tabCoordTexture[1] = QVector2D(0.5f,1.0f);
        m_tabCoordTexture[2] = QVector2D(0.5f,0.0f);
        m_tabCoordTexture[3] = QVector2D(0.0f,0.0f);
            break;
        case STATE_WALK_2 :
        m_tabCoordTexture[0] = QVector2D(0.5f,1.0f);
        m_tabCoordTexture[1] = QVector2D(1.0f,1.0f);
        m_tabCoordTexture[2] = QVector2D(1.0f,0.0f);
        m_tabCoordTexture[3] = QVector2D(0.5f,0.0f);
            break;
        default:
            break;
    }
}

void Character::nextState()
{
    switch(m_currentStateFrame)
    {
        case STATE_WALK_1 :
            m_currentStateFrame = STATE_WALK_2;
            break;
        case STATE_WALK_2 :
            m_currentStateFrame = STATE_WALK_1;
            break;
        default:
            break;
    }
}
