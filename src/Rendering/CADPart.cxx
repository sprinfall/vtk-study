// This simple example shows how to do basic rendering and pipeline
// creation. It also demonstrates the use of the LODActor.

#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkSTLReader.h"
#include "vtkLODActor.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkProperty.h"
#include "vtkCamera.h"

int main()
{
  vtkSmartPointer<vtkSTLReader> part = vtkSmartPointer<vtkSTLReader>::New();

  const char *vtkDataRoot = std::getenv("VTK_DATA_ROOT");
  if (vtkDataRoot == NULL) {
    std::cerr << "Cannot read env VTK_DATA_ROOT." << std::endl;
    return 1;
  }

  std::string filePath(vtkDataRoot);
  filePath += "/Data/42400-IDGH.stl";
  part->SetFileName(filePath.c_str());

  vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(part->GetOutputPort());

  // The LOD actor is a special type of actor.It will change appearance in
  // order to render faster.At the highest resolution, it renders everything
  // just like an actor.The middle level is a point cloud, and the lowest
  // level is a simple bounding box.
  //
  vtkSmartPointer<vtkLODActor> partActor = vtkSmartPointer<vtkLODActor>::New();
  partActor->SetMapper(mapper);
  partActor->GetProperty()->SetColor(0.3, 0.3, 0.3);
  partActor->RotateX(30.0);
  partActor->RotateY(-45.0);

  // Create the graphics structure. The renderer renders into the
  // render window. The render window interactor captures mouse events
  // and will perform appropriate camera or actor manipulation
  // depending on the nature of the events.
  //
  vtkRenderer *renderer = vtkRenderer::New();
  vtkRenderWindow *renderWindow = vtkRenderWindow::New();
  renderWindow->AddRenderer(renderer);

  vtkRenderWindowInteractor *renderWinInteractor = vtkRenderWindowInteractor::New();
  renderWinInteractor->SetRenderWindow(renderWindow);

  // Add the actors to the renderer, set the background and size
  //
  renderer->AddActor(partActor);
  renderer->SetBackground(0.1, 0.2, 0.4);
  renderWindow->SetSize(400, 400);

  // We'll zoom in a little by accessing the camera and invoking a "Zoom"
  // method on it.
  renderer->ResetCamera();
  renderer->GetActiveCamera()->Zoom(1.5);
  renderWindow->Render();

  // This starts the event loop and as a side effect causes an initial render.
  renderWinInteractor->Start();

  // Exiting from here, we have to delete all the instances that
  // have been created.
  renderer->Delete();
  renderWindow->Delete();
  renderWinInteractor->Delete();

  return 0;
}
