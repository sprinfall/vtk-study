#include <iostream>

#include "vtkBMPReader.h"
#include "vtkSmartPointer.h"
#include "vtkImageData.h"

int main() {
  {
    auto image_data = vtkSmartPointer<vtkImageData>::New();
    std::cout << image_data->GetReferenceCount() << std::endl;  // 1
    // New() 的实现:
    // static vtkSmartPointer<T> New() {
    //   return vtkSmartPointer<T>(T::New(), NoReference());
    // }
  }

  {
    auto image_data = vtkImageData::New();
    std::cout << image_data->GetReferenceCount() << std::endl;  // 1
    // 通过 New() 创建的对象必须通过 Delete() 释放，不能用 C++ 的 delete，否则
    // 引用计数不工作。
    image_data->Delete();
  }

  {
    auto reader = vtkSmartPointer<vtkBMPReader>::New();
    vtkImageData* image_data = reader->GetOutput();
    // 当 `reader` 超出其作用域时，数据即会被删除。

    vtkSmartPointer<vtkImageData> ptr1 = reader->GetOutput();
    std::cout << image_data->GetReferenceCount() << std::endl;  // 2
    // 使用了智能指针，所以数据的引用计数会自动 +1，除非 `reader` 和 `ptr1` 都
    // 超出它们的作用域，数据才会被删除。

    vtkSmartPointer<vtkImageData> ptr2{ reader->GetOutput() };
    std::cout << image_data->GetReferenceCount() << std::endl;  // 3
  }

  return 0;
}
