#ifndef CHARACTER_H
#define CHARACTER_H

#include <QJsonObject>
#include <QVector2D>
#include <QVector>

#include"AnimationSprite.h"

#define NB_COORD_TEXTURE 4

enum StatesCharacter
{
    STATE_WALK_1 = 0,
    STATE_WALK_2,
    END_STATE
};

class Character : public AnimationSprite
{

private:
    float m_orientation;// rad ?
    QString m_strImgTilesheetFilePath;
    QVector2D m_tabCoordTexture[NB_COORD_TEXTURE];

    // A character can be bigger than one unit square texture
    // The size of the character in number of tiles
    // ex : classic hero 1*1, big monster 3*3
    int m_iSizeSide;

    // At the begining it's 0 then after loading all the required texture (tilsheet) to draw the map in BattleRender,
    // it takes the value of its own texture value.
    // that way the index is use to switch from one tilsheet to another, depend on the texture
    int m_iIndexTexture;

    // Contains tile index on which character is present
    QVector<int> m_vecIndexTileArea;

    // A big character (3*3) have to be draw only
    int m_iTotalCountRender;
    int m_iCountRender;
    bool m_bIsReadyToRender;

    // State
    int m_states[END_STATE];

    void _initTotalCountRender();

public:
     Character();
     virtual ~Character();

     inline const bool& getIsReadyToRender(){return m_bIsReadyToRender;}

     // Generate data from code
     inline void setCoordTexture(QVector2D* i_pCoordTexture){std::memcpy(m_tabCoordTexture, i_pCoordTexture, NB_COORD_TEXTURE*sizeof(QVector2D));}
     inline const QVector2D* getCoordTexture(int& o_iNbElement)const{o_iNbElement = NB_COORD_TEXTURE;return m_tabCoordTexture;}

     inline const int& getIndexTexture()const{return m_iIndexTexture;}
     inline void setIndexTexture(int i_iIndex){m_iIndexTexture = i_iIndex;}// Generate data from code

     inline const int& getSizeSide()const{return m_iSizeSide;}
     inline void setSizeSide(int i_iSizeSide){m_iSizeSide = i_iSizeSide; _initTotalCountRender();}// Generate data from code

     inline const QVector<int>& getVecIndexTileArea()const{return m_vecIndexTileArea;}
     inline void setIndexTileArea(QVector<int> i_vecIndexTileArea){m_vecIndexTileArea = i_vecIndexTileArea;}// Generate data from code

     inline const QString& getImgTilesheetFilePath()const{return m_strImgTilesheetFilePath;}
     inline void setImgTilesheetFilePath(QString i_strFilePath){m_strImgTilesheetFilePath = i_strFilePath;}// Generate data from code

     void saveCharacterData(QJsonObject &json)const;
     void loadCharacterData(const QJsonObject &json);
     bool isReadyToRender();

     void updateCoordSprite(int i_stateFrame);
     void nextState();


};

#endif // CHARACTER_H
