#ifndef BATTLE_MAP_RENDER_H
#define BATTLE_MAP_RENDER_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QTimer>
#include <QObject>

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

class AnimationSprite;

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


class BattleMapRender : protected QOpenGLFunctions, public QObject
{

public:

    BattleMapRender(BattleMapData* i_pBattleMapData);
    ~BattleMapRender();

    void initBattleMapRender();
    void renderBattleMap();

    /*void render();
    void draw();
    void initialize();*/

private:

    void calculTileVerticesBuffer(float i_fPositionBaseX, float i_fPositionBaseY, int i_iNbSquareUp, int i_iNbSquareDown);
    void calculCharacterVerticesBuffer(float i_fPositionBaseX, float i_fPositionBaseY, int i_iCharacterSizeSide, float i_fHeightTile);
    void initShader();
    //void updateVertexBuffer();
    void _processSpriteAnimation();

    QOpenGLShaderProgram m_shaderProgram;

    // Variable binding with the shader
    int m_positionAttrShader;
    int m_colorAttrShader;
    int m_matrixUniformShader;

    // Reference Vertex = Left Base Vertex => all vertex vertices are calculate from this point
    // It's the corner of the texture that will be mapped on it
    // On ne se déplace pas selon un pattern de losange représentant la tile,
    // mais selon des quad qui contiennent la texture en diamant à l'intérieur d'un quad
    //      _____
    //     |     |
    //     |  *  |
    //     *     *
    //  -->|__*__|
    QVector3D m_fLeftBaseCornerVertex;

    // Tile base dimension
    /*float m_fWidthBaseTile;
    float m_fHeightBaseTile;*/

    // On Opengl 0 is the middle position of the image, so m_iMiddleRowColumn is the reference
    int m_iMiddleRowColumn;

    // Contains data to display
    BattleMapData* m_pBattleMapData;

    int m_iNbTileSide;
    int m_iNbTileTotal;

    bool m_bIsNbTileSidePair;

    QOpenGLTexture* m_pTextureTiles;

    QVector<QVector3D>   m_vecTileVertexBuffer;
    QVector<QVector3D>   m_vecCharacterVertexBuffer;
    QVector<QVector3D>   m_vecColors;

    // For texture loading
    QVector<QOpenGLTexture*> m_vecTextureTilset;
    std::map<QString, int> m_mapFilenameToTextureIndex;

    // Timer for sprite animation
    QTimer* m_timerSpriteAnimation;

    // TEST : TEMP
    OpenGlRender m_openGlRender;

};

#endif // BATTLE_MAP_RENDER_H
