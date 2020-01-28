#include <QApplication>
#include <QSurfaceFormat>

#include "QVTKOpenGLWidget.h"

#include "my_window.h"

int main(int argc, char** argv) {
  // Ensure appropriate OpenGL context is created for VTK rendering.
  QSurfaceFormat::setDefaultFormat(QVTKOpenGLWidget::defaultFormat());

  QApplication app(argc, argv);

  MyWindow window;
  window.show();

  return app.exec();
}
