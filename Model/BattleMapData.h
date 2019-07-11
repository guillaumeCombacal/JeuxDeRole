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
#include "Character.h"

// Struct that contains each elements which could be on a tile area like:
// Tile, Character, Decor...
struct TileArea
{
    // Vecteur de Mask de presence contenant des 1 et des 0
    // Position dans le mask 123: 1=tile, 2=personnage, 3=decor
    // exemple : 110 contient une tile et un personnage
    int m_maskPresence;
    Tile m_tile;
    Character* m_character;
};

class BattleMapData
{

private:

    // Loading the textures tilset
    QVector<QString> m_vecFilenameTileset;
    std::map<QString, int> m_mapFilenameTilsetToIndex;

    // Add the filename texture if it does not exist,
    // and anyway return the index to find the filename texture in m_vecFilenameTileset
    int _addFilenameTexture(QString i_strFilenameTexture);

    // Associate all the object which can be on a tile area
    // RQ: elements have to loading before using this fonction
    void _associateTileAreaObject();

    // Data Container that will be expose with getter
    QVector<TileArea> m_vecTileArea;
    QVector<Character*> m_vecCharacter;


    // TODO : Futur container
    /*
    QVector<Decor> m_vecDecor;*/

    // Vecteur de Mask de presence contenant des 1 et des 0 ex:110
    // Position dans le mask 123: 1=tile, 2=personnage, 3=decor
    // Il sera de la taille de la map chargée
    //QVector<int> m_vecMaskPresence;

    int m_nbTileTotal;
    int m_nbTileSide;

    float m_fWidthTile;
    float m_fHeightTile;

public:
     BattleMapData();
    virtual ~BattleMapData();

     // Generate Data from code
     void generateMapData();

     // Load data from JSON File
     void loadDataBattleMap(const QJsonObject &json);
     void saveDataBattleMap(QJsonObject &json)const;

     inline const float& getWidthTile()const{return m_fWidthTile;}
     inline const float& getHeightTile()const{return m_fHeightTile;}

     inline const int& getNbTileTotal()const{return m_nbTileTotal;}
     inline const int& getNbTileSide()const{return m_nbTileSide;}

     // TODO : Futur Container
     /*inline const QVector<Character>& getMapCharacter()const{return m_vecCharacter;}
     inline const QVector<Decor>& getMapDecor()const{return m_vecDecor;}*/


     inline const QVector<TileArea>& getVecTileArea(){return m_vecTileArea;}
     inline const QVector<QString>& getVecFilenameTileset(){return m_vecFilenameTileset;}

};

#endif // BATTLE_MAP_DATA_H
