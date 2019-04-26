#ifndef TILE_RENDER_H
#define TILE_RENDER_H

//#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>

#include "ObjectRender.h"

#include <QVector>
#include <QVector3D>

QT_FORWARD_DECLARE_CLASS(QOpenGLTexture)

class QOpenGLShaderProgram;

class TileRender : protected QOpenGLFunctions, public ObjectRender
{

public:

    TileRender();
    ~TileRender();

    void initialize(QOpenGLShaderProgram* program);

    void initialize();
    void render();

private:

    QVector<QVector3D> m_vecVertexBuffer;
    QVector<QVector3D> m_vecCoordTexture;

    QOpenGLShaderProgram* m_shaderProgram;

    QOpenGLTexture* m_pTexture;

    // Useless -> un seul shader pour tous les objets à rendre => les attributs sont déclarées dans la classe commune
    // qui gère le rendu de toutes les tuiles
    //int m_positionAttrShader;
    //int m_colorAttrShader;
};

#endif // TILE_RENDER_H
