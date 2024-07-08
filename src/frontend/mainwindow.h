#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

#include "../Controller/CalcController.h"
#include "credit_window.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  int flag_bracket, flag_plot;
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void digits_numbers();
  void basic_operations();
  void on_pushButton_equal_clicked();
  void funcs();
  void on_pushButton_delete_to_left_key_clicked();
  void plot();
  void on_pushButton_clear_clicked();
  void x();
  void on_pushButton_credit_clicked();

  void on_pushButton_e_clicked();

 private:
  bool check_string(QString &current_text);
  Ui::MainWindow *ui;
  credit_window *credit;
  double x_begin, x_end, h, X;
  int N;
  int x_detector;
  int credit_flag;
  s21::CalcController value_;
};
#endif  // MAINWINDOW_H
