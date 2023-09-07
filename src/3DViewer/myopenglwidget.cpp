#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "myopenglwidget.h"
#include "3DViewer.h"



MyOpenGLWidget::MyOpenGLWidget(QWidget *parent) : QOpenGLWidget{parent} {}

void MyOpenGLWidget::initializeGL() {
  initializeOpenGLFunctions();
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);
}

void MyOpenGLWidget::paintGL() {
    if (line_type == 0) glEnable(GL_LINES);
    if (line_type == 1) {
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(1, 0x00FF);
    }
  glLineWidth(line_width);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  if (projection==true) {
     glFrustum(-1, 1, -1, 1, 1, 5);
  } else {
      glOrtho(-1, 1, -1, 1, 1, 5);
  }
  glTranslatef(0, 0, -2);
  glMatrixMode(GL_MODELVIEW);
  glClearColor(r_back, g_back, b_back, a);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3f(r, g, b);
  if (is_open == true) {
        for (unsigned int i = 0; i < x->amount_of_polygons-1; i++) {
            glBegin(GL_LINE_LOOP);
             for (int j = 0; j < x->poly[i].amount_p; j++) {
                glVertex3d((x->vertex->cooridinats[(x->poly[i].p[j]) - 1].X + x_gl) * scale_gl, (x->vertex->cooridinats[(x->poly[i].p[j]) - 1].Y + y_gl) * scale_gl, (x->vertex->cooridinats[(x->poly[i].p[j]) - 1].Z + z_gl) * scale_gl);
              }
           glEnd();
        }

    }
  if (line_type == 0) glDisable(GL_LINES);
  if (line_type == 1) glDisable(GL_LINE_STIPPLE);

  if (vertex_type) {
      if (vertex_type==1) glEnable(GL_POINT_SMOOTH);
      if (vertex_type==2) glEnable(GL_POINT_BIT);
      glPointSize(vertex_size);
      glColor3f(r_point, g_point, b_point);
      glBegin(GL_POINTS);
      if (is_open == true) {
            for (unsigned int i = 0; i < x->amount_of_polygons; i++) {
              for (int j = 0; j < x->poly[i].amount_p;) {
                  glVertex3d((x->vertex->cooridinats[(x->poly[i].p[j]) - 1].X + x_gl) * scale_gl, (x->vertex->cooridinats[(x->poly[i].p[j]) - 1].Y + y_gl) * scale_gl, (x->vertex->cooridinats[(x->poly[i].p[j]) - 1].Z + z_gl) * scale_gl);
                  j++;
              }
          }
      }
      glEnd();
      if (vertex_type==1) glDisable(GL_POINT_SMOOTH);
      if (vertex_type==2) glDisable(GL_POINT_BIT);
  }
}

void MyOpenGLWidget::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

