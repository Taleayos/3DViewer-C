#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "3DViewer.h"

START_TEST(file_exist) {
  char str[256] = "pyramid1.obj";
  int res = file_exists(str);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(count_size_err_2) {
  char str[256] = "obj/pyramid1.obj";
  int vert_amount = 0;
  int pol_amount = 0;
  int res = count_size_for_init(str, &vert_amount, &pol_amount);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(count_size_err_3) {
  char str[256] = "obj/pyramid_bit_1.obj";
  int vert_amount = 0;
  int pol_amount = 0;
  int res = count_size_for_init(str, &vert_amount, &pol_amount);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(m_v_2) {
  char str[256] = "obj/pyramid.obj";
  int vert_amount = 5;
  int pol_amount = 6;
  double MinMax_X[2] = {-1, 1};
  double MinMax_Y[2] = {0, 1};
  double MinMax_Z[2] = {-1, 1};
  view *x = m_viewer(str);
  ck_assert_int_eq(vert_amount, x->amount_of_vertexes);
  ck_assert_int_eq(pol_amount, x->amount_of_polygons);
  for (int i = 0; i < 2; i++) {
    ck_assert_double_eq(MinMax_X[i], x->vertex->MinMax_X[i]);
    ck_assert_double_eq(MinMax_Y[i], x->vertex->MinMax_Y[i]);
    ck_assert_double_eq(MinMax_Z[i], x->vertex->MinMax_Z[i]);
  }
  free_view(x);
}
END_TEST

START_TEST(m_v_3) {
  char str[256] = "obj/circle.obj";
  int vert_amount = 386;
  int pol_amount = 384;
  double MinMax_X[2] = {-1.742230, 1.742230};
  double MinMax_Y[2] = {-1.739946, 1.739946};
  double MinMax_Z[2] = {-1.745721, 1.745721};
  view *x = m_viewer(str);
  ck_assert_int_eq(vert_amount, x->amount_of_vertexes);
  ck_assert_int_eq(pol_amount, x->amount_of_polygons);
  for (int i = 0; i < 2; i++) {
    ck_assert_double_eq(MinMax_X[i], x->vertex->MinMax_X[i]);
    ck_assert_double_eq(MinMax_Y[i], x->vertex->MinMax_Y[i]);
    ck_assert_double_eq(MinMax_Z[i], x->vertex->MinMax_Z[i]);
  }

  free_view(x);
}
END_TEST

START_TEST(m_v_4) {
  char str[256] = "obj/pyramid.obj";
  double x1 = 0.25;
  double y1 = 1;
  double z1 = 0.25;
  view *x = m_viewer(str);
  translationX(x, 0.25);
  translationY(x, 0.5);
  translationZ(x, 0.25);
  ck_assert_double_eq(x1, x->vertex->cooridinats[0].X);
  ck_assert_double_eq(y1, x->vertex->cooridinats[0].Y);
  ck_assert_double_eq(z1, x->vertex->cooridinats[0].Z);

  free_view(x);
}
END_TEST

START_TEST(m_v_5) {
  char str[256] = "obj/cube.obj";
  double x1 = 0.75;
  double y1 = -0.25;
  double z1 = -0.25;
  view *x = m_viewer(str);
  translation(x, 0.25, 0.25, 0.25);
  ck_assert_double_eq_tol(x1, x->vertex->cooridinats[0].X, 2);
  ck_assert_double_eq_tol(y1, x->vertex->cooridinats[0].Y, 2);
  ck_assert_double_eq_tol(z1, x->vertex->cooridinats[0].Z, 2);

  free_view(x);
}
END_TEST

START_TEST(m_v_6) {
  char str[256] = "obj/heart.obj";
  int vert_amount = 5634;
  int pol_amount = 5632;
  double MinMax_X[2] = {-10.625, 10.625};
  double MinMax_Y[2] = {-4.5701, 4.5712};
  double MinMax_Z[2] = {0.0463, 19.9612};
  view *x = m_viewer(str);
  ck_assert_int_eq(vert_amount, x->amount_of_vertexes);
  ck_assert_int_eq(pol_amount, x->amount_of_polygons);
  for (int i = 0; i < 2; i++) {
    ck_assert_double_eq(MinMax_X[i], x->vertex->MinMax_X[i]);
    ck_assert_double_eq(MinMax_Y[i], x->vertex->MinMax_Y[i]);
    ck_assert_double_eq(MinMax_Z[i], x->vertex->MinMax_Z[i]);
  }

  free_view(x);
}
END_TEST

START_TEST(rotation_1) {
  char str[256] = "obj/pyramid.obj";
  double x1 = 0;
  view *x = m_viewer(str);
  rotationX(x, 10);
  ck_assert_double_eq(x1, x->vertex->cooridinats[0].X);

  free_view(x);
}
END_TEST

START_TEST(rotation_2) {
  char str[256] = "obj/pyramid.obj";
  double y1 = 0.5;
  view *x = m_viewer(str);
  rotationY(x, 10);
  ck_assert_double_eq(y1, x->vertex->cooridinats[0].Y);

  free_view(x);
}
END_TEST

START_TEST(rotation_3) {
  char str[256] = "obj/pyramid.obj";
  double z1 = 0;
  view *x = m_viewer(str);
  rotationZ(x, 10);
  ck_assert_double_eq(z1, x->vertex->cooridinats[0].Z);

  free_view(x);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, file_exist);
  tcase_add_test(tc1_1, count_size_err_2);
  tcase_add_test(tc1_1, count_size_err_3);
  tcase_add_test(tc1_1, m_v_2);
  tcase_add_test(tc1_1, m_v_3);
  tcase_add_test(tc1_1, m_v_4);
  tcase_add_test(tc1_1, m_v_5);
  tcase_add_test(tc1_1, m_v_6);
  tcase_add_test(tc1_1, rotation_1);
  tcase_add_test(tc1_1, rotation_2);
  tcase_add_test(tc1_1, rotation_3);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
