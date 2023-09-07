#include "3DViewer.h"

void translation(view *figure, double newX, double newY, double newZ) {
  for (unsigned int i = 0; i < figure->amount_of_vertexes; i++) {
    figure->vertex->cooridinats[i].X += newX;
    figure->vertex->cooridinats[i].Y += newY;
    figure->vertex->cooridinats[i].Z += newZ;
  }
}
void translationX(view *figure, double newX) {
  for (unsigned int i = 0; i < figure->amount_of_vertexes; i++) {
    figure->vertex->cooridinats[i].X += newX;
  }
}
void translationY(view *figure, double newY) {
  for (unsigned int i = 0; i < figure->amount_of_vertexes; i++) {
    figure->vertex->cooridinats[i].Y += newY;
  }
}
void translationZ(view *figure, double newZ) {
  for (unsigned int i = 0; i < figure->amount_of_vertexes; i++) {
    figure->vertex->cooridinats[i].Z += newZ;
  }
}

void scaling(view *figure, double scale_value) {
  for (unsigned int i = 0; i < figure->amount_of_vertexes; i++) {
    figure->vertex->cooridinats[i].X *= scale_value;
    figure->vertex->cooridinats[i].Y *= scale_value;
    figure->vertex->cooridinats[i].Z *= scale_value;
  }
}

double max_for_scale(view *figure) {
  double max = 0;
  double x = figure->vertex->MinMax_X[1] - figure->vertex->MinMax_X[0];
  double y = figure->vertex->MinMax_Y[1] - figure->vertex->MinMax_Y[0];
  double z = figure->vertex->MinMax_Z[1] - figure->vertex->MinMax_Z[0];
  if (x > y)
    max = x;
  else
    max = y;
  if (z > max) max = z;
  return max;
}

double scale_rate(double value, double max) {
  double scal = 0;
  scal = (value - (value * (-1))) / max;
  return scal;
}

void rotationX(view *figure, double rotation_angle) {
  for (unsigned int i = 0; i < figure->amount_of_vertexes; i++) {
    double tmpY = figure->vertex->cooridinats[i].Y;
    double tmpZ = figure->vertex->cooridinats[i].Z;
    figure->vertex->cooridinats[i].Y =
        tmpY * cos(rotation_angle) + tmpZ * sin(rotation_angle);
    figure->vertex->cooridinats[i].Z =
        tmpY * (-sin(rotation_angle)) + tmpZ * cos(rotation_angle);
  }
}

void rotationY(view *figure, double rotation_angle) {
  for (unsigned int i = 0; i < figure->amount_of_vertexes; i++) {
    double tmpX = figure->vertex->cooridinats[i].X;
    double tmpZ = figure->vertex->cooridinats[i].Z;
    figure->vertex->cooridinats[i].X =
        tmpX * cos(rotation_angle) + tmpZ * sin(rotation_angle);
    figure->vertex->cooridinats[i].Z =
        tmpX * (-sin(rotation_angle)) + tmpZ * cos(rotation_angle);
  }
}

void rotationZ(view *figure, double rotation_angle) {
  for (unsigned int i = 0; i < figure->amount_of_vertexes; i++) {
    double tmpX = figure->vertex->cooridinats[i].X;
    double tmpY = figure->vertex->cooridinats[i].Y;
    figure->vertex->cooridinats[i].X =
        tmpX * cos(rotation_angle) - tmpY * sin(rotation_angle);
    figure->vertex->cooridinats[i].Y =
        tmpX * sin(rotation_angle) + tmpY * cos(rotation_angle);
  }
}
