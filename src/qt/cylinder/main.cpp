#include <QApplication>
#include <QSurfaceFormat>

#include "QVTKOpenGLWidget.h"

#include "my_window.h"

int main(int argc, char** argv) {
  // needed to ensure appropriate OpenGL context is created for VTK rendering.
  QSurfaceFormat::setDefaultFormat(QVTKOpenGLWidget::defaultFormat());

  QApplication app(argc, argv);

  //QApplication::setStyle("fusion");

  MyWindow window;
  window.show();

  return app.exec();
}
