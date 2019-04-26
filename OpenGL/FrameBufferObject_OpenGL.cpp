#include "FrameBufferObject_OpenGL.h"

QQuickFramebufferObject::Renderer* FrameBufferObject_OpenGL::createRenderer() const
{
    qDebug()<<"QQuickFramebufferObject::Renderer* createRenderer()";

    return new FrameBufferRenderer_OpenGL;
}


/*FrameBufferObject_OpenGL::FrameBufferObject_OpenGL(BattleMapRender* battleRender):
    //m_rendererFrameBuffer(NULL),
    m_pBattleRender(battleRender)
{
    //connect(this, &QQuickItem::windowChanged, this, &FrameBufferObject_OpenGL::handleWindowChanged);
}*/

/*
void FrameBufferObject_OpenGL::handleWindowChanged(QQuickWindow *win)
{
    if (win) {
        connect(win, &QQuickWindow::beforeSynchronizing, this, &FrameBufferObject_OpenGL::sync, Qt::DirectConnection);
        //connect(win, &QQuickWindow::sceneGraphInvalidated, this, &FrameBufferObject_OpenGL::cleanup, Qt::DirectConnection);

        win->setClearBeforeRendering(false);
    }
}

void FrameBufferObject_OpenGL::sync()
{
    if (!m_rendererFrameBuffer) {
        m_rendererFrameBuffer = new FrameBufferRenderer_OpenGL();
        connect(window(), &QQuickWindow::beforeRendering, m_rendererFrameBuffer, &FrameBufferRenderer_OpenGL::paint, Qt::DirectConnection);
    }
    m_rendererFrameBuffer->setViewportSize(window()->size() * window()->devicePixelRatio());
    m_rendererFrameBuffer->setWindow(window());
}
*/
