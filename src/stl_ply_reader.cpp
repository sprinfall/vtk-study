// STL and PLY file readers.

#include <iostream>

#include "vtkActor.h"
#include "vtkPolyData.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkPLYReader.h"
#include "vtkSTLReader.h"

std::string GetExt(const std::string& file_path) {
  std::size_t dot = file_path.find_last_of('.');
  if (dot != std::string::npos) {
    return file_path.substr(dot + 1);
  }
  return "";
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "Usage: stl_ply_reader <STL or PLY file>" << std::endl;
    return 1;
  }

  const char* file_path = argv[1];
  std::cout << "file: " << file_path << std::endl;

  std::string ext = GetExt(file_path);
  
  vtkSmartPointer<vtkAbstractPolyDataReader> reader;

  if (ext == "ply") {
    reader = vtkSmartPointer<vtkPLYReader>::New();
  } else if (ext == "stl") {
    reader = vtkSmartPointer<vtkSTLReader>::New();
  } else {
    return 1;
  }

  reader->SetFileName(file_path);
  reader->Update();

  if (ext == "ply") {  // vtkSTLReader doesn't have CanReadFile().
    if (!vtkPLYReader::CanReadFile(file_path)) {  // static
      std::cerr << "Can't read file." << std::endl;
      return 1;
    }
  }

  vtkSmartPointer<vtkPolyData> poly_data{ reader->GetOutput() };
  // vtkPolyData 是有引用计数的，会在 smart pointer 和 `reader` 都超出作用域时
  // 被删除。祥见 smart_pointer 示例。

  std::cout << "Number of points: " << poly_data->GetNumberOfPoints()
            << std::endl;

  // Create the mapper and set the appropriate scalar range (default is (0,1)).
  auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputData(poly_data);
  mapper->SetScalarRange(0, 40);  // ?

  // Create an actor.
  auto actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  // Create the rendering objects.
  auto renderer = vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);

  auto render_window = vtkSmartPointer<vtkRenderWindow>::New();
  render_window->AddRenderer(renderer);

  auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(render_window);
  interactor->Initialize();
  interactor->Start();

  return 0;
}
