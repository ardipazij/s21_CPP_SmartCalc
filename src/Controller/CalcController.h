#ifndef CPP3_SMARTCALC_V2_SRC_CONTROLLER_CALCCONTROLLER_H_
#define CPP3_SMARTCALC_V2_SRC_CONTROLLER_CALCCONTROLLER_H_

#include "../backend/Calculate.h"

namespace s21 {
class CalcController {
 public:
  CalcController() = default;
  ~CalcController() = default;

  inline void EvaluateInput(std::string input_expression, int num_params,
                            double x) {
    value_.Evaluate(input_expression, num_params, x);
  }

  inline double EvaluateOutput() { return value_.GetResult(); }

 private:
  Calculate value_;
};
}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_SRC_CONTROLLER_CALCCONTROLLER_H_
