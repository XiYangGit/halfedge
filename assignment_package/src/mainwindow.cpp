#include "mainwindow.h"
#include <ui_mainwindow.h>
#include "cameracontrolshelp.h"
#include <QFileDialog>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <cstddef>
#include "mesh.h"
#include <iostream>
#include <cstring>
#include <vector>
#include <QCoreApplication>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mygl->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::exit();
}

void MainWindow::on_actionCamera_Controls_triggered()
{
    CameraControlsHelp* c = new CameraControlsHelp();
    c->show();
}

void MainWindow::on_actionLoad_OBJ_triggered()
{
    QString filename = QFileDialog::getOpenFileName(0, QString("Load OBJ File"), QDir::currentPath().append(QString("../..")), QString("*.obj"));
    if(filename==NULL)
        return;
    std::string name=filename.toStdString();

    using namespace std;
    std::vector<glm::vec3> vert_pos;
    std::vector<glm::vec2> vert_vt;
    std::vector<glm::vec3> vert_nor;
    std::vector<std::vector<glm::vec3>> faceVector;

    ifstream ifs;
    ifs.open(name);
    string s;
    while(std::getline(ifs,s))
    {
         if(s.length()<2)continue;
         if(s[0]=='v')
         {
             if(s[1]=='t')    //read vt
             {
                 istringstream in(s);
                 glm::vec2 vt;
                 std::string head;
                 in>>head>>vt[0]>>vt[1];
                 vert_vt.push_back(vt);
             }
             else if(s[1]=='n')    //read vn
             {
                 istringstream in(s);
                 glm::vec3 vn;
                 std::string head;
                 in>>head>>vn[0]>>vn[1]>>vn[2];
                 vert_nor.push_back(vn);
             }
             else       //read v
             {
                 istringstream in(s);
                 glm::vec3 pos;
                 std::string head;
                 in>>head>>pos[0]>>pos[1]>>pos[2];
                 vert_pos.push_back(pos);
             }
         }

          else if(s[0]=='f')  //read face
         {
             int ptCount=1;
             for(int k=s.size()-1;k>=0;k--)
             {
                if(s[k]=='/')
                {
                    s[k]=' ';
                    ptCount++;
                }
             }
             ptCount/=2;
             istringstream in(s);
             string head;
             in>>head;
             glm::vec3 fc;
             vector<glm::vec3> fcvector;
             for(int k=0;k<ptCount;k++)
             {
                 in>>fc[0]>>fc[1]>>fc[2];
                 fcvector.push_back(fc);
             }
             faceVector.push_back(fcvector);

         }
    }


//    for(int i=0;i<vert_pos.size();i++)
//    {
//        cout<<"vert "<<i<<endl;
//    }
//    for(int i=0;i<faceVector.size();i++)
//    {
//        cout<<"face "<<i<<endl;
//        for(int k=0;k<faceVector[i].size();k++)
//        {
//            vector<glm::vec3> m=faceVector[i];
//            cout<<m[k][0]<<" "<<m[k][1]<<" "<<m[k][2]<<endl;
//        }
//    }
    ui->mygl->LoadObj(vert_pos,vert_vt,vert_nor,faceVector);

}

void MainWindow::on_actionLoad_Json_File_triggered()
{
        QString filename = QFileDialog::getOpenFileName(0, QString("Load Json File"), QDir::currentPath().append(QString("../..")), QString("*.json"));
        if(filename==NULL)
            return;
        int i = filename.length() - 1;
        while(QString::compare(filename.at(i), QChar('/')) != 0)
        {
            i--;
        }
        //QStringRef local_path = filename.leftRef(i+1);

        QFile file(filename);
        if(!file.open(QIODevice::ReadOnly)){
            qWarning("Could not open the JSON file.");
            return;
        }
        QByteArray file_data = file.readAll();

        QJsonDocument jdoc(QJsonDocument::fromJson(file_data));
        //Read the mesh data in the file
        QJsonObject root = jdoc.object()["root"].toObject();
        //QJsonObject root=jdoc.object();
        ui->mygl->clearmeshjoints();
        Joint* rootj=ui->mygl->CreateFromJson(root);
        //std::cout<<rootj->GetJointName().toStdString()<<std::endl;

        ui->mygl->SetRootJoint(rootj);


}
void MainWindow::slot_ShowLocalTrans(Joint *j)
{
    glm::mat4 trans=j->GetLocalTransformation();
    //glm::mat4 trans=j->GetBindMatrix();
    trans=glm::transpose(trans);
    ui->r00->setText(QString::number(trans[0][0]));
    ui->r01->setText(QString::number(trans[0][1]));
    ui->r02->setText(QString::number(trans[0][2]));
    ui->r03->setText(QString::number(trans[0][3]));
    ui->r10->setText(QString::number(trans[1][0]));
    ui->r11->setText(QString::number(trans[1][1]));
    ui->r12->setText(QString::number(trans[1][2]));
    ui->r13->setText(QString::number(trans[1][3]));
    ui->r20->setText(QString::number(trans[2][0]));
    ui->r21->setText(QString::number(trans[2][1]));
    ui->r22->setText(QString::number(trans[2][2]));
    ui->r23->setText(QString::number(trans[2][3]));
    ui->r30->setText(QString::number(trans[3][0]));
    ui->r31->setText(QString::number(trans[3][1]));
    ui->r32->setText(QString::number(trans[3][2]));
    ui->r33->setText(QString::number(trans[3][3]));
}

void MainWindow::slot_ShowRotation(Joint *j)
{
    glm::quat rot=j->GetRotation();
    ui->label_30->setText(QString::number(rot.w));
    ui->label_31->setText(QString::number(rot.x));
    ui->label_32->setText(QString::number(rot.y));
    ui->label_33->setText(QString::number(rot.z));


}
