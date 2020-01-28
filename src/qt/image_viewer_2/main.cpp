#include <QApplication>
#include <QFileInfo>
#include <QSurfaceFormat>

#include "QVTKOpenGLWidget.h"

#include "my_window.h"

int main(int argc, char* argv[]) {
  // ����ͨ��������ָ��һ�� JPEG �ļ�·���������ǿ�ѡ�ġ�
  // ��������Ȼ���ṩ�˵����û�ѡ���µ� JPEG �ļ���
  // ����������ṩ����� JPEG �ļ�����ô��ֱ�Ӵ򿪡�
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
