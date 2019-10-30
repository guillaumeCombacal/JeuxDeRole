#include "Curseur.h"

/*
#include "QDebug"

#include <QJsonArray>
#include <QVector2D>

#define TIMEOUT_ANIMATION_Curseur 300// timeout in ms between changing state
*/
Curseur::Curseur():
    m_iIndexTileAreaPathFinding(0),
    m_iIndexTexture(0),
    m_strImgFilePath(""),
    m_bIsVisible(false)
{
    std::memset(&m_tabCoordTexture, 0, sizeof(QVector2D)*NB_COORD_TEXTURE);
}

Curseur::~Curseur()
{
}
