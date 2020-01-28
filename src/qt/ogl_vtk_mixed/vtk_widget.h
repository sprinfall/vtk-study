#ifndef VTK_WIDGET_H_
#define VTK_WIDGET_H_

#include <QWidget>

#include <vtkActor.h>
#include <vtkOpenGLRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>

#include <QVTKOpenGLWidget.h>

class VtkWidget : public QVTKOpenGLWidget {
  Q_OBJECT

public:
  explicit VtkWidget(QWidget* parent = nullptr);

  ~VtkWidget();

private:
  vtkSmartPointer<vtkOpenGLRenderWindow> render_window_;
  vtkSmartPointer<vtkRenderer> render_;
  vtkSmartPointer<vtkActor> actor;  // TODO
};

#endif  // VTK_WIDGET_H_