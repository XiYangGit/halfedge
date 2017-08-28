#ifndef JSPHERE_H
#define JSPHERE_H

#include "drawable.h"

#include <QOpenGLContext>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <la.h>
#include <joint.h>
class Joint;
class JSphere : public Drawable
{
public:
    JSphere(GLWidget277 *context);
    virtual void create();
    virtual GLenum drawMode();
    void SetJoint(Joint*);
    void SetJoint(Joint *,glm::vec4);
private:
    Joint* jt;
    glm::vec4 color;
};

#endif // JSPHERE_H
