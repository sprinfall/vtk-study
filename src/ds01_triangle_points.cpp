// 演示只有几何结构 (Geometry)，没有拓扑结构 (Topology) 的数据集。

#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataWriter.h>
#include <vtkSmartPointer.h>

int main(int argc, char* argv[]) {
  // 创建点数据
  auto points = vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(1.0, 0.0, 0.0);
  points->InsertNextPoint(0.0, 0.0, 0.0);
  points->InsertNextPoint(0.0, 1.0, 0.0);

  // 创建 vtkPolyData 类型的数据，vtkPolyData 派生自 vtkPointSet，后者又派生自
  // vtkDataSet。
  auto poly_data = vtkSmartPointer<vtkPolyData>::New();
  // 设置点数据，即指定几何结构。
  poly_data->SetPoints(points);

  // Write the data set to file.
  auto writer = vtkSmartPointer<vtkPolyDataWriter>::New();
  writer->SetFileName("TrianglePoints.vtk");
  writer->SetInputData(poly_data);
  writer->Write();

  return 0;
}
