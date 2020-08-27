#include "BattleMapData.h"

#include "QDebug"

#include <QJsonArray>
#include<QKeyEvent>

#include "PathFinding.h"

static const float coeffOrientationBonus = 1.25f;
static const float coeffOrientationNormal = 1;
static const float coeffOrientationMalus = 0.75f;

BattleMapData::BattleMapData(InterfaceQML* i_pInterfaceQml):
    m_nbTileTotal(0),
    m_pCurrentSelectedCharacter(NULL),
    m_pInterfaceQml(i_pInterfaceQml),
    m_stateBattleMap(EnumBattleMapData::StateBattleMap::DEFAULT)
{
    m_mapFilenameTilsetToIndex.clear();
    m_vecFilenameTileset.clear();
    m_vecTileArea.clear();
    m_vecCharacter.clear();
    m_vecAnimationSprite.clear();

    m_pPathFinding = new PathFinding(0, 0, 0);

    // the coeff is attributed according to the attack orientation (attacker position vs defender position)
    // and the defender orientation
    // Example
    // . . A . .  ^N
    // . . D . .  |
    // A attack D from above so attack come from North to D
    // If D orientation is North he is front of the attack => coeff = 1
    m_tabAttackOrientationCoeff[EnumCharacter::Orientation::NORTH][EnumCharacter::Orientation::NORTH] = 0.75;
    m_tabAttackOrientationCoeff[EnumCharacter::Orientation::NORTH][EnumCharacter::Orientation::SOUTH] = 1.25;
    m_tabAttackOrientationCoeff[EnumCharacter::Orientation::NORTH][EnumCharacter::Orientation::EAST] = 1;
    m_tabAttackOrientationCoeff[EnumCharacter::Orientation::NORTH][EnumCharacter::Orientation::WEST] = 1;
    m_tabAttackOrientationCoeff[EnumCharacter::Orientation::SOUTH][EnumCharacter::Orientation::NORTH] = 1.25;
    m_tabAttackOrientationCoeff[EnumCharacter::Orientation::SOUTH][EnumCharacter::Orientation::SOUTH] = 0.75;
    m_tabAttackOrientationCoeff[EnumCharacter::Orientation::SOUTH][EnumCharacter::Orientation::EAST] = 1;
    m_tabAttackOrientationCoeff[EnumCharacter::Orientation::SOUTH][EnumCharacter::Orientation::WEST] = 1;
    m_tabAttackOrientationCoeff[EnumCharacter::Orientation::EAST][EnumCharacter::Orientation::NORTH] = 1;
    m_tabAttackOrientationCoeff[EnumCharacter::Orientation::EAST][EnumCharacter::Orientation::SOUTH] = 1;
    m_tabAttackOrientationCoeff[EnumCharacter::Orientation::EAST][EnumCharacter::Orientation::EAST] = 0.75;
    m_tabAttackOrientationCoeff[EnumCharacter::Orientation::EAST][EnumCharacter::Orientation::WEST] = 1.25;
    m_tabAttackOrientationCoeff[EnumCharacter::Orientation::WEST][EnumCharacter::Orientation::NORTH] = 1;
    m_tabAttackOrientationCoeff[EnumCharacter::Orientation::WEST][EnumCharacter::Orientation::SOUTH] = 1;
    m_tabAttackOrientationCoeff[EnumCharacter::Orientation::WEST][EnumCharacter::Orientation::EAST] = 1.25;
    m_tabAttackOrientationCoeff[EnumCharacter::Orientation::WEST][EnumCharacter::Orientation::WEST] = 0.75;
}

BattleMapData::~BattleMapData()
{
    for(int i=0; i<m_vecCharacter.size(); i++)
    {
        if(m_vecCharacter[i] != NULL)
        {
            delete m_vecCharacter[i];
            m_vecCharacter[i] = NULL;
        }
    }
    m_vecCharacter.clear();
    m_vecAnimationSprite.clear();
}

void BattleMapData::generateMapData()
{
    // -------------------  Générateur de tuile sans lecture de fichier ---------------------------------
    // Cette fonction est une simulation du chargement de fichier

        m_nbTileSide = 10;
        m_nbTileTotal = m_nbTileSide * m_nbTileSide;

        m_fWidthTile = 0.15f;
        m_fHeightTile = m_fWidthTile/2.0f;//0.075

        int l_iIndexTexture = -1;

        // PathFinding
        m_pPathFinding->setNbTileSideMap(m_nbTileSide);
        l_iIndexTexture = _addFilenameTexture(m_pPathFinding->getImgTilesheetFilePath());
        if( l_iIndexTexture != -1)
        {
            m_pPathFinding->setIndexTexture(l_iIndexTexture);
        }
        l_iIndexTexture = -1;

        // --- CURSEUR INITIALISATION ---
        m_curseur.setImgFilePath(QString("C:/Users/Yaku/Documents/DeveloppementCode/PROJECT/jeuxDeRole/JeuDeRole/Ressources/ImgTest/curseur.png"));
        m_curseur.setIsVisible(true);
        m_curseur.setIndexTileAreaPathFinding(0);
        QVector2D l_tabCoordCurseur[NB_COORD_TEXTURE];
        l_tabCoordCurseur[0] = QVector2D(0.0f,1.0f);
        l_tabCoordCurseur[1] = QVector2D(1.0f,1.0f);
        l_tabCoordCurseur[2] = QVector2D(1.0f,0.0f);
        l_tabCoordCurseur[3] = QVector2D(0.0f,0.0f);
        m_curseur.setCoordTexture(l_tabCoordCurseur);
        l_iIndexTexture = _addFilenameTexture(m_curseur.getImgFilePath());
        if( l_iIndexTexture != -1)
        {
            m_curseur.setIndexTexture(l_iIndexTexture);
        }
        l_iIndexTexture = -1;

        // --- GENERATION DE 6 PERSONNAGES ---
        for(int i=0; i<6; i++)
        {
            Character* l_pCharacter = new Character();

            l_pCharacter->setSizeSide(1);
            l_pCharacter->setVecIndexTileAreaPathFinding(QVector<int>{i});
            l_pCharacter->setMoveSteps(4);

            Stats l_stats;
            l_stats.m_Armure = 4;
            l_stats.m_Dexterite = 10;
            l_stats.m_Force = 7;
            l_stats.m_Intelligence = 10;
            l_stats.m_PA = 10;
            l_stats.m_PA_max = 30;
            l_stats.m_PM = 10;
            l_stats.m_Protection = 10;
            l_stats.m_PV = 20;
            l_stats.m_PV_max = 100;

            Features l_features;
            l_features.m_sStats = l_stats;
            l_features.m_eJob = SOLDIER;
            l_features.m_eRace = HUMAN;
            l_features.m_eSex = MALE;
            l_features.m_Lvl = i;
            l_features.m_Name = "Yaku";
            l_features.m_Xp = 10;
            l_features.m_UrlImg = tabUrlMenuCharacterImg[SOLDIER][HUMAN][MALE];
            l_pCharacter->setFeatures(l_features);

            l_pCharacter->setImgTilesheetFilePath(QString("C:/Users/Yaku/Documents/DeveloppementCode/PROJECT/jeuxDeRole/JeuDeRole/Ressources/ImgTest/tilesetCharacter/tilsetLuso160x160.png"));
            QVector2D l_tabCoordCharacter[NB_COORD_TEXTURE];
            l_tabCoordCharacter[0] = QVector2D(0.0f,1.0f);
            l_tabCoordCharacter[1] = QVector2D(0.5f,1.0f);
            l_tabCoordCharacter[2] = QVector2D(0.5f,0.0f);
            l_tabCoordCharacter[3] = QVector2D(0.0f,0.0f);
            l_pCharacter->setCoordTexture(l_tabCoordCharacter);

            l_iIndexTexture = _addFilenameTexture(l_pCharacter->getImgTilesheetFilePath());
            if( l_iIndexTexture != -1)
            {
                l_pCharacter->setIndexTexture(l_iIndexTexture);
            }
            else
            {

            }
            l_iIndexTexture = -1;
            m_vecCharacter << l_pCharacter;
            m_vecAnimationSprite << l_pCharacter;
        }

        // --- GENERATION D'1 PERSONNAGE SUR PLUSIEURS CASE DE LARGE ---
//        Character* l_pCharacter = new Character();

//        l_pCharacter->setSizeSide(2);
//        l_pCharacter->setIndexTileArea(QVector<int>{0,1,2,4});

//        l_pCharacter->setImgTilesheetFilePath(QString("C:/Users/Yaku/Documents/DeveloppementCode/PROJECT/jeuxDeRole/JeuDeRole/Ressources/ImgTest/SpriteAnimation128x64Right.png"));
//        //l_pCharacter->setImgTilesheetFilePath(QString("C:/Users/Yaku/Documents/DeveloppementCode/PROJECT/jeuxDeRole/JeuDeRole/Ressources/ImgTest/DebugTileset.png"));
//        QVector2D l_tabCoordCharacter[NB_COORD_TEXTURE];
//        l_tabCoordCharacter[0] = QVector2D(0.0f,1.0f);
//        l_tabCoordCharacter[1] = QVector2D(0.5f,1.0f);
//        l_tabCoordCharacter[2] = QVector2D(0.5f,0.0f);
//        l_tabCoordCharacter[3] = QVector2D(0.0f,0.0f);
//        l_pCharacter->setCoordTexture(l_tabCoordCharacter);

//        l_iIndexTexture = _addFilenameTexture(l_pCharacter->getImgTilesheetFilePath());
//        if( l_iIndexTexture != -1)
//        {
//            l_pCharacter->setIndexTexture(l_iIndexTexture);
//        }
//        else
//        {

//        }
//        l_iIndexTexture = -1;
//        m_vecCharacter << l_pCharacter;
//        m_vecAnimationSprite << l_pCharacter;

        // GENERATION de plusieurs personnages grands
//        Character* l_pCharacter1 = new Character();
//        Character* l_pCharacter2 = new Character();
//        Character* l_pCharacter3 = new Character();

//        l_pCharacter1->setSizeSide(2);
//        l_pCharacter2->setSizeSide(2);
//        l_pCharacter3->setSizeSide(2);

//        l_pCharacter1->setIndexTileArea(QVector<int>{0,1,2,4});
//        l_pCharacter2->setIndexTileArea(QVector<int>{3,6,7,10});
//        l_pCharacter3->setIndexTileArea(QVector<int>{5,8,9,14});

//        l_pCharacter1->setImgTilesheetFilePath(QString("C:/Users/Yaku/Documents/DeveloppementCode/PROJECT/jeuxDeRole/JeuDeRole/Ressources/ImgTest/SpriteAnimation128x64Right.png"));
//        l_pCharacter2->setImgTilesheetFilePath(QString("C:/Users/Yaku/Documents/DeveloppementCode/PROJECT/jeuxDeRole/JeuDeRole/Ressources/ImgTest/SpriteAnimation128x64Right.png"));
//        l_pCharacter3->setImgTilesheetFilePath(QString("C:/Users/Yaku/Documents/DeveloppementCode/PROJECT/jeuxDeRole/JeuDeRole/Ressources/ImgTest/SpriteAnimation128x64Right.png"));


//        QVector2D l_tabCoordCharacter[NB_COORD_TEXTURE];
//        l_tabCoordCharacter[0] = QVector2D(0.0f,1.0f);
//        l_tabCoordCharacter[1] = QVector2D(0.5f,1.0f);
//        l_tabCoordCharacter[2] = QVector2D(0.5f,0.0f);
//        l_tabCoordCharacter[3] = QVector2D(0.0f,0.0f);
//        l_pCharacter1->setCoordTexture(l_tabCoordCharacter);
//        l_pCharacter2->setCoordTexture(l_tabCoordCharacter);
//        l_pCharacter3->setCoordTexture(l_tabCoordCharacter);

//        l_iIndexTexture = _addFilenameTexture(l_pCharacter1->getImgTilesheetFilePath());
//        if( l_iIndexTexture != -1)
//        {
//            l_pCharacter1->setIndexTexture(l_iIndexTexture);
//        }
//        l_iIndexTexture = -1;

//        l_iIndexTexture = _addFilenameTexture(l_pCharacter2->getImgTilesheetFilePath());
//        if( l_iIndexTexture != -1)
//        {
//            l_pCharacter2->setIndexTexture(l_iIndexTexture);
//        }
//        l_iIndexTexture = -1;

//        l_iIndexTexture = _addFilenameTexture(l_pCharacter3->getImgTilesheetFilePath());
//        if( l_iIndexTexture != -1)
//        {
//            l_pCharacter3->setIndexTexture(l_iIndexTexture);
//        }
//        l_iIndexTexture = -1;

//        m_vecCharacter << l_pCharacter1;
//        m_vecAnimationSprite << l_pCharacter1;
//        m_vecCharacter << l_pCharacter2;
//        m_vecAnimationSprite << l_pCharacter2;
//        m_vecCharacter << l_pCharacter3;
//        m_vecAnimationSprite << l_pCharacter3;



        // --- GENERATION DES TUILES ---
        for(int i = 0; i<m_nbTileTotal; i++)
        {
            TileArea l_tileArea;
            l_tileArea.m_maskPresence.tile = 0;
            l_tileArea.m_maskPresence.character = 0;
            l_tileArea.m_maskPresence.object= 0;
            l_tileArea.m_maskPresence.cursor = 0;
            l_tileArea.m_maskPresence.pathFinding = 0;

             //TODO : clarifier la hauteur tuile et faire une différence entre la hauteur du bord et la hauteur du diamant !!!
            l_tileArea.m_tile.setElevationTile(0.02f);

            l_tileArea.m_tile.setImgTilesheetFilePath(QString("C:/Users/Yaku/Documents/DeveloppementCode/PROJECT/jeuxDeRole/JeuDeRole/Ressources/ImgTest/tilsetIsometric/testTileSet.png"));

            if(i%2 == 0)
            {
                l_tileArea.m_tile.addCoord(QVector2D(0.0f, 0.25f));
                l_tileArea.m_tile.addCoord(QVector2D(0.5f, 0.25f));
                l_tileArea.m_tile.addCoord(QVector2D(0.5f, 0.0f));
                l_tileArea.m_tile.addCoord(QVector2D(0.0f, 0.0f));
            }
            else
            {
                l_tileArea.m_tile.addCoord(QVector2D(0.5f, 0.25f));
                l_tileArea.m_tile.addCoord(QVector2D(1.0f, 0.25f));
                l_tileArea.m_tile.addCoord(QVector2D(1.0f, 0.0f));
                l_tileArea.m_tile.addCoord(QVector2D(0.5f, 0.0f));

            }

            l_iIndexTexture = _addFilenameTexture(l_tileArea.m_tile.getImgTilesheetFilePath());
            if( l_iIndexTexture != -1)
            {
                l_tileArea.m_tile.setIndexTexture(l_iIndexTexture);
            }
            else
            {

            }
            l_iIndexTexture = -1;

            l_tileArea.m_maskPresence.tile = 1;

            // Add the tile in the container
            m_vecTileArea << l_tileArea;
        }

        _initVecTileAreaPathFinding();

        _associateTileAreaObject();
}

void BattleMapData::loadDataBattleMap(const QJsonObject &json)
{
    int l_iIndexTexture = -1;

    // Loadind battleMapData from the json file
    QJsonObject l_jsonObjBattleMap = json["battleMap"].toObject();

    m_nbTileTotal = l_jsonObjBattleMap["nbTileTotal"].toInt();
    m_nbTileSide = l_jsonObjBattleMap["nbTileSide"].toInt();
    m_fWidthTile = l_jsonObjBattleMap["widthTile"].toDouble();
    m_fHeightTile = l_jsonObjBattleMap["heightTile"].toDouble();

    // Prepare vector AnimationSprite
    m_vecAnimationSprite.clear();

    // Load Characters
    m_vecCharacter.clear();
    QJsonArray characterArray = l_jsonObjBattleMap["characters"].toArray();
    for (int itCharacter = 0; itCharacter < characterArray.size(); itCharacter++)
    {
        QJsonObject characterObject = characterArray[itCharacter].toObject();
        Character* l_pCharacter = new Character();
        l_pCharacter->loadCharacterData(characterObject);


        l_iIndexTexture = _addFilenameTexture(l_pCharacter->getImgTilesheetFilePath());
        if( l_iIndexTexture != -1)
        {
            l_pCharacter->setIndexTexture(l_iIndexTexture);
        }
        else
        {

        }
        l_iIndexTexture = -1;

        m_vecCharacter << l_pCharacter;
        m_vecAnimationSprite << l_pCharacter;
    }


    // Create All TileArea
    m_vecTileArea.clear();

    // Load Tiles Data
    int indexTileTexture = 0;
    QJsonArray tileArray = l_jsonObjBattleMap["tiles"].toArray();
    for (int itTile = 0; itTile < tileArray.size(); itTile++)
    {
        QJsonObject tileObject = tileArray[itTile].toObject();
        TileArea l_tileArea;
        l_tileArea.m_tile.loadTileData(tileObject);

        l_iIndexTexture = _addFilenameTexture(l_tileArea.m_tile.getImgTilesheetFilePath());
        if( l_iIndexTexture != -1)
        {
            l_tileArea.m_tile.setIndexTexture(l_iIndexTexture);
        }
        else
        {

        }
        l_iIndexTexture = -1;

        l_tileArea.m_maskPresence.tile = 1;

        m_vecTileArea << l_tileArea;
    }

    _associateTileAreaObject();

}

int BattleMapData::_addFilenameTexture(QString i_strFilenameTexture)
{
    int index = -1;

    // Check if the texture's tilset filename is already known
    std::map<QString, int>::iterator itTileset;
    itTileset = m_mapFilenameTilsetToIndex.find(i_strFilenameTexture);

    // Known Tilset
    if(itTileset != m_mapFilenameTilsetToIndex.end())
    {
        index = itTileset->second;
    }
    // Unknown Tilset - add a new pair and increment indexTileTexture
    else
    {
        m_vecFilenameTileset << i_strFilenameTexture;

        std::pair<QString, int> l_pair (i_strFilenameTexture, m_vecFilenameTileset.size()-1);
        m_mapFilenameTilsetToIndex.insert(l_pair);
        index = m_vecFilenameTileset.size()-1;
    }

    return index;
}

void BattleMapData::saveDataBattleMap(QJsonObject &json)const
{
    QJsonObject l_jsonObjBattleMap;
    l_jsonObjBattleMap["nbTileTotal"] = m_nbTileTotal;
    l_jsonObjBattleMap["nbTileSide"]  = m_nbTileSide;
    l_jsonObjBattleMap["widthTile"]   = m_fWidthTile;
    l_jsonObjBattleMap["heightTile"]  = m_fHeightTile;

    // Save Character
    QJsonArray l_arrayJsonCharacter;    
    for(int i=0; i<m_vecCharacter.size(); i++)
    {
        QJsonObject characterJsonObject;
        m_vecCharacter[i]->saveCharacterData(characterJsonObject);
        l_arrayJsonCharacter.append(characterJsonObject);
    }
    l_jsonObjBattleMap["characters"] = l_arrayJsonCharacter;


    // Save Tile
    QJsonArray l_arrayJsonTiles;
    QVector<TileArea>::const_iterator itTileArea;
    for(itTileArea = m_vecTileArea.begin(); itTileArea != m_vecTileArea.end(); itTileArea++)
    {
        QJsonObject tileJsonObject;
        itTileArea->m_tile.saveTileData(tileJsonObject);
        l_arrayJsonTiles.append(tileJsonObject);
    }
    l_jsonObjBattleMap["tiles"] = l_arrayJsonTiles;

    // Save BattleMap
    json["battleMap"] = l_jsonObjBattleMap;
}

void BattleMapData::_associateTileAreaObject()
{
    // Associate TileArea with Curseur
    m_vecTileAreaPathFinding[m_curseur.getIndexTileAreaPathFinding()]->m_maskPresence.cursor = 1;

    // Associate TileArea with Character
    for(int i=0; i<m_vecCharacter.size(); i++)
    {
        for(int j=0; j<m_vecCharacter[i]->getVecIndexTileAreaPathFinding().size(); j++)
        {
            m_vecTileAreaPathFinding[m_vecCharacter[i]->getVecIndexTileAreaPathFinding()[j]]->m_pCharacter = m_vecCharacter[i];
            m_vecTileAreaPathFinding[m_vecCharacter[i]->getVecIndexTileAreaPathFinding()[j]]->m_maskPresence.character = 1;
        }
    }
}

// TODO : il faudra mettre des conditions suivant l'état courant
// TODO : Voir si on ne peut pas améliorer l'algo
void BattleMapData::eventKeyBoard(KeyValue i_eKey)
{
    int l_iNewIndex = m_curseur.getIndexTileAreaPathFinding();

    switch (i_eKey)
    {
        case ENTER :
            if(m_pPathFinding->getIsActivated() &&
               m_pPathFinding->isIndexInPathFinding(m_curseur.getIndexTileAreaPathFinding()) &&
               m_vecTileAreaPathFinding[m_curseur.getIndexTileAreaPathFinding()]->m_maskPresence.character == 0 &&
               m_stateBattleMap == EnumBattleMapData::StateBattleMap::MOVING)
            {
                _moveCharacter(m_curseur.getIndexTileAreaPathFinding());
                m_stateBattleMap = EnumBattleMapData::StateBattleMap::DEFAULT;
            }
            else if(m_vecTileAreaPathFinding[m_curseur.getIndexTileAreaPathFinding()]->m_maskPresence.character == 1 &&
                    !m_pPathFinding->getIsActivated() &&
                    m_stateBattleMap == EnumBattleMapData::StateBattleMap::DEFAULT)
            {
                _clearPathFinding();
                m_pCurrentSelectedCharacter = m_vecTileAreaPathFinding[m_curseur.getIndexTileAreaPathFinding()]->m_pCharacter;
                _pathFinding(m_curseur.getIndexTileAreaPathFinding(), 3);
                m_stateBattleMap = EnumBattleMapData::StateBattleMap::MOVING;
            }
            else if(m_pPathFinding->getIsActivated() &&
                    m_pPathFinding->isIndexInPathFinding(m_curseur.getIndexTileAreaPathFinding()) &&
                    m_vecTileAreaPathFinding[m_curseur.getIndexTileAreaPathFinding()]->m_maskPresence.character == 1 &&
                    m_stateBattleMap == EnumBattleMapData::StateBattleMap::FIGHTING)
            {
                _fight(m_pCurrentSelectedCharacter, m_vecTileAreaPathFinding[m_curseur.getIndexTileAreaPathFinding()]->m_pCharacter);
                m_stateBattleMap = EnumBattleMapData::StateBattleMap::DEFAULT;
            }
            else
            {
                _clearPathFinding();
                m_stateBattleMap = EnumBattleMapData::StateBattleMap::DEFAULT;
            }
            break;
        case BACK_SPACE :
            qDebug()<<"InterfaceQML::eventFromQML()--> BACK_SPACE";
            break;
        case LEFT :
            if(EnumBattleMapData::StateBattleMap::ORIENTING== m_stateBattleMap)
            {
                m_vecTileAreaPathFinding[m_curseur.getIndexTileAreaPathFinding()]->m_pCharacter->setOrientation(EnumCharacter::Orientation::WEST);
            }
            else
            {
                l_iNewIndex++;
                _changeIndexCursor(l_iNewIndex);
            }
            break;
        case RIGHT :
            if(EnumBattleMapData::StateBattleMap::ORIENTING== m_stateBattleMap)
            {
                m_vecTileAreaPathFinding[m_curseur.getIndexTileAreaPathFinding()]->m_pCharacter->setOrientation(EnumCharacter::Orientation::EAST);
            }
            else
            {
                l_iNewIndex--;
                _changeIndexCursor(l_iNewIndex);
            }
            break;
        case UP :
            if(EnumBattleMapData::StateBattleMap::ORIENTING== m_stateBattleMap)
            {
                m_vecTileAreaPathFinding[m_curseur.getIndexTileAreaPathFinding()]->m_pCharacter->setOrientation(EnumCharacter::Orientation::NORTH);
            }
            else
            {
                l_iNewIndex += m_nbTileSide;
                _changeIndexCursor(l_iNewIndex);
            }
            break;
        case DOWN :
            if(EnumBattleMapData::StateBattleMap::ORIENTING== m_stateBattleMap)
            {
                m_vecTileAreaPathFinding[m_curseur.getIndexTileAreaPathFinding()]->m_pCharacter->setOrientation(EnumCharacter::Orientation::SOUTH);
            }
            else
            {
                l_iNewIndex -= m_nbTileSide;
                _changeIndexCursor(l_iNewIndex);
            }
            break;
        default:
        break;
    }
}

void BattleMapData::fightRequest()
{
    _clearPathFinding();
    m_pCurrentSelectedCharacter = m_vecTileAreaPathFinding[m_curseur.getIndexTileAreaPathFinding()]->m_pCharacter;
    _pathFinding(m_curseur.getIndexTileAreaPathFinding(), 1);
    m_stateBattleMap = EnumBattleMapData::StateBattleMap::FIGHTING;
}

void BattleMapData::orientationRequest()
{
    m_pCurrentSelectedCharacter = m_vecTileAreaPathFinding[m_curseur.getIndexTileAreaPathFinding()]->m_pCharacter;
    m_stateBattleMap = EnumBattleMapData::StateBattleMap::ORIENTING;
}

void BattleMapData::_fight(Character* pFighterAttack, Character* pFighterDefense)
{
    EnumCharacter::Orientation attackOrientation = _attackOrientation(pFighterAttack, pFighterDefense);

    float attackOrientationCoeff = m_tabAttackOrientationCoeff[attackOrientation][pFighterDefense->getOrientation()];

    // Change Character State
    pFighterAttack->attacking(pFighterDefense->getVecIndexTileAreaPathFinding()[0], m_nbTileSide);

    // Dommage
    int l_totalDommage = ((pFighterAttack->getFeatures().m_sStats.m_Force /*+ equipment + bonus capacité*/)
                           * attackOrientationCoeff /* * efficacité type * facteur criticité*/)
                          - pFighterDefense->getFeatures().m_sStats.m_Armure;
    pFighterDefense->takingDamage(l_totalDommage);

    _clearPathFinding();

    m_pInterfaceQml->setFeaturesCharacter(pFighterDefense->getFeatures());
}

// Find attack orientation relative to the defender position
EnumCharacter::Orientation BattleMapData::_attackOrientation(Character* pFighterAttack, Character* pFighterDefense)
{
    //TODO : ATTENTION voir comment cela se comporte avec des character qui font plusieurs cases
    //de plus cela ne couvre pas les cas d attack sur plusieurs cases (voir algo de pathfinding pour attack ?)

    int result = pFighterAttack->getVecIndexTileAreaPathFinding()[0] - pFighterDefense->getVecIndexTileAreaPathFinding()[0];
    if(1 == result)
    {
        return EnumCharacter::Orientation::WEST;
    }
    else if(-1 == result)
    {
        return EnumCharacter::Orientation::EAST;
    }
    else if(m_nbTileSide == result)
    {
        return EnumCharacter::Orientation::NORTH;
    }
    else if(-m_nbTileSide == result)
    {
        return EnumCharacter::Orientation::SOUTH;
    }
    else
    {
        qDebug()<<"ERROR attacking orientation";
        return EnumCharacter::Orientation::END_ORIENTATION;
    }
}

// Check if index is inside the map's bounds and set the new index
void BattleMapData::_changeIndexCursor(int i_newIndex)
{
    if(i_newIndex >= 0 && i_newIndex < m_nbTileSide*m_nbTileSide )
    {
        m_vecTileAreaPathFinding[m_curseur.getIndexTileAreaPathFinding()]->m_maskPresence.cursor = 0;
        m_vecTileAreaPathFinding[i_newIndex]->m_maskPresence.cursor = 1;
        m_curseur.setIndexTileAreaPathFinding(i_newIndex);

        if(m_vecTileAreaPathFinding[i_newIndex]->m_maskPresence.character == 1)
        {
            m_pInterfaceQml->setIsCursorOnCharacter(true);
            m_pInterfaceQml->setFeaturesCharacter(m_vecTileAreaPathFinding[i_newIndex]->m_pCharacter->getFeatures());
        }
        else
        {
            m_pInterfaceQml->setIsCursorOnCharacter(false);
        }
    }
    else
    {
    }
}

void BattleMapData::_moveCharacter(int i_tileIndexSelected)
{
    // Calcul the new position and handle the case where character is several tile size side
    // Find the closer tile from the selected tile by cursor among the character tiles
    int l_iLineIndexSelectedTile = i_tileIndexSelected / m_nbTileSide;
    int l_iColumnIndexSelectedTile = i_tileIndexSelected % m_nbTileSide;
    int l_iLineIndexTile = -1;
    int l_iColumnIndexTile = -1;
    int l_iMinOffsetBetweenTile = 1000;// 1000 is the default value
    int l_iIndexClosestTile = -1;
    int l_iOffsetBetweenTile = -1;
    int l_iOffsetLine = 0;
    int l_iOffsetColumn = 0;
    for(int i=0; i<m_pCurrentSelectedCharacter->getVecIndexTileAreaPathFinding().size(); i++)
    {
        l_iLineIndexTile = m_pCurrentSelectedCharacter->getVecIndexTileAreaPathFinding()[i] / m_nbTileSide;
        l_iColumnIndexTile = m_pCurrentSelectedCharacter->getVecIndexTileAreaPathFinding()[i] % m_nbTileSide;
        l_iOffsetBetweenTile = abs(l_iLineIndexTile-l_iLineIndexSelectedTile) + abs(l_iColumnIndexTile-l_iColumnIndexSelectedTile);
        if(l_iMinOffsetBetweenTile > l_iOffsetBetweenTile)
        {
           l_iMinOffsetBetweenTile = l_iOffsetBetweenTile;
           l_iOffsetLine = l_iLineIndexSelectedTile - l_iLineIndexTile;
           l_iOffsetColumn = l_iColumnIndexSelectedTile - l_iColumnIndexTile;
           l_iIndexClosestTile = m_pCurrentSelectedCharacter->getVecIndexTileAreaPathFinding()[i];
        }
    }

    // Calcul the new position
    QVector<int> l_vecNewPositionCharacter;
    for(int i=0; i<m_pCurrentSelectedCharacter->getVecIndexTileAreaPathFinding().size(); i++)
    {
       l_vecNewPositionCharacter<< m_pCurrentSelectedCharacter->getVecIndexTileAreaPathFinding()[i]
                                   + (l_iOffsetLine*m_nbTileSide) + l_iOffsetColumn;
    }

    // Reset the old position
    for(int i=0; i<m_pCurrentSelectedCharacter->getVecIndexTileAreaPathFinding().size(); i++)
    {
        m_vecTileAreaPathFinding[m_pCurrentSelectedCharacter->getVecIndexTileAreaPathFinding()[i]]->m_pCharacter = NULL;
        m_vecTileAreaPathFinding[m_pCurrentSelectedCharacter->getVecIndexTileAreaPathFinding()[i]]->m_maskPresence.character = 0;
    }

    // Set the new position
    m_pCurrentSelectedCharacter->setVecIndexTileAreaPathFinding(l_vecNewPositionCharacter);
    for(int i=0; i<m_pCurrentSelectedCharacter->getVecIndexTileAreaPathFinding().size(); i++)
    {
        m_vecTileAreaPathFinding[m_pCurrentSelectedCharacter->getVecIndexTileAreaPathFinding()[i]]->m_pCharacter = m_pCurrentSelectedCharacter;
        m_vecTileAreaPathFinding[m_pCurrentSelectedCharacter->getVecIndexTileAreaPathFinding()[i]]->m_maskPresence.character = 1;
    }

    _clearPathFinding();
}

void BattleMapData::_initVecTileAreaPathFinding()
{
    m_vecTileAreaPathFinding.resize(m_nbTileSide*m_nbTileSide);

    int l_iNbValLine = 1, l_iCountLine = 1, l_iCountVal = 0;

    for(int i =0; i<m_nbTileSide*m_nbTileSide; i++)
    {
        l_iCountVal++;

        if(l_iCountLine <= m_nbTileSide)
        {
            m_vecTileAreaPathFinding[(l_iCountLine-l_iCountVal)+((l_iCountVal-1)*m_nbTileSide)] = &m_vecTileArea[i];
            m_vecTileAreaPathFinding[(l_iCountLine-l_iCountVal)+((l_iCountVal-1)*m_nbTileSide)]->m_indexVecPathFinding =
            (l_iCountLine-l_iCountVal) + (l_iCountVal-1)*m_nbTileSide;
        }
        else
        {
            m_vecTileAreaPathFinding[((l_iCountLine-m_nbTileSide)*m_nbTileSide) + (l_iCountVal*(m_nbTileSide-1))] = &m_vecTileArea[i];
            m_vecTileAreaPathFinding[((l_iCountLine-m_nbTileSide)*m_nbTileSide) + (l_iCountVal*(m_nbTileSide-1))]->m_indexVecPathFinding =
            ((l_iCountLine-m_nbTileSide)*m_nbTileSide) + (l_iCountVal*(m_nbTileSide-1));
        }


        if(l_iCountVal == l_iNbValLine)// Change line
        {
            l_iCountLine++;
            if(l_iCountLine <= m_nbTileSide)
            {
                l_iNbValLine++;
            }
            else
            {
                l_iNbValLine--;
            }
            l_iCountVal=0;
        }
    }
}

void BattleMapData::_clearPathFinding()
{
    for(int i=0; i<m_pPathFinding->getVecIndexPathFinding().size(); i++)
    {
        m_vecTileAreaPathFinding[m_pPathFinding->getVecIndexPathFinding()[i]]->m_maskPresence.pathFinding = 0;
    }

    m_pPathFinding->clearVecPathFinding();
    m_pPathFinding->setIsActivated(false);
}

void BattleMapData::_pathFinding(int indexTileCursor, int depthLevel)
{
    QVector<int> l_vecTilePathFinding;
    if(m_pCurrentSelectedCharacter != NULL)
    {
        m_pPathFinding->setDepthPathFinding(depthLevel);
        m_pPathFinding->setIsActivated(true);

        // Handle the case where character has a several tile's size side
       for(int i=0; i<(m_pCurrentSelectedCharacter->getSizeSide()*m_pCurrentSelectedCharacter->getSizeSide()); i++)
       {
          m_pPathFinding->setIndexOrigin(m_pCurrentSelectedCharacter->getVecIndexTileAreaPathFinding()[i]);

          for(int j=0; j<m_pPathFinding->getVecIndexPathFinding().size(); j++)
          {
              if(!m_pCurrentSelectedCharacter->getVecIndexTileAreaPathFinding().contains(m_pPathFinding->getVecIndexPathFinding()[j])
                 && !l_vecTilePathFinding.contains(m_pPathFinding->getVecIndexPathFinding()[j]))
              {
                 l_vecTilePathFinding << m_pPathFinding->getVecIndexPathFinding()[j];
              }
          }
       }

       for(int i=0; i<l_vecTilePathFinding.size(); i++)
       {
          m_vecTileAreaPathFinding[m_pPathFinding->getVecIndexPathFinding()[i]]->m_maskPresence.pathFinding = 1;
       }
    }
}


