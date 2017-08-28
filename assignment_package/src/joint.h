#ifndef JOINT_H
#define JOINT_H
#include <vector>
#include<QString>
#include "la.h"
#include <glm/glm.hpp>
#include "drawable.h"
#include <QTreeWidgetItem>

class Joint:public QTreeWidgetItem
{
private:
    QString Name;
    Joint* Parents;
    std::vector<Joint*> children;
    glm::vec3 Position;
    glm::quat Rotation;
    glm::mat4 BindMatrix;

public:
    Joint();
    Joint(const QString &name);
    ~Joint();
    glm::mat4 GetLocalTransformation();
    glm::mat4 GetOverallTransformation();
    Joint* GetParents();
    std::vector<Joint*> GetChildren();
    glm::vec3 GetPosition();
    glm::quat GetRotation();
    glm::mat4 GetBindMatrix();
    QString GetJointName();
    void SetParents(Joint*);
    virtual void addChild(QTreeWidgetItem*);
    void SetPosition(glm::vec3);
    void SetRotation(glm::quat);
    void SetBindMatrix(glm::mat4);
    Joint* GetChildrenByNum(unsigned int);
    void GetJointList(Joint*, std::vector<Joint*> &);
    void RotateByQuat(glm::quat);
};

#endif // JOINT_H
