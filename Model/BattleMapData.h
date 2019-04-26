#ifndef BATTLE_MAP_DATA_H
#define BATTLE_MAP_DATA_H

#include<QString>
#include<QVector>
#include<QVector2D>
#include<QImage>

#include<vector>
#include<map>

struct Sprite
{
    float m_orientation;// rad ?
    QImage m_imageTilsheet;
    QVector<QVector2D> m_coordTexture;
    float m_height;// height of the tile
};


class BattleMapData
{

private:

    std::map<int, Sprite> m_mapTile;
    std::map<int, Sprite> m_mapCharacter;
    std::map<int, Sprite> m_mapDecor;

    int m_heightMap;
    int m_widthMap;
    int m_nbTileTotal;

    // Vecteur de Mask de presence contenant des 1 et des 0 ex:110
    // Position dans le mask 123: 1=tile, 2=personnage, 3=decor
    // Il sera de la taille de la map chargée
    QVector<int> m_vecMaskPresence;

public:
     BattleMapData();
    virtual ~BattleMapData();

     void loadDataBattleMap();

     inline const int& getNbTileTotal()const{return m_nbTileTotal;}

     inline const std::map<int, Sprite>& getMapTile()const{return m_mapTile;}
     inline const std::map<int, Sprite>& getMapCharacter()const{return m_mapCharacter;}
     inline const std::map<int, Sprite>& getMapDecor()const{return m_mapDecor;}
     inline const QVector<int>& getVecMaskPresence()const{return m_vecMaskPresence;}

    //inline const QVector<Tile>& getTileMap(){return m_tileMap;};

};

#endif // BATTLE_MAP_DATA_H
