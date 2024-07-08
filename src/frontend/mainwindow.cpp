#include "mainwindow.h"

#include "ui_mainwindow.h"

// #include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  flag_bracket = x_detector = 0;
  ui->setupUi(this);
  ui->label->setText("0");
  credit_flag = 0;
  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_point, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this,
          SLOT(basic_operations()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this,
          SLOT(basic_operations()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this,
          SLOT(basic_operations()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this,
          SLOT(basic_operations()));
  connect(ui->pushButton_exp, SIGNAL(clicked()), this,
          SLOT(basic_operations()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this,
          SLOT(basic_operations()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(funcs()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(funcs()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(funcs()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(funcs()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(funcs()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(funcs()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(funcs()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(funcs()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(funcs()));
  connect(ui->pushButton_bracket_open, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_bracket_close, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_plot, SIGNAL(clicked()), this, SLOT(plot()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(x()));
}

MainWindow::~MainWindow() { delete ui; }
void MainWindow::digits_numbers() {
  QPushButton *button = static_cast<QPushButton *>(sender());
  QString currentText = ui->label->text();
  std::string label_text = ui->label->text().toStdString();
  if (check_string(currentText)) {
    label_text = button->text().toStdString();
  } else {
    label_text += button->text().toStdString();
  }
  ui->label->setText(QString::fromStdString(label_text));
}

void MainWindow::basic_operations() {
  QPushButton *button = static_cast<QPushButton *>(sender());
  QString currentText = ui->label->text();
  if (check_string(currentText)) {
    ui->label->setText(button->text());
  } else {
    ui->label->setText(currentText + button->text());
  }
}

void MainWindow::on_pushButton_equal_clicked() {
  QString currentText = ui->label->text();
  QByteArray tmp_byte_array = currentText.toLatin1();
  std::string input_expression = tmp_byte_array.data();
  QString current_x = ui->line_x->text();
  bool status = false;
  double x = current_x.toDouble(&status);
  try {
    if (status) {
      value_.EvaluateInput(input_expression, 1, x);
    } else {
      value_.EvaluateInput(input_expression, 0, 0);
    }
    double result = value_.EvaluateOutput();
    ui->label->setText(QString::number(result));
  } catch (const std::exception &e) {
    ui->label->setText(QString::fromStdString(e.what()));
  }
}

void MainWindow::funcs() {
  QPushButton *button = static_cast<QPushButton *>(sender());
  QString currentText = ui->label->text();
  if (check_string(currentText))
    ui->label->setText(button->text() + "(");
  else
    ui->label->setText(currentText + button->text() + "(");
  flag_bracket++;
}

void MainWindow::on_pushButton_clear_clicked() {
  flag_bracket = 0;
  ui->label->setText(QString::fromStdString("0"));
}

void MainWindow::x() {
  QPushButton *button = static_cast<QPushButton *>(sender());
  QString currentText = ui->label->text();
  QChar lastChar = currentText.back();
  if (check_string(currentText)) {
    ui->label->setText(button->text());
    x_detector = 1;
  } else if (lastChar != 'x' && !lastChar.isDigit() && lastChar != '.' &&
             lastChar != ')' && lastChar != 'e') {
    ui->label->setText(currentText + button->text());
    x_detector = 1;
  }
}
void MainWindow::plot() {
  if (flag_plot) {
    ui->widget->graph(0)->data()->clear();
    ui->widget->replot();
  }
  QVector<double> x, y;
  h = 0.1;
  bool x_max_detector, x_min_detector, y_min_detector, y_max_detector = false;
  int x_max = ui->line_x_max_2->text().toInt(&x_max_detector);
  int x_min = ui->line_x_min->text().toInt(&x_min_detector);
  int y_max = ui->line_y_max_2->text().toInt(&y_min_detector);
  int y_min = ui->line_y_min_2->text().toInt(&y_max_detector);
  if (x_max_detector && x_min_detector && y_min_detector && y_max_detector &&
      x_min < x_max && y_min < y_max) {
    x_begin = x_min;
    x_end = x_max;
    ui->widget->xAxis->setRange(x_min, x_max);
    ui->widget->yAxis->setRange(y_min, y_max);
    X = x_begin;
    QString currentText = ui->label->text();
    QByteArray tmp_byte_array = currentText.toLatin1();
    std::string input_expression = tmp_byte_array.data();

    for (X = x_begin; X <= x_end; X += h) {
      try {
        value_.EvaluateInput(input_expression, 1, X);
        double res = value_.EvaluateOutput();
        y.push_back(res);
        x.push_back(X);
      } catch (const std::exception &e) {
        continue;
      }
    }

    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x, y);
    ui->widget->replot();
    flag_plot++;
  } else {
    ui->label->setText("Error");
  }
}

void MainWindow::on_pushButton_credit_clicked() {
  if (credit_flag == 0) credit = new credit_window(this);
  credit->show();
  credit_flag = 1;
}

void MainWindow::on_pushButton_delete_to_left_key_clicked() {
  QString currentText = ui->label->text();

  if (!check_string(currentText)) {
    static const QStringList functions = {"atan(", "asin(", "acos(",
                                          "sin(",  "cos(",  "tan(",
                                          "log(",  "ln(",   "sqrt("};

    bool functionFound = false;
    for (const auto &func : functions) {
      if (currentText.endsWith(func)) {
        currentText.chop(func.length());
        functionFound = true;
        break;
      }
    }

    if (!functionFound) {
      currentText.chop(1);
    }

    ui->label->setText(currentText);
  }
}

bool MainWindow::check_string(QString &current_text) {
  return (current_text == "0" || current_text == "Error" ||
          current_text == "Find two or more 'e' in number" ||
          current_text == "Find two or more periods in number" ||
          current_text == "Insufficient values for operation" ||
          current_text == "Invalid argument" ||
          current_text == "Out of range" || current_text == "Invalid token" ||
          current_text == "Invalid value encountered" ||
          current_text == "Evaluation error");
}

void MainWindow::on_pushButton_e_clicked() {
  QPushButton *button = static_cast<QPushButton *>(sender());
  QString currentText = ui->label->text();
  QChar lastChar = currentText.back();
  if (lastChar != 'x' && lastChar.isDigit() && lastChar != '.' &&
      lastChar != ')') {
    ui->label->setText(currentText + button->text());
    x_detector = 1;
  }
}
