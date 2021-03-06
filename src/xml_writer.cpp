// Write XML poly-data using vtkXMLPolyDataWriter.
// The poly-data is the same as `arrays` example.

// See: https://programtalk.com/python-examples/vtkAll.vtkXMLPolyDataWriter/

#include <iostream>
#include <fstream>

#include "vtkCellArray.h"
#include "vtkDoubleArray.h"
#include "vtkIntArray.h"
#include "vtkPointData.h"
#include "vtkPoints.h"
#include "vtkPolyData.h"
#include "vtkXMLPolyDataWriter.h"
#include "vtkPolyDataWriter.h"
#include "vtkTransform.h"

std::ostream& operator<<(std::ostream& os, const vtkMatrix4x4& matrix) {
  for (size_t i = 0; i < 4; ++i) {
    for (size_t j = 0; j < 4; ++j) {
      os << matrix.Element[i][j] << " ";
    }
  }
  return os;
}

std::istream& operator>>(std::istream& is, vtkMatrix4x4& matrix) {
  for (size_t i = 0; i < 4; ++i) {
    for (size_t j = 0; j < 4; ++j) {
      is >> matrix.Element[i][j];
    }
  }
  return is;
}

int main() {
  auto points = vtkSmartPointer<vtkPoints>::New();
  points->SetNumberOfPoints(4);

  float pts[4][3] = {
    { 0.0, 0.0, 0.0 },
    { 0.0, 1.0, 0.0 },
    { 1.0, 0.0, 0.0 },
    { 1.0, 1.0, 0.0 },
  };

  for (int i = 0; i < 4; ++i) {
    points->SetPoint(i, pts[i]);
  }

  //points->PrintSelf(std::cout, vtkIndent());
  // ...
  // Data Array Name: Points
  // Number Of Points: 4
  // Bounds:
  //   Xmin,Xmax: (0, 1)
  //   Ymin,Ymax: (0, 1)
  //   Zmin,Zmax: (0, 0)

  //  Z|              / Y
  //   |            /
  //   |          /
  //   |        / P1           P3
  //   |      /
  //   |    /
  //   |  /
  //   |/_____________________ X
  //  P0             P2

  // Create the cells. In this case, a triangle strip with 2 triangles
  // (which can be represented by 4 points)
  auto strips = vtkSmartPointer<vtkCellArray>::New();
  strips->InsertNextCell(4);
  strips->InsertCellPoint(0);
  strips->InsertCellPoint(1);
  strips->InsertCellPoint(2);
  strips->InsertCellPoint(3);

  //strips->PrintSelf(std::cout, vtkIndent());

  // Create an integer array with 4 tuples. Note that when using
  // InsertNextValue (or InsertNextTuple1 which is equivalent in
  // this situation), the array will expand automatically
  auto temperature = vtkSmartPointer<vtkIntArray>::New();
  temperature->SetName("Temperature");
  temperature->InsertNextValue(10);
  temperature->InsertNextValue(20);
  temperature->InsertNextValue(30);
  temperature->InsertNextValue(40);

  // Create a double array.
  // vorticity: 环量
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
  poly_data->GetPointData()->SetScalars(temperature);
  // Add the vorticity array. In this example, this field is not used.
  poly_data->GetPointData()->AddArray(vorticity);

  //poly_data->PrintSelf(std::cout, vtkIndent());

  auto writer = vtkSmartPointer<vtkXMLPolyDataWriter>::New();
  //auto writer = vtkSmartPointer<vtkPolyDataWriter>::New();

  //writer->SetFileName("test.vtk");

  //writer->SetFileName("D:\\proj\\scan_refresh\\data\\RestoreVtk\\test.vtk");
  //writer->SetInputData(poly_data);

  //writer->Update();
  //writer->Write();  // TODO

  // Optional - set the mode. The default is binary.
  //writer->SetDataModeToBinary();
  //writer->SetDataModeToAscii();

  // Test transform
  //auto transform = vtkSmartPointer<vtkTransform>::New();
  //vtkMatrix4x4* matrix = transform->GetMatrix();
  //std::cout << *matrix << std::endl;

  //std::ofstream ofs("D:\\matrix.txt");
  //ofs << *matrix << std::endl;

  auto matrix = vtkSmartPointer<vtkMatrix4x4>::New();
  std::ifstream ifs("D:\\matrix.txt");
  ifs >> *matrix;
  std::cout << *matrix << std::endl;

  return 0;
}
