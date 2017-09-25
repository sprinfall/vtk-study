// This simple example shows how to do basic rendering and pipeline
// creation.

#include "vtkCylinderSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkProperty.h"
#include "vtkCamera.h"

int main()
{
  // This creates a polygonal cylinder model with eight circumferential facets.
  // cylinder: 圆柱，圆筒状
  vtkCylinderSource *cylinder = vtkCylinderSource::New();
  cylinder->SetResolution(8);  // 侧面有八面 (facets)

  // The mapper is responsible for pushing the geometry into the graphics
  // library. It may also do color mapping, if scalars or other attributes
  // are defined.
  //
  vtkPolyDataMapper *cylinderMapper = vtkPolyDataMapper::New();
  cylinderMapper->SetInputConnection(cylinder->GetOutputPort());

  // The actor is a grouping mechanism: besides the geometry (mapper), it
  // also has a property, transformation matrix, and/or texture map.
  // Here we set its color and rotate it -22.5 degrees.
  vtkActor *cylinderActor = vtkActor::New();
  cylinderActor->SetMapper(cylinderMapper);
  cylinderActor->GetProperty()->SetColor(1.0000, 0.3882, 0.2784);
  cylinderActor->RotateX(30.0);  // ?
  cylinderActor->RotateY(45.0);  // ?

  // Create the graphics structure. The renderer renders into the
  // render window. The render window interactor captures mouse events
  // and will perform appropriate camera or actor manipulation
  // depending on the nature of the events.
  //
  vtkRenderer *renderer = vtkRenderer::New();
  vtkRenderWindow *renderWin = vtkRenderWindow::New();
  renderWin->AddRenderer(renderer);
  vtkRenderWindowInteractor *renderWinInteractor = vtkRenderWindowInteractor::New();
  renderWinInteractor->SetRenderWindow(renderWin);

  // Add the actors to the renderer, set the background and size
  //
  renderer->AddActor(cylinderActor);
  renderer->SetBackground(0.1, 0.2, 0.4);
  renderWin->SetSize(400, 400);

  // We'll zoom in a little by accessing the camera and invoking a "Zoom"
  // method on it.
  renderer->ResetCamera();
  renderer->GetActiveCamera()->Zoom(1.5);
  renderWin->Render();

  // This starts the event loop and as a side effect causes an initial render.
  renderWinInteractor->Start();

  // Exiting from here, we have to delete all the instances that
  // have been created.
  // 如果用 vtkSmartPointer，会简单很多。
  cylinder->Delete();
  cylinderMapper->Delete();
  cylinderActor->Delete();
  renderer->Delete();
  renderWin->Delete();
  renderWinInteractor->Delete();

  return 0;
}
