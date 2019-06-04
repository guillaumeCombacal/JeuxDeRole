#include "BattleMapData.h"

#include "QDebug"

#include <QJsonArray>

BattleMapData::BattleMapData():
    m_nbTileTotal(0)
{
    m_mapFilenameTilsetToIndex.clear();
    m_vecFilenameTileset.clear();
    m_vecTile.clear();
}

BattleMapData::~BattleMapData()
{
}


void BattleMapData::loadDataBattleMap(const QJsonObject &json)
{
    // Loadind battleMapData from the json file
    QJsonObject l_jsonObjBattleMap = json["battleMap"].toObject();

    m_nbTileTotal = l_jsonObjBattleMap["nbTileTotal"].toInt();
    m_nbTileSide = l_jsonObjBattleMap["nbTileSide"].toInt();
    m_fWidthTile = l_jsonObjBattleMap["widthTile"].toDouble();
    m_fHeightTile = l_jsonObjBattleMap["heightTile"].toDouble();

    m_vecTile.clear();
    int indexTile = 0;
    QJsonArray tileArray = l_jsonObjBattleMap["tiles"].toArray();
    for (int itTile = 0; itTile < tileArray.size(); itTile++)
    {
        QJsonObject tileObject = tileArray[itTile].toObject();
        Tile l_tile;
        l_tile.loadTileData(tileObject);

        // Check if the texture's tilset filename is already known
        std::map<QString, int>::iterator itTileset;
        itTileset = m_mapFilenameTilsetToIndex.find(l_tile.getImgTilesheetFilePath());

        // Known Tilset
        if(itTileset != m_mapFilenameTilsetToIndex.end())
        {
            l_tile.setIndexTexture(itTileset->second);
        }
        // Unknown Tilset - add a new pair and increment indexTile
        else
        {
            std::pair<QString, int> l_pair (l_tile.getImgTilesheetFilePath(), indexTile);
            m_mapFilenameTilsetToIndex.insert(l_pair);
            m_vecFilenameTileset << l_tile.getImgTilesheetFilePath();
            indexTile++;
        }

        m_vecTile << l_tile;
        m_vecMaskPresence << 100;
    }





// ------------------- Ancien Générateur de tuile sans lecture de fichier ---------------------------------

/*
    // Dans un premier temps, cette fonction est une simulation du chargement de fichier

    m_nbTileSide = 10;
    m_nbTileTotal = m_nbTileSide * m_nbTileSide;

    m_fWidthTile = 0.3f;
    m_fHeightTile = m_fWidthTile/2.0f;

    Tile l_tile;
    l_tile.setTileOrientation(0.0f);
    l_tile.setTileHeight(0.0f);

    //l_tile.setImgTilesheetFilePath(QString("C:/Users/Yaku/Documents/DeveloppementCode/PROJECT/jeuxDeRole/JeuDeRole/Ressources/ImgTest/tilsetIsometric/testTileSet.png"));

    // GL_TrianleFan
    /*l_tileSprite.m_coordTexture << QVector2D(0.0f, 1.0f);
    l_tileSprite.m_coordTexture << QVector2D(1.0f, 1.0f);
    l_tileSprite.m_coordTexture << QVector2D(1.0f, 0.0f);
    l_tileSprite.m_coordTexture << QVector2D(0.0f, 0.0f);
    */

    // GL_QUADS
    /*l_tile.addCoord(QVector2D(0.0f, 0.25f));
    l_tile.addCoord(QVector2D(0.5f, 0.25f));
    l_tile.addCoord(QVector2D(0.5f, 0.0f));
    l_tile.addCoord(QVector2D(0.0f, 0.0f));*/



    //TODO : il faudra une seul loop qui parcours tous les objets potentiellement présent sur la tuile,
    // dans le but de metre à jour le vecMaskPresence d'un seul cout
/*
    int indexTile = 0;
    // Test map de tile de 1*1
    for(int i = 0; i<m_nbTileTotal; i++)
    {
        l_tile.cleanVecCoordText();

        if(i%2 == 0)
        {
            l_tile.addCoord(QVector2D(0.0f, 0.25f));
            l_tile.addCoord(QVector2D(0.5f, 0.25f));
            l_tile.addCoord(QVector2D(0.5f, 0.0f));
            l_tile.addCoord(QVector2D(0.0f, 0.0f));

            l_tile.setImgTilesheetFilePath(QString("C:/Users/Yaku/Documents/DeveloppementCode/PROJECT/jeuxDeRole/JeuDeRole/Ressources/ImgTest/tilsetIsometric/testTileSet.png"));

        }
        else
        {
            l_tile.addCoord(QVector2D(0.5f, 0.25f));
            l_tile.addCoord(QVector2D(1.0f, 0.25f));
            l_tile.addCoord(QVector2D(1.0f, 0.0f));
            l_tile.addCoord(QVector2D(0.5f, 0.0f));

            l_tile.setImgTilesheetFilePath(QString("C:/Users/Yaku/Documents/DeveloppementCode/PROJECT/jeuxDeRole/JeuDeRole/Ressources/ImgTest/tilsetIsometric/testTileSet2.png"));

        }


        // TODO : Il faudra faire évoluer cette partie là pour récupérer chaque tuile et non une unique tuile
        // Check if the texture's tilset filename is already known
        std::map<QString, int>::iterator itTileset;
        itTileset = m_mapFilenameTilsetToIndex.find(l_tile.getImgTilesheetFilePath());

        // Known Tilset
        if(itTileset != m_mapFilenameTilsetToIndex.end())
        {
            l_tile.setIndexTexture(itTileset->second);
        }
        // Unknown Tilset - add a new pair and increment indexTile
        else
        {
            std::pair<QString, int> l_pair (l_tile.getImgTilesheetFilePath(), indexTile);
            m_mapFilenameTilsetToIndex.insert(l_pair);
            m_vecFilenameTileset << l_tile.getImgTilesheetFilePath();
            indexTile++;
        }

        // Add the tile in the container
        m_vecTile << l_tile;
        m_vecMaskPresence << 100;
    }*/

}

void BattleMapData::saveDataBattleMap(QJsonObject &json)const
{
    QJsonObject l_jsonObjBattleMap;
    l_jsonObjBattleMap["nbTileTotal"] = m_nbTileTotal;
    l_jsonObjBattleMap["nbTileSide"] = m_nbTileSide;
    l_jsonObjBattleMap["widthTile"] = m_fWidthTile;
    l_jsonObjBattleMap["heightTile"] = m_fHeightTile;

    QJsonArray l_arrayJsonTiles;

    QVector<Tile>::const_iterator itTileMap;
    for(itTileMap = m_vecTile.begin(); itTileMap != m_vecTile.end(); itTileMap++)
    {
        QJsonObject tileJsonObject;
        itTileMap->saveTileData(tileJsonObject);
        l_arrayJsonTiles.append(tileJsonObject);
    }

    l_jsonObjBattleMap["tiles"] = l_arrayJsonTiles;

    json["battleMap"] = l_jsonObjBattleMap;
}


