#include "vtkActor.h"
#include "vtkCylinderSource.h"
#include "vtkInteractorStyleTrackballCamera.h"
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

  auto rwin = vtkSmartPointer<vtkRenderWindow>::New();
  rwin->AddRenderer(renderer);
  rwin->SetSize(400, 400);

  auto interator = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interator->SetRenderWindow(rwin);

  auto style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
  interator->SetInteractorStyle(style);

  interator->Initialize();
  interator->Start();

  return 0;
}
