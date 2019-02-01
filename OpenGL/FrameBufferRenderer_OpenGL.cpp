#include "FrameBufferRenderer_OpenGL.h"

FrameBufferRenderer_OpenGL::FrameBufferRenderer_OpenGL()
{
    // Init Obj OpenGL, ex:
    m_openGlRender.initialize();
}

QOpenGLFramebufferObject* FrameBufferRenderer_OpenGL::createFramebufferObject(const QSize &size)
{
    QOpenGLFramebufferObjectFormat format;
    format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    // optionally enable multisampling by doing
    // format.setSamples(4);

    return new QOpenGLFramebufferObject(size, format);
}

void FrameBufferRenderer_OpenGL::render()
{
    // render de l'objet openGL
    m_openGlRender.render();
    update();
}

