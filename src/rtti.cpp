#include <iostream>

#include "vtkBMPReader.h"
#include "vtkSmartPointer.h"

int main() {
  auto reader = vtkSmartPointer<vtkBMPReader>::New();
  const char* type = reader->GetClassName();
  std::cout << type << std::endl;  // vtkBMPReader

  std::cout << reader->IsA("vtkImageReader") << std::endl;  // 1

  // SafeDownCast, 静态函数
  auto reader_base = vtkSmartPointer<vtkImageReader>::New();
  vtkBMPReader* bmp_reader = vtkBMPReader::SafeDownCast(reader_base);
  std::cout << (bmp_reader != nullptr) << std::endl;  // 0

  // Print, 用于调试的状态输出接口
  reader_base->Print(std::cout);
  // vtkImageReader (0x1e83650)
  // Debug: Off
  // Modified Time: 128
  // Reference Count: 2
  // Registered Events: (none)
  // Executive: 0x1e84330
  // ...

  return 0;
}
