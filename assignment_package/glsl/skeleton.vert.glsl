#version 150
// ^ Change this to version 130 if you have compatibility issues
uniform mat4 u_Model;
uniform mat4 u_ModelInvTr;
uniform mat4 u_ViewProj;

uniform mat4 u_Bind_Matrices[100];
uniform mat4 u_Joint_Transformations[100];
in ivec2 vs_Vertex_Influencer_IDs;
in vec2 vs_Vertex_Weights;

in vec4 vs_Pos;
in vec4 vs_Nor;
in vec4 vs_Col;

out vec4 fs_Nor;
out vec4 fs_LightVec;
out vec4 fs_Col;

const vec4 lightPos = vec4(5,5,3,1);

void main()
{
    fs_Col=vs_Col;
    //fs_Col = vec4(u_Joint_Transformations[vs_Vertex_Influencer_IDs[0]],u_Joint_Transformations[vs_Vertex_Influencer_IDs[1]],0,1);
    //fs_Col = vec4(abs(u_Bind_Matrices[vs_Vertex_Influencer_IDs[0]][0][3]) / 2.0f, abs(u_Bind_Matrices[vs_Vertex_Influencer_IDs[0]][1][3]) / 2.0f, 0, 1);
    //fs_Col = vec4(abs(u_Joint_Transformations[vs_Vertex_Influencer_IDs[0]][0][1]) / 2.0f, abs(u_Joint_Transformations[vs_Vertex_Influencer_IDs[0]][0][2]) / 2.0f, 0, 1);
    //fs_Col=vec4(vs_Vertex_Influencer_IDs[0]/20.f,vs_Vertex_Influencer_IDs[1]/20.f,0,1);
    mat3 invTranspose = mat3(u_ModelInvTr);
//    vec4 pos0=vs_Vertex_Weights[0]*u_Joint_Transformations[vs_Vertex_Influencer_IDs[0]]*u_Bind_Matrices[vs_Vertex_Influencer_IDs[0]]*vs_Pos+
//            vs_Vertex_Weights[1]*u_Joint_Transformations[vs_Vertex_Influencer_IDs[1]]*u_Bind_Matrices[vs_Vertex_Influencer_IDs[1]]*vs_Pos;
    float w1=vs_Vertex_Weights[0];
    float w2=vs_Vertex_Weights[1];
    mat4 t1=u_Joint_Transformations[vs_Vertex_Influencer_IDs[0]];
    mat4 t2=u_Joint_Transformations[vs_Vertex_Influencer_IDs[1]];
    mat4 b1=u_Bind_Matrices[vs_Vertex_Influencer_IDs[0]];
    mat4 b2=u_Bind_Matrices[vs_Vertex_Influencer_IDs[1]];
    vec4 pos0=w1*t1*b1*vs_Pos+w2*t2*b2*vs_Pos;
    //pos0=vs_Pos;
    fs_Nor = vec4(invTranspose * vec3(vs_Nor), 0);
    vec4 modelposition = u_Model * pos0;
    fs_LightVec = lightPos - modelposition;
    gl_Position = u_ViewProj * modelposition;



}
