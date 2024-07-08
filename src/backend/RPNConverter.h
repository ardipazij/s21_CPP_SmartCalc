//
// Created by Brett Roscoe on 5/8/24.
//

#ifndef CPP3_SMARTCALC_V2_0_1_SRC_BACKEND_RPNCONVERTER_H
#define CPP3_SMARTCALC_V2_0_1_SRC_BACKEND_RPNCONVERTER_H

#include <cctype>
#include <iostream>
#include <stack>
#include <string>
#include <tuple>
#include <vector>

namespace s21 {
class RPNConverter {
 public:
  void InfixToPostfix();
  void SetExpression(std::string new_expression);
  std::string GetRpnExpression();

 private:
  int GetPrecedence(char op);

  void ModifiedMultiLettersFunctions();

  void ReplaceFunctions(std::string &str, const std::string &target,
                        const std::string &replacement, char compare_value,
                        bool check_number);

 private:
  std::string expression;
  std::string rpn_expression;
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_1_RPNCONVERTER_H