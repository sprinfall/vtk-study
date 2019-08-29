#ifndef MY_PANEL_H_
#define MY_PANEL_H_

#include "wx/panel.h"

#include <vtkActor.h>
#include <vtkOpenGLRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>

class MyPanel : public wxPanel {
  DECLARE_EVENT_TABLE()

public:
  explicit MyPanel(wxWindow* parent = nullptr);

  ~MyPanel() = default;

protected:
  void OnSize(wxSizeEvent& evt);
  void OnPaint(wxPaintEvent& evt);

private:
  vtkSmartPointer<vtkRenderWindow> render_window_;
  vtkSmartPointer<vtkRenderer> render_;
  vtkSmartPointer<vtkActor> actor;
  vtkSmartPointer<vtkRenderWindowInteractor> interactor_;
};

#endif  // MY_PANEL_H_