#include "vtk_widget.h"

#include <QDebug>

#include <vtkCylinderSource.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkInteractorStyleMultiTouchCamera.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindowInteractor.h>

VtkWidget::VtkWidget(QWidget* parent)
    : QVTKOpenGLWidget(parent),
      render_window_(vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New()),
      render_(vtkSmartPointer<vtkRenderer>::New()) {

  SetRenderWindow(render_window_);
  GetRenderWindow()->AddRenderer(render_);

  auto cylinder = vtkSmartPointer<vtkCylinderSource>::New();
  cylinder->SetHeight(3.0);
  cylinder->SetRadius(1.0);
  cylinder->SetResolution(10);

  auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(cylinder->GetOutputPort());

  auto actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  render_->AddActor(actor);

  // Set interactor style.
  // vtkInteractorStyleMultiTouchCamera could also be a good choice.
  //auto style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
  auto style = vtkSmartPointer<vtkInteractorStyleMultiTouchCamera>::New();
  render_window_->GetInteractor()->SetInteractorStyle(style);
}

VtkWidget::~VtkWidget() {
}
