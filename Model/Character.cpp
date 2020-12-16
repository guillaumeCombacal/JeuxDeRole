#include "Character.h"

#include "QDebug"

#include <QJsonArray>
#include <QVector2D>

#define TIMEOUT_ANIMATION_CHARACTER 300// timeout in ms between changing state

// Define the number of tiles in row and column.
// Allow to find coords of the current tile to display function of the current state
#define NUMBER_TILES_IN_ROW  5
#define NUMBER_TILES_IN_COLUMN  5

Character::Character():
    m_bIsReadyToRender(false),
    m_iCountRender(0),
    m_iTotalCountRender(0),
    m_iSizeSide(0),
    m_moveSteps(0),
    m_orientation(EnumCharacter::Orientation::SOUTH),
    m_currentActionState(EnumCharacter::ActionStatesCharacter::WALKING)
{
    // Init inherited members
    m_currentStateFrame = EnumCharacter::SpriteStatesCharacter::STATE_FRAME_TRANSITION;
    m_timeoutSignal_ms = TIMEOUT_ANIMATION_CHARACTER;

    m_frameTransitionTab[EnumCharacter::ActionStatesCharacter::WALKING][EnumCharacter::Orientation::NORTH] = EnumCharacter::SpriteStatesCharacter::STATE_WALK_BACK_1;
    m_frameTransitionTab[EnumCharacter::ActionStatesCharacter::WALKING][EnumCharacter::Orientation::SOUTH] = EnumCharacter::SpriteStatesCharacter::STATE_WALK_FRONT_1;
    m_frameTransitionTab[EnumCharacter::ActionStatesCharacter::WALKING][EnumCharacter::Orientation::EAST] = EnumCharacter::SpriteStatesCharacter::STATE_WALK_FRONT_1;
    m_frameTransitionTab[EnumCharacter::ActionStatesCharacter::WALKING][EnumCharacter::Orientation::WEST] = EnumCharacter::SpriteStatesCharacter::STATE_WALK_BACK_1;
    m_frameTransitionTab[EnumCharacter::ActionStatesCharacter::ATTACKING][EnumCharacter::Orientation::NORTH] = EnumCharacter::SpriteStatesCharacter::STATE_FIGHT_BACK_1;
    m_frameTransitionTab[EnumCharacter::ActionStatesCharacter::ATTACKING][EnumCharacter::Orientation::SOUTH] = EnumCharacter::SpriteStatesCharacter::STATE_FIGHT_FRONT_1;
    m_frameTransitionTab[EnumCharacter::ActionStatesCharacter::ATTACKING][EnumCharacter::Orientation::EAST] = EnumCharacter::SpriteStatesCharacter::STATE_FIGHT_FRONT_1;
    m_frameTransitionTab[EnumCharacter::ActionStatesCharacter::ATTACKING][EnumCharacter::Orientation::WEST] = EnumCharacter::SpriteStatesCharacter::STATE_FIGHT_BACK_1;
    m_frameTransitionTab[EnumCharacter::ActionStatesCharacter::DEFENDING][EnumCharacter::Orientation::NORTH] = EnumCharacter::SpriteStatesCharacter::STATE_STAND_BACK;
    m_frameTransitionTab[EnumCharacter::ActionStatesCharacter::DEFENDING][EnumCharacter::Orientation::SOUTH] = EnumCharacter::SpriteStatesCharacter::STATE_STAND_FRONT;
    m_frameTransitionTab[EnumCharacter::ActionStatesCharacter::DEFENDING][EnumCharacter::Orientation::EAST] = EnumCharacter::SpriteStatesCharacter::STATE_STAND_FRONT;
    m_frameTransitionTab[EnumCharacter::ActionStatesCharacter::DEFENDING][EnumCharacter::Orientation::WEST] = EnumCharacter::SpriteStatesCharacter::STATE_STAND_BACK;
    m_frameTransitionTab[EnumCharacter::ActionStatesCharacter::DEAD][EnumCharacter::Orientation::NORTH] = EnumCharacter::SpriteStatesCharacter::STATE_DEAD_BACK;
    m_frameTransitionTab[EnumCharacter::ActionStatesCharacter::DEAD][EnumCharacter::Orientation::SOUTH] = EnumCharacter::SpriteStatesCharacter::STATE_DEAD_FRONT;
    m_frameTransitionTab[EnumCharacter::ActionStatesCharacter::DEAD][EnumCharacter::Orientation::EAST] = EnumCharacter::SpriteStatesCharacter::STATE_DEAD_FRONT;
    m_frameTransitionTab[EnumCharacter::ActionStatesCharacter::DEAD][EnumCharacter::Orientation::WEST] = EnumCharacter::SpriteStatesCharacter::STATE_DEAD_BACK;

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
    for(int i=0; i<m_vecIndexTileAreaPathFinding.size(); i++)
    {
        QJsonObject indexObject;
        indexObject["index"] = m_vecIndexTileAreaPathFinding[i];
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
    //m_orientation = json["orientation"].toDouble();
    //m_height = json["height"].toDouble();
    m_strImgTilesheetFilePath = json["imgTilesheetFilePath"].toString();

    m_iSizeSide = json["sizeSide"].toInt();

    _initTotalCountRender();

    m_vecIndexTileAreaPathFinding.clear();
    QJsonArray indexTileAreaArray = json["indexTileArea"].toArray();
    for (int itIndex = 0; itIndex < indexTileAreaArray.size(); itIndex++)
    {
        QJsonObject indexObject = indexTileAreaArray[itIndex].toObject();
        m_vecIndexTileAreaPathFinding.append(indexObject["index"].toInt());
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

    if(1 < m_iSizeSide)
    {
        if(0 == m_iCountRender)
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
    else
    {
        return true;
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

//TODO: ne faire q un changement d orientation en plus du chngement d etat
void Character::attacking(int indexDefendingCharacter, int nbTileSide)
{
    m_currentActionState = EnumCharacter::ActionStatesCharacter::ATTACKING;
    m_currentStateFrame = EnumCharacter::SpriteStatesCharacter::STATE_FRAME_TRANSITION;

    // change orientation function of defender position
    int result = m_vecIndexTileAreaPathFinding[0] - indexDefendingCharacter;
    if(1 == result)
    {
        setOrientation(EnumCharacter::Orientation::EAST);
    }
    else if(-1 == result)
    {
        setOrientation(EnumCharacter::Orientation::WEST);
    }
    else if(nbTileSide == result)
    {
        setOrientation(EnumCharacter::Orientation::SOUTH);
    }
    else if(-nbTileSide == result)
    {
        setOrientation(EnumCharacter::Orientation::NORTH);
    }
    else
    {
        qDebug()<<"ERROR attacking orientation";
    }
}

void Character::takingDamage(int nbDamage)
{
    m_sFeatures.m_sStats.m_PV-= nbDamage;
    m_currentActionState = EnumCharacter::ActionStatesCharacter::DEFENDING;
    m_currentStateFrame = EnumCharacter::SpriteStatesCharacter::STATE_FRAME_TRANSITION;
}

void Character::setOrientation(EnumCharacter::Orientation orientation)
{
    m_orientation = orientation;
    m_currentStateFrame = EnumCharacter::SpriteStatesCharacter::STATE_FRAME_TRANSITION;
}

void Character::updateCoordSprite(int i_stateFrame)
{
    // Mécanisme pour trouver quelle coords binder pour avoir la bonne texture dans le tileset d image
    // --> chaque tileset doit avoir la même configuration de l'odre des tiles proposées:
    // 0=STATE_STAND_FRONT,  1=STATE_STAND_BACK,  2=STATE_WALK_FRONT_1,  3=STATE_WALK_FRONT_2,
    // 4=STATE_WALK_BACK_1,  5=STATE_WALK_BACK_2, 6=STATE_HURT_FRONT,  7=STATE_HURT_BACK,
    // 8=STATE_FIGHT_FRONT_1,  9=STATE_FIGHT_FRONT_2,
    // 10=STATE_FIGHT_BACK_1,  11=STATE_FIGHT_BACK_2,
    // 13=STATE_MAGIC_FIGHT_FRONT_1,  14=STATE_MAGIC_FIGHT_FRONT_2,
    // 15=STATE_MAGIC_FIGHT_BACK_1,  16=STATE_MAGIC_FIGHT_BACK_2, 17=STATE_DEAD_FRONT,
    // 18=STATE_DEAD_BACK

    // debug
    //i_stateFrame = 12;

    // Find the coord of the frame inside the tileset -- Coord is the left-top corner
    // STATES            INDEX
    // 0 1 2 3 4         0,0  0,1  0,2  0,3  0,4
    // 5 6 7 8 9         1,0  1,1  1,2  1,3  1,4
    // ...               ...
    int indexRow = (i_stateFrame) / NUMBER_TILES_IN_ROW;
    int indexColumn = i_stateFrame % NUMBER_TILES_IN_ROW;

    float purcentOffsetRow = 1.0f / (float)NUMBER_TILES_IN_ROW;
    float purcentOffsetColumn = 1.0f / (float)NUMBER_TILES_IN_COLUMN;

    if(indexRow == 3)
    {
        qDebug()<<"test";//todo STATE_DEAD_BACK ???
    }

    // Coords index for the texture - Symetric : NORTH<->WEST EAST<->SOUTH
    //  2__3
    //  |  |
    //  1--0
    if(EnumCharacter::Orientation::NORTH == m_orientation || EnumCharacter::Orientation::EAST == m_orientation)
    {
        m_tabCoordTexture[0] = QVector2D(indexColumn*purcentOffsetColumn+purcentOffsetColumn, indexRow*purcentOffsetRow + purcentOffsetRow);
        m_tabCoordTexture[1] = QVector2D(indexColumn*purcentOffsetColumn, indexRow*purcentOffsetRow + purcentOffsetRow);
        m_tabCoordTexture[2] = QVector2D(indexColumn*purcentOffsetColumn, indexRow*purcentOffsetRow);
        m_tabCoordTexture[3] = QVector2D(indexColumn*purcentOffsetColumn+purcentOffsetColumn, indexRow*purcentOffsetRow);
    }
    // Coords index for the texture - Normal
    //  3__2
    //  |  |
    //  0--1
    else
    {
        m_tabCoordTexture[0] = QVector2D(indexColumn*purcentOffsetColumn, indexRow*purcentOffsetRow + purcentOffsetRow);
        m_tabCoordTexture[1] = QVector2D(indexColumn*purcentOffsetColumn+purcentOffsetColumn, indexRow*purcentOffsetRow + purcentOffsetRow);
        m_tabCoordTexture[2] = QVector2D(indexColumn*purcentOffsetColumn+purcentOffsetColumn, indexRow*purcentOffsetRow);
        m_tabCoordTexture[3] = QVector2D(indexColumn*purcentOffsetColumn, indexRow*purcentOffsetRow);
    }

}

 //Switch case Else pour couvrir tous les cas dans le nextState + pb de sprite attacking
void Character::nextState()
{
    switch(m_currentActionState)
    {
        case EnumCharacter::ActionStatesCharacter::WALKING :
            switch(m_currentStateFrame)
            {
                case EnumCharacter::SpriteStatesCharacter::STATE_FRAME_TRANSITION :
                    m_currentStateFrame = m_frameTransitionTab[m_currentActionState][m_orientation];
                    break;
                case EnumCharacter::SpriteStatesCharacter::STATE_WALK_FRONT_1 :
                    m_currentStateFrame = EnumCharacter::SpriteStatesCharacter::STATE_WALK_FRONT_2;
                    break;
                case EnumCharacter::SpriteStatesCharacter::STATE_WALK_FRONT_2 :
                    m_currentStateFrame = EnumCharacter::SpriteStatesCharacter::STATE_WALK_FRONT_1;
                    break;
                case EnumCharacter::SpriteStatesCharacter::STATE_WALK_BACK_1 :
                    m_currentStateFrame = EnumCharacter::SpriteStatesCharacter::STATE_WALK_BACK_2;
                    break;
                case EnumCharacter::SpriteStatesCharacter::STATE_WALK_BACK_2 :
                    m_currentStateFrame = EnumCharacter::SpriteStatesCharacter::STATE_WALK_BACK_1;
                    break;
                default:
                    break;
            }
        case EnumCharacter::ActionStatesCharacter::ATTACKING :
            switch(m_currentStateFrame)
            {
                case EnumCharacter::SpriteStatesCharacter::STATE_FRAME_TRANSITION :
                    m_currentStateFrame = m_frameTransitionTab[m_currentActionState][m_orientation];
                    break;
                case EnumCharacter::SpriteStatesCharacter::STATE_FIGHT_FRONT_1 :
                    m_currentStateFrame = EnumCharacter::SpriteStatesCharacter::STATE_FIGHT_FRONT_2;
                    break;
                case EnumCharacter::SpriteStatesCharacter::STATE_FIGHT_FRONT_2 :
                    m_currentActionState = EnumCharacter::ActionStatesCharacter::WALKING;
                    m_currentStateFrame = EnumCharacter::SpriteStatesCharacter::STATE_FRAME_TRANSITION;
                    break;
                case EnumCharacter::SpriteStatesCharacter::STATE_FIGHT_BACK_1 :
                    m_currentStateFrame = EnumCharacter::SpriteStatesCharacter::STATE_FIGHT_BACK_2;
                    break;
                case EnumCharacter::SpriteStatesCharacter::STATE_FIGHT_BACK_2 :
                    m_currentActionState = EnumCharacter::ActionStatesCharacter::WALKING;
                    m_currentStateFrame = EnumCharacter::SpriteStatesCharacter::STATE_FRAME_TRANSITION;
                    break;
                default:
                    break;
            }
        case EnumCharacter::ActionStatesCharacter::DEFENDING :
            switch(m_currentStateFrame)
            {
                case EnumCharacter::SpriteStatesCharacter::STATE_FRAME_TRANSITION :
                    m_currentStateFrame = m_frameTransitionTab[m_currentActionState][m_orientation];
                    break;
                case EnumCharacter::SpriteStatesCharacter::STATE_STAND_FRONT :
                    m_currentStateFrame = EnumCharacter::SpriteStatesCharacter::STATE_HURT_FRONT;
                    break;
                case EnumCharacter::SpriteStatesCharacter::STATE_STAND_BACK :
                    m_currentStateFrame = EnumCharacter::SpriteStatesCharacter::STATE_HURT_BACK;
                    break;
                case EnumCharacter::SpriteStatesCharacter::STATE_HURT_FRONT :
                    m_currentActionState = EnumCharacter::ActionStatesCharacter::WALKING;
                    m_currentStateFrame = EnumCharacter::SpriteStatesCharacter::STATE_FRAME_TRANSITION;
                    break;
                case EnumCharacter::SpriteStatesCharacter::STATE_HURT_BACK :
                    m_currentActionState = EnumCharacter::ActionStatesCharacter::WALKING;
                    m_currentStateFrame = EnumCharacter::SpriteStatesCharacter::STATE_FRAME_TRANSITION;
                    break;
                default:
                    break;
            }
        default:
            break;
    }

    if(EnumCharacter::SpriteStatesCharacter::STATE_FRAME_TRANSITION == m_currentStateFrame)
    {
        nextState();
    }
}
