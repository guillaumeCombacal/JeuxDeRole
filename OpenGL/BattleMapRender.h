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


#include<map>

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

    BattleMapRender(BattleMapData i_battleMapData);
    ~BattleMapRender();

    void initBattleMapRender();
    void renderBattleMap();

    /*void render();
    void draw();
    void initialize();*/

private:

    void calculVerticesBuffer(int i_iIndiceRow, int i_iIndiceTileInRow, int i_iNbSquareUp, int i_iNbSquareDown, float i_fHeightTile);
    void initShader();
    //void updateVertexBuffer();

    QOpenGLShaderProgram m_shaderProgram;

    // Variable binding with the shader
    int m_positionAttrShader;
    int m_colorAttrShader;
    int m_matrixUniformShader;

    // Reference Vertex = Left Base Vertex => all vertex vertices are calculate from this point
    QVector3D m_fLeftBaseVertex;

    // Test
    QVector3D m_fLeftCornerVertex;

    // Tile base dimension
    /*float m_fWidthBaseTile;
    float m_fHeightBaseTile;*/

    // On Opengl 0 is the middle position of the image, so m_iMiddleRowColumn is the reference
    int m_iMiddleRowColumn;

    // TODO : Finir déclaration
    BattleMapData m_battleMapData;

    int m_iNbTileSide;
    int m_iNbTileTotal;

    bool m_bIsNbTileSidePair;

    QOpenGLTexture* m_pTextureTiles;

    QVector<QVector3D>   m_vecVertexBuffer;
    QVector<QVector3D>   m_vecColors;

    // For texture loading
    QVector<QOpenGLTexture*> m_vecTextureTilset;
    std::map<QString, int> m_mapFilenameToTextureIndex;

    // TEST : TEMP
    OpenGlRender m_openGlRender;

};

#endif // BATTLE_MAP_RENDER_H
