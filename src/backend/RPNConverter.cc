#include "RPNConverter.h"

namespace s21 {

int RPNConverter::GetPrecedence(char op) {
  switch (op) {
    case '-':
      return 2;
    case '+':
      return 2;
    case '/':
      return 3;
    case '*':
      return 3;
    case '%':
      return 3;
    case '^':
      return 4;
    case 'a':
    case 'b':
    case 'c':
    case 'w':
    case 'y':
    case 'z':
    case 's':
    case 'l':
    case 'n':
    case '~':
    case '#':
      return 5;
    case '(':
      return 0;
    default:
      return -1;
  }
}
std::string RPNConverter::GetRpnExpression() { return rpn_expression; }
void RPNConverter::SetExpression(std::string new_expression) {
  expression = new_expression;
}

void RPNConverter::ReplaceFunctions(std::string &str, const std::string &target,
                                    const std::string &replacement,
                                    char compare_value, bool check_number) {
  size_t pos = 0;
  const size_t targetLen = target.length();
  const size_t replacementLen = replacement.length();
  while ((pos = str.find(target, pos)) != std::string::npos) {
    bool replace =
        check_number
            ? ((pos == 0 || str[pos - 1] != compare_value) &&
               (pos + targetLen < str.length() && str[pos + targetLen] == '('))
            : (pos == 0 || str[pos - 1] == '(');
    if (replace) {
      str.replace(pos, targetLen, replacement);
      pos += replacementLen;
    } else {
      pos += targetLen;
    }
  }
}

void RPNConverter::ModifiedMultiLettersFunctions() {
  const std::vector<std::tuple<std::string, std::string, char, bool>>
      replacements = {{{"atan", "w", 'a', true},
                       {"asin", "y", 'a', true},
                       {"acos", "z", 'a', true},
                       {"sin", "a", 's', true},
                       {"cos", "b", 'c', true},
                       {"tan", "c", 't', true},
                       {"sqrt", "s", 's', true},
                       {"log", "l", 'l', true},
                       {"ln", "n", 'l', true},
                       {"-", "~", '\0', false},
                       {"+", "#", '\0', false}}};

  for (const auto &replacement : replacements) {
    ReplaceFunctions(expression, std::get<0>(replacement),
                     std::get<1>(replacement), std::get<2>(replacement),
                     std::get<3>(replacement));
  }
}

void RPNConverter::InfixToPostfix() {
  ModifiedMultiLettersFunctions();
  std::stack<char> stack;
  int flag = 0;
  for (size_t i = 0; i < expression.length(); ++i) {
    char item = expression[i];
    if (std::isdigit(item) || item == '.' || item == 'e' || item == 'E' ||
        ((item == '+' || item == '-') &&
         (i > 0 && (expression[i - 1] == 'E' || expression[i - 1] == 'e') &&
          (((expression[i + 1] != '\0') &&
            std::isdigit(expression[i + 1])))))) {
      if (flag == 1) {
        rpn_expression += ' ';
        flag = 0;
      }
      rpn_expression += item;
      continue;
    } else if (item == 'x') {
      rpn_expression += ' ';
      flag = 1;
      rpn_expression += item;
      continue;
    } else if (item == '(') {
      flag = 1;
      stack.push(item);
    } else if (item == ')') {
      flag = 1;
      while (!stack.empty() && stack.top() != '(') {
        rpn_expression += stack.top();
        stack.pop();
      }
      if (!stack.empty()) stack.pop();  // Pop the '(' from the stack
    } else {
      while (!stack.empty() &&
             GetPrecedence(item) <= GetPrecedence(stack.top())) {
        if (item == '^' && stack.top() == '^') break;
        flag = 1;
        rpn_expression += stack.top();
        stack.pop();
      }
      if (GetPrecedence(item)) {
        flag = 1;
        stack.push(item);
      }
    }
    rpn_expression += ' ';
  }
  while (!stack.empty()) {
    rpn_expression += stack.top();
    stack.pop();
  }
}

}  // namespace s21
