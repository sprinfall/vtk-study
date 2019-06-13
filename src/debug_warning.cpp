#include "vtkImageViewer2.h"
#include "vtkPNGReader.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkSmartPointer.h"

// vtkObject 里定义的程序调试相关的接口

int main() {
  // static
  vtkObject::SetGlobalWarningDisplay(true);  // GlobalWarningDisplayOn()

  auto reader = vtkSmartPointer<vtkPNGReader>::New();
  reader->SetFileName("/home/adam/hello.png");
  reader->SetDebug(true);  // DebugOn()
  reader->Update();

  auto viewer = vtkSmartPointer<vtkImageViewer2>::New();
  viewer->SetInputData(reader->GetOutput());

  auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  viewer->SetupInteractor(interactor);
  viewer->Render();

  interactor->Initialize();
  interactor->Start();

  return 0;
}
