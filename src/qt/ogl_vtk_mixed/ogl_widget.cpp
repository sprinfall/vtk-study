#include <QOpenGLContext>

#include "ogl_widget.h"

OglWidget::OglWidget(QWidget* parent) : QOpenGLWidget(parent) {
  vertices_ = new GLfloat[9] {
    -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
  };
}

OglWidget::~OglWidget() {
  // Make sure the context is current and then explicitly
  // destroy all underlying OpenGL resources.
  makeCurrent();

  vbo_.destroy();
  vao_.destroy();

  doneCurrent();

  delete[] vertices_;
}

void OglWidget::initializeGL() {
  initializeOpenGLFunctions();

  bool transparent = false;
  glClearColor(0, 0, 0, transparent ? 0 : 1);

  vao_.create();
  if (vao_.isCreated()) {
    vao_.bind();
  }

  vbo_.create();
  vbo_.bind();

  vbo_.allocate(&vertices_[0], 9 * sizeof(GLfloat));

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

void OglWidget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  vao_.bind();

  glDrawArrays(GL_TRIANGLES, 0, 3);
}

void OglWidget::resizeGL(int width, int height) {
  projection_.setToIdentity();
  //projection_.perspective(45.0f, GLfloat(width) / height, 0.01f, 100.0f);
}
