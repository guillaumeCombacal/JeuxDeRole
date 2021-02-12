#include "PathFinding.h"

#include "QDebug"

PathFinding::PathFinding(int i_depthPathFinding, int i_nbTileSideMap):
    m_bIsActivated(false),
    m_depthPathFinding(i_depthPathFinding),
    m_nbTileSideMap(i_nbTileSideMap),
    m_nbTileSidePathfinding(1),
    m_characterTileSide(0),
    m_strImgTilesheetFilePath(QString("C:/Users/Yaku/Documents/DeveloppementCode/PROJECT/jeuxDeRole/JeuDeRole/Ressources/ImgTest/tilePathFinding.png"))
{
    _calculPathFinding();

    m_tabCoordTexture[0] = QVector2D(0.0f,1.0f);
    m_tabCoordTexture[1] = QVector2D(1.0f,1.0f);
    m_tabCoordTexture[2] = QVector2D(1.0f,0.0f);
    m_tabCoordTexture[3] = QVector2D(0.0f,0.0f);
}

PathFinding::~PathFinding()
{
}

void PathFinding::clearVecPathFinding()
{
    m_vecIndexPathFinding.clear();
}

void PathFinding::_calculPathFinding()
{
    m_vecIndexPathFinding.clear();

    if(m_characterTileSide > 0 && m_indexesOrigin.size()>0 && m_depthPathFinding > 0 && m_nbTileSideMap > 0 && m_nbTileSidePathfinding >= 1)
    {
        // CALCUL LIMITS PATHFINDING

        // Limits example        
        // Character tile side = 1 (P) ==> Limit to reach border 1 or 2
        //               *
        //          *         *
        //     2         *          2
        //*         *         *          *
        //     *         P          *
        //          1         1
        //               *
        // Character tile side = 2 (P,D,U)
        // Limits (1) found according to D and U (Downest and uppest index among character's indexes)
        //               *
        //          1         1
        //     *         U          *
        //*         P         P          *
        //     *         D          *
        //          1         1
        //               *


        // In case characterTileSide = 1, indexUpTile = indexDownTile
        int indexUpTile = -1;
        int indexDownTile = m_nbTileSideMap * m_nbTileSideMap +1;
        for(int i=0; i<m_indexesOrigin.size(); i++)
        {
            if(indexUpTile < m_indexesOrigin[i])
            {
                indexUpTile = m_indexesOrigin[i];
            }

            if(indexDownTile > m_indexesOrigin[i])
            {
                indexDownTile = m_indexesOrigin[i];
            }
        }

        // Example index map with character (P)
        //               15
        //          11        14
        //     7         P          13
        //3         P         P          12
        //     2         P          8
        //          1         4
        //               0


        m_vecIndexPathFinding.clear();
        // Tile side character = 1 and depth path finding = 2 (0 and X = points found with pathfinding)
        //                    *
        //               *         *
        //          0         X          0
        //     *         0         0          *
        //*         X         P         X          *
        //     *         0         0          *
        //          0         X          0
        //               *         *
        //                    *
        //
        // Tile side character = 2 and depth path finding = 2 (0 and X = points found with pathfinding)
        //                    *
        //               0         X
        //          0         0          0
        //     *         0         P          0
        //*         X         P         P          X
        //     *         0         P          0
        //          0         0          0
        //               0         X
        //                    *


        QVector<int> currentSeedIndexes;
        QVector<int> nextSeedIndex;
        bool isChangeColumnUp = false;// when row iteration it's impossible to change column (no teleportation ;)
        bool isChangeColumnDown = false;
        for(int i=0; i<m_depthPathFinding; i++)
        {
            // Add tile as seed progression
            //                    *
            //               2         2
            //          2         1          1
            //     *         1         P          1
            //*         2         P         P          2
            //     *         1         P          1
            //          2         1          1
            //               2         2
            //                    *

            // First turn start from character
            if(i == 0){
                nextSeedIndex = m_indexesOrigin;
            }
            currentSeedIndexes = nextSeedIndex;
            nextSeedIndex.clear();

            for(int j=0; j<currentSeedIndexes.size(); j++)
            {
                // Row
                isChangeColumnUp = (currentSeedIndexes[j] / m_nbTileSideMap) != ((currentSeedIndexes[j]+1) / m_nbTileSideMap);
                if(!m_vecIndexPathFinding.contains(currentSeedIndexes[j]+1) && !isChangeColumnUp &&
                   m_nbTileSideMap*m_nbTileSideMap > currentSeedIndexes[j]+1 )
                {
                   nextSeedIndex << currentSeedIndexes[j]+1;
                   m_vecIndexPathFinding << currentSeedIndexes[j]+1;
                }
                isChangeColumnDown = (currentSeedIndexes[j] / m_nbTileSideMap) != ((currentSeedIndexes[j]-1) / m_nbTileSideMap);
                if(!m_vecIndexPathFinding.contains(currentSeedIndexes[j]-1) && !isChangeColumnDown &&
                   0 <= currentSeedIndexes[j]-1 )
                {
                   nextSeedIndex << currentSeedIndexes[j]-1;
                   m_vecIndexPathFinding << currentSeedIndexes[j]-1;
                }

                // Column
                if(!m_vecIndexPathFinding.contains(currentSeedIndexes[j]+m_nbTileSideMap) &&
                   m_nbTileSideMap*m_nbTileSideMap > currentSeedIndexes[j]+m_nbTileSideMap)
                {
                   nextSeedIndex << currentSeedIndexes[j]+m_nbTileSideMap;
                   m_vecIndexPathFinding << currentSeedIndexes[j]+m_nbTileSideMap;
                }
                if(!m_vecIndexPathFinding.contains(currentSeedIndexes[j]-m_nbTileSideMap) &&
                   0 < currentSeedIndexes[j]-m_nbTileSideMap)
                {
                   nextSeedIndex << currentSeedIndexes[j]-m_nbTileSideMap;
                   m_vecIndexPathFinding << currentSeedIndexes[j]-m_nbTileSideMap;
                }
            }
        }
    }
}

