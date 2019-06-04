#ifndef BATTLE_MAP_DATA_H
#define BATTLE_MAP_DATA_H

#include<QString>
#include<QVector>
#include<QVector2D>
#include<QImage>

#include<vector>
#include<map>

#include <QJsonObject>

#include "Tile.h"

class BattleMapData
{

private:

    // Loading the textures tilset
    QVector<QString> m_vecFilenameTileset;
    std::map<QString, int> m_mapFilenameTilsetToIndex;

    // Data Container that will be expose with getter
    QVector<Tile> m_vecTile;

    // TODO : Futur container
    /*QVector<Character> m_vecCharacter;
    QVector<Decor> m_vecDecor;*/

    // Vecteur de Mask de presence contenant des 1 et des 0 ex:110
    // Position dans le mask 123: 1=tile, 2=personnage, 3=decor
    // Il sera de la taille de la map chargée
    QVector<int> m_vecMaskPresence;

    int m_nbTileTotal;
    int m_nbTileSide;

    float m_fWidthTile;
    float m_fHeightTile;

public:
     BattleMapData();
    virtual ~BattleMapData();

     void loadDataBattleMap(const QJsonObject &json);
     void saveDataBattleMap(QJsonObject &json)const;

     inline const float& getWidthTile()const{return m_fWidthTile;}
     inline const float& getHeightTile()const{return m_fHeightTile;}

     inline const int& getNbTileTotal()const{return m_nbTileTotal;}
     inline const int& getNbTileSide()const{return m_nbTileSide;}

     // TODO : Futur Container
     /*inline const QVector<Character>& getMapCharacter()const{return m_vecCharacter;}
     inline const QVector<Decor>& getMapDecor()const{return m_vecDecor;}*/

     inline const QVector<int>& getVecMaskPresence()const{return m_vecMaskPresence;}
     inline const QVector<Tile>& getVecTile(){return m_vecTile;}
     inline const QVector<QString>& getVecFilenameTileset(){return m_vecFilenameTileset;}

};

#endif // BATTLE_MAP_DATA_H
