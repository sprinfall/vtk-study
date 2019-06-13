// This example introduces the concepts of interaction into the
// C++ environment. A different interaction style (than
// the default) is defined.

#include "vtkActor.h"
#include "vtkCamera.h"
#include "vtkConeSource.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"

int main() {
  auto cone = vtkConeSource::New();
  cone->SetHeight(3.0);
  cone->SetRadius(1.0);
  cone->SetResolution(10);

  auto mapper = vtkPolyDataMapper::New();
  mapper->SetInputConnection(cone->GetOutputPort());

  auto actor = vtkActor::New();
  actor->SetMapper(mapper);

  auto renderer = vtkRenderer::New();
  renderer->AddActor(actor);
  renderer->SetBackground(0.1, 0.2, 0.4);

  auto render_window = vtkRenderWindow::New();
  render_window->AddRenderer(renderer);
  render_window->SetSize(300, 300);

  // The vtkRenderWindowInteractor class watches for events (e.g., keypress,
  // mouse) in the vtkRenderWindow. These events are translated into
  // event invocations that VTK understands (see VTK/Common/vtkCommand.h
  // for all events that VTK processes). Then observers of these VTK
  // events can process them as appropriate.

  auto interactor = vtkRenderWindowInteractor::New();
  interactor->SetRenderWindow(render_window);

  // By default the vtkRenderWindowInteractor instantiates an instance
  // of vtkInteractorStyle. vtkInteractorStyle translates a set of events
  // it observes into operations on the camera, actors, and/or properties
  // in the vtkRenderWindow associated with the vtkRenderWinodwInteractor.
  // Here we specify a particular interactor style.

  auto style = vtkInteractorStyleTrackballCamera::New();
  interactor->SetInteractorStyle(style);

  // Unlike the previous scripts where we performed some operations and then
  // exited, here we leave an event loop running. The user can use the mouse
  // and keyboard to perform the operations on the scene according to the
  // current interaction style. When the user presses the "e" key, by default
  // an ExitEvent is invoked by the vtkRenderWindowInteractor which is caught
  // and drops out of the event loop (triggered by the Start() method that
  // follows.

  interactor->Initialize();
  interactor->Start();

  // Final note: recall that an observers can watch for particular events and
  // take appropriate action. Pressing "u" in the render window causes the
  // vtkRenderWindowInteractor to invoke a UserEvent. This can be caught to
  // popup a GUI, etc. So the Tcl Cone5.tcl example for an idea of how this
  // works.

  // Free up any objects we created. All instances in VTK are deleted by
  // using the Delete() method.

  cone->Delete();
  mapper->Delete();
  actor->Delete();
  renderer->Delete();
  render_window->Delete();
  interactor->Delete();
  style->Delete();

  return 0;
}
