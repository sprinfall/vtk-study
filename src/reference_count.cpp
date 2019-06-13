#include <iostream>

#include "vtkBMPReader.h"
#include "vtkImageData.h"
#include "vtkSmartPointer.h"

int main() {
  auto reader = vtkSmartPointer<vtkBMPReader>::New();
  reader->SetFileName("/home/adam/hello.bmp");
  reader->Update();

  std::cout << "Reference Count of reader->GetOutput = "
            << reader->GetOutput()->GetReferenceCount() << std::endl;
  // 1

  // vtkSmartPointer<vtkImageData>
  auto image1 = reader->GetOutput();

  std::cout << "Reference Count of reader->GetOutput (Assign to image1) = "
            << reader->GetOutput()->GetReferenceCount() << std::endl;
  // 2

  std::cout << "Reference Count of image1 = " << image1->GetReferenceCount()
            << std::endl;
  // 2

  auto image2 = reader->GetOutput();

  std::cout << "Reference Count of reader->GetOutput (Assign to image2) = "
            << reader->GetOutput()->GetReferenceCount() << std::endl;
  // 3

  std::cout << "Reference Count of image2 = " << image2->GetReferenceCount()
            << std::endl;
  // 3

  return 0;
}
