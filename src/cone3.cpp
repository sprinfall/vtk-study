// This example demonstrates how to use multiple renderers within a
// render window.

#include "vtkActor.h"
#include "vtkCamera.h"
#include "vtkConeSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
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

  // Create two renderers and assign actors to them. A renderer renders into
  // a viewport within the vtkRenderWindow. It is part or all of a window on
  // the screen and it is responsible for drawing the actors it has.  We also
  // set the background color here. In this example we are adding the same
  // actor to two different renderers; it is okay to add different actors to
  // different renderers as well.

  auto renderer1 = vtkRenderer::New();
  renderer1->AddActor(actor);
  renderer1->SetBackground(0.1, 0.2, 0.4);
  renderer1->SetViewport(0.0, 0.0, 0.5, 1.0);

  auto renderer2 = vtkRenderer::New();
  renderer2->AddActor(actor);
  renderer2->SetBackground(0.2, 0.3, 0.5);
  renderer2->SetViewport(0.5, 0.0, 1.0, 1.0);

  auto render_window = vtkRenderWindow::New();
  render_window->AddRenderer(renderer1);
  render_window->AddRenderer(renderer2);
  render_window->SetSize(600, 300);

  // Make one view 90 degrees from other.

  renderer1->ResetCamera();
  renderer1->GetActiveCamera()->Azimuth(90);

  // Now we loop over 360 degrees and render the cone each time.

  for (int i = 0; i < 360; ++i) {
    // Render the image.
    render_window->Render();
    // Rotate the active camera by one degree.
    renderer1->GetActiveCamera()->Azimuth(1);
    renderer2->GetActiveCamera()->Azimuth(1);
  }

  cone->Delete();
  mapper->Delete();
  actor->Delete();
  renderer1->Delete();
  renderer2->Delete();
  render_window->Delete();

  return 0;
}
