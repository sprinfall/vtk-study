#include "vtkActor.h"
#include "vtkCamera.h"
#include "vtkCylinderSource.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkLight.h"
#include "vtkPNGReader.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkSmartPointer.h"
#include "vtkTexture.h"

int main() {
  auto png_reader = vtkSmartPointer<vtkPNGReader>::New();
  png_reader->SetFileName("/home/adam/hello.png");

  auto texture = vtkSmartPointer<vtkTexture>::New();
  texture->SetInputConnection(png_reader->GetOutputPort());
  texture->InterpolateOn();

  auto cylinder = vtkSmartPointer<vtkCylinderSource>::New();
  cylinder->SetHeight(3.0);
  cylinder->SetRadius(1.0);
  cylinder->SetResolution(10);

  auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(cylinder->GetOutputPort());

  auto actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->SetTexture(texture);

  auto renderer = vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);
  renderer->SetBackground(0.1, 0.2, 0.4);

  // Add lights

  auto light1 = vtkSmartPointer<vtkLight>::New();
  light1->SetColor(0, 1, 0);
  light1->SetPosition(0, 0, 1);
  light1->SetFocalPoint(renderer->GetActiveCamera()->GetFocalPoint());
  renderer->AddLight(light1);

  auto light2 = vtkSmartPointer<vtkLight>::New();
  light2->SetColor(0, 0, 1);
  light2->SetPosition(0, 0, -1);
  light2->SetFocalPoint(renderer->GetActiveCamera()->GetFocalPoint());
  renderer->AddLight(light2);

  auto rwin = vtkSmartPointer<vtkRenderWindow>::New();
  rwin->AddRenderer(renderer);
  rwin->SetSize(400, 400);

  auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(rwin);

  auto style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
  interactor->SetInteractorStyle(style);

  interactor->Initialize();
  interactor->Start();

  return 0;
}
