#ifndef CHARACTER_H
#define CHARACTER_H

#include <QJsonObject>
#include <QVector2D>
#include <QVector>

#include"AnimationSprite.h"
#include"sharedDataHero.h"

#define NB_COORD_TEXTURE 4

namespace EnumCharacter
{
    enum SpriteStatesCharacter
    {
        STATE_STAND_FRONT=0,
        STATE_STAND_BACK,
        STATE_WALK_FRONT_1,
        STATE_WALK_FRONT_2,
        STATE_WALK_BACK_1,
        STATE_WALK_BACK_2,
        STATE_HURT_FRONT,
        STATE_HURT_BACK,
        STATE_FIGHT_FRONT_1,
        STATE_FIGHT_FRONT_2,
        STATE_FIGHT_BACK_1,
        STATE_FIGHT_BACK_2,
        STATE_MAGIC_FIGHT_FRONT_1,
        STATE_MAGIC_FIGHT_FRONT_2,
        STATE_MAGIC_FIGHT_BACK_1,
        STATE_MAGIC_FIGHT_BACK_2,
        STATE_DEAD_FRONT,
        STATE_DEAD_BACK,
        STATE_FRAME_TRANSITION,
        END_STATE
    };

    enum ActionStatesCharacter
    {
        WALKING=0,
        ATTACKING,
        DEFENDING,
        DEAD,
        END_ACTION
    };

    enum Orientation
    {
        NORTH=0,
        SOUTH,
        EAST,
        WEST,
        END_ORIENTATION
    };
}


class Character : public AnimationSprite/*, public QObject*/ //--> a revoir
{

//    Q_OBJECT

private:

    Stats m_sStats;
    Features m_sFeatures;

    int m_moveSteps;

    EnumCharacter::Orientation m_orientation;
    QString m_strImgTilesheetFilePath;
    QVector2D m_tabCoordTexture[NB_COORD_TEXTURE];
    EnumCharacter::SpriteStatesCharacter m_frameTransitionTab[EnumCharacter::ActionStatesCharacter::END_ACTION][EnumCharacter::Orientation::END_ORIENTATION];

    // A character can be bigger than one unit square texture
    // The size of the character in number of tiles
    // ex : classic hero 1*1, big monster 3*3
    int m_iSizeSide;

    // At the begining it's 0 then after loading all the required texture (tilsheet) to draw the map in BattleRender,
    // it takes the value of its own texture value.
    // that way the index is use to switch from one tilsheet to another, depend on the texture
    int m_iIndexTexture;

    // Contains tile index on which character is present
    QVector<int> m_vecIndexTileAreaPathFinding;

    // A big character (3*3) have to be draw only
    int m_iTotalCountRender;
    int m_iCountRender;
    bool m_bIsReadyToRender;

    // State
    int m_states[EnumCharacter::END_STATE];

    EnumCharacter::ActionStatesCharacter m_currentActionState;

    void _initTotalCountRender();

public:
     Character();
     virtual ~Character();

     //inline Stats& getStats(){return m_sStats;}
     //inline void setStats(Stats i_stats){m_sStats = i_stats;}// Generate data from code

     void attacking(int indexDefendingCharacter, int nbTileSide);
     void takingDamage(int nbDamage);

     inline const EnumCharacter::Orientation& getOrientation(){return m_orientation;}
     void setOrientation(EnumCharacter::Orientation orientation);

     inline const Features& getFeatures(){return m_sFeatures;}
     inline void setFeatures(Features i_features){m_sFeatures = i_features;}// Generate data from code

     inline const bool& getIsReadyToRender(){return m_bIsReadyToRender;}

     // Generate data from code
     inline void setMoveSteps(int i_moveSteps){m_moveSteps = i_moveSteps;}
     inline const int& getMoveSteps(){return m_moveSteps ;}

     inline void setCoordTexture(QVector2D* i_pCoordTexture){std::memcpy(m_tabCoordTexture, i_pCoordTexture, NB_COORD_TEXTURE*sizeof(QVector2D));}
     inline const QVector2D* getCoordTexture(int& o_iNbElement)const{o_iNbElement = NB_COORD_TEXTURE;return m_tabCoordTexture;}

     inline const int& getIndexTexture()const{return m_iIndexTexture;}
     inline void setIndexTexture(int i_iIndex){m_iIndexTexture = i_iIndex;}// Generate data from code

     inline const int& getSizeSide()const{return m_iSizeSide;}
     inline void setSizeSide(int i_iSizeSide){m_iSizeSide = i_iSizeSide; _initTotalCountRender();}// Generate data from code

     inline const QVector<int>& getVecIndexTileAreaPathFinding()const{return m_vecIndexTileAreaPathFinding;}
     inline void setVecIndexTileAreaPathFinding(QVector<int> i_vecIndexTileArea){m_vecIndexTileAreaPathFinding = i_vecIndexTileArea;}// Generate data from code

     inline const QString& getImgTilesheetFilePath()const{return m_strImgTilesheetFilePath;}
     inline void setImgTilesheetFilePath(QString i_strFilePath){m_strImgTilesheetFilePath = i_strFilePath;}// Generate data from code

     inline void setRenderCounter(int counter){m_iCountRender = counter;}

     void saveCharacterData(QJsonObject &json)const;
     void loadCharacterData(const QJsonObject &json);
     bool isReadyToRender();

     void updateCoordSprite(int i_stateFrame);
     void nextState();


};

#endif // CHARACTER_H
