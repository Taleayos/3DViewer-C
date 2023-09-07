#include "mainwindow.h"

extern "C" {
    #include "3DViewer.h"
}
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  previous_x = 0;
  previous_y = 0;
  previous_z = 0;
}

MainWindow::~MainWindow() {
    if (ui->widget->x != NULL) {
         free_view(ui->widget->x);
    }
    delete ui;
}

void MainWindow::on_actionReally_exit_triggered() { close(); }

void MainWindow::get_points(char *str2) {
    int vert_am = 0;
    int pol_am = 0;
    if (count_size_for_init(str2, &vert_am, &pol_am) == 1) {
        QMessageBox::information(this, "Поломаный файл",
                                 "Файл имеет неверные данные");
    } else {

          ui->widget->is_open = true;
          view* x = m_viewer(str2);
          ui->widget->x = x;

          lines_count = 0;
          for (unsigned int i = 0; i < x->amount_of_polygons; i++) {
            for (int j = 0; j < x->poly[i].amount_p - 1;) {
              j++;
              lines_count += 1;
            }
          }
          ui->label_Lines_count->setText(QString::number(lines_count / 2));
          ui->label_vertex_count->setText(QString::number(x->amount_of_vertexes));
   }
}

void MainWindow::on_horizontalSlider_MoveX_valueChanged(int value) {
  ui->doubleSpinBox_MoveX->setValue(value);
  x_diff += ((value - 50) / 100);
  ui->widget->x_gl = x_diff;
  ui->widget->update();
}

void MainWindow::on_doubleSpinBox_MoveX_valueChanged(double arg1) {
  ui->horizontalSlider_MoveX->setValue(arg1);
  x_diff = ((arg1 - 50) / 100);
  ui->widget->x_gl = x_diff;
  ui->widget->update();
}

void MainWindow::on_horizontalSlider_MoveY_valueChanged(int value) {
  ui->doubleSpinBox_MoveY->setValue(value);
  y_diff += ((value - 50) / 100);
  ui->widget->y_gl = y_diff;
  ui->widget->update();
}

void MainWindow::on_doubleSpinBox_MoveY_valueChanged(double arg1) {
  ui->horizontalSlider_MoveY->setValue(arg1);
  y_diff = ((arg1 - 50) / 100);
  ui->widget->y_gl = y_diff;
  ui->widget->update();
}

void MainWindow::on_horizontalSlider_MoveZ_valueChanged(int value) {
  ui->doubleSpinBox_MoveZ->setValue(value);
  z_diff += ((value - 50) / 100);
  ui->widget->z_gl = z_diff;
  ui->widget->update();
}

void MainWindow::on_doubleSpinBox_MoveZ_valueChanged(double arg1) {
  ui->horizontalSlider_MoveZ->setValue(arg1);
  z_diff = ((arg1 - 50) / 100);
  ui->widget->z_gl = z_diff;
  ui->widget->update();
}

void MainWindow::on_horizontalSlider_RotateX_valueChanged(int value) {
  ui->doubleSpinBox_RotateX->setValue(value);
  ui->widget->update();
}

void MainWindow::on_doubleSpinBox_RotateX_valueChanged(double arg1) {
  if (arg1 > 100) {
    arg1 = 100;
    ui->doubleSpinBox_RotateX->setValue(arg1);
  } else if (arg1 < 0) {
    arg1 = 0;
    ui->doubleSpinBox_RotateX->setValue(arg1);
  }
  ui->horizontalSlider_RotateX->setValue(arg1);
  double radiant = (previous_x - arg1) * (M_PI / 25);
  previous_x = arg1;
  ui->doubleSpinBox_RotateX->setValue(arg1);
  rotationX(ui->widget->x, radiant);
  ui->widget->update();
}

void MainWindow::on_horizontalSlider_RotateY_valueChanged(int value) {
  ui->doubleSpinBox_RotateY->setValue(value);
  ui->widget->update();
}

void MainWindow::on_doubleSpinBox_RotateY_valueChanged(double arg1) {
  if (arg1 > 100) {
    arg1 = 100;
    ui->doubleSpinBox_RotateY->setValue(arg1);
  } else if (arg1 < 0) {
    arg1 = 0;
    ui->doubleSpinBox_RotateY->setValue(arg1);
  }
  ui->horizontalSlider_RotateY->setValue(arg1);
  double radiant = (previous_y - arg1) * (M_PI / 25);
  previous_y = arg1;
  ui->doubleSpinBox_RotateY->setValue(arg1);
  rotationY(ui->widget->x, radiant);
  ui->widget->update();
}

void MainWindow::on_horizontalSlider_RotateZ_valueChanged(int value) {
  ui->doubleSpinBox_RotateZ->setValue(value);
  ui->widget->update();
}

void MainWindow::on_doubleSpinBox_RotateZ_valueChanged(double arg1) {
  if (arg1 > 100) {
    arg1 = 100;
    ui->doubleSpinBox_RotateZ->setValue(arg1);
  } else if (arg1 < 0) {
    arg1 = 0;
    ui->doubleSpinBox_RotateZ->setValue(arg1);
  }
  ui->horizontalSlider_RotateZ->setValue(arg1);
  double radiant = (arg1 - previous_z) * (M_PI / 25);
  previous_z = arg1;
  ui->doubleSpinBox_RotateZ->setValue(arg1);
  rotationZ(ui->widget->x, radiant);
  ui->widget->update();
}

void MainWindow::on_horizontalSlider_Scale_valueChanged(int value) {
  ui->doubleSpinBox_Scale->setValue(value);
  scale_diff += ((value - 50) / 100);
  ui->widget->scale_gl = 1 + scale_diff;
  ui->widget->update();
}

void MainWindow::on_doubleSpinBox_Scale_valueChanged(double arg1) {
  ui->horizontalSlider_Scale->setValue(arg1);
  scale_diff = ((arg1 - 50) / 100);
  ui->widget->scale_gl = 1 + scale_diff;
  ui->widget->update();
}

void MainWindow::on_back_Red_valueChanged(int value) {
  ui->widget->r_back = value / 255.0f;
  ui->widget->update();
}

void MainWindow::on_back_Green_valueChanged(int value) {
  ui->widget->g_back = value / 255.0f;
  ui->widget->update();
}

void MainWindow::on_back_Blue_valueChanged(int value) {
  ui->widget->b_back = value / 255.0f;
  ui->widget->update();
}

void MainWindow::on_line_Red_valueChanged(int value) {
  ui->widget->r = value / 255.0f;
  ui->widget->update();
}

void MainWindow::on_line_Green_valueChanged(int value) {
  ui->widget->g = value / 255.0f;
  ui->widget->update();
}

void MainWindow::on_line_Blue_valueChanged(int value) {
  ui->widget->b = value / 255.0f;
  ui->widget->update();
}

void MainWindow::on_point_Red_valueChanged(int value) {
  ui->widget->r_point = value / 255.0f;
  ui->widget->update();
}

void MainWindow::on_point_Green_valueChanged(int value) {
  ui->widget->g_point = value / 255.0f;
  ui->widget->update();
}

void MainWindow::on_point_Blue_valueChanged(int value) {
  ui->widget->b_point = value / 255.0f;
  ui->widget->update();
}

void MainWindow::on_pushButton_File_clicked() {
    ui->widget->clearFocus();
  QString str;
  str = QFileDialog::getOpenFileName(this, "Choose OBJ file", "/Users/",
                                     "OBJ Files (*.obj);; All Files (*.*)");
  ui->label->setText(str.split('/').last());
  QByteArray ba = str.toLocal8Bit();
  char *str2 = ba.data();
  get_points(str2);
}

void MainWindow::on_radioButton_Central_toggled(bool checked) {
  if (checked == true) ui->widget->projection = true;
}

void MainWindow::on_radioButton_Parallel_toggled(bool checked) {
  if (checked == true) ui->widget->projection = false;
}

void MainWindow::on_radioButton_Central_clicked() { ui->widget->update(); }
void MainWindow::on_radioButton_Parallel_clicked() { ui->widget->update(); }

void MainWindow::on_radioButton_Vert_No_toggled(bool checked) {
  if (checked == true) ui->widget->vertex_type = 0;
}

void MainWindow::on_radioButton_Vert_Crcl_toggled(bool checked) {
  if (checked == true) ui->widget->vertex_type = 1;
}

void MainWindow::on_radioButton_Vert_Sqr_toggled(bool checked) {
  if (checked == true) ui->widget->vertex_type = 2;
}

void MainWindow::on_radioButton_Vert_No_clicked() { ui->widget->update(); }
void MainWindow::on_radioButton_Vert_Crcl_clicked() { ui->widget->update(); }
void MainWindow::on_radioButton_Vert_Sqr_clicked() { ui->widget->update(); }

void MainWindow::on_radioButton_Line_Solid_toggled(bool checked) {
  if (checked == true) ui->widget->line_type = 0;
}

void MainWindow::on_radioButton_LineStipple_toggled(bool checked) {
  if (checked == true) ui->widget->line_type = 1;
}

void MainWindow::on_radioButton_Line_Solid_clicked() { ui->widget->update(); }
void MainWindow::on_radioButton_LineStipple_clicked() { ui->widget->update(); }

void MainWindow::on_horizontalSlider_pxLine_valueChanged(int value) {
    ui->widget->line_width = value;
    ui->horizontalSlider_pxLine->setValue(value);
    ui->widget->update();
}

void MainWindow::on_horizontalSlider_pxVert_valueChanged(int value) {
    ui->widget->vertex_size = value;
    ui->horizontalSlider_pxVert->setValue(value);
    ui->widget->update();
}

void MainWindow::on_pushButton_jpeg_clicked()
{
    QPixmap viewer = ui->widget->grab();
    QString Path = QFileDialog::getSaveFileName(this, NULL, NULL, "jpeg(*.jpeg)");
    if (!Path.isNull()) viewer.save(Path);
}

void MainWindow::on_pushButton_bmp_clicked()
{
    QPixmap viewer = ui->widget->grab();
     QString Path = QFileDialog::getSaveFileName(this, NULL, NULL, "bmp(*.bmp)");
     if (!Path.isNull()) viewer.save(Path);
}

void MainWindow::on_pushButton_save_clicked()  {
  QSettings settings("settings_Viewer", "Conf");
  settings.setValue("X_translation", ui->doubleSpinBox_MoveX->value());
  settings.setValue("Y_translation", ui->doubleSpinBox_MoveY->value());
  settings.setValue("Z_translation", ui->doubleSpinBox_MoveZ->value());
  settings.setValue("X_rotation", ui->doubleSpinBox_RotateX->value());
  settings.setValue("Y_rotation", ui->doubleSpinBox_RotateY->value());
  settings.setValue("Z_rotation", ui->doubleSpinBox_RotateZ->value());
  settings.setValue("Scale", ui->doubleSpinBox_Scale->value());
  settings.setValue("Edge_size", ui->horizontalSlider_pxLine->value());
  settings.setValue("Vertex_size", ui->horizontalSlider_pxVert->value());
  settings.setValue("Dotten", ui->radioButton_Vert_No->isChecked());
  settings.setValue("Dotten2", ui->radioButton_Vert_Crcl->isChecked());
  settings.setValue("Dotten3", ui->radioButton_Vert_Sqr->isChecked());
  settings.setValue("Perspective", ui->radioButton_Parallel->isChecked());
  settings.setValue("Line", ui->radioButton_LineStipple->isChecked());
  settings.setValue("back_color", ui->back_Red->value());
  settings.setValue("back_color1", ui->back_Green->value());
  settings.setValue("back_color2", ui->back_Blue->value());
  settings.setValue("line_color", ui->line_Red->value());
  settings.setValue("line_color1", ui->line_Green->value());
  settings.setValue("line_color2", ui->line_Blue->value());
  settings.setValue("point_color", ui->point_Red->value());
  settings.setValue("point_color1", ui->point_Green->value());
  settings.setValue("point_color2", ui->point_Blue->value());
  settings.setValue("text", ui->label->text());
  QMessageBox::information(this, "Сохранение настроек",
                           "Сохранение настроек выполнено успешно");
}

void MainWindow::on_pushButton_load_clicked() {
  QSettings settings("settings_Viewer", "Conf");
  ui->label->setText(settings.value("text", "").toString());
  filename = ui->label->text();
  ui->gif_label->setText(filename.split('/').last());
  ui->doubleSpinBox_MoveX->setValue(settings.value("X_translation", 0).toDouble());
  ui->doubleSpinBox_MoveY->setValue(settings.value("Y_translation", 0).toDouble());
  ui->doubleSpinBox_MoveZ->setValue(settings.value("Z_translation", 0).toDouble());
  ui->doubleSpinBox_RotateX->setValue(settings.value("X_rotation", 0).toDouble());
  ui->doubleSpinBox_RotateY->setValue(settings.value("Y_rotation", 0).toDouble());
  ui->doubleSpinBox_RotateZ->setValue(settings.value("Z_rotation", 0).toDouble());
  ui->doubleSpinBox_Scale->setValue(settings.value("Scale", 0).toDouble());
  ui->horizontalSlider_pxLine->setValue(settings.value("Edge_size", 0).toInt());
  ui->horizontalSlider_pxVert->setValue(settings.value("Vertex_size", 0).toInt());
  ui->radioButton_Vert_No->setChecked(settings.value("Dotten").toBool());
  ui->radioButton_Vert_Crcl->setChecked(settings.value("Dotten2").toBool());
  ui->radioButton_Vert_Sqr->setChecked(settings.value("Dotten3").toBool());

  ui->radioButton_Parallel->setChecked(settings.value("Perspective").toBool());
  if (settings.value("Perspective") == 1){ ui->radioButton_Parallel->isChecked();
  on_radioButton_Parallel_clicked();}

  ui->radioButton_LineStipple->setChecked(settings.value("Line").toBool());
  if (settings.value("Line") == 1){ ui->radioButton_LineStipple->isChecked();
  on_radioButton_LineStipple_clicked();}

  ui->back_Red->setValue(settings.value("back_color").toInt());
  ui->back_Green->setValue(settings.value("back_color1").toInt());
  ui->back_Blue->setValue(settings.value("back_color2").toInt());

  ui->line_Red->setValue(settings.value("line_color").toInt());
  ui->line_Green->setValue(settings.value("line_color1").toInt());
  ui->line_Blue->setValue(settings.value("line_color2").toInt());

  ui->point_Red->setValue(settings.value("point_color").toInt());
  ui->point_Green->setValue(settings.value("point_color1").toInt());
  ui->point_Blue->setValue(settings.value("point_color2").toInt());

}

void MainWindow::on_pushButton_gif_clicked() {
  sfileName = QFileDialog::getSaveFileName(this, "Сохранить файл", nullptr,
                                           "Image(*.gif)");
  if (sfileName.isNull()) return;
  gif = new QGifImage;
  gif->setDefaultDelay(1000 / gifFps);
  startTime = 0, tmpTime = 1000 / gifFps;
  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(oneGif()));
  timer->start(1000 / gifFps);
  this->ui->pushButton_gif->setEnabled(false);
  this->ui->gif_label->setText("идет запись GIF файла");
}

void MainWindow::oneGif() {
  if (startTime == tmpTime) {
    QPixmap screenGIF(this->ui->widget->size());
    this->ui->widget->render(&screenGIF);

    QImage image = screenGIF.toImage();
    image=image.scaled(640, 480, Qt::KeepAspectRatio);
    image=image.copy((image.width()-640)/2, 0, 640, 480);
    gif->addFrame(image, 1000 / gifFps);
    timePrint = (float)startTime / 1e3;
    tmpTime += 1000 / gifFps;
  }
  if (startTime == 1000 * gifLength) {
    gif->save(sfileName);
    timer->stop();
    disconnect(timer, SIGNAL(timeout()), this, SLOT(oneGif()));
    delete gif;
    delete timer;
    this->ui->pushButton_gif->setEnabled(true);
    this->ui->gif_label->setText("GIF файл записан");
  }
  startTime += 1000 / gifFps;
}
