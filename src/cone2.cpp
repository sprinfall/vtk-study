// This example shows how to add an observer to a C++ program.
//
// VTK uses a command/observer design pattern. That is, observers watch for
// particular events that any vtkObject (or subclass) may invoke on
// itself. For example, the vtkRenderer invokes a "StartEvent" as it begins
// to render. Here we add an observer that invokes a command when this event
// is observed.

#include "vtkActor.h"
#include "vtkCamera.h"
#include "vtkCommand.h"
#include "vtkConeSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkRenderer.h"

class MyCallback : public vtkCommand {
public:
  static MyCallback* New() {
    return new MyCallback;
  }

  void Execute(vtkObject* caller, unsigned long, void*) override {
    // Consider to use vtkRenderer::SafeDownCast instead.
    vtkRenderer* renderer = reinterpret_cast<vtkRenderer*>(caller);
    cout << renderer->GetActiveCamera()->GetPosition()[0] << " "
         << renderer->GetActiveCamera()->GetPosition()[1] << " "
         << renderer->GetActiveCamera()->GetPosition()[2] << "\n";
  }
};

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
  renderer->ResetCamera();

  auto render_window = vtkRenderWindow::New();
  render_window->AddRenderer(renderer);
  render_window->SetSize(300, 300);

  // Here is where we setup the observer, we do a new and renderer will
  // eventually free the observer.
  auto callback = MyCallback::New();
  renderer->AddObserver(vtkCommand::StartEvent, callback);
  callback->Delete();

  for (int i = 0; i < 360; ++i) {
    render_window->Render();
    renderer->GetActiveCamera()->Azimuth(1);
  }

  cone->Delete();
  mapper->Delete();
  actor->Delete();
  renderer->Delete();
  render_window->Delete();

  return 0;
}
