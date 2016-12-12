#include "SideBySideRenderWindowsQt.h"

#include <QtSerialPort/QSerialPortInfo>
#include <QTextStream>
#include <QStringList>
#include <QDebug>
#include <QThread>
//#include <unistd.h>

#include <iostream>
using namespace std;

// Constructor

const double SideBySideRenderWindowsQt::translation1[3] = {0.0,65,0.0};
const double SideBySideRenderWindowsQt::translation2[3] = {0.0,69.803599,0.0};
const double SideBySideRenderWindowsQt::translation3[3] = {0.267949,91.428531};

SideBySideRenderWindowsQt::SideBySideRenderWindowsQt() 
{

    this->setupUi(this);
    count = 0;
    serialPort1 = new QSerialPort("Com3");
    //serialPort1 = new QSerialPort("/dev/ttyACM1");
    //serialPort1 = new QSerialPort("/dev/tty.usbmodem1412");
    serialPort1->setBaudRate(QSerialPort::Baud9600);
    serialPort1->open(QIODevice::ReadWrite);
    serialPort1->setDataBits(QSerialPort::Data8);
    serialPort1->setParity(QSerialPort::NoParity);
    serialPort1->setStopBits(QSerialPort::OneStop);
    serialPort1->setFlowControl(QSerialPort::NoFlowControl);
    connect(serialPort1, SIGNAL(readyRead()), this, SLOT(readData()));
    qw = 1;
    qx = 0;
    qy = 0;
    qz = 0;

    // Read stl
    for (int i=0; i<4; i++ ){
        reader[i] = vtkSmartPointer<vtkSTLReader>::New();
    }

    reader[0]->SetFileName("stl/Base_Joint.STL");
    reader[1]->SetFileName("stl/Joint1.STL");
    reader[2]->SetFileName("stl/Joint2.STL");
    reader[3]->SetFileName("stl/Joint3.STL");

    //Mapper
    for (int i=0; i<4; i++){
        mapper[i] = vtkSmartPointer<vtkPolyDataMapper>::New();
        mapper[i] -> SetInputConnection(reader[i]->GetOutputPort());
    }

    //Actor
    for (int i=0; i<4; i++){
        actor[i] = vtkSmartPointer<vtkActor>::New();
        actor[i] -> SetMapper(mapper[i]);
    }

    //Changing Colors
    actor[1]-> GetProperty()->SetColor(0.0,220./255,225./255);
    actor[3]-> GetProperty()->SetColor(0.0,220./255,225./255);

    //Base Axes
    baseAxes = vtkSmartPointer<vtkAxesActor>::New();
    // Set coordinate axes rendering
    baseAxes->SetTotalLength(40,40,40);

    //Transformations
    transform[0] = vtkSmartPointer<vtkTransform>::New();
    actor[0]->SetUserTransform(transform[0]);

    for (int i=1; i<4; i++){
        transform[i] = vtkSmartPointer<vtkTransform>::New();
        transform[i]->SetInput(transform[i-1]);
        actor[i]->SetUserTransform(transform[i]);
    }

    leftRenderer = vtkSmartPointer<vtkRenderer>::New();
    rightRenderer = vtkSmartPointer<vtkRenderer>::New();

    for (int i=0; i<4 ; i++){
        leftRenderer->AddActor(actor[i]);
    }

    leftRenderer->AddActor(baseAxes);
    leftRenderer->SetBackground(1.0, 1.0, 1.0);

    transform[2]-> Translate(translation2);
    transform[3]-> Translate(translation3);

    //double element00 = 1 - (2*(qy*qy)) - (2*(qz*qz));
    double element00 = (qw*qw) + (qx*qx) - (qy*qy) - (qz*qz);
    double element01 = (2 * qx * qy) - (2*qz*qw);
    double element02 = (2*qx*qz) + (2*qy*qw);
    double element03 = translation1[0];

    double element10 = (2*qx*qy) + (2*qz*qw);
    //double element11 = (1-(2*qx*qx)-(2*qz*qz));
    double element11 = (qw*qw) - (qx*qx) + (qy*qy) - (qz*qz);
    double element12 = (2*qy*qz) - (2*qx*qw);
    double element13 = translation1[1];

    double element20 = (2*qx*qz) - (2*qy*qw);
    double element21 = (2*qy*qz) + (2*qx*qw);
    //double element22 = 1 - (2*qx*qx) - (2*qy*qy);
    double element22 = (qw*qw) - (qx*qx) - (qy*qy) + (qz*qz);
    double element23 = translation1[2];

    double element30 = 0;
    double element31 = 0;
    double element32 = 0;
    double element33 = 1;

    matrix = vtkSmartPointer<vtkMatrix4x4>::New();
    matrix->SetElement(0,0,element00);
    matrix->SetElement(0,1,element01);
    matrix->SetElement(0,2,element02);
    matrix->SetElement(0,3,element03);

    matrix->SetElement(1,0,element10);
    matrix->SetElement(1,1,element11);
    matrix->SetElement(1,2,element12);
    matrix->SetElement(1,3,element13);

    matrix->SetElement(2,0,element20);
    matrix->SetElement(2,1,element21);
    matrix->SetElement(2,2,element22);
    matrix->SetElement(2,3,element23);

    matrix->SetElement(3,0,element30);
    matrix->SetElement(3,1,element31);
    matrix->SetElement(3,2,element32);
    matrix->SetElement(3,3,element33);

    transform[1]->SetMatrix(matrix);

    // VTK/Qt wedded
    this->qvtkWidgetLeft->GetRenderWindow()->AddRenderer(leftRenderer);
    this->qvtkWidgetRight->GetRenderWindow()->AddRenderer(rightRenderer);

    // Set up action signals and slots
    // connect(this->actionExit, SIGNAL(triggered()), this, SLOT(slotExit()));
}

void SideBySideRenderWindowsQt::updateModel(){

    double element00 = (qw*qw) + (qx*qx) - (qy*qy) - (qz*qz);
    double element01 = (2 * qx * qy) - (2*qz*qw);
    double element02 = (2*qx*qz) + (2*qy*qw);
    double element03 = translation1[0];

    double element10 = (2*qx*qy) + (2*qz*qw);
    double element11 = (qw*qw) - (qx*qx) + (qy*qy) - (qz*qz);
    double element12 = (2*qy*qz) - (2*qx*qw);
    double element13 = translation1[1];

    double element20 = (2*qx*qz) - (2*qy*qw);
    double element21 = (2*qy*qz) + (2*qx*qw);
    double element22 = (qw*qw) - (qx*qx) - (qy*qy) + (qz*qz);
    double element23 = translation1[2];

    double element30 = 0;
    double element31 = 0;
    double element32 = 0;
    double element33 = 1;

    vtkSmartPointer<vtkMatrix4x4> matrix = vtkSmartPointer<vtkMatrix4x4>::New();
    matrix->SetElement(0,0,element00);
    matrix->SetElement(0,1,element01);
    matrix->SetElement(0,2,element02);
    matrix->SetElement(0,3,element03);

    matrix->SetElement(1,0,element10);
    matrix->SetElement(1,1,element11);
    matrix->SetElement(1,2,element12);
    matrix->SetElement(1,3,element13);

    matrix->SetElement(2,0,element20);
    matrix->SetElement(2,1,element21);
    matrix->SetElement(2,2,element22);
    matrix->SetElement(2,3,element23);

    matrix->SetElement(3,0,element30);
    matrix->SetElement(3,1,element31);
    matrix->SetElement(3,2,element32);
    matrix->SetElement(3,3,element33);
    transform[1]->Identity();
    transform[1]->SetMatrix(matrix);
    this->qvtkWidgetLeft->GetRenderWindow()->Render();
    //this->qvtkWidgetLeft->GetRenderWindow()->Modified();
    // this->qvtkWidgetRight->GetRenderWindow()->AddRenderer(rightRenderer);

}

void SideBySideRenderWindowsQt::readData()
{
    QStringList receivedBufferSplit = receivedBuffer.split(",");
    if(receivedBufferSplit.length() < 10){
        receivedData = serialPort1->readAll();
        receivedBuffer += QString :: fromStdString(receivedData.toStdString());
    }else{
        for(int i = 1 ; i < receivedBufferSplit.length()-2;i++){
            if(receivedBufferSplit[i-1]=="qw" && receivedBufferSplit[i+1]=="qx"){
                qw = receivedBufferSplit[i].toDouble();
            }
            if(receivedBufferSplit[i-1]=="qx" && receivedBufferSplit[i+1]=="qy"){
                qx = receivedBufferSplit[i].toDouble();
            }
            if(receivedBufferSplit[i-1]=="qy" && receivedBufferSplit[i+1]=="qz"){
                qy = receivedBufferSplit[i].toDouble();
            }
            if(receivedBufferSplit[i-1]=="qz" && receivedBufferSplit[i+1]=="qw"){
                qz = receivedBufferSplit[i].toDouble();
            }
            qDebug()<<"received"<<receivedBufferSplit;
            qDebug()<<qw;
            qDebug()<<qx;
            qDebug()<<qy;
            qDebug()<<qz;
            receivedBuffer = "";
        }
        updateModel();
    }
}


void SideBySideRenderWindowsQt::slotExit() 
{
    qApp->exit();
}

