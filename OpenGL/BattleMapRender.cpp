#include "BattleMapRender.h"

#include <QOpenGLTexture>

// All Tile have the same size
const float c_fWidthBaseTile = 0.4f;
const float c_fHeightBaseTile = c_fWidthBaseTile/2.0f;

BattleMapRender::BattleMapRender(BattleMapData i_battleMapData):
    m_battleMapData(i_battleMapData),
    m_fLeftBaseVertex(QVector3D(0.0f, 0.0f, 0.0f)),
    m_iMiddleRowColumn(0.0f),
    m_bIsNbTileSidePair(false)
{
    m_iNbTileSide   = m_battleMapData.getNbTileSide();
    m_iNbTileTotal  = m_battleMapData.getNbTileTotal();

    if(m_iNbTileSide%2 == 0)
    {
        // Pair
        m_bIsNbTileSidePair = true;
    }
    else
    {
        // Impair
        m_bIsNbTileSidePair = false;
    }

    float l_fHalfHeightTile = 0.0f;
    // Add an half of tile --> TODO: vérifier si le cas impair fonctionne bien
    if(!m_bIsNbTileSidePair)
    {
        l_fHalfHeightTile = c_fHeightBaseTile/2;
    }
    // Init the base vertices - Base Vertices is the down corner of the map
    // If there is an nb Tile impair, it's necessary to had an half of height map
    m_fLeftBaseVertex   = QVector3D(-(c_fWidthBaseTile/2),
                                    ((m_iNbTileSide/2)*c_fHeightBaseTile)-(c_fHeightBaseTile/2) + l_fHalfHeightTile,
                                    0.0f);


    // Test : TEMP
    QImage l_imgTexture(QString("C:/Users/Yaku/Documents/DeveloppementCode/PROJECT/jeuxDeRole/JeuDeRole/Ressources/ImgTest/Ritz.png"));
    //l_imgTexture.convertToFormat(QImage::Format_ARGB32);
    m_pTextureTiles = new QOpenGLTexture(l_imgTexture);

}

BattleMapRender::~BattleMapRender()
{
    // Test : TEMP
    delete m_pTextureTiles;
}

void BattleMapRender::initBattleMapRender()
{
    // TODO : Initialisation des données
    // Utilisation du Model BattleMapData qui aura préalablement chargé l'état de la battle map
    // On récupère les map de data par référence et on les met à jour !
    // Cela met à jour le model en même temps (moins de copie)

    // Initialisation OpenGl
    initializeOpenGLFunctions();
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);

    // Initialisation des shaders
    initShader();


    // Test: Temp
    //m_openGlRender.initialize();
}

// Shader initialisation
void BattleMapRender::initShader()
{
    // Vertex Shader => Positionne les coordonnées de vertex et partage les coordonnées de texture vers le fragment shader
    QOpenGLShader* vertexShader = new QOpenGLShader(QOpenGLShader::Vertex, &m_shaderProgram);
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

    // Fragment Shader => récupère les coordonnées de texture depuis le vertex shader,
    // et calcul la couleur en fonction de cette coordonnées et de la texture chargée en Sampler2D
    QOpenGLShader *fragmentShader = new QOpenGLShader(QOpenGLShader::Fragment, &m_shaderProgram);
    const char *fragmentShaderSource =
            "uniform sampler2D texture;\n"
            "varying mediump vec4 texc;\n"
            "void main(void)\n"
            "{\n"
            "    gl_FragColor = texture2D(texture, texc.st);\n"
            "}\n";
    fragmentShader->compileSourceCode(fragmentShaderSource);


    m_shaderProgram.addShader(vertexShader);
    m_shaderProgram.addShader(fragmentShader);

    m_shaderProgram.link();

    // Identifie les variables shader
    m_positionAttrShader    = m_shaderProgram.attributeLocation("vertex");
    m_colorAttrShader       = m_shaderProgram.attributeLocation("texCoord");
    m_matrixUniformShader   = m_shaderProgram.uniformLocation("matrix");

    m_shaderProgram.setUniformValue("texture", 0);
}


// TODO : enlever tous les appel de fonction inutiles (glDepthMask)
// draw all the object inside the battle map
void BattleMapRender::renderBattleMap()
{
    // Test : Temp
    //m_openGlRender.render();


    glDepthMask(true);

    // init the background color of the battle map
    glClearColor(0.5f, 0.5f, 0.7f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // TODO : analyser le comportement de cette matrice
    QMatrix4x4 l_matrixModelView;
    l_matrixModelView.perspective(60.0f, 4.0f/3.0f, 0.1f, 100.0f);
    l_matrixModelView.translate(0, 0, -2);

    m_shaderProgram.bind();

    // Bind the uniform model matrix with the shader
    m_shaderProgram.setUniformValue(m_matrixUniformShader, l_matrixModelView);

    // Bind attribute color with shader
    m_shaderProgram.enableAttributeArray(m_colorAttrShader);

    // Bind attribute position with shader
    m_shaderProgram.enableAttributeArray(m_positionAttrShader);



    // TODO : Verifier si la map est appropriée... en effet sur les éléments non contenus dedans,
    // elle va parcourir toute la map à chaque fois ?!
    // Loop for the number of vertical row
    int l_iNbRow = (m_iNbTileSide*2)-1;// TODO : Deporter l'initialisation vers le constructeur
    int l_iNbTileInRow = 0;// TODO : Deporter l'initialisation vers le constructeur
    int l_iTileCounter = 0;
    for(int itRow=0; itRow<l_iNbRow; itRow++)
    {
        if(itRow < m_iNbTileSide)
        {
            l_iNbTileInRow++;
        }
        else
        {
            l_iNbTileInRow--;
        }

        for(int itTileInRow=0; itTileInRow<l_iNbTileInRow; itTileInRow++)
        {
            // Render Tile if tile is present
            if(m_battleMapData.getVecMaskPresence()[l_iTileCounter] & 100)// Presence Tuile
            {
                std::map<int, Sprite>::const_iterator itTile;
                itTile = m_battleMapData.getMapTile().find(l_iTileCounter);
                if(itTile != m_battleMapData.getMapTile().end())
                {
                    // Bind the tilsheet texture which contains the sprite
                    Sprite l_sprite = itTile->second;
                    //QOpenGLTexture l_texture (l_sprite.m_imageTilsheet);
                    //l_texture.bind();

                    m_pTextureTiles->bind();

                    // Calcul the new coordinates of each vertices
                    calculVerticesBuffer(itRow, itTileInRow, l_sprite.m_height);

                    // TODO : changer les vecteur de données avec les données correspondant aux tiles, personnage, element du decor, etc...
                    //        il faut notamment mettre à jour m_vecVertexBuffer
                    // Set vertices and color with the respective data for each elements
                    m_shaderProgram.setAttributeArray(m_positionAttrShader, m_vecVertexBuffer.constData());
                    m_shaderProgram.setAttributeArray(m_colorAttrShader, l_sprite.m_coordTexture.constData());

                }
            }

            // Alpha value activated for transparence
            glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_BLEND);

            // Dessine les Vertices en les associants sous forme de Quad non relié les uns aux autres
            glDrawArrays(GL_TRIANGLE_FAN, 0, m_vecVertexBuffer.size());

            // Increment the tile counter for the next
            l_iTileCounter++;
        }

    }
    // END FOR LOOP

    // End render
    m_shaderProgram.disableAttributeArray(m_colorAttrShader);
    m_shaderProgram.disableAttributeArray(m_positionAttrShader);
    m_shaderProgram.release();

}

void BattleMapRender::calculVerticesBuffer(int i_iIndiceRow, int i_iIndiceTileInRow, float i_fHeightTile)
{
    m_vecVertexBuffer.clear();

    float l_fPositionX = 0.0f;
    float l_fPositionY = 0.0f;

    // Position Y
    l_fPositionY = m_fLeftBaseVertex.y() - ((c_fHeightBaseTile/2)*i_iIndiceRow);

    // Position X
    // For every row adding +/-WTile/2 from the reference point
    // => Get the position on the beginning of the row
    if(i_iIndiceRow < m_iNbTileSide)
    {
        l_fPositionX = m_fLeftBaseVertex.x() - (i_iIndiceRow * c_fWidthBaseTile/2);
    }
    else
    {
        l_fPositionX = m_fLeftBaseVertex.x() - ((m_iNbTileSide-1)*c_fWidthBaseTile/2)
                     + ((i_iIndiceRow-(m_iNbTileSide-1)) * c_fWidthBaseTile/2);
    }
    // Adding an offset function of the position of the tile in the row
    l_fPositionX += (i_iIndiceTileInRow * c_fWidthBaseTile);

    // Calcul the left vertex coord from base vertex
    QVector3D l_vecLeftBaseTileVertex (l_fPositionX, l_fPositionY, 0.0f);

    // Calcul the middle and the right vertices from the left vertex position => so the base of 3 vertex is known
    QVector3D l_vecMiddleBaseTileVertex (l_vecLeftBaseTileVertex.x()+c_fWidthBaseTile/2,
                                         l_vecLeftBaseTileVertex.y()+c_fHeightBaseTile/2,
                                         0.0f);
    QVector3D l_vecRightBaseTileVertex (l_vecLeftBaseTileVertex.x()+c_fWidthBaseTile,
                                        l_vecLeftBaseTileVertex.y(),
                                        0.0f);

    // Add Base Vertices in the vertex buffer
    m_vecVertexBuffer << l_vecLeftBaseTileVertex;
    m_vecVertexBuffer << l_vecMiddleBaseTileVertex;
    m_vecVertexBuffer << l_vecRightBaseTileVertex;

    // TODO : Verifier l'ordre dans lequel doive etre ajouté les vertices suivant la méthode de dessin
    // Calcul the last vertices depend on the height of the tile
    if(i_fHeightTile > 0)
    {
        m_vecVertexBuffer << QVector3D(l_vecLeftBaseTileVertex.x(), l_vecLeftBaseTileVertex.y()+i_fHeightTile, 0.0f);
        m_vecVertexBuffer << QVector3D(l_vecMiddleBaseTileVertex.x(), l_vecMiddleBaseTileVertex.y()+i_fHeightTile+c_fHeightBaseTile, 0.0f);
        m_vecVertexBuffer << QVector3D(l_vecRightBaseTileVertex.x(), l_vecRightBaseTileVertex.y()+i_fHeightTile, 0.0f);
    }
    else if(i_fHeightTile == 0)
    {
        m_vecVertexBuffer << QVector3D(l_vecMiddleBaseTileVertex.x(), l_vecMiddleBaseTileVertex.y()-c_fHeightBaseTile, 0.0f);
    }

}
