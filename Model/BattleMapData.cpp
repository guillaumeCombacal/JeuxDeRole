#include "BattleMapData.h"

#include "QDebug"

#include <QJsonArray>
#include<QKeyEvent>
#include<QMutex>

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

    m_pPathFinding = new PathFinding(0, 0);

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
    // Cette fonction est une simulation du chargement de fichier JSON

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

        // List de character pouvant etre chargés dans la battlemap
        QStringList list = {"Soldier", "Ritz", "blackMage"};
        m_pInterfaceQml->setListCharacterToAddInBattleMap(list);

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
            l_features.m_eNature = HUMAN;
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
            //m_vecCharacter << l_pCharacter;
            //m_vecAnimationSprite << l_pCharacter;
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
        for(int i = 0, j=0; i<m_nbTileTotal; i++)
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

            // Index de tuiles
            if(j==0)
            {
                // tile 1
                l_tileArea.m_tile.addCoord(QVector2D(0.0f, 0.25f));
                l_tileArea.m_tile.addCoord(QVector2D(0.5f, 0.25f));
                l_tileArea.m_tile.addCoord(QVector2D(0.5f, 0.0f));
                l_tileArea.m_tile.addCoord(QVector2D(0.0f, 0.0f));
            }
            else if(j==1)
            {
                // tile 2
                l_tileArea.m_tile.addCoord(QVector2D(0.5f, 0.25f));
                l_tileArea.m_tile.addCoord(QVector2D(1.0f, 0.25f));
                l_tileArea.m_tile.addCoord(QVector2D(1.0f, 0.0f));
                l_tileArea.m_tile.addCoord(QVector2D(0.5f, 0.0f));
            }
            else if(j==2)
            {
                // tile 3
                l_tileArea.m_tile.addCoord(QVector2D(0.0f, 0.5f));
                l_tileArea.m_tile.addCoord(QVector2D(0.5f, 0.5f));
                l_tileArea.m_tile.addCoord(QVector2D(0.5f, 0.25f));
                l_tileArea.m_tile.addCoord(QVector2D(0.0f, 0.25f));
            }

            if(j==2)
            {
                j=0;
            }
            else
            {
                j++;
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

// TODO : Voir si on ne peut pas améliorer l'algo (création de classe de State avec une StateMachine ?)
void BattleMapData::eventKeyBoard(KeyValue i_eKey)
{
    switch (i_eKey)
    {
        case ENTER :
            if(m_pPathFinding->getIsActivated() &&
               m_pPathFinding->getVecIndexPathFinding().contains(m_curseur.getIndexTileAreaPathFinding())/*m_pPathFinding->isIndexAlreadyInPathFinding(m_curseur.getIndexTileAreaPathFinding())*/ &&
               m_vecTileAreaPathFinding[m_curseur.getIndexTileAreaPathFinding()]->m_maskPresence.character == 0 &&
               m_stateBattleMap == EnumBattleMapData::StateBattleMap::MOVING)
            {
                int moveOffset = m_curseur.getIndexTileAreaPathFinding() - m_pCurrentSelectedCharacter->getVecIndexTileAreaPathFinding()[0];
                if(_isCharacterAuthorizedToMove(moveOffset))
                {
                    _moveCharacter(moveOffset);
                    _clearPathFinding();
                    m_curseur.setIsSelectingCharacter(false);
                    m_stateBattleMap = EnumBattleMapData::StateBattleMap::DEFAULT;
                }
            }
            else if(m_vecTileAreaPathFinding[m_curseur.getIndexTileAreaPathFinding()]->m_maskPresence.character == 1 &&
                    !m_pPathFinding->getIsActivated() &&
                    m_stateBattleMap == EnumBattleMapData::StateBattleMap::DEFAULT)
            {
                _clearPathFinding();
                m_pCurrentSelectedCharacter = m_vecTileAreaPathFinding[m_curseur.getIndexTileAreaPathFinding()]->m_pCharacter;
                _pathFinding(m_curseur.getIndexTileAreaPathFinding(), 3);
                m_curseur.setIsSelectingCharacter(true);
                m_stateBattleMap = EnumBattleMapData::StateBattleMap::MOVING;
            }
            else if(m_pPathFinding->getIsActivated() &&
                    m_pPathFinding->getVecIndexPathFinding().contains(m_curseur.getIndexTileAreaPathFinding())/*m_pPathFinding->isIndexAlreadyInPathFinding(m_curseur.getIndexTileAreaPathFinding())*/ &&
                    m_vecTileAreaPathFinding[m_curseur.getIndexTileAreaPathFinding()]->m_maskPresence.character == 1 &&
                    m_stateBattleMap == EnumBattleMapData::StateBattleMap::FIGHTING)
            {
                _fight(m_pCurrentSelectedCharacter, m_vecTileAreaPathFinding[m_curseur.getIndexTileAreaPathFinding()]->m_pCharacter);
                m_stateBattleMap = EnumBattleMapData::StateBattleMap::DEFAULT;
            }
            else if(m_stateBattleMap == EnumBattleMapData::StateBattleMap::ADDING_NEW_CHARACTER)
            {
                m_pCurrentSelectedCharacter = NULL;
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
            if(EnumBattleMapData::StateBattleMap::ORIENTING == m_stateBattleMap)
            {
                m_vecTileAreaPathFinding[m_curseur.getIndexTileAreaPathFinding()]->m_pCharacter->setOrientation(EnumCharacter::Orientation::WEST);
            }
            else if(EnumBattleMapData::StateBattleMap::ADDING_NEW_CHARACTER == m_stateBattleMap)
            {
                if(NULL != m_pCurrentSelectedCharacter)
                {
                     _changeIndexSelectedCharacterToAdd(m_pCurrentSelectedCharacter->getVecIndexTileAreaPathFinding(), 1);
                }
            }
            else if(m_curseur.getIsSelectingCharacter())
            {
                _selectNewPositionCharacter(1);
            }
            else
            {
                _changeIndexCursor(1);
            }
            break;
        case RIGHT :
            if(EnumBattleMapData::StateBattleMap::ORIENTING == m_stateBattleMap)
            {
                m_vecTileAreaPathFinding[m_curseur.getIndexTileAreaPathFinding()]->m_pCharacter->setOrientation(EnumCharacter::Orientation::EAST);
            }
            else if(EnumBattleMapData::StateBattleMap::ADDING_NEW_CHARACTER == m_stateBattleMap)
            {
                if(NULL != m_pCurrentSelectedCharacter)
                {
                    _changeIndexSelectedCharacterToAdd(m_pCurrentSelectedCharacter->getVecIndexTileAreaPathFinding(), -1);
                }
            }
            else if(m_curseur.getIsSelectingCharacter())
            {
                _selectNewPositionCharacter(-1);
            }
            else
            {
                _changeIndexCursor(-1);
            }
            break;
        case UP :
            if(EnumBattleMapData::StateBattleMap::ORIENTING== m_stateBattleMap)
            {
                m_vecTileAreaPathFinding[m_curseur.getIndexTileAreaPathFinding()]->m_pCharacter->setOrientation(EnumCharacter::Orientation::NORTH);
            }
            else if(EnumBattleMapData::StateBattleMap::ADDING_NEW_CHARACTER == m_stateBattleMap)
            {
                if(NULL != m_pCurrentSelectedCharacter)
                {
                    _changeIndexSelectedCharacterToAdd(m_pCurrentSelectedCharacter->getVecIndexTileAreaPathFinding(), m_nbTileSide);
                }
            }
            else if(m_curseur.getIsSelectingCharacter())
            {
                _selectNewPositionCharacter(m_nbTileSide);
            }
            else
            {
                _changeIndexCursor(m_nbTileSide);
            }
            break;
        case DOWN :
            if(EnumBattleMapData::StateBattleMap::ORIENTING== m_stateBattleMap)
            {
                m_vecTileAreaPathFinding[m_curseur.getIndexTileAreaPathFinding()]->m_pCharacter->setOrientation(EnumCharacter::Orientation::SOUTH);
            }
            else if(EnumBattleMapData::StateBattleMap::ADDING_NEW_CHARACTER == m_stateBattleMap)
            {
                if(NULL != m_pCurrentSelectedCharacter)
                {
                     _changeIndexSelectedCharacterToAdd(m_pCurrentSelectedCharacter->getVecIndexTileAreaPathFinding(), -m_nbTileSide);
                }
            }
            else if(m_curseur.getIsSelectingCharacter())
            {
                _selectNewPositionCharacter(-m_nbTileSide);
            }
            else
            {
                _changeIndexCursor(-m_nbTileSide);
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

void BattleMapData::selectCharacterToAddInBattle(QString name, QString job, QString nature, int lvl)
{
    //TODO : bouchonné à changer plus tard /////////////////////////
    Character* l_pCharacter = new Character();

    l_pCharacter->setSizeSide(1);
    l_pCharacter->setVecIndexTileAreaPathFinding(_identifyInitPositionCharacter(l_pCharacter->getSizeSide()));
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
    l_features.m_eNature = HUMAN;
    l_features.m_eSex = MALE;
    l_features.m_Lvl = 10;
    l_features.m_Name = name;
    l_features.m_Xp = 10;
    l_features.m_UrlImg = tabUrlMenuCharacterImg[SOLDIER][HUMAN][MALE];
    l_pCharacter->setFeatures(l_features);

    l_pCharacter->setImgTilesheetFilePath(QString("C:/Users/Yaku/Documents/DeveloppementCode/PROJECT/jeuxDeRole/JeuDeRole/Ressources/ImgTest/tilesetCharacter/tilsetRitz160x160.png"));

    // Used just for init, the real coords will be calculated by the character himself with his state
    QVector2D l_tabCoordCharacter[NB_COORD_TEXTURE];
    l_tabCoordCharacter[0] = QVector2D(0.0f,0.0f);
    l_tabCoordCharacter[1] = QVector2D(0.0f,0.0f);
    l_tabCoordCharacter[2] = QVector2D(0.0f,0.0f);
    l_tabCoordCharacter[3] = QVector2D(0.0f,0.0f);
    l_pCharacter->setCoordTexture(l_tabCoordCharacter);

    int l_iIndexTexture = _addFilenameTexture(l_pCharacter->getImgTilesheetFilePath());
    if( l_iIndexTexture != -1)
    {
        l_pCharacter->setIndexTexture(l_iIndexTexture);
        emit addIndexTexture(l_iIndexTexture);
    }
    else
    {

    }
    l_iIndexTexture = -1;
    m_vecCharacter << l_pCharacter;
    m_vecAnimationSprite << l_pCharacter;

    for(int i=0; i < l_pCharacter->getVecIndexTileAreaPathFinding().length(); i++)
    {
        m_vecTileAreaPathFinding[l_pCharacter->getVecIndexTileAreaPathFinding()[i]]->m_pCharacter = l_pCharacter;
        m_vecTileAreaPathFinding[l_pCharacter->getVecIndexTileAreaPathFinding()[i]]->m_maskPresence.character = 1;
    }

    m_pCurrentSelectedCharacter = l_pCharacter;
    ////////////////////////////////////////////////////////////////
}

// Default position is tile 0 or the closest iteration possible
// the tested tile in case of several tile character is the low tile, from which the others tiles are tested
QVector<int> BattleMapData::_identifyInitPositionCharacter(int sizeSide)
{
   QVector<int> initPosition;
   int indexTile = 0;
   bool isCharacterPresent = true;
   for(int i=0; i<(m_nbTileSide*m_nbTileSide)-(sizeSide-1) && initPosition.size() != (sizeSide*sizeSide); i++)
   {
      indexTile  = i;// the low tile
      initPosition.clear();
      if(m_vecTileAreaPathFinding[indexTile]->m_maskPresence.character != 1)
      {
          isCharacterPresent=false;
          for(int j=0; j<sizeSide && !isCharacterPresent; j++)
          {
              indexTile = i+(j*m_nbTileSide);
              if(m_vecTileAreaPathFinding[indexTile]->m_maskPresence.character == 1)
              {
                isCharacterPresent = true;
              }

              for(int k=0; k<sizeSide && !isCharacterPresent; k++)
              {
                  indexTile += k;
                  if(m_vecTileAreaPathFinding[indexTile]->m_maskPresence.character == 1)
                  {
                    isCharacterPresent = true;
                  }
                  else
                  {
                      initPosition.append(indexTile);
                  }
              }
          }
      }
   }
   return initPosition;
}

void BattleMapData::enterAddingCharacterState()
{
    m_stateBattleMap = EnumBattleMapData::StateBattleMap::ADDING_NEW_CHARACTER;
}

void BattleMapData::finishAddingCharacterState()
{
    m_stateBattleMap = EnumBattleMapData::StateBattleMap::DEFAULT;
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

void BattleMapData::_changeIndexSelectedCharacterToAdd(QVector<int> initialPosition, int step, int nbIteration/*=1*/)
{
    int nbTileOK = 0;
    for(int i=0; i<initialPosition.size(); i++)
    {
        if(_checkNewPositionToMoveCharacter(initialPosition[i], step*nbIteration, step))
        {
            // If a character is already on the new position it test for the next one until a free position is found
            if(m_vecTileAreaPathFinding[initialPosition[i] + step*nbIteration]->m_maskPresence.character == 1
                    && (m_vecTileAreaPathFinding[initialPosition[i] + step*nbIteration]->m_pCharacter !=
                        m_vecTileAreaPathFinding[initialPosition[i]]->m_pCharacter) )
            {
                _changeIndexSelectedCharacterToAdd(initialPosition, step, nbIteration+1);
                return;
            }
            else
            {
                nbTileOK++;
            }
        }
        else
        {
           qDebug()<<"Out of the limit";
        }
    }

    if(initialPosition.size() == nbTileOK)
    {
       _moveCharacter(step*nbIteration);
    }
}


bool BattleMapData::_checkNewPositionToMoveCharacter(int initialPosition, int shift, int step)
{
    int newPosition = initialPosition + shift;
    bool isInsideMap = (newPosition >= 0 && newPosition < m_nbTileSide*m_nbTileSide);

    // for right and left move the step is 1 or -1
    bool isRightLeftMoving = (step/m_nbTileSide == 0);
    bool isRightLeftMovingNewPositionInSameColumn = ( newPosition/m_nbTileSide == initialPosition/m_nbTileSide );
    bool isUpDownMoving = (step/m_nbTileSide == 1 || step/m_nbTileSide == -1 );

    // check if the right or left move stay inside the border and so, don't change the column index
    // or if it's up / down moving
    bool isInsideBorder = ( ( isRightLeftMoving && isRightLeftMovingNewPositionInSameColumn ) || isUpDownMoving );

    return( isInsideMap && isInsideBorder);
}

// Move the cursor to set the new position where the character will move
void BattleMapData::_selectNewPositionCharacter(int step)
{
    bool nextPositionIsInsideMap = m_curseur.getIndexTileAreaPathFinding()+step >= 0 && m_curseur.getIndexTileAreaPathFinding()+step < m_nbTileSide*m_nbTileSide;
    if(nextPositionIsInsideMap)
    {
        int newIndex = m_curseur.getIndexTileAreaPathFinding() + step;

        // Reset the old position cursor
        m_vecTileAreaPathFinding[m_curseur.getIndexPresenceCursor()]->m_maskPresence.cursor = 0;

        m_vecTileAreaPathFinding[newIndex]->m_maskPresence.cursor = 1;
        m_curseur.setIndexTileAreaPathFinding(newIndex);
        m_curseur.setIndexPresenceCursor(newIndex);
    }
}




// Check if index is inside the map's bounds and set the new index
void BattleMapData::_changeIndexCursor(int step)
{   
    bool nextPositionIsInsideMap = m_curseur.getIndexTileAreaPathFinding()+step >= 0 && m_curseur.getIndexTileAreaPathFinding()+step < m_nbTileSide*m_nbTileSide;
    if(nextPositionIsInsideMap)
    {
        // if it isn't moving a character and there is a character next position, it go till the next tile without character
        int nbIteration = 1;
        bool cursorIsOnCharacter = m_vecTileAreaPathFinding[m_curseur.getIndexTileAreaPathFinding()]->m_maskPresence.character == 1;
        bool nextPositionIsOnCharacter = m_vecTileAreaPathFinding[m_curseur.getIndexTileAreaPathFinding()+step]->m_maskPresence.character == 1;
        if( cursorIsOnCharacter && nextPositionIsOnCharacter)
        {
            nbIteration = m_vecTileAreaPathFinding[m_curseur.getIndexTileAreaPathFinding()]->m_pCharacter->getSizeSide();
        }

        // Calcul the new index position
        int newIndex = m_curseur.getIndexTileAreaPathFinding() + (step * nbIteration);

        // check if it's inside the limits
        if(newIndex >= 0 && newIndex < m_nbTileSide*m_nbTileSide )
        {
            int lowIndex = newIndex;

            // Reset the old position cursor
            m_vecTileAreaPathFinding[m_curseur.getIndexPresenceCursor()]->m_maskPresence.cursor = 0;

            if(m_vecTileAreaPathFinding[newIndex]->m_maskPresence.character == 1)
            {
                // send character data to qml
                m_pInterfaceQml->setIsCursorOnCharacter(true);
                m_pInterfaceQml->setFeaturesCharacter(m_vecTileAreaPathFinding[newIndex]->m_pCharacter->getFeatures());

                Character* pCharacter = m_vecTileAreaPathFinding[newIndex]->m_pCharacter;
                if(nullptr != pCharacter)
                {
                    int sizeCharacter = pCharacter->getSizeSide();
                    m_curseur.setSizeSide(sizeCharacter);

                    // If character size is more than 1 the cursor rendering have to be from the first character tile
                    //     *
                    // *       *
                    //     *<-- low index tile
                    if(1 < sizeCharacter){
                        for(int i=0; i<pCharacter->getVecIndexTileAreaPathFinding().size(); i++){
                            if(lowIndex > pCharacter->getVecIndexTileAreaPathFinding()[i])
                            {
                               lowIndex = pCharacter->getVecIndexTileAreaPathFinding()[i];
                            }
                        }
                    }
                }
            }
            else
            {
                m_pInterfaceQml->setIsCursorOnCharacter(false);
                m_curseur.setSizeSide(1);
            }

            // Set new position cursor
            // In case where characterSize = 1 => lowIndex = newIndex
            // Otherwise it rendered from the lowest character tile (example below with 2 tile side character)
            //    *
            //*       *
            //    *<--
            m_vecTileAreaPathFinding[lowIndex]->m_maskPresence.cursor = 1;
            m_curseur.setIndexTileAreaPathFinding(newIndex);
            m_curseur.setIndexPresenceCursor(lowIndex);
        }
        else
        {
            qDebug()<<"Cursor outside of the map";
        }
    }
    else
    {
        qDebug()<<"next position cursor is outside of the map";
    }

}

void BattleMapData::_moveCharacter(int moveOffset)
{
    QMutex mutex;
    mutex.lock();

    // Calcul the new position, reset the old one, and set it to the new one
    int newIndexPosition = -1;
    QVector<int> l_vecNewPositionCharacter;

    // Reset the old Position before change with the one
    // It's necessary to have 2 differents loops between the reset of the old position and the new position
    // Otherwise it will reset new position that you just have added for multi tiles side character
    for(int i=0; i<m_pCurrentSelectedCharacter->getVecIndexTileAreaPathFinding().size(); i++)
    {
       m_vecTileAreaPathFinding[m_pCurrentSelectedCharacter->getVecIndexTileAreaPathFinding()[i]]->m_pCharacter = NULL;
       m_vecTileAreaPathFinding[m_pCurrentSelectedCharacter->getVecIndexTileAreaPathFinding()[i]]->m_maskPresence.character = 0;
    }

    // Update the new position
    for(int i=0; i<m_pCurrentSelectedCharacter->getVecIndexTileAreaPathFinding().size(); i++)
    {
       newIndexPosition = m_pCurrentSelectedCharacter->getVecIndexTileAreaPathFinding()[i] + moveOffset;
       if(-1 != newIndexPosition)
       {
           // Set the new one for the map
           m_vecTileAreaPathFinding[newIndexPosition]->m_pCharacter = m_pCurrentSelectedCharacter;
           m_vecTileAreaPathFinding[newIndexPosition]->m_maskPresence.character = 1;

          l_vecNewPositionCharacter<< newIndexPosition;
       }
       else
       {
           qDebug()<<"Wrong Position";
       }
    }

    // Reset the render counter to avoid bad rendering
    m_pCurrentSelectedCharacter->setRenderCounter(0);

    // Set the new character position
    if(m_pCurrentSelectedCharacter->getVecIndexTileAreaPathFinding().size() == l_vecNewPositionCharacter.size())
    {
       m_pCurrentSelectedCharacter->setVecIndexTileAreaPathFinding(l_vecNewPositionCharacter);
    }
    else
    {
        qDebug()<<"Impossible to move the character, wrong vec size";
    }

    mutex.unlock();
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
        m_curseur.setSizeSide(m_pCurrentSelectedCharacter->getSizeSide());

        m_pPathFinding->setDepthPathFinding(depthLevel);
        m_pPathFinding->setIsActivated(true);
        m_pPathFinding->setCharacterTileSide(m_pCurrentSelectedCharacter->getSizeSide());
        m_pPathFinding->setIndexesOrigin(m_pCurrentSelectedCharacter->getVecIndexTileAreaPathFinding());

        l_vecTilePathFinding = m_pPathFinding->getVecIndexPathFinding();

       for(int i=0; i<l_vecTilePathFinding.size(); i++)
       {
          m_vecTileAreaPathFinding[m_pPathFinding->getVecIndexPathFinding()[i]]->m_maskPresence.pathFinding = 1;
       }
    }
}

bool BattleMapData::_isCharacterAuthorizedToMove(int moveOffset)
{
    bool result = true;
    for(int i=0; i<m_pCurrentSelectedCharacter->getVecIndexTileAreaPathFinding().size(); i++)
    {
        int newIndexPosition = m_pCurrentSelectedCharacter->getVecIndexTileAreaPathFinding()[i]+ moveOffset;
        if(!m_pPathFinding->getVecIndexPathFinding().contains(newIndexPosition))
        {
          result= false;
          break;
        }
    }
    return result;
}


