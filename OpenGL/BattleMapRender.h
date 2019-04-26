#ifndef BATTLE_MAP_RENDER_H
#define BATTLE_MAP_RENDER_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

/*
#include <QOpenGLWidget>
#include <QVector>
#include <QVector3D>
#include <QMatrix4x4>
*/

#include "BattleMapData.h"

// Test : Temp
#include "OpenGL_Render.h"

//QT_FORWARD_DECLARE_CLASS(QOpenGLTexture)

// Information to know which object need to be rendered
struct PresenceOnTile
{
    bool m_bIsTile;
    bool m_bIsPerso;
    bool m_bIsDecorObject;

    // TODO : Verfier init par défaut
    PresenceOnTile():
        m_bIsTile(false),
        m_bIsPerso(false),
        m_bIsDecorObject(false)
    {

    }
};


// Faire un singleton !!!!!

class BattleMapRender : protected QOpenGLFunctions
{

public:

    BattleMapRender(int i_nbTileSide, BattleMapData i_battleMapData);
    ~BattleMapRender();

    void initBattleMapRender();
    void renderBattleMap();

    /*void render();
    void draw();
    void initialize();*/

private:

    void calculVerticesBuffer(int i_iIndiceRow, int i_iIndiceTileInRow, int i_iNbTileInRow, float i_fHeightTile);
    void initShader();
    //void updateVertexBuffer();

    QOpenGLShaderProgram m_shaderProgram;

    // Variable binding with the shader
    int m_positionAttrShader;
    int m_colorAttrShader;
    int m_matrixUniformShader;

    // Base Vertices
    QVector3D m_fLeftBaseVertex;
    QVector3D m_fMiddleBaseVertex;
    QVector3D m_fRightBaseVertex;

    // Tile base dimension
    /*float m_fWidthBaseTile;
    float m_fHeightBaseTile;*/

    // On Opengl 0 is the middle position of the image, so m_iMiddleRowColumn is the reference
    int m_iMiddleRowColumn;

    // Vector of the presence object with the map size
    std::vector<PresenceOnTile> m_vecPresence;
    //QVector<PresenceOnTile> m_presenceMatrix;

    // TODO : Finir déclaration
    BattleMapData m_battleMapData;
    // map contenant les différents élément à rendre
    /*std::map<int position, Tile> m_mapTile;
    std::map<int position, Personnage> m_mapPersonnage;
    std::map<int position, Decor> m_mapDecor;
    */

    int m_iNbTileSide;
    int m_iNbTileTotal;

    bool m_bIsNbTileSidePair;


    QVector<QVector3D>   m_vecVertexBuffer;
    QVector<QVector3D>   m_vecColors;
    /*QVector<QVector3D> m_vecVertexBuffer2;
    QVector<QVector3D>   m_vecColors2;

    int m_fScale;
    int m_fAngle;

    QOpenGLTexture* m_pTexture;

    TileRender m_tileRender;
    */

    // TEST : TEMP
    OpenGlRender m_openGlRender;

};

#endif // BATTLE_MAP_RENDER_H
