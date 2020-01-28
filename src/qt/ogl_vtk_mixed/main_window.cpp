#include "main_window.h"

#include <QVBoxLayout>

#include "vtk_widget.h"
#include "ogl_widget.h"

MainWindow::MainWindow() {
  setWindowTitle(tr("Qt OGL & VTK Mixed"));

  QWidget* central_widget = new QWidget{};
  setCentralWidget(central_widget);

  VtkWidget* vtk_widget = new VtkWidget{ central_widget };
  OglWidget* ogl_widget = new OglWidget{ central_widget };

  QHBoxLayout* hlayout = new QHBoxLayout{ central_widget };
  hlayout->addWidget(vtk_widget, 1);
  hlayout->addWidget(ogl_widget, 1);

  resize(1000, 500);
}