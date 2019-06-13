// This example creates a polygonal model of a cone, and then renders it to
// the screen. It will rotate the cone 360 degrees and then exit. The basic
// setup of source -> mapper -> actor -> renderer -> renderwindow is
// typical of most VTK programs.

// polygonal, 多边形的
// cone, 圆锥体

#include "vtkActor.h"
#include "vtkCamera.h"
#include "vtkConeSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkRenderer.h"

int main() {
  // Firstly we create an instance of vtkConeSource and set some of its
  // properties. The instance of vtkConeSource "cone" is part of a
  // visualization pipeline (it is a source process object); it produces data
  // (output type is vtkPolyData) which other filters may process.

  auto cone = vtkConeSource::New();
  cone->SetHeight(3.0);
  cone->SetRadius(1.0);
  cone->SetResolution(10);

  // In this example we terminate the pipeline with a mapper process object.
  // (Intermediate filters such as vtkShrinkPolyData could be inserted in
  // between the source and the mapper.)  We create an instance of
  // vtkPolyDataMapper to map the polygonal data into graphics primitives. We
  // connect the output of the cone source to the input of this mapper.

  auto mapper = vtkPolyDataMapper::New();
  mapper->SetInputConnection(cone->GetOutputPort());

  // Create an actor to represent the cone. The actor orchestrates rendering
  // of the mapper's graphics primitives. An actor also refers to properties
  // via a vtkProperty instance, and includes an internal transformation
  // matrix. We set this actor's mapper to be mapper which we created
  // above.

  auto actor = vtkActor::New();
  actor->SetMapper(mapper);

  // Create the Renderer and assign actors to it. A renderer is like a
  // viewport. It is part or all of a window on the screen and it is
  // responsible for drawing the actors it has. We also set the background
  // color here.

  auto renderer = vtkRenderer::New();
  renderer->AddActor(actor);
  renderer->SetBackground(0.1, 0.2, 0.4);

  // Finally we create the render window which will show up on the screen.
  // We put our renderer into the render window using AddRenderer. We also
  // set the size to be 300 pixels by 300.

  auto render_window = vtkRenderWindow::New();
  render_window->AddRenderer(renderer);
  render_window->SetSize(300, 300);

  // Now we loop over 360 degrees and render the cone each time.

  for (int i = 0; i < 360; ++i) {
    // Render the image.
    render_window->Render();
    // Rotate the active camera by one degree.
    renderer->GetActiveCamera()->Azimuth(1);
  }

  // Free up any objects we created. All instances in VTK are deleted by
  // using the Delete() method.

  cone->Delete();
  mapper->Delete();
  actor->Delete();
  renderer->Delete();
  render_window->Delete();

  return 0;
}
