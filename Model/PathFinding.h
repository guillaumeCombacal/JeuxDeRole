#ifndef PATH_FINDING_H
#define PATH_FINDING_H

//#include <QJsonObject>
#include <QVector2D>
#include <QVector>

//#include"AnimationSprite.h"

#define NB_COORD_TEXTURE 4

class PathFinding
{

private:

    // Texture
    QString m_strImgTilesheetFilePath;
    QVector2D m_tabCoordTexture[NB_COORD_TEXTURE];

    // At the begining it's 0 then after loading all the required texture (tilsheet) to draw the map in BattleRender,
    // it takes the value of its own texture value.
    // that way the index is use to switch from one tilsheet to another, depend on the texture
    //int m_iIndexTexture;

    // data pathfinding
    int m_indexOrigin;
    int m_depthPathFinding;
    int m_nbTileSideMap;
    int m_iIndexTexture;
    bool m_bIsActivated;
    QVector<int>m_vecIndexPathFinding;

    void _calculPathFinding();

public:
     PathFinding(int i_indexOrigin, int i_depthPathFinding, int i_nbTileSideMap);
     virtual ~PathFinding();

     void clearVecPathFinding();
     bool isIndexInPathFinding(int i_index);

     inline void setIsActivated(int i_bIsActivated){m_bIsActivated = i_bIsActivated;}
     inline bool getIsActivated(){return m_bIsActivated;}
     inline void setNbTileSideMap(int i_nbTileSideMap){m_nbTileSideMap = i_nbTileSideMap;}
     inline void setIndexOrigin(int i_indexOrigin){m_indexOrigin = i_indexOrigin; _calculPathFinding();}
     inline void setDepthPathFinding(int i_depthPathFinding){m_depthPathFinding = i_depthPathFinding; _calculPathFinding();}
     inline QVector<int> getVecIndexPathFinding(){return m_vecIndexPathFinding;}

    // inline const bool& getIsReadyToRender(){return m_bIsReadyToRender;}

     // Generate data from code
     //inline void setCoordTexture(QVector2D* i_pCoordTexture){std::memcpy(m_tabCoordTexture, i_pCoordTexture, NB_COORD_TEXTURE*sizeof(QVector2D));}
     inline const QVector2D* getCoordTexture(int& o_iNbElement)const{o_iNbElement = NB_COORD_TEXTURE;return m_tabCoordTexture;}

     inline const int& getIndexTexture()const{return m_iIndexTexture;}
     inline void setIndexTexture(int i_iIndex){m_iIndexTexture = i_iIndex;}// Generate data from code

     //inline const QVector<int>& getVecIndexTileArea()const{return m_vecIndexTileArea;}
     //inline void setIndexTileArea(QVector<int> i_vecIndexTileArea){m_vecIndexTileArea = i_vecIndexTileArea;}// Generate data from code

     inline const QString& getImgTilesheetFilePath()const{return m_strImgTilesheetFilePath;}
     inline void setImgTilesheetFilePath(QString i_strFilePath){m_strImgTilesheetFilePath = i_strFilePath;}// Generate data from code

     //void saveCharacterData(QJsonObject &json)const;
     //void loadCharacterData(const QJsonObject &json);
     //bool isReadyToRender();
};

#endif // PATH_FINDING_H
