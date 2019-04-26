#include "BattleMapData.h"

#include "QDebug"

BattleMapData::BattleMapData():
    m_nbTileTotal(0)
{

}

BattleMapData::~BattleMapData()
{
}


void BattleMapData::loadDataBattleMap()
{
    m_heightMap = 3;
    m_widthMap  = 4;
    m_nbTileTotal = m_heightMap * m_widthMap;

    Sprite l_tileSprite;
    l_tileSprite.m_orientation = 0.0f;
    l_tileSprite.m_imageTilsheet = QImage("C:/Users/Yaku/Documents/DeveloppementCode/PROJECT/jeuxDeRole/JeuDeRole/Ressources/ImgTest/Ritz.png");
    l_tileSprite.m_coordTexture << QVector2D(0.0f, 1.0f);
    l_tileSprite.m_coordTexture << QVector2D(1.0f, 1.0f);
    l_tileSprite.m_coordTexture << QVector2D(1.0f, 0.0f);
    l_tileSprite.m_coordTexture << QVector2D(0.0f, 0.0f);

    l_tileSprite.m_height = 0.0f;

    // Test map de tile de 3*4
    for(int i = 0; i<m_heightMap * m_widthMap; i++)
    {
        std::pair<int, Sprite> newPair(i, l_tileSprite);
        m_mapTile.insert(newPair);

        m_vecMaskPresence << 100;
    }
}


