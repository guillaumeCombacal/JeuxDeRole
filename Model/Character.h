#ifndef CHARACTER_H
#define CHARACTER_H

#include <QJsonObject>
#include <QVector2D>
#include <QVector>

class Character
{

private:
    float m_orientation;// rad ?
    QString m_strImgTilesheetFilePath;
    QVector<QVector2D> m_coordTexture;

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

    void _initTotalCountRender();

public:
     Character();
     virtual ~Character();

     inline const bool& getIsReadyToRender(){return m_bIsReadyToRender;}

     inline void setCoordTexture(QVector<QVector2D> i_vecCoordTexture){m_coordTexture = i_vecCoordTexture;}// Generate data from code
     inline const QVector<QVector2D>& getCoordTexture()const{return m_coordTexture;}

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


};

#endif // CHARACTER_H
