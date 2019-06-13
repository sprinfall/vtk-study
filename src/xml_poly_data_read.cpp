// Read XML poly-data using vtkXMLPolyDataReader.

#include "vtkActor.h"
#include "vtkPolyData.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkXMLPolyDataReader.h"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "Usage:" << std::endl;
    std::cout << "\t" << argv[0] << " <vtk xml file>" << std::endl;
    return 1;
  }

  const char* file_path = argv[1];
  std::cout << "VTK XML file: " << file_path << std::endl;

  auto reader = vtkSmartPointer<vtkXMLPolyDataReader>::New();

  if (!reader->CanReadFile(file_path)) {
    std::cerr << "Can't read " << file_path << std::endl;
    return 1;
  }

  reader->SetFileName(file_path);
  reader->Update();  // Update() forces execution of the pipeline.

  vtkSmartPointer<vtkPolyData> poly_data(reader->GetOutput());

  std::cout << "Number of points: " << poly_data->GetNumberOfPoints()
            << std::endl;

  // Create the mapper and set the appropriate scalar range (default is (0,1)).
  auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputData(poly_data);
  mapper->SetScalarRange(0, 40);

  // Create an actor.
  vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
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
