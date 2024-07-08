#ifndef CPP3_SMARTCALC_V2_SRC_CONTROLLER_CREDITCONTROLLER_H_
#define CPP3_SMARTCALC_V2_SRC_CONTROLLER_CREDITCONTROLLER_H_

#include "../backend/Credit.h"

namespace s21 {
class CreditController {
 public:
  CreditController() = default;
  ~CreditController() = default;

  inline void CalculateAnn(double percents, double months, double sum,
                           double &percents_result, double &result,
                           double &monthly_pay) {
    value_.CalculateAnn(percents, months, sum, percents_result, result,
                        monthly_pay);
  }

  inline int CalculateDiff(double percents, double months, double sum,
                           double &percents_result, double &result,
                           std::vector<double> &monthly_payments) {
    return value_.CalculateDiff(percents, months, sum, percents_result, result,
                                monthly_payments);
  }

 private:
  CreditCalculator value_;
};
}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_SRC_CONTROLLER_CREDITCONTROLLER_H_
