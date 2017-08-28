#include "halfedge.h"


///--------------------------------------------
/// ----------implements of HalfEdge-----------
/// -------------------------------------------
HalfEdge::HalfEdge():HalfEdge(nullptr,nullptr,nullptr,nullptr,0){}
HalfEdge::HalfEdge(Face *f, Vertex *v, HalfEdge *n, HalfEdge *s, unsigned int i):
    face(f),vert(v),next(n),sym(s),HalfEdgeID(i)
{

}
HalfEdge::~HalfEdge()
{
    face=nullptr;
    vert=nullptr;
    next=nullptr;
    sym=nullptr;
}

void HalfEdge::SetFace(Face *f)
{
    face=f;
}
void HalfEdge::SetVertex(Vertex *v)
{
    vert=v;
}
void HalfEdge::SetNext(HalfEdge *n)

{
    next=n;
}
void HalfEdge::SetSym(HalfEdge *s)
{
    sym=s;
}
void HalfEdge::SetHalfEdgeID(unsigned int i)
{
    HalfEdgeID=i;
}

Face* HalfEdge::GetFace()
{
    return face;
}
Vertex* HalfEdge::GetVertex()
{
    return vert;
}
HalfEdge* HalfEdge::GetNext()
{
    return next;
}
HalfEdge* HalfEdge::GetSym()
{
    return sym;
}
unsigned int HalfEdge::GetHalfEdgeID()
{
    return HalfEdgeID;
}
HalfEdge* HalfEdge::GetPrevious()
{
    return face->GetPreEdge(this);
}
