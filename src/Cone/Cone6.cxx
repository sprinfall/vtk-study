//
// This example introduces 3D widgets. 3D widgets take advantage of the
// event/observer design pattern introduced previously. They typically
// have a particular representation in the scene which can be interactively
// selected and manipulated using the mouse and keyboard. As the widgets
// are manipulated, they in turn invoke events such as StartInteractionEvent,
// InteractionEvent, and EndInteractionEvent which can be used to manipulate
// the scene that the widget is embedded in. 3D widgets work in the context
// of the event loop which was set up in the previous example.
//
// Note: there are more 3D widget examples in VTK/Examples/GUI/.
//

#include "vtkConeSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkCamera.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkCommand.h"
#include "vtkBoxWidget.h"
#include "vtkTransform.h"
#include "vtkInteractorStyleTrackballCamera.h"

//
// Similar to Cone2.cxx, we define a callback for interaction.
//
class vtkMyCallback : public vtkCommand
{
public:
  static vtkMyCallback *New()
  {
    return new vtkMyCallback;
  }

  void Execute(vtkObject *caller, unsigned long, void*) VTK_OVERRIDE
  {
    vtkTransform *t = vtkTransform::New();
    vtkBoxWidget *widget = reinterpret_cast<vtkBoxWidget*>(caller);
    widget->GetTransform(t);
    widget->GetProp3D()->SetUserTransform(t);
    t->Delete();
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

  vtkRenderWindow *renderWindow = vtkRenderWindow::New();
  renderWindow->AddRenderer(renderer);
  renderWindow->SetSize(300, 300);

  vtkRenderWindowInteractor *renderWindowInteractor
    = vtkRenderWindowInteractor::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);

  vtkInteractorStyleTrackballCamera *style =
    vtkInteractorStyleTrackballCamera::New();
  renderWindowInteractor->SetInteractorStyle(style);

  //
  // Here we use a vtkBoxWidget to transform the underlying coneActor (by
  // manipulating its transformation matrix). Many other types of widgets
  // are available for use, see the documentation for more details.
  //
  // The SetInteractor method is how 3D widgets are associated with the render
  // window interactor. Internally, SetInteractor sets up a bunch of callbacks
  // using the Command/Observer mechanism (AddObserver()). The place factor
  // controls the initial size of the widget with respect to the bounding box
  // of the input to the widget.
  //
  vtkBoxWidget *boxWidget = vtkBoxWidget::New();
  boxWidget->SetInteractor(renderWindowInteractor);
  boxWidget->SetPlaceFactor(1.25);

  //
  // Place the interactor initially. The input to a 3D widget is used to
  // initially position and scale the widget. The EndInteractionEvent is
  // observed which invokes the SelectPolygons callback.
  //
  boxWidget->SetProp3D(coneActor);
  boxWidget->PlaceWidget();
  vtkMyCallback *callback = vtkMyCallback::New();
  boxWidget->AddObserver(vtkCommand::InteractionEvent, callback);

  //
  // Normally the user presses the "i" key to bring a 3D widget to life. Here
  // we will manually enable it so it appears with the cone.
  //
  boxWidget->On();

  //
  // Start the event loop.
  //
  renderWindowInteractor->Initialize();
  renderWindowInteractor->Start();

  //
  // Free up any objects we created. All instances in VTK are deleted by
  // using the Delete() method.
  //
  cone->Delete();
  coneMapper->Delete();
  coneActor->Delete();
  callback->Delete();
  boxWidget->Delete();
  renderer->Delete();
  renderWindow->Delete();
  renderWindowInteractor->Delete();
  style->Delete();

  return 0;
}
