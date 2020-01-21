#ifndef FRAMEBUFFERRENDERER_OPENGL_H
#define FRAMEBUFFERRENDERER_OPENGL_H

#include <QQuickFramebufferObject>
#include <QOpenGLFramebufferObjectFormat>
#include <QOpenGLFramebufferObject>
#include <QOpenGLShaderProgram>

class FrameBufferRenderer_OpenGL : public QQuickFramebufferObject::Renderer
{

public:
    FrameBufferRenderer_OpenGL();

    QOpenGLFramebufferObject* createFramebufferObject(const QSize &size);

    void render();
};

#endif // FRAMEBUFFERRENDERER_OPENGL_H
