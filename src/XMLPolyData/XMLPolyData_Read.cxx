// Read XML poly-data using vtkXMLPolyDataReader.

#include "vtkActor.h"
#include "vtkPolyData.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkXMLPolyDataReader.h"

typedef vtkSmartPointer<vtkXMLPolyDataReader> vtkXMLPolyDataReaderPtr;
typedef vtkSmartPointer<vtkPolyData> vtkPolyDataPtr;

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage:\n\tXMLPolyData_Read <VTK XML file>" << std::endl;
    return 1;
  }

  const char *filePath = argv[1];
  std::cout << "VTK file: " << filePath << std::endl;

  vtkXMLPolyDataReaderPtr reader = vtkXMLPolyDataReaderPtr::New();

  if (!reader->CanReadFile(filePath))
  {
    std::cerr << "Can't read " << filePath << std::endl;
    return 1;
  }

  reader->SetFileName(filePath);
  reader->Update();  // Update() forces execution of the pipeline.

  vtkPolyDataPtr polyData(reader->GetOutput());

  std::cout << "Number of points: " << polyData->GetNumberOfPoints() << std::endl;

  // Create the mapper and set the appropriate scalar range (default is (0,1)).
  vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputData(polyData);
  mapper->SetScalarRange(0, 40);

  // Create an actor.
  vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  // Create the rendering objects.
  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
  renderer->AddActor(actor);

  vtkSmartPointer<vtkRenderWindow> renderWin = vtkSmartPointer<vtkRenderWindow>::New();
  renderWin->AddRenderer(renderer);

  vtkSmartPointer<vtkRenderWindowInteractor> renderWinInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWinInteractor->SetRenderWindow(renderWin);
  renderWinInteractor->Initialize();
  renderWinInteractor->Start();

  return 0;
}
