#ifndef SFACE_H
#define SFACE_H

#include "drawable.h"

#include <QOpenGLContext>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <la.h>
#include "halfedge.h"
#include "vertex.h"
#include "face.h"


class sFace : public Drawable
{
public:
    sFace(GLWidget277 *context);
    virtual void create();
    virtual GLenum drawMode();
    void SetsFace(Face *);
private:
    Face *fc;

};

#endif // SFACE_H
