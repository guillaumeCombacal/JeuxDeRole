#ifndef FRAMEBUFFEROBJECT_OPENGL_H
#define FRAMEBUFFEROBJECT_OPENGL_H

#include <QQuickFramebufferObject>
//#include <QtQuick/QQuickFramebufferObject>

#include "FrameBufferRenderer_OpenGL.h"

class FrameBufferObject_OpenGL : public QQuickFramebufferObject
{
    Q_OBJECT

public:
    QQuickFramebufferObject::Renderer* createRenderer() const;

private:
    //FrameBufferRenderer_OpenGL* m_rendererFrameBuffer;
};

#endif // FRAMEBUFFEROBJECT_OPENGL_H

