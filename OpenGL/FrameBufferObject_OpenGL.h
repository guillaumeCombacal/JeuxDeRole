#ifndef FRAMEBUFFEROBJECT_OPENGL_H
#define FRAMEBUFFEROBJECT_OPENGL_H

#include <QQuickFramebufferObject>
#include "FrameBufferRenderer_OpenGL.h"

class FrameBufferObject_OpenGL : public QQuickFramebufferObject
{
    Q_OBJECT

public:
    QQuickFramebufferObject::Renderer* createRenderer() const;
};

#endif // FRAMEBUFFEROBJECT_OPENGL_H

