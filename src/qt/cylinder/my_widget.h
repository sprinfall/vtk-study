#ifndef MY_WIDGET_H_
#define MY_WIDGET_H_

#include <QWidget>

#include <vtkActor.h>
#include <vtkOpenGLRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>

#include <QVTKOpenGLWidget.h>

class MyWidget : public QVTKOpenGLWidget {
  Q_OBJECT

public:
  explicit MyWidget(QWidget* parent = nullptr);

  ~MyWidget();

private:
  vtkSmartPointer<vtkOpenGLRenderWindow> render_window_;
  vtkSmartPointer<vtkRenderer> render_;
  vtkSmartPointer<vtkActor> actor;
};

#endif  // MY_WIDGET_H_