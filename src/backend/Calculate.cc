#include "Calculate.h"

#include <cmath>

#include "RPNConverter.h"
namespace s21 {
double Calculate::Addition(double param_1, double param_2) {
  return param_1 + param_2;
}
double Calculate::Subtraction(double param_1, double param_2) {
  return param_1 - param_2;
}
double Calculate::Multiplication(double param_1, double param_2) {
  return param_1 * param_2;
}
double Calculate::Division(double param_1, double param_2) {
  return param_1 / param_2;
}
double Calculate::Mod(double param_1, double param_2) {
  return fmod(param_1, param_2);
}
double Calculate::PowFunc(double param_1, double param_2) {
  return pow(param_1, param_2);
}
double Calculate::Sinus(double param_1) { return sin(param_1); }
double Calculate::Cosinus(double param_1) { return cos(param_1); }
double Calculate::Tangent(double param_1) { return tan(param_1); }
double Calculate::Acosinus(double param_1) { return acos(param_1); }
double Calculate::Asinus(double param_1) { return asin(param_1); }
double Calculate::Atangent(double param_1) { return atan(param_1); }
double Calculate::SquareRoot(double param_1) { return sqrt(param_1); }
double Calculate::NaturalLogariphtm(double param_1) { return log(param_1); }
double Calculate::CommonLogariphtm(double param_1) { return log10(param_1); }
double Calculate::MinusOne(double param_1) { return param_1 * (-1); }

void Calculate::NumberProcessing(int &i, std::stack<double> &stack) {
  bool flag_exit = false;
  bool flag_point = false;
  bool flag_e = false;
  std::string number;

  while ((token[i] >= '0' && token[i] <= '9') || token[i] == '.' ||
         token[i] == 'E' || token[i] == 'e' ||
         ((token[i] == '-' || token[i] == '+') &&
          (i > 0 && (token[i - 1] == 'E' || token[i - 1] == 'e')))) {
    if (token[i] == '.' && flag_point) {
      flag_exit = true;
    }
    if ((token[i] == 'e' || token[i] == 'E') && flag_e) {
      flag_exit = true;
    }
    if (token[i] == '.' && !flag_point) {
      flag_point = true;
    }
    if ((token[i] == 'e' || token[i] == 'E') && !flag_e) {
      flag_e = true;
    }
    number += token[i];
    i++;
    if (flag_exit) break;
  }
  if (flag_exit && flag_point) {
    throw std::runtime_error("Find two or more periods in number");
  }
  if (flag_exit && flag_e) {
    throw std::runtime_error("Find two or more 'e' in number");
  }
  i--;
  try {
    double temp = std::stod(number);
    stack.push(temp);
  } catch (const std::invalid_argument &) {
    throw std::runtime_error("Invalid argument");
  } catch (const std::out_of_range &) {
    throw std::runtime_error("Out of range");
  }
}

void Calculate::ValidateForEvaluate(double (*func)(double, double)) {
  if (values.size() < 2)
    throw std::runtime_error("Insufficient values for operation");
  double b = values.top();
  values.pop();
  double a = values.top();
  values.pop();
  values.push(func(a, b));
}

void Calculate::ValidateForEvaluate(double (*func)(double)) {
  if (values.empty())
    throw std::runtime_error("Insufficient values for operation");
  double a = values.top();
  values.pop();
  values.push(func(a));
}
void Calculate::PushValue(double x, int num_params) {
  if (num_params) values.push(x);
}
void Calculate::Evaluate(std::string input_expression, int num_params,
                         double x) {
  RPNConverter obj;
  obj.SetExpression(input_expression);
  obj.InfixToPostfix();
  token = obj.GetRpnExpression();
  while (!values.empty()) {
    values.pop();
  }
  std::unordered_map<char, std::function<void()>> operations = {
      {'+', [this]() { ValidateForEvaluate(Addition); }},
      {'-', [this]() { ValidateForEvaluate(Subtraction); }},
      {'*', [this]() { ValidateForEvaluate(Multiplication); }},
      {'/', [this]() { ValidateForEvaluate(Division); }},
      {'%', [this]() { ValidateForEvaluate(Mod); }},
      {'^', [this]() { ValidateForEvaluate(PowFunc); }},
      {'a', [this]() { ValidateForEvaluate(Sinus); }},
      {'b', [this]() { ValidateForEvaluate(Cosinus); }},
      {'c', [this]() { ValidateForEvaluate(Tangent); }},
      {'w', [this]() { ValidateForEvaluate(Atangent); }},
      {'y', [this]() { ValidateForEvaluate(Asinus); }},
      {'z', [this]() { ValidateForEvaluate(Acosinus); }},
      {'s', [this]() { ValidateForEvaluate(SquareRoot); }},
      {'l', [this]() { ValidateForEvaluate(CommonLogariphtm); }},
      {'n', [this]() { ValidateForEvaluate(NaturalLogariphtm); }},
      {'~', [this]() { ValidateForEvaluate(MinusOne); }},
      {'x', [this, num_params, x]() { PushValue(x, num_params); }},
      {' ', []() {}},
      {'#', []() {}}};
  for (int i = 0; token[i] != '\0'; ++i) {
    if ((token[i] >= '0' && token[i] <= '9') || token[i] == '.' ||
        token[i] == 'e' || token[i] == 'E') {
      NumberProcessing(i, values);
    } else if (operations.find(token[i]) != operations.end()) {
      operations[token[i]]();
    } else {
      throw std::runtime_error("Invalid token");
    }
    if (!values.empty() && (IsInf(values.top()) || IsNan(values.top()))) {
      throw std::runtime_error("Invalid value encountered");
    }
  }
  if (values.size() != 1) {
    throw std::runtime_error("Evaluation error");
  }
  result = values.top();
}

bool Calculate::IsInf(double value) { return std::isinf(value); }

bool Calculate::IsNan(double value) { return std::isnan(value); }
double Calculate::GetResult() { return result; }
}  // namespace s21