// ds02_triangle_vertices.cpp
// 在 Triangle Points 示例的基础上为数据集定义拓扑结构。
// 这里的拓扑结构是零维的点，单元类型是 Vertex。

#include "vtkCellArray.h"
#include "vtkPoints.h"
#include "vtkPolyData.h"
#include "vtkPolyDataWriter.h"
#include "vtkSmartPointer.h"

int main() {
  // 创建点的坐标
  double X[3] = { 1.0, 0.0, 0.0 };
  double Y[3] = { 0.0, 0.0, 1.0 };
  double Z[3] = { 0.0, 0.0, 0.0 };

  // 创建点数据以及在每个点坐标上加入顶点 (Vertex) 类型的单元。
  auto points = vtkSmartPointer<vtkPoints>::New();
  auto vertices = vtkSmartPointer<vtkCellArray>::New();

  for (unsigned int i = 0; i < 3; ++i) {
    // 定义用于存储点索引的中间变量，vtkIdType 就相当于 int、long 等类型
    vtkIdType pid[1];

    // 把每个点坐标加入到 vtkPoints 中，InsertNextPoint() 返回加入的点的索引号，
    // 下面我们需要使用这个索引号来创建顶点类型的单元
    pid[0] = points->InsertNextPoint(X[i], Y[i], Z[i]);

    // 在每个坐标点上分别创建一个顶点，顶点是单元 (Cell) 里的一种类型
    vertices->InsertNextCell(1, pid);

    // 上面这几句也可以这样写：
    //   vtkIdType pid = points->InsertNextPoint(X[i], Y[i], Z[i]);
    //   vertices->InsertNextCell(1, &pid);
  }

  // 创建 vtkPolyData 对象
  auto poly_data = vtkSmartPointer<vtkPolyData>::New();

  poly_data->SetPoints(points);  // 几何结构
  poly_data->SetVerts(vertices);  // 拓扑结构

  // Write the data set to file.
  auto writer = vtkSmartPointer<vtkPolyDataWriter>::New();
  writer->SetFileName("TriangleVertices.vtk");
  writer->SetInputData(poly_data);
  writer->Write();

  return 0;
}
