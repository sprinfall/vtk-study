//
// This example demonstrates how to use multiple renderers within a
// render window. It is a variation of the Cone.cxx example. Please
// refer to that example for additional documentation.
//

#include "vtkConeSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkCamera.h"
#include "vtkActor.h"
#include "vtkRenderer.h"

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

  //
  // Create two renderers and assign actors to them. A renderer renders into
  // a viewport within the vtkRenderWindow. It is part or all of a window on
  // the screen and it is responsible for drawing the actors it has.  We also
  // set the background color here. In this example we are adding the same
  // actor to two different renderers; it is okay to add different actors to
  // different renderers as well.
  //
  vtkRenderer *renderer1 = vtkRenderer::New();
  renderer1->AddActor(coneActor);
  renderer1->SetBackground(0.1, 0.2, 0.4);
  renderer1->SetViewport(0.0, 0.0, 0.5, 1.0);

  vtkRenderer *renderer2 = vtkRenderer::New();
  renderer2->AddActor(coneActor);
  renderer2->SetBackground(0.2, 0.3, 0.5);
  renderer2->SetViewport(0.5, 0.0, 1.0, 1.0);

  vtkRenderWindow *renderWindow = vtkRenderWindow::New();
  renderWindow->AddRenderer(renderer1);
  renderWindow->AddRenderer(renderer2);
  renderWindow->SetSize(600, 300);

  //
  // Make one view 90 degrees from other.
  //
  renderer1->ResetCamera();
  renderer1->GetActiveCamera()->Azimuth(90);

  //
  // Now we loop over 360 degrees and render the cone each time.
  //
  for (int i = 0; i < 360; ++i)
  {
    // render the image
    renderWindow->Render();
    // rotate the active camera by one degree
    renderer1->GetActiveCamera()->Azimuth(1);
    renderer2->GetActiveCamera()->Azimuth(1);
  }

  cone->Delete();
  coneMapper->Delete();
  coneActor->Delete();
  renderer1->Delete();
  renderer2->Delete();
  renderWindow->Delete();

  return 0;
}
