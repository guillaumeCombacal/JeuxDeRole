#ifndef CURSEUR_H
#define CURSEUR_H

#include <QString>
#include <QVector2D>

#define NB_COORD_TEXTURE 4

class Curseur
{

private:
    QString m_strImgFilePath;
    QVector2D m_tabCoordTexture[NB_COORD_TEXTURE];

    // At the begining it's 0 then after loading all the required texture (tilsheet) to draw the map and all elements in BattleRender,
    // it takes the value of its own texture value.
    // that way the index is use to switch from one tilsheet to another, depend on the texture
    int m_iIndexTexture;

    // Contains the tile index in the vecTileAreaPathFinding on which cuseur is present
    int m_iIndexTileAreaPathFinding;

    int m_indexPresenceCursor;

    bool m_bIsVisible;

    int m_sizeSide;

    bool m_isSelectingCharacter;

public:
     Curseur();
     virtual ~Curseur();

     inline const bool getIsSelectingCharacter(){return m_isSelectingCharacter;}
     inline void setIsSelectingCharacter(bool isSelectingCharacter){m_isSelectingCharacter = isSelectingCharacter;}

     inline const int& getIndexPresenceCursor()const{return m_indexPresenceCursor;}
     inline void setIndexPresenceCursor(int indexPresenceCursor){m_indexPresenceCursor = indexPresenceCursor;}

     inline const int& getSizeSide()const{return m_sizeSide;}
     inline void setSizeSide(int sizeSide){m_sizeSide = sizeSide;}

     // Generate data from code
     inline void setCoordTexture(QVector2D* i_pCoordTexture){std::memcpy(m_tabCoordTexture, i_pCoordTexture, NB_COORD_TEXTURE*sizeof(QVector2D));}
     inline const QVector2D* getCoordTexture(int& o_iNbElement)const{o_iNbElement = NB_COORD_TEXTURE; return m_tabCoordTexture;}

     inline const int& getIndexTexture()const{return m_iIndexTexture;}
     inline void setIndexTexture(int i_iIndex){m_iIndexTexture = i_iIndex;}// Generate data from code

     inline const int& getIndexTileAreaPathFinding()const{return m_iIndexTileAreaPathFinding;}
     inline void setIndexTileAreaPathFinding(int i_iIndexTileArea){m_iIndexTileAreaPathFinding = i_iIndexTileArea;}// Generate data from code

     inline const QString& getImgFilePath()const{return m_strImgFilePath;}
     inline void setImgFilePath(QString i_strFilePath){m_strImgFilePath = i_strFilePath;}// Generate data from code

     inline const bool getIsVisible(){return m_bIsVisible;}
     inline void setIsVisible(bool i_bIsVisible){m_bIsVisible = i_bIsVisible;}


};

#endif // CURSEUR_H
