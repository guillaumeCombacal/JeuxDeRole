#include "OpenGL_Render.h"

#include <QPainter>
#include <QPaintEngine>
#include <math.h>

#include <QOpenGLTexture>

const float g_fLengthMap = 4.0f;
const float g_fCoeffSubdivision = 2.0f;// nb de tuiles qui divisent la longueur

const int g_map[4]  = {1,0,0,1};

OpenGlRender::OpenGlRender()
{
    //m_pTexture = new QOpenGLTexture(QImage(QString("C:/Users/Yaku/Documents/DeveloppementCode/PROJECT/jeuxDeRole/JeuDeRole/Ressources/ImgTest/Ritz.png")));
}

OpenGlRender::~OpenGlRender()
{
}


// Dans cette fonction les calculs de vertex peuvent être conservés dans une classe BattleMapRender à partir de la boucle for,
// En revanche, les coord de texture seront calculées dans la classe tile
// ATTENTION: au niveau de l'algorithme sur la boucle for, opengl dessine en FILO (first déclaré Last dessiné)
//            il faut donc repenser le parcours en commençant par le premier plan de la map
// Draw the rendering
void OpenGlRender::updateVertexBuffer()
{

    // Init variable for tile dimension
    const float tileHorizontalLength = g_fLengthMap / g_fCoeffSubdivision;
    const float tileVerticalLength = tileHorizontalLength / 2.0f;

    const QVector3D baseVertex1 (0.0f, -(g_fLengthMap / 4.0f), 0.0f);
    const QVector3D baseVertex2 ((tileHorizontalLength / 2.0f), -((g_fLengthMap / 4.0f))+tileVerticalLength/2.0f, 0.0f);
    const QVector3D baseVertex3 (0.0f, -(g_fLengthMap / 4.0f)+tileVerticalLength, 0.0f);
    const QVector3D baseVertex4 (-(tileHorizontalLength / 2.0f), -((g_fLengthMap / 4.0f))+tileVerticalLength/2.0f, 0.0f);

    // Nombre de ligne
    int nbRow = (g_fCoeffSubdivision * 2) - 1;
    int nbTilesInRow = 0;
    float offsetRowX = 0.0f;
    float offsetX = 0.0f;
    float offsetY = 0.0f;

    int itMap = -1;

    for(int itRow=0; itRow<nbRow; itRow++)
    {
        itRow < g_fCoeffSubdivision ? nbTilesInRow+=1 : nbTilesInRow-=1;

        offsetY = itRow * (tileVerticalLength/2);

        if(itRow < g_fCoeffSubdivision)
        {
            offsetRowX = -itRow * tileHorizontalLength/2;
        }
        else
        {
            offsetRowX = -(nbRow-itRow-1) * tileHorizontalLength/2;
        }

        for(int itTile=0; itTile<nbTilesInRow; itTile++)
        {
            itMap++;

            //setRenderProperties(itMap);

            offsetX = offsetRowX + (itTile * tileHorizontalLength);

            m_vecVertexBuffer << QVector3D(baseVertex1.x() + offsetX, baseVertex1.y() + offsetY, 0.0f);
            m_vecVertexBuffer << QVector3D(baseVertex2.x() + offsetX, baseVertex2.y() + offsetY, 0.0f);
            m_vecVertexBuffer << QVector3D(baseVertex3.x() + offsetX, baseVertex3.y() + offsetY, 0.0f);
            m_vecVertexBuffer << QVector3D(baseVertex4.x() + offsetX, baseVertex4.y() + offsetY, 0.0f);

            m_vecColors << QVector3D(0.0f, 1.0f, 0.0f);
            m_vecColors << QVector3D(1.0f, 1.0f, 0.0f);
            m_vecColors << QVector3D(1.0f, 0.0f, 0.0f);
            m_vecColors << QVector3D(0.0f, 0.0f, 0.0f);            
        }
    }

    // RENDU 2
    m_vecVertexBuffer2 << QVector3D(0.0f, 0.0f, 0.0f);
    m_vecVertexBuffer2 << QVector3D(1.0f, 0.0f, 0.0f);
    m_vecVertexBuffer2 << QVector3D(1.0f, -1.0f, 0.0f);
    m_vecVertexBuffer2 << QVector3D(0.0f, -1.0f, 0.0f);

    m_vecColors2 << QVector3D(0.0f, 1.0f, 0.0f);
    m_vecColors2 << QVector3D(1.0f, 1.0f, 0.0f);
    m_vecColors2 << QVector3D(1.0f, 0.0f, 0.0f);
    m_vecColors2 << QVector3D(0.0f, 0.0f, 0.0f);

}

/*void OpenGlRender::setRenderProperties(int numTile)
{

}*/


// Tout ce qui se trouve dans cette fonction est identique pour chaqu'un des objets à rendre
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

    //m_tileRender.initialize(&m_program);

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

    m_program.enableAttributeArray(m_colorAttrShader);
    m_program.enableAttributeArray(m_positionAttrShader);





    // BINDING RENDU 2
    // Bind vertices with the Vector3D data
    m_program.setAttributeArray(m_positionAttrShader, m_vecVertexBuffer2.constData());
    m_program.setAttributeArray(m_colorAttrShader, m_vecColors2.constData());

    QOpenGLTexture texture (QImage(QString("C:/Users/Yaku/Documents/DeveloppementCode/PROJECT/jeuxDeRole/JeuDeRole/Ressources/ImgTest/Ritz.png")));
    //m_pTexture->bind();
    texture.bind();

    // Dessine les Vertices en les associants sous forme de Quad non relié les uns aux autres
    glDrawArrays(GL_QUADS, 0, m_vecVertexBuffer2.size());



    // BINDING RENDU 1
    // Active the respective Shader attribute

    // Bind vertices with the Vector3D data
    m_program.setAttributeArray(m_positionAttrShader, m_vecVertexBuffer.constData());
    m_program.setAttributeArray(m_colorAttrShader, m_vecColors.constData());

    //m_pTexture->bind();
    QOpenGLTexture texture2 (QImage(QString("C:/Users/Yaku/Documents/DeveloppementCode/PROJECT/jeuxDeRole/JeuDeRole/Ressources/ImgTest/Marche.png")));
    texture2.bind();

    // Dessine les Vertices en les associants sous forme de Quad non relié les uns aux autres
    glDrawArrays(GL_QUADS, 0, m_vecVertexBuffer.size());










    m_program.disableAttributeArray(m_colorAttrShader);
    m_program.disableAttributeArray(m_positionAttrShader);


    //m_tileRender.render();




    m_program.release();

}
