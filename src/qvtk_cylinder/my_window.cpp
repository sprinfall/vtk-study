#include "my_window.h"

#include <QVBoxLayout>

#include "my_widget.h"

MyWindow::MyWindow() {
  setWindowTitle(tr("Paint Study"));

  QWidget* central_widget = new QWidget();
  setCentralWidget(central_widget);

  MyWidget* my_widget = new MyWidget();

  QVBoxLayout* vlayout = new QVBoxLayout();

  vlayout->addWidget(my_widget, 1);

  central_widget->setLayout(vlayout);

  resize(800, 600);
}