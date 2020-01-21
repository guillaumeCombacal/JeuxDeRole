#include "PathFinding.h"

#include "QDebug"

PathFinding::PathFinding(int i_indexOrigin, int i_depthPathFinding, int i_nbTileSideMap):
    m_bIsActivated(false),
    m_indexOrigin(i_indexOrigin),
    m_depthPathFinding(i_depthPathFinding),
    m_nbTileSideMap(i_nbTileSideMap),
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

bool PathFinding::isIndexInPathFinding(int i_index)
{
    for(int i=0; i<m_vecIndexPathFinding.size(); i++)
    {
        if(m_vecIndexPathFinding[i] == i_index)
        {
            return true;
        }
    }
    return false;
}


void PathFinding::_calculPathFinding()
{
    m_vecIndexPathFinding.clear();

    if(m_depthPathFinding>0 && m_nbTileSideMap>0)
    {
        int l_limitIndexColumnMap_Up;
        if((m_nbTileSideMap-1) - (m_indexOrigin%m_nbTileSideMap) > m_depthPathFinding)
        {
            l_limitIndexColumnMap_Up = m_indexOrigin+m_depthPathFinding;
        }
        else
        {
            l_limitIndexColumnMap_Up = m_indexOrigin + ((m_nbTileSideMap-1) - (m_indexOrigin%m_nbTileSideMap));
        }

        int l_limitIndexColumnMap_Down;
        if(m_indexOrigin%m_nbTileSideMap > m_depthPathFinding)
        {
            l_limitIndexColumnMap_Down = m_indexOrigin-m_depthPathFinding;
        }
        else
        {
            l_limitIndexColumnMap_Down = m_indexOrigin - (m_indexOrigin%m_nbTileSideMap);
        }

        int l_limitIndexLineMap_Down;
        if(m_indexOrigin/m_nbTileSideMap > m_depthPathFinding)
        {
            l_limitIndexLineMap_Down = m_indexOrigin - (m_depthPathFinding*m_nbTileSideMap);
        }
        else
        {
            l_limitIndexLineMap_Down = m_indexOrigin - ((m_indexOrigin/m_nbTileSideMap)*m_nbTileSideMap);
        }

        int l_limitIndexLineMap_Up;
        if((m_nbTileSideMap-1) - (m_indexOrigin/m_nbTileSideMap) > m_depthPathFinding)
        {
            l_limitIndexLineMap_Up = m_indexOrigin + (m_depthPathFinding*m_nbTileSideMap);
        }
        else
        {
            l_limitIndexLineMap_Up = m_indexOrigin + ((((m_nbTileSideMap-1)-(m_indexOrigin/m_nbTileSideMap))) * m_nbTileSideMap);
        }

        m_vecIndexPathFinding.clear();

        for(int i=0; i<m_depthPathFinding; i++)
        {
            // Add tile in cross extremities (*)
            //    *
            //    *
            //* * * * *
            //    *
            //    *
            if(l_limitIndexColumnMap_Up >= m_indexOrigin+(i+1))
            {
                m_vecIndexPathFinding<<m_indexOrigin + (i+1);
            }
            if(l_limitIndexColumnMap_Down <= m_indexOrigin-(i+1))
            {
                m_vecIndexPathFinding<<m_indexOrigin - (i+1);
            }
            if(l_limitIndexLineMap_Up >= m_indexOrigin + ((i+1)*m_nbTileSideMap))
            {
                m_vecIndexPathFinding<<m_indexOrigin + ((i+1)*m_nbTileSideMap);
            }
            if(l_limitIndexLineMap_Down <= m_indexOrigin - ((i+1)*m_nbTileSideMap))
            {
                m_vecIndexPathFinding<<m_indexOrigin - ((i+1)*m_nbTileSideMap);
            }

            // Tiles which dont belong to the cross.
            // Begin with the extrem tiles and get closer to to the origin tile (0)
            //        *
            //      0 * 0
            //    0 0 * 0 0
            //  0 0 0 * 0 0 0
            //* * * * * * * * *
            //  0 0 0 * 0 0 0
            //    0 0 * 0 0
            //      0 * 0
            //        *
            if(i >= 1)
            {
                for(int j=0; j<i; j++)
                {
                    if(m_indexOrigin + (j+1) <= l_limitIndexColumnMap_Up
                       && m_indexOrigin + ((i-j)*m_nbTileSideMap) <= l_limitIndexLineMap_Up)
                    {
                        m_vecIndexPathFinding << m_indexOrigin + ((i-j)*m_nbTileSideMap) + (j+1);
                    }
                    if(m_indexOrigin - (j+1) >= l_limitIndexColumnMap_Down
                       && m_indexOrigin + ((i-j)*m_nbTileSideMap) <= l_limitIndexLineMap_Up)
                    {
                        m_vecIndexPathFinding << m_indexOrigin + ((i-j)*m_nbTileSideMap) - (j+1);
                    }
                    if(m_indexOrigin + (j+1) <= l_limitIndexColumnMap_Up
                       && m_indexOrigin - ((i-j)*m_nbTileSideMap) >= l_limitIndexLineMap_Down)
                    {
                        m_vecIndexPathFinding << m_indexOrigin - ((i-j)*m_nbTileSideMap) + (j+1);
                    }
                    if(m_indexOrigin - (j+1) >= l_limitIndexColumnMap_Down
                       && m_indexOrigin - ((i-j)*m_nbTileSideMap) >= l_limitIndexLineMap_Down)
                    {
                        m_vecIndexPathFinding << m_indexOrigin - ((i-j)*m_nbTileSideMap) - (j+1);
                    }
                }
            }
        }
    }
}

