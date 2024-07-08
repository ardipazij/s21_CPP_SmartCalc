#include "credit_window.h"

#include "ui_credit_window.h"

credit_window::credit_window(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::credit_window) {
  ui->setupUi(this);
}

credit_window::~credit_window() { delete ui; }

void credit_window::on_pushButton_calculate_clicked() {
  bool percents_validate = false, sum_validate = false, months_validate = false;
  double percents = ui->lineEdit_percents->text().toDouble(&percents_validate);
  double sum = ui->lineEdit_sum->text().toDouble(&sum_validate);
  double months =
      ui->comboBox_type_date->currentText() == "Месяцев"
          ? ui->lineEdit_months->text().toDouble(&months_validate)
          : ui->lineEdit_months->text().toDouble(&months_validate) * 12;

  if (!percents_validate || !sum_validate || !months_validate ||
      percents < 0.01 || percents > 999 || months <= 0 || months > 600 ||
      sum <= 0) {
    ui->textEdit->clear();
    ui->textEdit->append("Error");
    ui->label_7_percents->setText("Error");
    ui->label_7_result->setText("Error");
    return;
  }
  double monthly_pay, percents_result, result = 0;

  if (ui->radioButton->isChecked()) {
    value_.CalculateAnn(percents, months, sum, percents_result, result,
                        monthly_pay);
    ui->textEdit->clear();
    ui->textEdit->append(QString::number(monthly_pay));
    ui->label_7_percents->setNum(percents_result);
    ui->label_7_result->setNum(result);
  } else if (ui->radioButton_2->isChecked()) {
    std::vector<double> monthly_payments;
    ui->textEdit->clear();
    int i = value_.CalculateDiff(percents, months, sum, percents_result, result,
                                 monthly_payments);
    for (int k = 0; k < i; ++k) {
      ui->textEdit->append(QString::number(k + 1) + " " +
                           QString::number(monthly_payments[k]));
    }
    ui->label_7_percents->setNum(percents_result);
    ui->label_7_result->setNum(result);
  }
}
