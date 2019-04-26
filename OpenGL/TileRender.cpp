#include "TileRender.h"

#include <QOpenGLShaderProgram>


TileRender::TileRender()
{
    /*m_vecVertexBuffer << QVector3D(0.0f, 0.0f, 0.0f);
    m_vecVertexBuffer << QVector3D(1.0f, 0.0f, 0.0f);
    m_vecVertexBuffer << QVector3D(1.0f, 1.0f, 0.0f);
    m_vecVertexBuffer << QVector3D(0.0f, 1.0f, 0.0f);
*/
    /*m_vecColors << QVector3D(0.0f, 1.0f, 0.0f);
    m_vecColors << QVector3D(1.0f, 1.0f, 0.0f);
    m_vecColors << QVector3D(1.0f, 0.0f, 0.0f);
    m_vecColors << QVector3D(0.0f, 0.0f, 0.0f);   */
}

TileRender::~TileRender()
{
}

void TileRender::initialize()
{

}

void TileRender::initialize(QOpenGLShaderProgram* program)
{

    m_shaderProgram = program;

    //initializeOpenGLFunctions();

    //glClearColor(0.1f, 0.1f, 0.2f, 1.0f);

    // INITIALISE LES SHADERS
    /*QOpenGLShader *vertexShader = new QOpenGLShader(QOpenGLShader::Vertex, &m_program);
    // Vertex Shader => Positionne les coordonnées de vertex et partage les coordonnées de texture vers le fragment shader
    const char *vertexShaderSource =
        "attribute highp vec4 vertex;\n"
        "uniform mediump mat4 matrix;\n"
        "void main(void)\n"
        "{\n"
        "    gl_Position = matrix * vertex;\n"
        "}\n";
    vertexShader->compileSourceCode(vertexShaderSource);

    QOpenGLShader *fragmentShader = new QOpenGLShader(QOpenGLShader::Fragment, &m_program);
    // Fragment Shader => récupère les coordonnées de texture depuis le vertex shader,
    // et calcul la couleur en fonction de cette coordonnées et de la texture chargée en Sampler2D
   const char *fragmentShaderSource =
            "void main(void)\n"
            "{\n"
            "    gl_FragColor = vec3(0.0f, 0.0f, 0.0f);\n"
            "}\n";
    fragmentShader->compileSourceCode(fragmentShaderSource);


    m_program.addShader(vertexShader);
    m_program.addShader(fragmentShader);

    m_program.link();

    // Identifie les variables shader
    m_positionAttrShader    = m_program.attributeLocation("vertex");
    m_matrixUniformShader   = m_program.uniformLocation("matrix");
    */

}

void TileRender::render()
{
    //m_shaderProgram->enableAttributeArray(m_colorAttrShader2);
    //m_shaderProgram->enableAttributeArray(m_positionAttrShader2);

    // Bind vertices with the Vector3D data
    //m_shaderProgram->setAttributeArray(m_positionAttrShader2, m_vecVertexBuffer.constData());
    //m_shaderProgram->setAttributeArray(m_colorAttrShader2, m_vecCoordTexture.constData());

    //m_pTexture->bind();

    // RQ: on ne peut utiliser glDrawArrays() qu'en héritant de QOpenGLFunctions
    //     Il n'est peut etre pas necessaire d'utiliser glDrawArray dans la classe tuile et donc de faire hérité de QOpenGLFunctions
    //     Surtout si la méthode draw dessine de manière identique
    // Dessine les Vertices en les associants sous forme de Quad non relié les uns aux autres
    glDrawArrays(GL_QUADS, 0, m_vecVertexBuffer.size());

    //m_shaderProgram->disableAttributeArray(m_colorAttrShader2);
    //m_shaderProgram->disableAttributeArray(m_positionAttrShader2);
}
