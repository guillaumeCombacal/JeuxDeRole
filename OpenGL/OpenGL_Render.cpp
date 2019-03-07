#include "OpenGL_Render.h"

#include <QPainter>
#include <QPaintEngine>
#include <math.h>

#include <QOpenGLTexture>

OpenGlRender::OpenGlRender()
{
    m_pTexture = new QOpenGLTexture(QImage(QString("C:/Users/Yaku/Documents/DeveloppementCode/PROJECT/jeuxDeRole/JeuDeRole/Ressources/ImgTest/Ritz.png")));
}

OpenGlRender::~OpenGlRender()
{
}


// Draw the rendering
void OpenGlRender::updateVertexBuffer()
{
    // Coordonnées du rectangle
    m_vecVertices << QVector3D(-1.5f, 0.0f , 0.0f);
    m_vecVertices << QVector3D(0.0f, 1.5f , 0.0f);
    m_vecVertices << QVector3D(1.5f, 0.0f , 0.0f);
    m_vecVertices << QVector3D(0.0f, -1.5f , 0.0f);

    // Contruction du vecteur de 4 tuiles par 4 vertices
    for(int i = 0; i<2; i++)
    {
        for(int j = 0; j<2; j++)
        {
            float offsetX = j * 1.0f;
            float offsetY = i * 1.0f;

            m_vecVertexBuffer << QVector3D(-1.0f + offsetX, 0.0f + offsetY, 0.0f);
            m_vecVertexBuffer << QVector3D(0.0f + offsetX, 0.0f + offsetY, 0.0f);
            m_vecVertexBuffer << QVector3D(0.0f + offsetX, -1.0f + offsetY, 0.0f);
            m_vecVertexBuffer << QVector3D(-1.0f + offsetX, -1.0f + offsetY, 0.0f);

            // Coordonnées de texture
            m_vecColors << QVector3D(0.0f, 0.0f, 0.0f);
            m_vecColors << QVector3D(0.0f, 1.0f, 0.0f);
            m_vecColors << QVector3D(1.0f, 1.0f, 0.0f);
            m_vecColors << QVector3D(1.0f, 0.0f, 0.0f);
        }

    }
}

void OpenGlRender::initialize()
{
    initializeOpenGLFunctions();

    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);

    // INITIALISE LES SHADERS

    QOpenGLShader *vertexShader = new QOpenGLShader(QOpenGLShader::Vertex, &m_program);
    // Vertex Shader => Positionne les coordonnées de vertex et partage les coordonnées de texture vers le fragment shader
    const char *vertexShaderSource =
        "attribute highp vec4 vertex;\n"
        "attribute mediump vec4 texCoord;\n"
        "varying mediump vec4 texc;\n"
        "uniform mediump mat4 matrix;\n"
        "void main(void)\n"
        "{\n"
        "    gl_Position = matrix * vertex;\n"
        "    texc = texCoord;\n"
        "}\n";
    vertexShader->compileSourceCode(vertexShaderSource);

    QOpenGLShader *fragmentShader = new QOpenGLShader(QOpenGLShader::Fragment, &m_program);
    // Fragment Shader => récupère les coordonnées de texture depuis le vertex shader,
    // et calcul la couleur en fonction de cette coordonnées et de la texture chargée en Sampler2D
   const char *fragmentShaderSource =
            "uniform sampler2D texture;\n"
            "varying mediump vec4 texc;\n"
            "void main(void)\n"
            "{\n"
            "    gl_FragColor = texture2D(texture, texc.st);\n"
            "}\n";
    fragmentShader->compileSourceCode(fragmentShaderSource);


    m_program.addShader(vertexShader);
    m_program.addShader(fragmentShader);

    m_program.link();

    // Identifie les variables shader
    m_positionAttrShader    = m_program.attributeLocation("vertex");
    m_colorAttrShader       = m_program.attributeLocation("texCoord");
    m_matrixUniformShader   = m_program.uniformLocation("matrix");

    m_program.setUniformValue("texture", 0);

    // Initialise les Coordonnées
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

    // TODO => Rendu à partir du tableau
    m_program.setAttributeArray(m_positionAttrShader, m_vecVertexBuffer.constData());
    m_program.setAttributeArray(m_colorAttrShader, m_vecColors.constData());

    m_pTexture->bind();

    // TODO => Rendu à partir du tableau
    // Dessine les m_vecVertices en les associants sous forme de Quad non relié les uns aux autres
    glDrawArrays(GL_QUADS, 0, m_vecVertexBuffer.size());

    m_program.disableAttributeArray(m_colorAttrShader);
    m_program.disableAttributeArray(m_positionAttrShader);


    m_program.release();

}
