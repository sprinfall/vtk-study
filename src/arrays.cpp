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
  // 要创建点集，没必要先创建 float array，见后面。
  // 但是作为 Data Array 的示例还是不错的。
  auto coords = vtkSmartPointer<vtkFloatArray>::New();

  // Note that by default, an array has 1 component.
  // We have to change it to 3 for points.
  coords->SetNumberOfComponents(3);

  // We ask coords to allocate room for at least 4 tuples
  // and set the number of tuples to 4.
  coords->SetNumberOfTuples(4);

  // Assign each tuple.
  float pts[4][3] = {
    { 0.0, 0.0, 0.0 },
    { 0.0, 1.0, 0.0 },
    { 1.0, 0.0, 0.0 },
    { 1.0, 1.0, 0.0 }
  };

  for (int i = 0; i < 4; i++) {
    coords->SetTuple(i, pts[i]);
  }

  // 等价于：
  //   coords->SetTuple3(0, 0.0, 0.0, 0.0);
  //   coords->SetTuple3(1, 0.0, 1.0, 0.0);
  //   coords->SetTuple3(2, 1.0, 0.0, 0.0);
  //   coords->SetTuple3(3, 1.0, 1.0, 0.0);

  // Create vtkPoints and assign coords as the internal data array.
  auto points = vtkSmartPointer<vtkPoints>::New();
  points->SetData(coords);
  // 其实，没必要先定义 coords，直接像下面这样就可以了：
  //   points->SetNumberOfPoints(4);
  //   for (int i = 0; i < 4; ++i) {
  //     points->SetPoint(i, pts[i]);
  //   }

  // Create the cells. In this case, a triangle strip with 2 triangles
  // (which can be represented by 4 points)
  // 三角形条带，点的个数为 N + 2，N 为条带数。
  auto strips = vtkSmartPointer<vtkCellArray>::New();
  strips->InsertNextCell(4);
  strips->InsertCellPoint(0);  // 参数为点的索引
  strips->InsertCellPoint(1);
  strips->InsertCellPoint(2);
  strips->InsertCellPoint(3);
  // 一个 cell，包含 4 个点。等价于：
  //   vtkIdType cell_points[] = { 0, 1, 2, 3 };
  //   strips->InsertNextCell(4, cell_points);
  // 是不是 strips，还得取决于后面的 poly_data->SetStrips()。

  // 4 个点的坐标在 Z 轴上都是 0，所以大概如下面这样：
  //
  //  Y|
  //   |
  //   |
  // 1 |            3
  //   |
  //   |
  //   |
  //   |____________________ X
  //  0             2

  // Strips (0-1-2-3) 则形如：
  //
  //  1 ------ 3
  //  |  \     |
  //  |    \   |
  //  |      \ |
  //  0 ------ 2

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
