// ds04_scalars.cpp
// Set scalar attribute data for point data (or cell data).
// 为点数据（或单元数据）指定标量属性数据。

#include <iostream>

#include "vtkDoubleArray.h"
#include "vtkPointData.h"
#include "vtkPoints.h"
#include "vtkPolyData.h"
#include "vtkSmartPointer.h"

int main() {
  // 创建点集数据：包含两个坐标点。
  auto points = vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0, 0, 0);
  points->InsertNextPoint(1, 0, 0);

  // 创建多边形数据。
  auto poly_data = vtkSmartPointer<vtkPolyData>::New();
  poly_data->SetPoints(points);  // 指定几何结构

  // 准备加入点数据的标量值，两个标量值分别为 1 和 2。
  auto weights = vtkSmartPointer<vtkDoubleArray>::New();
  weights->SetNumberOfValues(2);
  weights->SetValue(0, 1);
  weights->SetValue(1, 2);
  //weights->InsertNextValue(1);
  //weights->InsertNextValue(2);

  // 先获取多边形数据的点数据指针，然后设置该点数据的标量属性值。
  poly_data->GetPointData()->SetScalars(weights);

  // 输出索引号为 0 的点的标量值。
  double weight =
      vtkDoubleArray::SafeDownCast(poly_data->GetPointData()->GetScalars())
          ->GetValue(0);
  std::cout << "double weight: " << weight << std::endl;

  return 0;
}
