#include <QApplication>
#include <QFileInfo>
#include <QSurfaceFormat>

#include "QVTKOpenGLWidget.h"

#include "my_window.h"

int main(int argc, char* argv[]) {
  // 允许通过命令行指定一个 JPEG 文件路径，但这是可选的。
  // 界面上仍然会提供菜单供用户选择新的 JPEG 文件。
  // 如果命令行提供了这个 JPEG 文件，那么就直接打开。
  QString jpeg_path;
  if (argc > 1) {
    jpeg_path = QString::fromLocal8Bit(argv[1]);
  }

  // Ensure appropriate OpenGL context is created for VTK rendering.
  QSurfaceFormat::setDefaultFormat(QVTKOpenGLWidget::defaultFormat());

  QApplication app(argc, argv);

  MyWindow window;
  window.show();

  if (!jpeg_path.isEmpty() && QFileInfo::exists(jpeg_path)) {
    window.OpenFile(jpeg_path);
  }

  return app.exec();
}
