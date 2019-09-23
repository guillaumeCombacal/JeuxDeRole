#include "BattleMapData.h"

#include "QDebug"

#include <QJsonArray>

BattleMapData::BattleMapData():
    m_nbTileTotal(0)
{
    m_mapFilenameTilsetToIndex.clear();
    m_vecFilenameTileset.clear();
    m_vecTileArea.clear();
    m_vecCharacter.clear();
    m_vecAnimationSprite.clear();
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

        m_fWidthTile = 0.3f;
        m_fHeightTile = m_fWidthTile/2.0f;

        int l_iIndexTexture = -1;

        // --- GENERATION DE 6 PERSONNAGES ---
//        for(int i=0; i<6; i++)
//        {
//            Character* l_pCharacter = new Character();

//            l_pCharacter->setSizeSide(1);
//            l_pCharacter->setIndexTileArea(QVector<int>{i});

//            l_pCharacter->setImgTilesheetFilePath(QString("C:/Users/Yaku/Documents/DeveloppementCode/PROJECT/jeuxDeRole/JeuDeRole/Ressources/ImgTest/SpriteAnimation128x64Right.png"));
//            QVector2D l_tabCoordCharacter[NB_COORD_TEXTURE];
//            l_tabCoordCharacter[0] = QVector2D(0.0f,1.0f);
//            l_tabCoordCharacter[1] = QVector2D(0.5f,1.0f);
//            l_tabCoordCharacter[2] = QVector2D(0.5f,0.0f);
//            l_tabCoordCharacter[3] = QVector2D(0.0f,0.0f);
//            l_pCharacter->setCoordTexture(l_tabCoordCharacter);

//            l_iIndexTexture = _addFilenameTexture(l_pCharacter->getImgTilesheetFilePath());
//            if( l_iIndexTexture != -1)
//            {
//                l_pCharacter->setIndexTexture(l_iIndexTexture);
//            }
//            else
//            {

//            }
//            m_vecCharacter << l_pCharacter;
//            m_vecAnimationSprite << l_pCharacter;
//        }

        // --- GENERATION D'1 PERSONNAGE SUR PLUSIEURS CASE DE LARGE ---
        Character* l_pCharacter = new Character();

        l_pCharacter->setSizeSide(2);
        l_pCharacter->setIndexTileArea(QVector<int>{0,1,2,4});

        l_pCharacter->setImgTilesheetFilePath(QString("C:/Users/Yaku/Documents/DeveloppementCode/PROJECT/jeuxDeRole/JeuDeRole/Ressources/ImgTest/SpriteAnimation128x64Right.png"));
        //l_pCharacter->setImgTilesheetFilePath(QString("C:/Users/Yaku/Documents/DeveloppementCode/PROJECT/jeuxDeRole/JeuDeRole/Ressources/ImgTest/DebugTileset.png"));
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
        m_vecCharacter << l_pCharacter;
        m_vecAnimationSprite << l_pCharacter;

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

//        l_iIndexTexture = _addFilenameTexture(l_pCharacter2->getImgTilesheetFilePath());
//        if( l_iIndexTexture != -1)
//        {
//            l_pCharacter2->setIndexTexture(l_iIndexTexture);
//        }

//        l_iIndexTexture = _addFilenameTexture(l_pCharacter3->getImgTilesheetFilePath());
//        if( l_iIndexTexture != -1)
//        {
//            l_pCharacter3->setIndexTexture(l_iIndexTexture);
//        }

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

            l_tileArea.m_tile.setHeightTile(0.01f);

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

            l_tileArea.m_maskPresence = 100;

            // Add the tile in the container
            m_vecTileArea << l_tileArea;
        }

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

        /*// Check if the texture's tilset filename is already known
        std::map<QString, int>::iterator itTileset;
        itTileset = m_mapFilenameTilsetToIndex.find(l_tileArea.m_tile.getImgTilesheetFilePath());

        // Known Tilset
        if(itTileset != m_mapFilenameTilsetToIndex.end())
        {
            l_tileArea.m_tile.setIndexTexture(itTileset->second);
        }
        // Unknown Tilset - add a new pair and increment indexTileTexture
        else
        {
            std::pair<QString, int> l_pair (l_tileArea.m_tile.getImgTilesheetFilePath(), indexTileTexture);
            m_mapFilenameTilsetToIndex.insert(l_pair);
            m_vecFilenameTileset << l_tileArea.m_tile.getImgTilesheetFilePath();
            indexTileTexture++;
        }
        */

        l_tileArea.m_maskPresence = 100;

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
    // Associate TileArea with Character
    for(int i=0; i<m_vecCharacter.size(); i++)
    {
        for(int j=0; j<m_vecCharacter[i]->getVecIndexTileArea().size(); j++)
        {
            m_vecTileArea[m_vecCharacter[i]->getVecIndexTileArea()[j]].m_character = m_vecCharacter[i];
            m_vecTileArea[m_vecCharacter[i]->getVecIndexTileArea()[j]].m_maskPresence = m_vecTileArea[i].m_maskPresence | 010;
        }
    }
}


