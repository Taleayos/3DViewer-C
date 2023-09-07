#ifndef SRC_3DVIEWER_H_
#define SRC_3DVIEWER_H_

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Структура, хранящая одну координату по осям X, Y, Z
 * @param X значение по оси X
 * @param Y значение по оси Y
 * @param Z значение по оси Z
 * @param vertex_number номер вершины с данными координатами
 */
typedef struct points {
  double X;
  double Y;
  double Z;
  double vertex_number;
} points;

/**
 * @brief Структура, хранящая указатель на структуру координат, минимальные и
 * максимальные значения по осям X, Y, Z
 * @param coordinate указатель на структуру координат
 * @param X_minmax массив, содержащий min и max значения точек по X
 * @param Y_minmax массив, содержащий min и max значения точек по Y
 * @param Z_minmax массив, содержащий min и max значения точек по Z
 */
typedef struct vertex {
  points *cooridinats;
  double MinMax_X[2];
  double MinMax_Y[2];
  double MinMax_Z[2];
} vertex;

/**
 * @brief Структура, хранящая указатель на последовательность полигонов
 * @param p указатель на последовательность полигонов
 * @param amount_p количество полигонов
 */
typedef struct polygon {
  int *p;
  int amount_p;
} polygon;

/**
 * @brief Главная структура, объединяющая в себе все координаты, полигоны и их
 * количество
 * @param vertex указатель на структуру вершин
 * @param poly указатель на структуру полигонов
 * @param amount_of_vertexes количество вершин
 * @param amount_of_polygons количество полигонов
 */
typedef struct view {
  vertex *vertex;
  polygon *poly;
  unsigned int amount_of_vertexes;
  unsigned int amount_of_polygons;
} view;

/**
 * @brief Функция (главная) для обработки модели из объектного файла
 * @param file_name название объектного файла
 */
view *m_viewer(char *file_name);

/**
 * @brief Функция для проверки существования файла
 * @param file_name название объектного файла
 */
int file_exists(char *file_name);

/**
 * @brief Функция для определения количества вершин и полигонов в объектном
 * файле
 * @param file_name название объектного файла
 * @param vert_amount количество вершин в файле
 * @param pol_amount количество полигонов в файле
 */
int count_size_for_init(char *file_name, int *vert_amount, int *pol_amount);

/**
 * @brief Функция для выделения памяти
 * @param vert_amount количество вершин в файле
 * @param pol_amount количество полигонов в файле
 */
view *init_view(int vert_amount, int pol_amount);

/**
 * @brief Функция для сбора и структурирования информации из объектного файла
 * @param figure указатель на структуру модели
 * @param file_name название объектного файла
 */
int parcer(view *figure, char *file_name);

/**
 * @brief Функция для освобождения места выделенной памяти
 * @param figure указатель на структуру модели
 */
void free_view(view *figure);

/**
 * @brief Функция для дополнительного выделения памяти под полигоны
 * @param p указатель на последовательность полигонов
 * @param amount_p количество полигонов
 */
int *add_memory_poly(int *p, int amount_p);

/**
 * @brief Функция для определения MIN и MAX значения координат
 * @param figure указатель на структуру модели
 * @param minmaxX значение координаты по оси X
 * @param minmaxY значение координаты по оси Y
 * @param minmaxZ значение координаты по оси Z
 */
void minmax(view *figure, double minmaxX, double minmaxY, double minmaxZ);

/**
 * @brief Функция для первоначальной централизации модели на графике
 * @param figure указатель на структуру модели
 */
void centralization(view *figure);

/**
 * @brief Функция для первоначальной инициализации MIN и MAX значений координат
 * @param figure указатель на структуру модели
 */
void init_mimax(view *figure);

/**
 * @brief Функция для перемещения модели по всем осям
 * @param figure указатель на структуру модели
 * @param newX (newY, newZ) величина сдвига по разным осям
 */
void translation(view *figure, double newX, double newY, double newZ);

/**
 * @brief Функция для перемещения модели по оси X
 * @param figure указатель на структуру модели
 * @param newX  величина сдвига
 */
void translationX(view *figure, double newX);

/**
 * @brief Функция для перемещения модели по оси Y
 * @param figure указатель на структуру модели
 * @param newY  величина сдвига
 */
void translationY(view *figure, double newY);

/**
 * @brief Функция для перемещения модели по оси Z
 * @param figure указатель на структуру модели
 * @param newZ  величина сдвига
 */
void translationZ(view *figure, double newZ);

/**
 * @brief Функция для поворота модели по оси X
 * @param figure указатель на структуру модели
 * @param rotation_angle  угол поворота
 */
void rotationX(view *figure, double rotation_angle);

/**
 * @brief Функция для поворота модели по оси Y
 * @param figure указатель на структуру модели
 * @param rotation_angle  угол поворота
 */
void rotationY(view *figure, double rotation_angle);

/**
 * @brief Функция для поворота модели по оси Z
 * @param figure указатель на структуру модели
 * @param rotation_angle  угол поворота
 */
void rotationZ(view *figure, double rotation_angle);

/**
 * @brief Функция для масштабирования модели
 * @param figure указатель на структуру модели
 * @param scale_value  коэфициент масштабирования
 */
void scaling(view *figure, double scale_value);

/**
 * @brief Функция для нахождения MAX среди разности (MAX - MIN) всех координат,
 * необходима для нахождения коэфициента масштабирования
 * @param figure указатель на структуру модели
 */
double max_for_scale(view *figure);

/**
 * @brief Функция для вычисления коэфициента масштабирования
 * @param value value - масштаб для поля 0 1, по умолчанию будет 0.5 либо 1
 * @param max  MAXIMUM среди разности (MAX - MIN) всех координат
 */
double scale_rate(double value, double max);

#endif  // SRC_3DVIEWER_H_