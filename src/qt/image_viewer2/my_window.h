#ifndef MY_WINDOW_H_
#define MY_WINDOW_H_

#include <QMainWindow>

#include "vtkSmartPointer.h"

class vtkImageViewer2;
class vtkRenderer;
class QVTKOpenGLNativeWidget;

class MyWindow : public QMainWindow {
  Q_OBJECT

public:
  MyWindow();

private slots:
  void onOpenSlot();

private:
  QVTKOpenGLNativeWidget* widget_;
  vtkSmartPointer<vtkImageViewer2> image_viewer_;
  vtkSmartPointer<vtkRenderer> renderer_;
};

#endif  // MY_WINDOW_H_
