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
#include "Curseur.h"
#include "interfaceQML.h"

struct MaskPresence
{
    unsigned int tile : 1;// 1 bit
    unsigned int character : 1;
    unsigned int object : 1;
    unsigned int cursor : 1;
};


// Struct that contains each elements which could be on a tile area like:
// Tile, Character, Curseur, Decor...
struct TileArea
{
    // Vecteur de Mask de presence contenant des 1 et des 0
    // Position dans le mask 123: 1=tile, 2=personnage, 3=decor, 4=curseur
    // exemple : 1100 contient une tile et un personnage
    //int m_maskPresence;

    MaskPresence m_maskPresence;
    Tile m_tile;
    Character* m_character;
    int m_indexVecPathFinding;
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

    void _initVecTileAreaPathFinding();

    // Data Container exposed with getter
    QVector<TileArea> m_vecTileArea;
    QVector<TileArea*> m_vecTileAreaPathFinding;// easier to use for path finding
    QVector<Character*> m_vecCharacter;
    QVector<AnimationSprite*> m_vecAnimationSprite;
    // TODO : Futur container
    /*QVector<Decor> m_vecDecor;*/
    Curseur m_curseur;



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

     void eventKeyBoard(KeyValue i_eKey);

     inline const float& getWidthTile()const{return m_fWidthTile;}
     inline const float& getHeightTile()const{return m_fHeightTile;}

     inline const int& getNbTileTotal()const{return m_nbTileTotal;}
     inline const int& getNbTileSide()const{return m_nbTileSide;}

     inline const Curseur& getCurseur()const{return m_curseur;}

     // TODO : Futur Container
     /*inline const QVector<Decor>& getMapDecor()const{return m_vecDecor;}*/


     inline const QVector<TileArea>& getVecTileArea(){return m_vecTileArea;}
     inline const QVector<QString>& getVecFilenameTileset(){return m_vecFilenameTileset;}

     inline const QVector<AnimationSprite*>& getVecAnimationSprite(){return m_vecAnimationSprite;}

};

#endif // BATTLE_MAP_DATA_H
