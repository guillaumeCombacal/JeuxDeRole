#include "OpenGL_Render.h"

#include <QPainter>
#include <QPaintEngine>
#include <math.h>

OpenGlRender::OpenGlRender()
{
}

OpenGlRender::~OpenGlRender()
{
}


// Draw the rendering
void OpenGlRender::updateVertexBuffer()
{
    m_vecVertices << QVector3D(0.0f, 0.707f, 0.0f);
    m_vecVertices << QVector3D(-0.5f, -0.5f, 0.0f);
    m_vecVertices << QVector3D(0.5f, -0.5f, 0.0f);

    m_vecNormals << QVector3D(1.0f, 0.0f, 0.0f);// R
    m_vecNormals << QVector3D(0.0f, 1.0f, 0.0f);// G
    m_vecNormals << QVector3D(0.0f, 0.0f, 1.0f);// B
}

void OpenGlRender::initialize()
{
    initializeOpenGLFunctions();

    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);

    // Initialise les shaders
    QOpenGLShader *vertexShader = new QOpenGLShader(QOpenGLShader::Vertex, &m_program);
    const char *vertexShaderSource =
        "attribute highp vec4 posAttr;\n"
        "attribute lowp vec4 colAttr;\n"
        "varying lowp vec4 col;\n"
        "uniform highp mat4 matrix;\n"
        "void main() {\n"
        "   col = colAttr;\n"
        "   gl_Position = matrix * posAttr;\n"
        "}\n";
    vertexShader->compileSourceCode(vertexShaderSource);

    QOpenGLShader *fragmentShader = new QOpenGLShader(QOpenGLShader::Fragment, &m_program);
    const char *fragmentShaderSource =
        "varying lowp vec4 col;\n"
        "void main() {\n"
        "   gl_FragColor = col;\n"
        "}\n";
    fragmentShader->compileSourceCode(fragmentShaderSource);

    m_program.addShader(vertexShader);
    m_program.addShader(fragmentShader);
    m_program.link();

    // Définit les variables utilisés dans le shader
    m_positionAttrShader    = m_program.attributeLocation("posAttr");
    m_colorAttrShader       = m_program.attributeLocation("colAttr");
    m_matrixUniformShader   = m_program.uniformLocation("matrix");

    // Initialise les Vertex Buffer
    updateVertexBuffer();
}

void OpenGlRender::render()
{
    glDepthMask(true);

    glClearColor(0.5f, 0.5f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 modelview;
    modelview.perspective(60.0f, 4.0f/3.0f, 0.1f, 100.0f);
    modelview.translate(0, 0, -2);

    m_program.bind();
    m_program.setUniformValue(m_matrixUniformShader, modelview);

    // Bind Vertices (Vector3D) with the respective Shader attribute
    m_program.enableAttributeArray(m_colorAttrShader);
    m_program.enableAttributeArray(m_positionAttrShader);

    m_program.setAttributeArray(m_positionAttrShader, m_vecVertices.constData());
    m_program.setAttributeArray(m_colorAttrShader, m_vecNormals.constData());

    // Dessine les m_vecVertices en les associants sous forme de triangle
    glDrawArrays(GL_TRIANGLES, 0, m_vecVertices.size());

    m_program.disableAttributeArray(m_colorAttrShader);
    m_program.disableAttributeArray(m_positionAttrShader);


    m_program.release();
}
