#ifndef CPP3_SMARTCALC_V2_0_1_SRC_BACKEND_CREDIT_H
#define CPP3_SMARTCALC_V2_0_1_SRC_BACKEND_CREDIT_H
#include <cmath>
#include <ctime>
#include <iostream>
#include <vector>

inline constexpr int YEAR = 365;
inline constexpr int MONTHS_YEAR = 12;
namespace s21 {
enum Months {
  December,
  January,
  February,
  March,
  April,
  May,
  June,
  July,
  August,
  September,
  October,
  November
};

class CreditCalculator {
 public:
  CreditCalculator() = default;
  ~CreditCalculator() = default;
  void CalculateAnn(double percents, double months, double sum,
                    double &percents_result, double &result,
                    double &monthly_pay);

  int CalculateDiff(double percents, double months, double sum,
                    double &percents_result, double &result,
                    std::vector<double> &monthly_payments);
};
}  // namespace s21
#endif  //  CPP3_SMARTCALC_V2_0_1_SRC_BACKEND_CREDIT_H