#include <iostream>

#include "vtkRenderWindow.h"
#include "vtkSmartPointer.h"

int main() {
  auto render_window = vtkSmartPointer<vtkRenderWindow>::New();
  render_window->Render();

  std::cin.get();

  return 0;
}
