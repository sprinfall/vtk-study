// This example introduces 3D widgets. 3D widgets take advantage of the
// event/observer design pattern introduced previously. They typically
// have a particular representation in the scene which can be interactively
// selected and manipulated using the mouse and keyboard. As the widgets
// are manipulated, they in turn invoke events such as StartInteractionEvent,
// InteractionEvent, and EndInteractionEvent which can be used to manipulate
// the scene that the widget is embedded in. 3D widgets work in the context
// of the event loop which was set up in the previous example.

#include "vtkActor.h"
#include "vtkBoxWidget.h"
#include "vtkCamera.h"
#include "vtkCommand.h"
#include "vtkConeSource.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkTransform.h"

class MyCallback : public vtkCommand {
public:
  static MyCallback* New() {
    return new MyCallback;
  }

  void Execute(vtkObject* caller, unsigned long, void*) override {
    vtkTransform* t = vtkTransform::New();
    vtkBoxWidget* widget = reinterpret_cast<vtkBoxWidget*>(caller);
    widget->GetTransform(t);
    widget->GetProp3D()->SetUserTransform(t);
    t->Delete();
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

  auto render_window = vtkRenderWindow::New();
  render_window->AddRenderer(renderer);
  render_window->SetSize(300, 300);

  auto interactor = vtkRenderWindowInteractor::New();
  interactor->SetRenderWindow(render_window);

  auto style = vtkInteractorStyleTrackballCamera::New();
  interactor->SetInteractorStyle(style);

  // Here we use a vtkBoxWidget to transform the underlying actor (by
  // manipulating its transformation matrix). Many other types of widgets
  // are available for use, see the documentation for more details.
  //
  // The SetInteractor method is how 3D widgets are associated with the render
  // window interactor. Internally, SetInteractor sets up a bunch of callbacks
  // using the Command/Observer mechanism (AddObserver()). The place factor
  // controls the initial size of the widget with respect to the bounding box
  // of the input to the widget.

  auto box_widget = vtkBoxWidget::New();
  box_widget->SetInteractor(interactor);
  box_widget->SetPlaceFactor(1.25);

  // Place the interactor initially. The input to a 3D widget is used to
  // initially position and scale the widget. The EndInteractionEvent is
  // observed which invokes the SelectPolygons callback.

  box_widget->SetProp3D(actor);
  box_widget->PlaceWidget();
  auto callback = MyCallback::New();
  box_widget->AddObserver(vtkCommand::InteractionEvent, callback);

  // Normally the user presses the "i" key to bring a 3D widget to life. Here
  // we will manually enable it so it appears with the cone.

  box_widget->On();

  // Start the event loop.

  interactor->Initialize();
  interactor->Start();

  // Free up any objects we created. All instances in VTK are deleted by
  // using the Delete() method.

  cone->Delete();
  mapper->Delete();
  actor->Delete();
  callback->Delete();
  box_widget->Delete();
  renderer->Delete();
  render_window->Delete();
  interactor->Delete();
  style->Delete();

  return 0;
}
