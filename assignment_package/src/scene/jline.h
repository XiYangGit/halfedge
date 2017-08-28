#ifndef JLINE_H
#define JLINE_H
#include "drawable.h"

#include <QOpenGLContext>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <la.h>
#include "joint.h"
class Joint;
class JLine : public Drawable
{
public:
    JLine(GLWidget277 *context);
    virtual void create();
    virtual GLenum drawMode();
    void SetLJoint(Joint*);
private:
    Joint* jt;

};

#endif // JLINE_H
