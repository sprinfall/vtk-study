// ds03_triangle_lines.cpp
// 在 Triangle Vertices 示例的基础上，将零维的点拓扑结构改成一维的线拓扑结构。

#include "vtkCellArray.h"
#include "vtkLine.h"
#include "vtkPoints.h"
#include "vtkPolyData.h"
#include "vtkPolyDataWriter.h"
#include "vtkSmartPointer.h"

int main(int argc, char* argv[]) {
  // 创建点数据
  auto points = vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(1.0, 0.0, 0.0);  // 返回 ID: 0
  points->InsertNextPoint(0.0, 0.0, 0.0);  // 返回 ID: 1
  points->InsertNextPoint(0.0, 1.0, 0.0);  // 返回 ID: 2

  // 第一条线，连接 ID 为 0 和 1 两个点。
  auto line0 = vtkSmartPointer<vtkLine>::New();
  // SetId 的第一个参数是线的两个点的下标，总是 0 和 1。
  line0->GetPointIds()->SetId(0, 0);
  line0->GetPointIds()->SetId(1, 1);

  // 第二条线，连接 ID 为 1 和 2 两个点。
  auto line1 = vtkSmartPointer<vtkLine>::New();
  line1->GetPointIds()->SetId(0, 1);
  line1->GetPointIds()->SetId(1, 2);

  // 第三条线，连接 ID 为 2 和 0 两个点。
  auto line2 = vtkSmartPointer<vtkLine>::New();
  line2->GetPointIds()->SetId(0, 2);
  line2->GetPointIds()->SetId(1, 0);

  // 创建点数据以及在每个点坐标上加入顶点 (Vertex) 类型的单元。
  auto lines = vtkSmartPointer<vtkCellArray>::New();
  lines->InsertNextCell(line0);
  lines->InsertNextCell(line1);
  lines->InsertNextCell(line2);

  // 或者像下面这样，不必先创建 vtkLine：
  //   vtkIdType line_points[3][2] = {
  //     { 0, 1 }, { 1, 2 }, { 2, 0 }
  //   };
  //   for (int i = 0; i < 3; ++i) {
  //     lines->InsertNextCell(2, line_points[i]);
  //   }
  // InsertNextCell() 有很多不同的方式。

  // 创建 vtkPolyData 对象
  auto poly_data = vtkSmartPointer<vtkPolyData>::New();

  poly_data->SetPoints(points);  // 几何结构
  poly_data->SetLines(lines);  // 拓扑结构

  // Write the data set to file.
  auto writer = vtkSmartPointer<vtkPolyDataWriter>::New();
  writer->SetFileName("TriangleLines.vtk");
  writer->SetInputData(poly_data);
  writer->Write();

  return 0;
}
