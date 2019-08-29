#include "my_panel.h"

#include <vtkCylinderSource.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkInteractorStyleMultiTouchCamera.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindowInteractor.h>

BEGIN_EVENT_TABLE(MyPanel, wxPanel)
EVT_SIZE(MyPanel::OnSize)
EVT_PAINT(MyPanel::OnPaint)
END_EVENT_TABLE()

MyPanel::MyPanel(wxWindow* parent)
    : wxPanel(parent, wxID_ANY),
      render_window_(vtkSmartPointer<vtkRenderWindow>::New()),
      render_(vtkSmartPointer<vtkRenderer>::New()),
      interactor_(vtkSmartPointer<vtkRenderWindowInteractor>::New()) {
  render_window_->SetParentId(GetHWND());
  render_window_->AddRenderer(render_);

  auto cylinder = vtkSmartPointer<vtkCylinderSource>::New();
  cylinder->SetHeight(3.0);
  cylinder->SetRadius(1.0);
  cylinder->SetResolution(10);

  auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(cylinder->GetOutputPort());

  auto actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  render_->AddActor(actor);

  auto style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
  interactor_->SetInteractorStyle(style);
  render_window_->SetInteractor(interactor_);
}

void MyPanel::OnSize(wxSizeEvent& evt) {
  wxSize size = evt.GetSize();
  if (size.x < 10) {
    evt.Skip();
    return;
  }

  render_window_->SetSize(size.x, size.y);
}

void MyPanel::OnPaint(wxPaintEvent& evt) {
  render_window_->Render();
}
