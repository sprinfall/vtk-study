//
// This example shows how to add an observer to a C++ program. It extends
// the Cone1.cxx C++ example (see that example for information on
// the basic setup).
//
// VTK uses a command/observer design pattern. That is, observers watch for
// particular events that any vtkObject (or subclass) may invoke on
// itself. For example, the vtkRenderer invokes a "StartEvent" as it begins
// to render. Here we add an observer that invokes a command when this event
// is observed.
//

#include "vtkConeSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkCommand.h"
#include "vtkCamera.h"
#include "vtkActor.h"
#include "vtkRenderer.h"

// Callback for the interaction
class vtkMyCallback : public vtkCommand
{
public:
  static vtkMyCallback *New()
  {
    return new vtkMyCallback;
  }

  void Execute(vtkObject *caller, unsigned long, void *) VTK_OVERRIDE
  {
      vtkRenderer *renderer = reinterpret_cast<vtkRenderer *>(caller);
      cout << renderer->GetActiveCamera()->GetPosition()[0] << " "
           << renderer->GetActiveCamera()->GetPosition()[1] << " "
           << renderer->GetActiveCamera()->GetPosition()[2] << "\n";
  }
};

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
  renderer->ResetCamera();

  vtkRenderWindow *renderWindow = vtkRenderWindow::New();
  renderWindow->AddRenderer(renderer);
  renderWindow->SetSize(300, 300);

  // Here is where we setup the observer, we do a new and renderer will
  // eventually free the observer.
  vtkMyCallback *callback = vtkMyCallback::New();
  renderer->AddObserver(vtkCommand::StartEvent, callback);
  callback->Delete();

  //
  // now we loop over 360 degrees and render the cone each time
  //
  for (int i = 0; i < 360; ++i)
  {
    // render the image
    renderWindow->Render();
    // rotate the active camera by one degree
    renderer->GetActiveCamera()->Azimuth(1);
  }

  cone->Delete();
  coneMapper->Delete();
  coneActor->Delete();
  renderer->Delete();
  renderWindow->Delete();

  return 0;
}
