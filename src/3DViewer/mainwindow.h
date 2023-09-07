#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define SETTINGS_TRAY "settings"
#define SETTINGS "settings_combo"

#define GL_SILENCE_DEPRECATION

#include <QFileDialog>
#include <QMainWindow>
#include <QOpenGLWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QSettings>
#include <QTimer>

#include "QtGifImage/src/gifimage/qgifimage.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  double scale_diff = 1.0f;
  double x_diff = 0.0f;
  double y_diff = 0.0f;
  double z_diff = 0.0f;
  int tuner_flag = 1;
  int lines_count = 0;

  QString sfileName;

 private slots:
  void get_points(char *str);

  void on_actionReally_exit_triggered();
  /**
    * Перемещает объект относительно оси OX.
    */
  void on_horizontalSlider_MoveX_valueChanged(int value);
  void on_doubleSpinBox_MoveX_valueChanged(double arg1);
  /**
   * Перемещает объект относительно оси OY.
   */
  void on_horizontalSlider_MoveY_valueChanged(int value);
  void on_doubleSpinBox_MoveY_valueChanged(double arg1);
  /**
   * Перемещает объект относительно оси OZ.
   */
  void on_horizontalSlider_MoveZ_valueChanged(int value);
  void on_doubleSpinBox_MoveZ_valueChanged(double arg1);
  /**
   * Вращает объект относительно оси OX.
   */
  void on_horizontalSlider_RotateX_valueChanged(int value);
  void on_doubleSpinBox_RotateX_valueChanged(double arg1);
  /**
    * Вращает объект относительно оси OY.
    */
  void on_horizontalSlider_RotateY_valueChanged(int value);
  void on_doubleSpinBox_RotateY_valueChanged(double arg1);
  /**
   * Вращает объект относительно оси OZ.
   */
  void on_horizontalSlider_RotateZ_valueChanged(int value);
  void on_doubleSpinBox_RotateZ_valueChanged(double arg1);
  /**
   * Позволяет увеличивать и уменьшать масштаб.
   */
  void on_horizontalSlider_Scale_valueChanged(int value);
  void on_doubleSpinBox_Scale_valueChanged(double arg1);
  /**
   * Меняет цвет фона, точек или линий (RGB-модель).
   */
  void on_back_Red_valueChanged(int value);
  void on_back_Green_valueChanged(int value);
  void on_back_Blue_valueChanged(int value);
  void on_line_Red_valueChanged(int value);
  void on_line_Green_valueChanged(int value);
  void on_line_Blue_valueChanged(int value);
  void on_point_Red_valueChanged(int value);
  void on_point_Green_valueChanged(int value);
  void on_point_Blue_valueChanged(int value);
  /**
   * Позволяет выбрать файл для отрисовки.
   */
  void on_pushButton_File_clicked();
  /**
   * Меняет тип проекции. Центральная и Параллельная.
   */
  void on_radioButton_Central_toggled(bool checked);
  void on_radioButton_Parallel_toggled(bool checked);
  void on_radioButton_Parallel_clicked();
  void on_radioButton_Central_clicked();
  /**
   * Меняет способ отображения вершин (сфера, куб, отсутствует).
   */
  void on_radioButton_Vert_No_toggled(bool checked);
  void on_radioButton_Vert_Crcl_toggled(bool checked);
  void on_radioButton_Vert_Sqr_toggled(bool checked);
  void on_radioButton_Vert_No_clicked();
  void on_radioButton_Vert_Crcl_clicked();
  void on_radioButton_Vert_Sqr_clicked();
  /**
   * Меняет тип отрисовки рёбер (сплошная линия, пунктирная линия).
   */
  void on_radioButton_Line_Solid_toggled(bool checked);
  void on_radioButton_LineStipple_toggled(bool checked);
  void on_radioButton_Line_Solid_clicked();
  void on_radioButton_LineStipple_clicked();
  /**
   * Меняет толщину рёбер.
   * @param value толщина ребра
   */
  void on_horizontalSlider_pxLine_valueChanged(int value);
  /**
    * Меняет размер вершин.
    * @param value размер вершины
    */
  void on_horizontalSlider_pxVert_valueChanged(int value);
  /**
   * Сохраняет изображение объекта в формате jpeg.
   */
  void on_pushButton_jpeg_clicked();
  /**
   * Сохраняет изображение объекта в формате bmp.
   */
  void on_pushButton_bmp_clicked();
  /**
   * Сохраняет и загружает текущие настройки.
   */
  void on_pushButton_load_clicked();
  void on_pushButton_save_clicked();
  /**
   * Записывает gif-анимацию.
   */
  void on_pushButton_gif_clicked();
  void oneGif();


private:
  Ui::MainWindow *ui;
    double previous_x;
    double previous_y;
    double previous_z;

    QSettings *settings;

    int startTime, tmpTime;
    float timePrint;
    const int gifFps = 10, gifLength = 5;
    QTimer* timer;
    QGifImage* gif;
    QString filename;
};
#endif  // MAINWINDOW_H
