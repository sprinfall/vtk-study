#include <iostream>

#include "vtkBMPReader.h"
#include "vtkSmartPointer.h"
#include "vtkImageData.h"

int main() {
  auto image1 = vtkSmartPointer<vtkImageData>::New();
  std::cout << image1->GetReferenceCount() << std::endl;  // 1
  // New() 的实现:
  // static vtkSmartPointer<T> New() {
  //   return vtkSmartPointer<T>(T::New(), NoReference());
  // }

  auto image2 = vtkImageData::New();
  std::cout << image2->GetReferenceCount() << std::endl;  // 2
  // image2 内存最终不会被释放

  auto reader = vtkSmartPointer<vtkBMPReader>::New();
  vtkImageData* image3 = reader->GetOutput();
  // 当 `reader` 超出其作用域时，数据即会被删除。

  vtkSmartPointer<vtkImageData> image4 = reader->GetOutput();
  // 使用了智能指针，所以数据的引用计数会自动加1，除非 `reader` 和 `image4` 都
  // 超出它们的作用域，数据才会被删除。

  return 0;
}
