#ifndef CREDIT_WINDOW_H
#define CREDIT_WINDOW_H

#include <QMainWindow>

#include "../Controller/CreditController.h"
namespace Ui {
class credit_window;
}

class credit_window : public QMainWindow {
  Q_OBJECT

 public:
  explicit credit_window(QWidget *parent = nullptr);
  ~credit_window();

 private slots:
  void on_pushButton_calculate_clicked();

 private:
  Ui::credit_window *ui;
  s21::CreditController value_;
};

#endif  // CREDIT_WINDOW_H
