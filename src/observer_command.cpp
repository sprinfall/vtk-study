#include "vtkCallbackCommand.h"
#include "vtkImageViewer2.h"
#include "vtkPNGReader.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkSmartPointer.h"

std::size_t g_press_count = 0;

// 第一步，定义回调函数。
// 注意回调函数的签名，不能更改。

void MyCallbackFunc(vtkObject*, unsigned long eid, void* client_data,
                    void* call_data) {
  std::cout << "You have clicked " << ++g_press_count << " times." << std::endl;
}

int main() {
  auto reader = vtkSmartPointer<vtkPNGReader>::New();
  reader->SetFileName("/home/adam/hello.png");
  reader->Update();

  auto viewer = vtkSmartPointer<vtkImageViewer2>::New();
  viewer->SetInputData(reader->GetOutput());

  auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  viewer->SetupInteractor(interactor);
  viewer->Render();

  // 第二步，设置回调函数。
  auto mouse_callback = vtkSmartPointer<vtkCallbackCommand>::New();
  mouse_callback->SetCallback(MyCallbackFunc);

  // 第三步，将 vtkCallbackCommand 对象添加到观察者列表。
  interactor->SetRenderWindow(viewer->GetRenderWindow());
  interactor->AddObserver(vtkCommand::LeftButtonPressEvent, mouse_callback);
  interactor->Initialize();
  interactor->Start();

  return 0;
}
