#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#define GL_SILENCE_DEPRECATION

#include <QColor>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QMouseEvent>
#include <QtOpenGL>


 extern "C" {
     #include "3DViewer.h"
 }

class MyOpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions {

 public:
  MyOpenGLWidget(QWidget *parent = nullptr);

  float r = 0, g = 0.5, b = 0, a = 1;
  float r_point = 0, g_point = 0.5, b_point = 0.0;
  float r_back = 0, g_back = 0.0, b_back = 0.0;

  double scale_gl = 1.0f;
  double x_gl = 0.0f;
  double y_gl = 0.0f;
  double z_gl = 0.0f;

  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;

 view *x;

  bool is_open = false;
  bool projection = true;
  int line_width = 1;
  int line_type = 0;
  int vertex_type = 0;
  int vertex_size = 10;

};

#endif  // MYOPENGLWIDGET_H
