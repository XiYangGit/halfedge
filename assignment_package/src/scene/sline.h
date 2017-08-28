#ifndef SLINE_H
#define SLINE_H

#include "drawable.h"

#include <QOpenGLContext>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <la.h>
#include "halfedge.h"
#include "vertex.h"


class sLine : public Drawable
{
public:
    sLine(GLWidget277 *context);
    virtual void create();
    virtual GLenum drawMode();
    void SetHE(HalfEdge *);
private:
    HalfEdge* he;

};

#endif // SLINE_H
