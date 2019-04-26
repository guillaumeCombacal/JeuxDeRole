#include "FrameBufferRenderer_OpenGL.h"
#include "OpenGlRenderSingleton.h"

FrameBufferRenderer_OpenGL::FrameBufferRenderer_OpenGL()
{
    // Init Obj OpenGL, ex:
    //m_openGlRender.initialize();

    OpenGlRenderSingleton::getInstance()->init();

    // !!!! NOTE :
    // Ici on ne peut pas instancier le battleMapRender car FrameBufferRenderer_OpenGL ne détient pas
    // de données concernant le battleMapData et ne peut donc pas utiliser le constructeur,
    // Il faudrait que FrameBufferRenderer_OpenGL ce passe lui même (this) vers un controller au moment de son instanciation
    // par le biais d'une fonction statique (et d'un attribut statique de type FrameBufferRenderer_OpenGL),
    // vers un conroller qui assurerait la gestion des model de rendu à charger dans la classe FrameBufferRenderer_OpenGL
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
    //m_openGlRender.render();

    // Rendu via un singleton (pas besoin de créer l'instance)
    OpenGlRenderSingleton::getInstance()->render();

    update();
}

