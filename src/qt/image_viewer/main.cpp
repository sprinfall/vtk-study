// QVTKOpenGLWidget 最简单的一个例子。
// 通过 vtkJPEGReader 读入一张 JPEG 图像，再用 vtkImageViewer 显示于
// QVTKOpenGLWidget 中。
// 修改自：<VTK>\Examples\GUI\Qt\ImageViewer

#include <iostream>

#include <QApplication>
#include <QSurfaceFormat>

#include "vtkGenericOpenGLRenderWindow.h"
#include "vtkImageViewer.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkJPEGReader.h"

#include "QVTKOpenGLWidget.h"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: qt_image_viewer <JPEG file path>" << std::endl;
    return 1;
  }

  const char* jpg_path = argv[1];

  QSurfaceFormat::setDefaultFormat(QVTKOpenGLWidget::defaultFormat());

  QApplication app(argc, argv);

  QVTKOpenGLWidget widget;
  widget.setWindowTitle("Qt Image Viewer");  // TODO: tr
  widget.resize(800, 600);

  vtkNew<vtkGenericOpenGLRenderWindow> render_window;
  // 也可以在 QVTKOpenGLWidget 构造时作为参数传入
  widget.SetRenderWindow(render_window);

  vtkNew<vtkJPEGReader> reader;
  reader->SetFileName(jpg_path);

  vtkNew<vtkImageViewer> image_viewer;
  image_viewer->SetRenderWindow(render_window);

  // NOTE:
  // If use `SetInputData(reader->GetOutput())` instead, `Update()` should be
  // called on the reader.
  image_viewer->SetInputConnection(reader->GetOutputPort());

  image_viewer->SetupInteractor(render_window->GetInteractor());

  image_viewer->SetColorLevel(138.5);
  image_viewer->SetColorWindow(233);

  widget.show();

  app.exec();
  return 0;
}
