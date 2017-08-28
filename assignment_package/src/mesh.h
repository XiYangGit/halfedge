#ifndef MESH_H
#define MESH_H

#include "drawable.h"
#include <la.h>
#include "vertex.h"
#include "face.h"
#include "halfedge.h"
#include "joint.h"
#include <QOpenGLContext>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <vector>
#include <fstream>

class Mesh : public Drawable
{
private:

    std::vector<HalfEdge*> edges;
    std::vector<Face*> faces;
    std::vector<Vertex*> vertices;
    std::vector<Joint*> joints;
public:
    Mesh(GLWidget277* context);
    Mesh(GLWidget277* context,std::vector<HalfEdge*>,std::vector<Face*>,std::vector<Vertex*>);
    ~Mesh();
    void SetHalfEdge(HalfEdge*);
    void SetFace(Face*);
    void SetVertex(Vertex*);
    HalfEdge* GetEdgeByNum(unsigned int);
    Face* GetFaceByNum(unsigned int);
    Vertex* GetVertexByNum(unsigned int);
    int GetEgdeNum();
    int GetFaceNum();
    int GetVertexNum();
    virtual void create();
    void CreatCube();
    void CreateFromOBJ(std::vector<glm::vec3> vert_pos,std::vector<glm::vec2> vert_vt,
                       std::vector<glm::vec3> vert_nor,std::vector<std::vector<glm::vec3>> faceVector);

    void CalculateSYM();
    void AddVertex(HalfEdge *h,glm::vec3 pos);
    void TriangulateQuad(Face *f);
    void Triangulate(Face *f);

    std::vector<glm::vec3> CalculateCentroid();
    std::vector<glm::vec3> CalculateEdgeVertex(std::vector<glm::vec3>);
    void SmoothVertex(std::vector<glm::vec3>,std::vector<glm::vec3>);

    //void Quadrangulate(Face *f, glm::vec3 ct,std::vector<HalfEdge*> midEdge);
    void Quadrangulate(glm::vec3 ct,std::vector<HalfEdge*> midEdge);
    void Subdivision(std::vector<glm::vec3>,std::vector<glm::vec3>);

    void Extrude(Face *f);
    void skinningfunction();

    void AddInfluenceJoint(Joint*);
    Joint* GetJointByNum(unsigned int);
    void clearjoints();
    void SetInfluenceFactor(Vertex*);
    unsigned int GetJointsNum();
};
#endif // MESH_H

