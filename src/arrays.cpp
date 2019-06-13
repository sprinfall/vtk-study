// This example demonstrate the use of VTK data arrays as attribute
// data as well as field data. It creates geometry (vtkPolyData) as
// well as attribute data explicitly.

#include "vtkActor.h"
#include "vtkCellArray.h"
#include "vtkDoubleArray.h"
#include "vtkFloatArray.h"
#include "vtkIntArray.h"
#include "vtkPointData.h"
#include "vtkPoints.h"
#include "vtkPolyData.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkSmartPointer.h"

// scalar, 标量

int main() {
  // Create a float array which represents the points.
  auto coords = vtkSmartPointer<vtkFloatArray>::New();

  // Note that by default, an array has 1 component.
  // We have to change it to 3 for points.
  coords->SetNumberOfComponents(3);

  // We ask coords to allocate room for at least 4 tuples
  // and set the number of tuples to 4.
  coords->SetNumberOfTuples(4);

  // Assign each tuple. There are 5 specialized versions of SetTuple:
  // SetTuple1 SetTuple2 SetTuple3 SetTuple4 SetTuple9
  // These take 1, 2, 3, 4 and 9 components respectively.
  float pts[4][3] = {
    { 0.0, 0.0, 0.0 },
    { 0.0, 1.0, 0.0 },
    { 1.0, 0.0, 0.0 },
    { 1.0, 1.0, 0.0 }
  };

  for (int i = 0; i < 4; i++) {
    coords->SetTuple(i, pts[i]);
  }

  // Create vtkPoints and assign coords as the internal data array.
  auto points = vtkSmartPointer<vtkPoints>::New();
  points->SetData(coords);

  // Create the cells. In this case, a triangle strip with 2 triangles
  // (which can be represented by 4 points)
  auto strips = vtkSmartPointer<vtkCellArray>::New();
  strips->InsertNextCell(4);
  strips->InsertCellPoint(0);
  strips->InsertCellPoint(1);
  strips->InsertCellPoint(2);
  strips->InsertCellPoint(3);

  // Create an integer array with 4 tuples. Note that when using
  // InsertNextValue (or InsertNextTuple1 which is equivalent in
  // this situation), the array will expand automatically
  auto temperature = vtkSmartPointer<vtkIntArray>::New();
  temperature->SetName("Temperature");
  // See: mapper->SetScalarRange(0, 40);
  temperature->InsertNextValue(10);
  temperature->InsertNextValue(20);
  temperature->InsertNextValue(30);
  temperature->InsertNextValue(40);

  // Create a double array.
  // 涡量，旋度
  auto vorticity = vtkSmartPointer<vtkDoubleArray>::New();
  vorticity->SetName("Vorticity");
  vorticity->InsertNextValue(2.7);
  vorticity->InsertNextValue(4.1);
  vorticity->InsertNextValue(5.3);
  vorticity->InsertNextValue(3.4);

  // Create the dataset. In this case, we create a vtkPolyData
  auto poly_data = vtkSmartPointer<vtkPolyData>::New();
  // Assign points and cells
  poly_data->SetPoints(points);
  poly_data->SetStrips(strips);
  // Assign scalars
  // NOTE: The number of point attributes must equal to the number of points.
  poly_data->GetPointData()->SetScalars(temperature);
  // Add the vorticity array. In this example, this field is not used.
  poly_data->GetPointData()->AddArray(vorticity);

  // Create the mapper and set the appropriate scalar range
  // (default is (0,1))
  auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputData(poly_data);
  mapper->SetScalarRange(0, 40);

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
