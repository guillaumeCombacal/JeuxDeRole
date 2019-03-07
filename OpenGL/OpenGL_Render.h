#ifndef OPENGL_RENDER_H
#define OPENGL_RENDER_H

#include <QOpenGLFunctions>
#include <QOpenGLWidget>

#include <QVector>
#include <QVector3D>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>

QT_FORWARD_DECLARE_CLASS(QOpenGLTexture)


class OpenGlRender : protected QOpenGLFunctions
{

public:

    OpenGlRender();
    ~OpenGlRender();
    void render();
    void draw();
    void initialize();

private:

    void updateVertexBuffer();
    void createGeometry();
    void quad(qreal x1, qreal y1, qreal x2, qreal y2, qreal x3, qreal y3, qreal x4, qreal y4);
    void extrude(qreal x1, qreal y1, qreal x2, qreal y2);

    QVector<QVector3D>   m_vecVertices;
    QVector<QVector3D>   m_vecColors;
    QOpenGLShaderProgram m_program;

    int m_positionAttrShader;
    int m_colorAttrShader;
    int m_matrixUniformShader;

    int m_fScale;
    int m_fAngle;

    QOpenGLTexture* m_pTexture;

    QVector<QVector3D> m_vecVertexBuffer;

};

#endif // OPENGL_RENDER_H
