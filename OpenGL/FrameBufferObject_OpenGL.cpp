#include "FrameBufferObject_OpenGL.h"

QQuickFramebufferObject::Renderer* FrameBufferObject_OpenGL::createRenderer() const
{
    qDebug()<<"QQuickFramebufferObject::Renderer* createRenderer()";

    return new FrameBufferRenderer_OpenGL;
}
