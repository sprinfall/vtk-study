// Write XML poly-data using vtkXMLPolyDataWriter.
// The poly-data is the same as Arrays example.

// See: https://programtalk.com/python-examples/vtkAll.vtkXMLPolyDataWriter/

#include "vtkCellArray.h"
#include "vtkDoubleArray.h"
#include "vtkFloatArray.h"
#include "vtkIntArray.h"
#include "vtkPointData.h"
#include "vtkPoints.h"
#include "vtkPolyData.h"
#include "vtkXMLPolyDataWriter.h"

typedef vtkSmartPointer<vtkXMLPolyDataWriter> vtkXMLPolyDataWriterPtr;

int main()
{
  // Create a float array which represents the points.
  vtkSmartPointer<vtkFloatArray> pcoords = vtkSmartPointer<vtkFloatArray>::New();

  // Note that by default, an array has 1 component.
  // We have to change it to 3 for points
  // ADAM: X, Y, Z
  pcoords->SetNumberOfComponents(3);

  // We ask pcoords to allocate room for at least 4 tuples
  // and set the number of tuples to 4.
  pcoords->SetNumberOfTuples(4);

  // Assign each tuple. There are 5 specialized versions of SetTuple:
  // SetTuple1 SetTuple2 SetTuple3 SetTuple4 SetTuple9
  // These take 1, 2, 3, 4 and 9 components respectively.
  float pts[4][3] =
  {
    { 0.0, 0.0, 0.0 },
    { 0.0, 1.0, 0.0 },
    { 1.0, 0.0, 0.0 },
    { 1.0, 1.0, 0.0 }
  };


  for (int i = 0; i < 4; i++) {
    pcoords->SetTuple(i, pts[i]);
  }
  // �൱��:
  // pcoords->SetTuple3(0, 0.0, 0.0, 0.0);
  // pcoords->SetTuple3(1, 0.0, 1.0, 0.0);
  // pcoords->SetTuple3(2, 1.0, 0.0, 0.0);
  // pcoords->SetTuple3(3, 1.0, 1.0, 0.0);

  //pcoords->PrintSelf(std::cout, vtkIndent());

  // Create vtkPoints and assign pcoords as the internal data array.
  vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
  points->SetData(pcoords);

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
  vtkSmartPointer<vtkCellArray> strips = vtkSmartPointer<vtkCellArray>::New();
  strips->InsertNextCell(4);
  strips->InsertCellPoint(0);
  strips->InsertCellPoint(1);
  strips->InsertCellPoint(2);
  strips->InsertCellPoint(3);

  strips->PrintSelf(std::cout, vtkIndent());

  // Create an integer array with 4 tuples. Note that when using
  // InsertNextValue (or InsertNextTuple1 which is equivalent in
  // this situation), the array will expand automatically
  vtkSmartPointer<vtkIntArray> temperature = vtkSmartPointer<vtkIntArray>::New();
  temperature->SetName("Temperature");
  temperature->InsertNextValue(10);
  temperature->InsertNextValue(20);
  temperature->InsertNextValue(30);
  temperature->InsertNextValue(40);

  // Create a double array.
  // vorticity: ����������
  vtkSmartPointer<vtkDoubleArray> vorticity = vtkSmartPointer<vtkDoubleArray>::New();
  vorticity->SetName("Vorticity");
  vorticity->InsertNextValue(2.7);
  vorticity->InsertNextValue(4.1);
  vorticity->InsertNextValue(5.3);
  vorticity->InsertNextValue(3.4);

  // Create the dataset. In this case, we create a vtkPolyData
  vtkSmartPointer<vtkPolyData> polyData = vtkSmartPointer<vtkPolyData>::New();
  // Assign points and cells
  polyData->SetPoints(points);
  polyData->SetStrips(strips);
  // Assign scalars
  polyData->GetPointData()->SetScalars(temperature);
  // Add the vorticity array. In this example, this field is not used.
  polyData->GetPointData()->AddArray(vorticity);

  // TEST
  //polyData->PrintSelf(std::cout, vtkIndent());

  //vtkXMLPolyDataWriterPtr writer = vtkXMLPolyDataWriterPtr::New();

  //writer->SetFileName("test_write.vtk");
  //writer->SetInputData(polyData);
  //writer->Update();

  return 0;
}


