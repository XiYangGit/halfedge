#include "drawable.h"
#include <la.h>

Drawable::Drawable(GLWidget277* context)
    : bufIdx(), bufPos(), bufNor(), bufCol(),
      idxBound(false), posBound(false), norBound(false), colBound(false),
      context(context)
    ,bufInf(),bufWei(),infBound(false),weiBound(false)  //added by Xi Yang
{}


void Drawable::destroy()
{
    context->glDeleteBuffers(1, &bufIdx);
    context->glDeleteBuffers(1, &bufPos);
    context->glDeleteBuffers(1, &bufNor);
    context->glDeleteBuffers(1, &bufCol);
    //added by Xi Yang
    context->glDeleteBuffers(1, &bufInf);
    context->glDeleteBuffers(1, &bufWei);
}

GLenum Drawable::drawMode()
{
    // Since we want every three indices in bufIdx to be
    // read to draw our Drawable, we tell that the draw mode
    // of this Drawable is GL_TRIANGLES

    // If we wanted to draw a wireframe, we would return GL_LINES

    return GL_TRIANGLES;
}

int Drawable::elemCount()
{
    return count;
}

void Drawable::generateIdx()
{
    idxBound = true;
    // Create a VBO on our GPU and store its handle in bufIdx
    context->glGenBuffers(1, &bufIdx);
}

void Drawable::generatePos()
{
    posBound = true;
    // Create a VBO on our GPU and store its handle in bufPos
    context->glGenBuffers(1, &bufPos);
}

void Drawable::generateNor()
{
    norBound = true;
    // Create a VBO on our GPU and store its handle in bufNor
    context->glGenBuffers(1, &bufNor);
}

void Drawable::generateCol()
{
    colBound = true;
    // Create a VBO on our GPU and store its handle in bufCol
    context->glGenBuffers(1, &bufCol);
}

bool Drawable::bindIdx()
{
    if(idxBound) {
        context->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufIdx);
    }
    return idxBound;
}

bool Drawable::bindPos()
{
    if(posBound){
        context->glBindBuffer(GL_ARRAY_BUFFER, bufPos);
    }
    return posBound;
}

bool Drawable::bindNor()
{
    if(norBound){
        context->glBindBuffer(GL_ARRAY_BUFFER, bufNor);
    }
    return norBound;
}

bool Drawable::bindCol()
{
    if(colBound){
        context->glBindBuffer(GL_ARRAY_BUFFER, bufCol);
    }
    return colBound;
}


//added by Xi Yang
void Drawable::generateInf()
{
    infBound = true;
    // Create a VBO on our GPU and store its handle in bufInf
    context->glGenBuffers(1, &bufInf);
}
void Drawable::generateWei()
{
    weiBound = true;
    // Create a VBO on our GPU and store its handle in bufWei
    context->glGenBuffers(1, &bufWei);
}
bool Drawable::bindInf()
{
    if(infBound){
        context->glBindBuffer(GL_ARRAY_BUFFER, bufInf);
    }
    return infBound;
}
bool Drawable::bindWei()
{
    if(weiBound){
        context->glBindBuffer(GL_ARRAY_BUFFER, bufWei);
    }
    return weiBound;
}
