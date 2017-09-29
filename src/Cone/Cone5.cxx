//
// This example introduces the concepts of interaction into the
// C++ environment. A different interaction style (than
// the default) is defined.
//

#include "vtkConeSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkCamera.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkInteractorStyleTrackballCamera.h"

int main()
{
  vtkConeSource *cone = vtkConeSource::New();
  cone->SetHeight(3.0);
  cone->SetRadius(1.0);
  cone->SetResolution(10);

  vtkPolyDataMapper *coneMapper = vtkPolyDataMapper::New();
  coneMapper->SetInputConnection(cone->GetOutputPort());

  vtkActor *coneActor = vtkActor::New();
  coneActor->SetMapper(coneMapper);

  vtkRenderer *renderer = vtkRenderer::New();
  renderer->AddActor(coneActor);
  renderer->SetBackground(0.1, 0.2, 0.4);

  vtkRenderWindow *renderWindow = vtkRenderWindow::New();
  renderWindow->AddRenderer(renderer);
  renderWindow->SetSize(300, 300);

  //
  // The vtkRenderWindowInteractor class watches for events (e.g., keypress,
  // mouse) in the vtkRenderWindow. These events are translated into
  // event invocations that VTK understands (see VTK/Common/vtkCommand.h
  // for all events that VTK processes). Then observers of these VTK
  // events can process them as appropriate.
  //
  vtkRenderWindowInteractor *renderWindowInteractor =
    vtkRenderWindowInteractor::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  //
  // By default the vtkRenderWindowInteractor instantiates an instance
  // of vtkInteractorStyle. vtkInteractorStyle translates a set of events
  // it observes into operations on the camera, actors, and/or properties
  // in the vtkRenderWindow associated with the vtkRenderWinodwInteractor.
  // Here we specify a particular interactor style.
  //
  vtkInteractorStyleTrackballCamera *style =
    vtkInteractorStyleTrackballCamera::New();
  renderWindowInteractor->SetInteractorStyle(style);

  //
  // Unlike the previous scripts where we performed some operations and then
  // exited, here we leave an event loop running. The user can use the mouse
  // and keyboard to perform the operations on the scene according to the
  // current interaction style. When the user presses the "e" key, by default
  // an ExitEvent is invoked by the vtkRenderWindowInteractor which is caught
  // and drops out of the event loop (triggered by the Start() method that
  // follows.
  //
  renderWindowInteractor->Initialize();
  renderWindowInteractor->Start();

  //
  // Final note: recall that an observers can watch for particular events and
  // take appropriate action. Pressing "u" in the render window causes the
  // vtkRenderWindowInteractor to invoke a UserEvent. This can be caught to
  // popup a GUI, etc. So the Tcl Cone5.tcl example for an idea of how this
  // works.

  //
  // Free up any objects we created. All instances in VTK are deleted by
  // using the Delete() method.
  //
  cone->Delete();
  coneMapper->Delete();
  coneActor->Delete();
  renderer->Delete();
  renderWindow->Delete();
  renderWindowInteractor->Delete();
  style->Delete();

  return 0;
}
