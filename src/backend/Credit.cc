#include "Credit.h"
namespace s21 {
void CreditCalculator::CalculateAnn(double percents, double months, double sum,
                                    double &percents_result, double &result,
                                    double &monthly_pay) {
  double monthly_percent = percents / 12. / 100.;
  monthly_pay = sum * monthly_percent * pow(1 + monthly_percent, months) /
                (pow(1 + monthly_percent, months) - 1);
  result = monthly_pay * months;
  percents_result = result - sum;
}

int CreditCalculator::CalculateDiff(double percents, double months, double sum,
                                    double &percents_result, double &result,
                                    std::vector<double> &monthly_payments) {
  double monthly_credit_payment = sum / months;
  int current_days;
  time_t current_time;
  struct tm *time_info;
  time(&current_time);
  time_info = localtime(&current_time);
  int current_month_time = time_info->tm_mon + 1;
  int current_year = time_info->tm_year + 1900;

  for (int i = 0; i < months; ++i) {
    int current_month = current_month_time + i;
    if (current_month % MONTHS_YEAR == January)
      current_days = 31;
    else if (current_month % MONTHS_YEAR == February) {
      if (current_year % 4 != 0 && current_year % 100 != 0) {
        current_days = 28;
      } else
        current_days = 29;
    } else if (current_month % MONTHS_YEAR == March)
      current_days = 31;
    else if (current_month % MONTHS_YEAR == April)
      current_days = 30;
    else if (current_month % MONTHS_YEAR == May)
      current_days = 31;
    else if (current_month % MONTHS_YEAR == June)
      current_days = 30;
    else if (current_month % MONTHS_YEAR == July)
      current_days = 31;
    else if (current_month % MONTHS_YEAR == August)
      current_days = 31;
    else if (current_month % MONTHS_YEAR == September)
      current_days = 30;
    else if (current_month % MONTHS_YEAR == October)
      current_days = 31;
    else if (current_month % MONTHS_YEAR == November)
      current_days = 30;
    else if (current_month % MONTHS_YEAR == December) {
      current_days = 31;
      current_year++;
    }
    double percent_sum = (sum * (percents / 100) * current_days) / YEAR;
    sum -= monthly_credit_payment;
    result += percent_sum + monthly_credit_payment;
    percents_result += percent_sum;
    monthly_payments.push_back(percent_sum + monthly_credit_payment);
  }
  return months;
}
};  // namespace s21
