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

class PathFinding;

struct MaskPresence
{
    unsigned int tile : 1;// TODO : pour améliorer coder les champs sur 1 bit
    unsigned int character : 1;
    unsigned int object : 1;
    unsigned int cursor : 1;
    unsigned int pathFinding : 1;
};

namespace EnumBattleMapData
{
    enum StateBattleMap
    {
        DEFAULT=0,
        MOVING,
        FIGHTING,
        ORIENTING,
        ADDING_NEW_CHARACTER
    };
}


// Struct that contains each elements which could be on a tile area like:
// Tile, Character, Curseur, Decor...
struct TileArea
{
    // Vecteur de Mask de presence contenant des 1 et des 0
    // Position dans le mask 123: 1=tile, 2=personnage, 3=decor, 4=curseur
    // exemple : 1100 contient une tile et un personnage
    MaskPresence m_maskPresence;
    Tile m_tile;
    Character* m_pCharacter;
    int m_indexVecPathFinding;
};

class BattleMapData
{

private:

    // Loading the textures tilset
    QVector<QString> m_vecFilenameTileset;
    std::map<QString, int> m_mapFilenameTilsetToIndex;

    //[attack orientation][defend orientation]
    float m_tabAttackOrientationCoeff[EnumCharacter::Orientation::END_ORIENTATION][EnumCharacter::Orientation::END_ORIENTATION];

    // Add the filename texture if it does not exist,
    // and anyway return the index to find the filename texture in m_vecFilenameTileset
    int _addFilenameTexture(QString i_strFilenameTexture);

    // Associate all the object which can be on a tile area
    // RQ: elements have to loading before using this fonction
    void _associateTileAreaObject();

    void _initVecTileAreaPathFinding();

    void _pathFinding(int indexTileCursor, int depthLevel);
    void _clearPathFinding();
    void _changeIndexCursor(int i_newIndex);
    void _changeIndexSelectedCharacterToAdd(QVector<int> initialPosition, int step, int nbIteration=1);
    void _moveCharacter(int i_newTileIndex);
    void _fight(Character* pFighterAttack, Character* pFighterDefense);
    EnumCharacter::Orientation _attackOrientation(Character* pFighterAttack, Character* pFighterDefense);

    // Data Container exposed with getter
    //used for depth render (3D)
    //4   5   6
    //  3   2
    //    1
    QVector<TileArea> m_vecTileArea;

    // easier to use for path finding
    QVector<TileArea*> m_vecTileAreaPathFinding;
    //3   X   X
    //  2   X
    //    1

    QVector<Character*> m_vecCharacter;
    QVector<AnimationSprite*> m_vecAnimationSprite;
    // TODO : Futur container
    /*QVector<Decor> m_vecDecor;*/
    Curseur m_curseur;

    int m_nbTileTotal;
    int m_nbTileSide;

    float m_fWidthTile;
    float m_fHeightTile;

    PathFinding* m_pPathFinding;
    Character* m_pCurrentSelectedCharacter;
    InterfaceQML* m_pInterfaceQml;

    QString m_urlRepoProject;

    EnumBattleMapData::StateBattleMap m_stateBattleMap;

public:
     BattleMapData(InterfaceQML* i_pInterfaceQml);
     virtual ~BattleMapData();

     inline void setProjectRepoUrl(QString url){m_urlRepoProject=url;}

     // Generate Data from code
     void generateMapData();

     // Load data from JSON File
     void loadDataBattleMap(const QJsonObject &json);
     void saveDataBattleMap(QJsonObject &json)const;

     void eventKeyBoard(KeyValue i_eKey);
     void fightRequest();
     void orientationRequest();
     void selectCharacterToAddInBattle(QString name, QString job, QString nature, int lvl);
     void enterAddingCharacterState();
     void finishAddingCharacterState();

     inline const PathFinding* getPathFinding()const{return m_pPathFinding;}

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
