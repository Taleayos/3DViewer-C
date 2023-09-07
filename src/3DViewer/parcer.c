#include "3DViewer.h"

view *m_viewer(char *file_name) {
  int vert_amount = 0;
  int pol_amount = 0;
  view *x;
  count_size_for_init(file_name, &vert_amount, &pol_amount);
  x = init_view(vert_amount, pol_amount);
  init_mimax(x);
  parcer(x, file_name);
  centralization(x);
  scaling(x, scale_rate(1, max_for_scale(x)));
  return x;
}

int parcer(view *figure, char *file_name) {
  int res = 0;
  int m = 0;
  FILE *fp = fopen(file_name, "r");
  char c = '\0', c1 = '\0';
  char str[512];
  int i = 0;
  while (fgets(str, 512, fp) != NULL) {
    c = str[0];
    c1 = str[1];
    if (c == 'v' && c1 == ' ') {
      sscanf(str, "%*s %lf %lf %lf", &figure->vertex->cooridinats[i].X,
             &figure->vertex->cooridinats[i].Y,
             &figure->vertex->cooridinats[i].Z);
      minmax(figure, figure->vertex->cooridinats[i].X,
             figure->vertex->cooridinats[i].Y,
             figure->vertex->cooridinats[i].Z);
      figure->vertex->cooridinats[i].vertex_number = i + 1;
      i++;
      figure->amount_of_vertexes++;
    }
    if (c == 'f' && c1 == ' ') {
      int k = 0;
      char *tmp = str;
      int j = 1;
      int count_ver_p = 0;
      while (tmp[j] != '\0') {
        if (tmp[j] == ' ' && isdigit(tmp[j + 1])) {
          count_ver_p++;
        }
        j++;
      }
      figure->poly[m].p = add_memory_poly(figure->poly[m].p, count_ver_p);
      figure->poly[m].amount_p = count_ver_p;
      j = 0;
      while (str[j] != '\0') {
        if (str[j] == ' ' && isdigit(str[j + 1])) {
          j++;
          char number[10] = {0};
          for (int s = 0; isdigit(str[j]); s++) {
            number[s] = str[j];
            j++;
          }
          figure->poly[m].p[k] = atoi(number);
          k++;
          j--;
        }
        figure->poly[m].amount_p = k;
        j++;
      }
      m++;
      figure->amount_of_polygons++;
    }
  }
  fclose(fp);
  return res;
}

int file_exists(char *file_name) {
  int res = 0;
  FILE *fp = fopen(file_name, "r");
  if (fp == NULL) {
    res = 1;
  }
  fclose(fp);
  return res;
}

int count_size_for_init(char *file_name, int *vert_amount, int *pol_amount) {
  int res = 0;
  if (file_exists(file_name) == 1) {
    res = 1;
  } else {
    FILE *f_n = fopen(file_name, "r");
    char str[512];
    while (fgets(str, 512, f_n) != NULL) {
      char c = str[0];
      char c1 = str[1];
      if (c == 'v' && c1 == ' ') {
        *vert_amount += 1;
      }
      if (c == 'f' && c1 == ' ') {
        int count_ver_p = 0;
        int j = 1;
        *pol_amount += 1;
        while (str[j] != '\0') {
          if (str[j] == ' ' && isdigit(str[j + 1])) {
            count_ver_p++;
          }
          j++;
        }
      }
    }
    fclose(f_n);
    if (*vert_amount < 1 || *pol_amount < 1) {
      res = 1;
    }
  }
  return res;
}

view *init_view(int vert_amount, int pol_amount) {
  view *figure = calloc(1, sizeof(view));
  figure->poly = calloc(pol_amount, sizeof(polygon));
  figure->vertex = calloc(1, sizeof(vertex));
  figure->vertex->cooridinats = calloc(4 * vert_amount, sizeof(double));
  return figure;
}

void free_view(view *figure) {
  for (unsigned int i = 0; i < figure->amount_of_polygons; i++) {
    free(figure->poly[i].p);
  }
  free(figure->vertex->cooridinats);
  free(figure->vertex);
  free(figure->poly);
  free(figure);
}

int *add_memory_poly(int *p, int amount_p) {
  p = calloc(amount_p, sizeof(int));
  return p;
}
void init_mimax(view *figure) {
  figure->vertex->MinMax_X[0] = 10000;
  figure->vertex->MinMax_X[1] = -10000;
  figure->vertex->MinMax_Y[0] = 10000;
  figure->vertex->MinMax_Y[1] = -10000;
  figure->vertex->MinMax_Z[0] = 10000;
  figure->vertex->MinMax_Z[1] = -10000;
}

void minmax(view *figure, double minmaxX, double minmaxY, double minmaxZ) {
  if (minmaxX < figure->vertex->MinMax_X[0]) {
    figure->vertex->MinMax_X[0] = minmaxX;
  }
  if (minmaxX > figure->vertex->MinMax_X[1]) {
    figure->vertex->MinMax_X[1] = minmaxX;
  }

  if (minmaxY < figure->vertex->MinMax_Y[0]) {
    figure->vertex->MinMax_Y[0] = minmaxY;
  }
  if (minmaxY > figure->vertex->MinMax_Y[1]) {
    figure->vertex->MinMax_Y[1] = minmaxY;
  }
  if (minmaxZ < figure->vertex->MinMax_Z[0]) {
    figure->vertex->MinMax_Z[0] = minmaxZ;
  }
  if (minmaxZ > figure->vertex->MinMax_Z[1]) {
    figure->vertex->MinMax_Z[1] = minmaxZ;
  }
}

void centralization(view *figure) {
  double centerX =
      figure->vertex->MinMax_X[0] +
      (figure->vertex->MinMax_X[1] - figure->vertex->MinMax_X[0]) / 2;
  double centerY =
      figure->vertex->MinMax_Y[0] +
      (figure->vertex->MinMax_Y[1] - figure->vertex->MinMax_Y[0]) / 2;
  double centerZ =
      figure->vertex->MinMax_Z[0] +
      (figure->vertex->MinMax_Z[1] - figure->vertex->MinMax_Z[0]) / 2;
  for (unsigned int i = 0; i < figure->amount_of_vertexes; i++) {
    figure->vertex->cooridinats[i].X -= centerX;
    figure->vertex->cooridinats[i].Y -= centerY;
    figure->vertex->cooridinats[i].Z -= centerZ;
  }
}
