#ifndef SPOINT_H
#define SPOINT_H
#include "drawable.h"
#include "vertex.h"
#include <la.h>


#include <QOpenGLContext>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>

class sPoint : public Drawable
{
public:
    sPoint(GLWidget277* context);
    virtual void create();
    virtual GLenum drawMode();
    void SetPointPos(Vertex *);
private:
    Vertex* vert;
};

#endif // SPOINT_H
