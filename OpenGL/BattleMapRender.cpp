#include "BattleMapRender.h"
#include "AnimationSprite.h"
#include "PathFinding.h"

#include <QOpenGLTexture>

BattleMapRender::BattleMapRender(BattleMapData* i_pBattleMapData):
    m_pBattleMapData(i_pBattleMapData),
    m_fLeftBaseCornerVertex(QVector3D(0.0f, 0.0f, 0.0f)),
    m_bIsNbTileSidePair(false),
    m_iFragmentShaderRenderType(RENDER_TEXTURE_MAPPING)
{
    m_iNbTileSide   = m_pBattleMapData->getNbTileSide();
    m_iNbTileTotal  = m_pBattleMapData->getNbTileTotal();

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

    float l_fOddOffset = 0.0f;
    // Add an half of tile --> TODO: vérifier si le cas impair fonctionne bien
    if(!m_bIsNbTileSidePair)
    {
        l_fOddOffset = m_pBattleMapData->getHeightTile()/2;
    }


    // Point x 0,0 is the middle of the screen
    //  _______
    // |       |
    // |   x   |
    // |       |
    //  -------
    // Init the base vertices -> Base Vertices is down tile of the map and the down left corner of the tile
    // If there is an nb Tile impair, it's necessary to had an half of height map
    // 1--> show the first render tile (for x = tile)
    // m_fLeftBaseCornerVertex is the O in the second draw
    //  _____________      ___________
    // |      x      |    |           |
    // |   x  x  x   |    |     *     |
    // |x  x  x  x  x|    | *       * |
    // |   x  x  x   |    |     *     |
    // |  1-->x      |    O ----------
    //  -------------
    m_fLeftBaseCornerVertex = QVector3D(-(m_pBattleMapData->getWidthTile()/2),
                                       ((m_iNbTileSide/2)*m_pBattleMapData->getHeightTile())+ l_fOddOffset,
                                       0.0f);

    // Loading all required textures to render the battleMap
    // Note : Le chargement des texture dois être effectué en début d'initialisation
    //        pour éviter les problèmes de chargement dynamique qui ne sont pas exploitable (trop couteux !)
    //        Aussi, il doit être possible de charger toute les textures essentielles au rendu
    //        de la map, des perso, etc.. en début de fichier
    m_vecTextureTilset.clear();
    for(int i=0; i<m_pBattleMapData->getVecFilenameTileset().size(); i++)
    {
        m_vecTextureTilset << new QOpenGLTexture(QImage(m_pBattleMapData->getVecFilenameTileset()[i]));
    }


    // Init the timer for sprite animation and bind to the callback _processSpriteAnimation() every 50ms
    m_timerSpriteAnimation = new QTimer();
    QObject::connect(m_timerSpriteAnimation, &QTimer::timeout, this, &BattleMapRender::_processSpriteAnimation);
    m_timerSpriteAnimation->start(FREQUENCE_TIMER_SPRITE_ANIMATION);

    QObject::connect(m_pBattleMapData, &BattleMapData::addIndexTexture, this, &BattleMapRender::_addTexture);
}

BattleMapRender::~BattleMapRender()
{

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
    _initShader();
}

// Shader initialisation
void BattleMapRender::_initShader()
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
            "uniform mediump int driveRenderColor;\n"
            "void main(void)\n"
            "{\n"
            "vec4 texColor;\n"
            "if(driveRenderColor == 0)"
            "{"
            "   texColor = texture2D(texture, texc.st);\n"
            "}"
            "else if(driveRenderColor == 1)"
            "{"
            "   texColor = vec4(1.0, 1.0, 0.0, 0.0);\n"
            "}"
            "if(texColor.a < 0.1)"
            "{"
            "   discard;"
            "}"
            "gl_FragColor = texColor;\n"
            "}\n";

    fragmentShader->compileSourceCode(fragmentShaderSource);

    m_shaderProgram.addShader(vertexShader);
    m_shaderProgram.addShader(fragmentShader);

    m_shaderProgram.link();

    // Identifie les variables shader
    m_positionAttrShader    = m_shaderProgram.attributeLocation("vertex");
    m_colorAttrShader       = m_shaderProgram.attributeLocation("texCoord");
    m_matrixUniformShader   = m_shaderProgram.uniformLocation("matrix");
    m_iFragmentShaderRenderType = m_shaderProgram.uniformLocation("driveRenderColor");

    m_shaderProgram.setUniformValue("texture", 0);
}

void BattleMapRender::_addTexture(int indexFilename)
{
    m_vecTextureTilset << new QOpenGLTexture(QImage(m_pBattleMapData->getVecFilenameTileset()[indexFilename]));
}


// TODO : enlever tous les appel de fonction inutiles (glDepthMask)
// draw all the object inside the battle map
// NOTE : OPENGL RENDER is like a FILO (FirstInLastOut), so the first element declare in the render will be draw after all the others
void BattleMapRender::renderBattleMap()
{
    glDepthMask(true);

    // init the background color of the battle map
    glClearColor(0.5f, 0.5f, 0.7f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // TODO : analyser le comportement de cette matrice
    QMatrix4x4 l_matrixModelView;
    l_matrixModelView.perspective(60.0f, 4.0f/3.0f, 0.1f, 100.0f);
    l_matrixModelView.translate(0, 0, -1);

    m_shaderProgram.bind();

    // Bind the uniform model matrix with the shader
    m_shaderProgram.setUniformValue(m_matrixUniformShader, l_matrixModelView);

    // Bind attribute color with shader
    m_shaderProgram.enableAttributeArray(m_colorAttrShader);

    // Bind attribute position with shader
    m_shaderProgram.enableAttributeArray(m_positionAttrShader);


    // LOOP for render each tile area :
    // the tile area can contain
    // - Tile
    // - Character
    // - Decor
    // So, there are some OpenGl options in commun between each different object that can be present on the tile (Tile, Character, Decor...)
    // and there are some OpenGl options specific to the object
    // A mask is used to know the kind of the object contained on tile
    // 010 -> Character, 100 -> Tile
    // Draw order : 1)Character 2)Tile =>

    int l_iNbRow = (m_iNbTileSide*2)-1;// TODO : Deporter l'initialisation vers le constructeur
    int l_iNbTileInRow = 0;// TODO : Deporter l'initialisation vers le constructeur
    int l_iTileCounter = 0;
    float l_fLeftCornerTileX = 0.0f;
    float l_fLeftCornerTileY = 0.0f;
    // Alpha value activated for transparence & avoid interpolation white pixel
    glBlendFuncSeparate(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
    glEnable(GL_BLEND);

    // Active the shader texture rendering
    m_shaderProgram.setUniformValue(m_iFragmentShaderRenderType, RENDER_TEXTURE_MAPPING);

    // Loop for the number of vertical row
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

            // CALCUL TILE POSITION X/Y COMMUN FOR ALL OBJECT
            // NOTE : it begin by the lower tile, which is the last one to draw above the others
            // Indeed, Opengl draw in FILO (first in last out)

            //        *9 <-- last added for rendering but first drawn
            //    *       *
            //*       *       *
            //    *2      *3
            //        *1 <-- first added for rendering but last drawn

            // Position Y
            l_fLeftCornerTileY = m_fLeftBaseCornerVertex.y() - ((m_pBattleMapData->getHeightTile()/2)*itRow);

            // Position X
            // For every row adding +/-WTile/2 from the reference point
            // => Get the position on the beginning of the row
            if(itRow < m_iNbTileSide)
            {
                l_fLeftCornerTileX = m_fLeftBaseCornerVertex.x() - (itRow * m_pBattleMapData->getWidthTile()/2);
            }
            else
            {
                l_fLeftCornerTileX = m_fLeftBaseCornerVertex.x() - ((m_iNbTileSide-1)*m_pBattleMapData->getWidthTile()/2)
                                     + ((itRow-(m_iNbTileSide-1)) * m_pBattleMapData->getWidthTile()/2);
            }
            // Adding an offset function of the position of the tile in the row
            l_fLeftCornerTileX += (itTileInRow * m_pBattleMapData->getWidthTile());


            // RENDER / DRAW CHARACTER IF SOMEONE IS PRESENT
            // ---------------------------------------------
            if(m_pBattleMapData->getVecTileArea()[l_iTileCounter].m_maskPresence.character)// Presence Character
            {
                _renderCharacterLayer(l_iTileCounter, l_fLeftCornerTileX, l_fLeftCornerTileY);
            }

            // RENDER / DRAW CURSEUR
            //----------------------
            if(m_pBattleMapData->getVecTileArea()[l_iTileCounter].m_maskPresence.cursor)// Presence Curseur
            {
                _renderCurseurLayer(l_iTileCounter, l_fLeftCornerTileX, l_fLeftCornerTileY);
            }

            // RENDER / DRAW PATH FINDING LAYER
            // -------------------------------------
            if(m_pBattleMapData->getVecTileArea()[l_iTileCounter].m_maskPresence.pathFinding)// PathFinding activé
            {
                _renderPathFindingLayer(l_iTileCounter, l_fLeftCornerTileX, l_fLeftCornerTileY);
            }

            // RENDER / DRAW TILE IF TILE IS PRESENT
            // -------------------------------------
            if(m_pBattleMapData->getVecTileArea()[l_iTileCounter].m_maskPresence.tile)// Presence Tuile
            {
                _renderTileLayer(l_iTileCounter, l_fLeftCornerTileX, l_fLeftCornerTileY);
            }

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

void BattleMapRender::_calculTileVerticesBuffer(float i_fPositionBaseX, float i_fPositionBaseY, int i_iNbSquareUp, int i_iNbSquareDown)
{
    m_vecTileVertexBuffer.clear();

    // CALCUL COORDS FOR THE BOUNDING BOX THAT CONTAINING THE WHOLE TEXTURE.
    // ALL TEXTURES HAVE THE SAME WIDTH BUT NOT NECESSARY THE SAME HEIGHT.
    // UNIT FOR THE HEIGHT PAD IS ACCORDING TO THE WIDTH OF THE TILE.
    // SO THE SIZE SIDE OF 1 SQUARE IN THE TILSET IS EQUAL TO 1 * WIDTH OF THE TILE
    // FOR EXAMPLE : IF THE TEXTURE IS MAPPED ON 2 SQUARES, COORDS SHOULD BE  2 * WIDTH OF THE TILE
    // ALSO, IT CAN BE UP AND DOWN, DEPEND ON

    // Calcul the down right and left vertices coords
    QVector3D l_vecLeftDownTileVertex (i_fPositionBaseX,
                                       i_fPositionBaseY + i_iNbSquareDown * 0.3f,// TODO : 0.3 ????
                                       0.0f);

    QVector3D l_vecRightDownTileVertex (l_vecLeftDownTileVertex.x()+m_pBattleMapData->getWidthTile(),
                                        l_vecLeftDownTileVertex.y(),
                                        0.0f);

    // Calcul the up right and left vertices coords from the down vertices
    // Note : it s "*m_pBattleMapData->getWidthTile()" because the tile is a square and so, has the same size width and length
    QVector3D l_vecRightUpTileVertex (l_vecRightDownTileVertex.x(),
                                      i_fPositionBaseY-m_pBattleMapData->getWidthTile() - i_iNbSquareUp*m_pBattleMapData->getWidthTile(),
                                      0.0f);

    QVector3D l_vecLeftUpTileVertex (l_vecLeftDownTileVertex.x(),
                                     i_fPositionBaseY-m_pBattleMapData->getWidthTile() - i_iNbSquareUp*m_pBattleMapData->getWidthTile(),
                                     0.0f);


    // Add Base Vertices in the vertex buffer
    m_vecTileVertexBuffer << l_vecLeftDownTileVertex;
    m_vecTileVertexBuffer << l_vecRightDownTileVertex;
    m_vecTileVertexBuffer << l_vecRightUpTileVertex;
    m_vecTileVertexBuffer << l_vecLeftUpTileVertex;
}

void BattleMapRender::_calculCharacterVerticesBuffer(float i_fLeftCornerTileX, float i_fLeftCornerTileY,
                                                    int i_iCharacterSizeSide, float i_fHeightTile)
{
    m_vecCharacterVertexBuffer.clear();

    //float offsetHeightSprite = 0.03f;// Avoid that character's sprite is too small

    QVector3D l_vecLeftDownCharacterVertex (i_fLeftCornerTileX - ((i_iCharacterSizeSide-1)*m_pBattleMapData->getWidthTile()/2),
                                            (i_fLeftCornerTileY - (i_fHeightTile/2 * i_iCharacterSizeSide)),
                                            0.0f);

    QVector3D l_vecRightDownCharacterVertex (l_vecLeftDownCharacterVertex.x() + (i_iCharacterSizeSide * m_pBattleMapData->getWidthTile()),
                                             l_vecLeftDownCharacterVertex.y(),
                                             0.0f);

    QVector3D l_vecRightUpCharacterVertex (l_vecRightDownCharacterVertex.x(),
                                           (i_fLeftCornerTileY - (i_iCharacterSizeSide * m_pBattleMapData->getWidthTile())/*-offsetHeightSprite*/),
                                           0.0f);

    QVector3D l_vecLeftUpCharacterVertex (l_vecLeftDownCharacterVertex.x(),
                                          l_vecRightUpCharacterVertex.y(),
                                          0.0f);

    m_vecCharacterVertexBuffer << l_vecLeftDownCharacterVertex;
    m_vecCharacterVertexBuffer << l_vecRightDownCharacterVertex;
    m_vecCharacterVertexBuffer << l_vecRightUpCharacterVertex;
    m_vecCharacterVertexBuffer << l_vecLeftUpCharacterVertex;
}


// 3_____2
// |     |
// |     |
// 0-----1
void BattleMapRender::_calculCurseurVerticesBuffer(float i_fPositionBaseX, float i_fPositionBaseY, float i_fHeightTile)
{
    int sizeSide = m_pBattleMapData->getCurseur().getSizeSide();
    m_tabCurseurVertexBuffer[0] = QVector3D (i_fPositionBaseX - ((sizeSide-1)*m_pBattleMapData->getWidthTile()/2),
                                            (i_fPositionBaseY - (i_fHeightTile/2 * sizeSide)),
                                            0.0f);
    m_tabCurseurVertexBuffer[1] = QVector3D (m_tabCurseurVertexBuffer[0].x() + (sizeSide*m_pBattleMapData->getWidthTile()), m_tabCurseurVertexBuffer[0].y(), 0.0f);
    m_tabCurseurVertexBuffer[2] = QVector3D (m_tabCurseurVertexBuffer[1].x(), m_tabCurseurVertexBuffer[1].y() - sizeSide*m_pBattleMapData->getWidthTile(), 0.0f);
    m_tabCurseurVertexBuffer[3] = QVector3D (m_tabCurseurVertexBuffer[0].x(), m_tabCurseurVertexBuffer[2].y(), 0.0f);
}

void BattleMapRender::_calculPathFindingVerticesBuffer(float i_fPositionBaseX, float i_fPositionBaseY, float i_fHeightTile)
{
    m_tabPathFindingVertexBuffer[0] = QVector3D (i_fPositionBaseX, i_fPositionBaseY - i_fHeightTile, 0.0f);
    m_tabPathFindingVertexBuffer[1] = QVector3D (m_tabPathFindingVertexBuffer[0].x() + m_pBattleMapData->getWidthTile(), m_tabPathFindingVertexBuffer[0].y(), 0.0f);
    m_tabPathFindingVertexBuffer[2] = QVector3D (m_tabPathFindingVertexBuffer[1].x(), m_tabPathFindingVertexBuffer[1].y() - m_pBattleMapData->getWidthTile(), 0.0f);
    m_tabPathFindingVertexBuffer[3] = QVector3D (m_tabPathFindingVertexBuffer[0].x(), m_tabPathFindingVertexBuffer[2].y(), 0.0f);
}


void BattleMapRender::_processSpriteAnimation()
{
    // Parcours de tous les objets animation
    for(int i=0; i<m_pBattleMapData->getVecAnimationSprite().size(); i++)
    {
        m_pBattleMapData->getVecAnimationSprite()[i]->updateAnimationSprite();
    }
}

void BattleMapRender::_renderTileLayer(int numTile, float leftCornerTileX, float leftCornerTileY)
{
    // Binding the right tileSet texture to render the tile
    m_vecTextureTilset[m_pBattleMapData->getVecTileArea()[numTile].m_tile.getIndexTexture()]->bind();

    // Calcul the new coordinates of each vertices
    _calculTileVerticesBuffer(leftCornerTileX,
                             leftCornerTileY,
                             m_pBattleMapData->getVecTileArea()[numTile].m_tile.getNbSquareUp(),
                             m_pBattleMapData->getVecTileArea()[numTile].m_tile.getNbSquareDown()
                             );

    // TODO : changer les vecteurs de données avec les données correspondant aux tiles, personnage, element du decor, etc...
    //        il faut notamment mettre à jour m_vecVertexBuffer
    // Set vertices and color with the respective data for each elements
    m_shaderProgram.setAttributeArray(m_positionAttrShader, m_vecTileVertexBuffer.constData());
    m_shaderProgram.setAttributeArray(m_colorAttrShader, m_pBattleMapData->getVecTileArea()[numTile].m_tile.getCoordTexture().constData());

    // Dessine les Vertices en les associants sous forme de Quad non relié les uns aux autres
    //glDrawArrays(GL_TRIANGLE_FAN, 0, m_vecVertexBuffer.size());
    glDrawArrays(GL_QUADS, 0, m_vecTileVertexBuffer.size());
}

void BattleMapRender::_renderCharacterLayer(int numTile, float leftCornerTileX, float leftCornerTileY)
{
    // if the character take several tile on side, it's necessary to count how many tile are met.
    // The character have to be drawn when its lower tile is met
    // Indeed, the sense for the rendering is FILO (see schemas in renderBattleMap function)
    // ex: if the character is 2 tiles side (one tile here == *) it have to be drawn when
    //     the low tile is met
    //           *
    //       *       *
    //        -->*
    // Check if the extrem tile is met and so if it's necessary to render the character
    if(m_pBattleMapData->getVecTileArea()[numTile].m_pCharacter->isReadyToRender())
    {
        // Binding the right tileSet texture to render the tile
        m_vecTextureTilset[m_pBattleMapData->getVecTileArea()[numTile].m_pCharacter->getIndexTexture()]->bind();


        // Calcul the new coordinates of each vertices
        _calculCharacterVerticesBuffer(leftCornerTileX,
                                      leftCornerTileY,
                                      m_pBattleMapData->getVecTileArea()[numTile].m_pCharacter->getSizeSide(),
                                      m_pBattleMapData->getVecTileArea()[numTile].m_tile.getElevationTile() + m_pBattleMapData->getHeightTile()/2.0f
                                      );

        // Set vertices and color with the respective data for each elements
        m_shaderProgram.setAttributeArray(m_positionAttrShader, m_vecCharacterVertexBuffer.constData());
        int l_iNbCoordTexture = 0;// useless in this case, but allow to get the size of the coord texture by output argument
        m_shaderProgram.setAttributeArray(m_colorAttrShader, m_pBattleMapData->getVecTileArea()[numTile].m_pCharacter->getCoordTexture(l_iNbCoordTexture)/*.constData()*/);

        glDrawArrays(GL_QUADS, 0, m_vecCharacterVertexBuffer.size());
    }
}

void BattleMapRender::_renderCurseurLayer(int numTile, float leftCornerTileX, float leftCornerTileY)
{
    m_vecTextureTilset[m_pBattleMapData->getCurseur().getIndexTexture()]->bind();

    // TODO : 0.04 a été trouvé de manière empirique, il va falloire refaire une passe sur la hauteur des tiles !!!
    _calculCurseurVerticesBuffer(leftCornerTileX,
                                 leftCornerTileY,
                                 m_pBattleMapData->getVecTileArea()[numTile].m_tile.getElevationTile()
                                );

    // Set vertices and color with the respective data for each elements
    m_shaderProgram.setAttributeArray(m_positionAttrShader, m_tabCurseurVertexBuffer);
    int l_iNbCoordTexture = 0;// useless in this case, but allow to get the size of the coord texture by output argument
    m_shaderProgram.setAttributeArray(m_colorAttrShader, m_pBattleMapData->getCurseur().getCoordTexture(l_iNbCoordTexture));

    glDrawArrays(GL_QUADS, 0, SIZE_VB);
}

// TODO : Améliorer
void BattleMapRender::_renderPathFindingLayer(int numTile, float leftCornerTileX, float leftCornerTileY)
{
    m_vecTextureTilset[m_pBattleMapData->getPathFinding()->getIndexTexture()]->bind();

    _calculPathFindingVerticesBuffer(leftCornerTileX,
                                 leftCornerTileY,
                                 m_pBattleMapData->getVecTileArea()[numTile].m_tile.getElevationTile()
                                );

    // Set vertices and color with the respective data for each elements
    m_shaderProgram.setAttributeArray(m_positionAttrShader, m_tabPathFindingVertexBuffer);
    int l_iNbCoordTexture = 0;// useless in this case, but allow to get the size of the coord texture by output argument
    m_shaderProgram.setAttributeArray(m_colorAttrShader, m_pBattleMapData->getPathFinding()->getCoordTexture(l_iNbCoordTexture));

    glDrawArrays(GL_QUADS, 0, SIZE_VB);
}

//TODO : Finir
void BattleMapRender::_renderObjectLayer()
{

}

void BattleMapRender::_renderAnimationLayer()
{

}
