#ifndef BATTLE_MAP_RENDER_H
#define BATTLE_MAP_RENDER_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QTimer>
#include <QObject>

#include "BattleMapData.h"

#include<map>

#define SIZE_VB 4

class AnimationSprite;
class QOpenGLTexture;

enum FragmentShaderRenderTypeEnum
{
    RENDER_TEXTURE_MAPPING = 0,
    RENDER_COLOR_BASIC
};

// On Opengl, 0 is the middle position of the image
class BattleMapRender : protected QOpenGLFunctions, public QObject
{

public:

    BattleMapRender(BattleMapData* i_pBattleMapData);
    ~BattleMapRender();

    void initBattleMapRender();
    void renderBattleMap();

private:

    // TODO
    void _renderTileLayer(int numTile, float leftCornerTileX, float leftCornerTileY);
    void _renderCharacterLayer(int numTile, float leftCornerTileX, float leftCornerTileY);
    void _renderCurseurLayer(int numTile, float leftCornerTileX, float leftCornerTileY);
    void _renderPathFindingLayer(int numTile, float leftCornerTileX, float leftCornerTileY);
    void _renderObjectLayer();
    void _renderAnimationLayer();
    /////////////////////

    void _calculTileVerticesBuffer(float i_fPositionBaseX, float i_fPositionBaseY, int i_iNbSquareUp, int i_iNbSquareDown);
    void _calculCharacterVerticesBuffer(float i_fPositionBaseX, float i_fPositionBaseY, int i_iCharacterSizeSide, float i_fHeightTile);
    void _calculCurseurVerticesBuffer(float i_fPositionBaseX, float i_fPositionBaseY, float i_fHeightTile);
    void _calculPathFindingVerticesBuffer(float i_fPositionBaseX, float i_fPositionBaseY, float i_fHeightTile);
    void _initShader();
    void _processSpriteAnimation();
    void _addTexture(int indexFilename);

    QOpenGLShaderProgram m_shaderProgram;

    // Variable binding with the shader
    int m_positionAttrShader;
    int m_colorAttrShader;
    int m_matrixUniformShader;
    int m_iFragmentShaderRenderType;

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

    // Contains data to display
    BattleMapData* m_pBattleMapData;

    int m_iNbTileSide;
    int m_iNbTileTotal;

    bool m_bIsNbTileSidePair;

    // TODO : Enlever les vec et passer par des tab statiques de [4]
    QVector3D m_tabCurseurVertexBuffer[SIZE_VB];
    QVector3D m_tabPathFindingVertexBuffer[SIZE_VB];
    QVector<QVector3D>   m_vecTileVertexBuffer;
    QVector<QVector3D>   m_vecCharacterVertexBuffer;
    QVector<QVector3D>   m_vecColors;

    // For texture loading
    QVector<QOpenGLTexture*> m_vecTextureTilset;
    std::map<QString, int> m_mapFilenameToTextureIndex;

    // Timer for sprite animation
    QTimer* m_timerSpriteAnimation;

};

#endif // BATTLE_MAP_RENDER_H
