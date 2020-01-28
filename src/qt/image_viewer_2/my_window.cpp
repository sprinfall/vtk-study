#include "my_window.h"

#include <QDir>
#include <QFileDialog>
#include <QtWidgets>

#include "vtkRenderWindow.h"
#include "vtkRenderer.h"
#include "vtkImageViewer2.h"
#include "vtkJPEGReader.h"
#include "vtkImageActor.h"
#include "QVTKOpenGLNativeWidget.h"

MyWindow::MyWindow() {
  setWindowTitle(tr("Qt Image Viewer"));

  // QVTKOpenGLWidget
  widget_ = new QVTKOpenGLNativeWidget{};

#if 0
  // Optionally, add an extra layer of widget.

  QWidget* central_widget = new QWidget();
  setCentralWidget(central_widget);

  QVBoxLayout* vlayout = new QVBoxLayout();
  vlayout->addWidget(q_opengl_widget_, 1);
  central_widget->setLayout(vlayout);

#else
  // Directly add the QVTK widget as central widget.

  setCentralWidget(widget_);

#endif

  image_viewer_ = vtkSmartPointer<vtkImageViewer2>::New();
  renderer_ = vtkSmartPointer<vtkRenderer>::New();

  // GetRenderWindow() creates and returns a new vtkGenericOpenGLRenderWindow
  // if it is not already provided.
  widget_->GetRenderWindow()->AddRenderer(renderer_);

  // Action

  QAction* open_action = new QAction{ tr("&Open..."), this };
  open_action->setShortcuts(QKeySequence::Open);
  open_action->setStatusTip(tr("Open an image file"));

  connect(open_action, &QAction::triggered, this, &MyWindow::OnOpen);

  // Menu

  QMenu* file_menu = menuBar()->addMenu(tr("&File"));
  file_menu->addAction(open_action);
  file_menu->addSeparator();

  resize(800, 600);
}

void MyWindow::OpenFile(const QString& file_path) {
  auto reader = vtkSmartPointer<vtkJPEGReader>::New();

  QByteArray ba = file_path.toLocal8Bit();
  reader->SetFileName(ba.data());

  // 如下这两种写法都可以（注意背后的差别）：
#if 0
  reader->Update();  // Update() forces execution of the pipeline.
  image_viewer_->SetInputData(reader->GetOutput());
#else
  image_viewer_->SetInputConnection(reader->GetOutputPort());
#endif

  image_viewer_->UpdateDisplayExtent();
  image_viewer_->SetRenderWindow(widget_->GetRenderWindow());
  image_viewer_->SetRenderer(renderer_);
  image_viewer_->SetupInteractor(widget_->GetRenderWindow()->GetInteractor());
  image_viewer_->SetSliceOrientationToXY();  // default behavior
  image_viewer_->GetImageActor()->InterpolateOff();

  renderer_->ResetCamera();
  renderer_->DrawOn();

  widget_->GetRenderWindow()->Render();
}

void MyWindow::OnOpen() {
  QString filter = "JPEG image file (*.jpg *.jpeg)";

  QDir dir;
  QString file_name = QFileDialog::getOpenFileName(this,
                                                   QString(tr("Open Image")),
                                                   dir.absolutePath(), filter);
  if (file_name.isEmpty()) {
    return;
  }

  OpenFile(file_name);
}
