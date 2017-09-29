//
// This example demonstrates the creation of multiple actors and the
// manipulation of their properties and transformations.
//

#include "vtkConeSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkCamera.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkProperty.h"

int main()
{
  vtkConeSource *cone = vtkConeSource::New();
  cone->SetHeight(3.0);
  cone->SetRadius(1.0);
  cone->SetResolution(10);

  vtkPolyDataMapper *coneMapper = vtkPolyDataMapper::New();
  coneMapper->SetInputConnection(cone->GetOutputPort());

  //
  // Create an actor to represent the first cone. The actor's properties are
  // modified to give it different surface properties. By default, an actor
  // is create with a property so the GetProperty() method can be used.
  //
  vtkActor *coneActor = vtkActor::New();
  coneActor->SetMapper(coneMapper);
  coneActor->GetProperty()->SetColor(0.2, 0.63, 0.79);
  coneActor->GetProperty()->SetDiffuse(0.7);
  coneActor->GetProperty()->SetSpecular(0.4);
  coneActor->GetProperty()->SetSpecularPower(20);

  //
  // Create a property and directly manipulate it. Assign it to the
  // second actor.
  //
  vtkProperty *property = vtkProperty::New();
  property->SetColor(1.0, 0.3882, 0.2784);
  property->SetDiffuse(0.7);
  property->SetSpecular(0.4);
  property->SetSpecularPower(20);

  //
  // Create a second actor and a property. The property is directly
  // manipulated and then assigned to the actor. In this way, a single
  // property can be shared among many actors. Note also that we use the
  // same mapper as the first actor did. This way we avoid duplicating
  // geometry, which may save lots of memory if the geometry is large.
  //
  vtkActor *coneActor2 = vtkActor::New();
  coneActor2->SetMapper(coneMapper);
  coneActor2->GetProperty()->SetColor(0.2, 0.63, 0.79);
  coneActor2->SetProperty(property);
  coneActor2->SetPosition(0, 2, 0);

  //
  // Create the Renderer and assign actors to it. A renderer is like a
  // viewport. It is part or all of a window on the screen and it is
  // responsible for drawing the actors it has.  We also set the background
  // color here.
  //
  vtkRenderer *renderer = vtkRenderer::New();
  renderer->AddActor(coneActor);
  renderer->AddActor(coneActor2);
  renderer->SetBackground(0.1, 0.2, 0.4);

  //
  // Finally we create the render window which will show up on the screen.
  // We put our renderer into the render window using AddRenderer. We also
  // set the size to be 300 pixels by 300.
  //
  vtkRenderWindow *renderWindow = vtkRenderWindow::New();
  renderWindow->AddRenderer(renderer);
  renderWindow->SetSize(300, 300);

  //
  // Now we loop over 360 degrees and render the cone each time.
  //
  for (int i = 0; i < 360; ++i)
  {
    // render the image
    renderWindow->Render();
    // rotate the active camera by one degree
    renderer->GetActiveCamera()->Azimuth(1);
  }

  //
  // Free up any objects we created. All instances in VTK are deleted by
  // using the Delete() method.
  //
  cone->Delete();
  coneMapper->Delete();
  coneActor->Delete();
  property->Delete();
  coneActor2->Delete();
  renderer->Delete();
  renderWindow->Delete();

  return 0;
}
