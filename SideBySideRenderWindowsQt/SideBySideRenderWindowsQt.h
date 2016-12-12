#ifndef SideBySideRenderWindowsQt_H
#define SideBySideRenderWindowsQt_H

#include <vtkSmartPointer.h>
#include <vtkDataObjectToTable.h>
#include <vtkElevationFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkQtTableView.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkSphereSource.h>
#include <vtkCubeSource.h>
#include <vtkSmartPointer.h>
#include <vtkSTLReader.h>
#include <vtkAxesActor.h>
#include <vtkProperty.h>
#include <vtkTransform.h>
#include <vtkMatrix4x4.h>
#include <QMainWindow>
#include <QtSerialPort/QSerialPort>

#include "ui_SideBySideRenderWindowsQt.h"

class SideBySideRenderWindowsQt : public QMainWindow, private Ui::SideBySideRenderWindowsQt
{
  Q_OBJECT
public:

  // Constructor/Destructor
  SideBySideRenderWindowsQt(); 
  ~SideBySideRenderWindowsQt() {};
  int count;
  double qw;
  double qx;
  double qy;
  double qz;
  static const double translation1[3];
  static const double translation2[3];
  static const double translation3[3];

  vtkSmartPointer<vtkSTLReader> reader [4];
  vtkSmartPointer<vtkPolyDataMapper> mapper [4];
  vtkSmartPointer<vtkActor> actor [4];
  vtkSmartPointer<vtkAxesActor> baseAxes;
  vtkSmartPointer<vtkTransform> transform[4];
  vtkSmartPointer<vtkMatrix4x4> matrix;

  //Left Renderer
  vtkSmartPointer<vtkRenderer> leftRenderer;
  //Right Renderer
  vtkSmartPointer<vtkRenderer> rightRenderer;

private:
  QSerialPort *serialPort1;
  QByteArray receivedData;
  QString receivedBuffer;
public slots:

  virtual void slotExit();
  virtual void readData();
  virtual void updateModel();
};

#endif
