#include "../Controller/CalcController.h"
#include "../Controller/CreditController.h"
#include <gtest/gtest.h>

#include <gtest/gtest.h>
#include <stdexcept>
#include "../backend/Calculate.h"
#include "../backend/Calculate.cc"
#include "../backend/Credit.cc"
#include "../backend/Credit.h"
#include "../backend/RPNConverter.h"
#include "../backend/RPNConverter.cc"
namespace s21 {

TEST(CalcControllerTest, EvaluateInputBasicMath) {
  CalcController calc;
  calc.EvaluateInput("2+2", 0, 0.0);
  EXPECT_EQ(calc.EvaluateOutput(), 4.0);
}
TEST(CalcControllerTest, EvaluateInputBasicMath_2) {
  CalcController calc;
  calc.EvaluateInput("2-2", 0, 0.0);
  EXPECT_EQ(calc.EvaluateOutput(), 0.0);
}
TEST(CalcControllerTest, EvaluateInputBasicMath_3) {
  CalcController calc;
  calc.EvaluateInput("2/2", 0, 0.0);
  EXPECT_EQ(calc.EvaluateOutput(), 1.0);
}
TEST(CalcControllerTest, EvaluateInputBasicMath_4) {
  CalcController calc;
  calc.EvaluateInput("2*2", 0, 0.0);
  EXPECT_EQ(calc.EvaluateOutput(), 4.0);
}
TEST(CalcControllerTest, EvaluateInputBasicMath_5) {
  CalcController calc;
  calc.EvaluateInput("3%2", 0, 0.0);
  EXPECT_EQ(calc.EvaluateOutput(), 1.0);
}
TEST(CalcControllerTest, EvaluateInputBasicMath_6) {
  CalcController calc;
  calc.EvaluateInput("(2+2)*2", 0, 0.0);
  EXPECT_EQ(calc.EvaluateOutput(), 8.0);
}
TEST(CalcControllerTest, EvaluateInputBasicMath_7) {
  CalcController calc;
  calc.EvaluateInput("3+4*2/(1-5)^2^3", 0, 0.0);
  EXPECT_NEAR(calc.EvaluateOutput(), 3.0, 1e-2);;
}
TEST(CalcControllerTest, EvaluateInputBasicMath_8) {
  CalcController calc;
  calc.EvaluateInput("2+2+(-2)", 0, 0.0);
  EXPECT_EQ(calc.EvaluateOutput(), 2.0);
}
TEST(CalcControllerTest, EvaluateInputWithExponentialNotation_2) {
  CalcController calc;
  calc.EvaluateInput("2e+2", 0, 0.0);
  EXPECT_EQ(calc.EvaluateOutput(), 200.0);
}

TEST(CalcControllerTest, EvaluateInputDoublePow) {
  CalcController calc;
  calc.EvaluateInput("2^2^3", 0, 0.0);
  EXPECT_EQ(calc.EvaluateOutput(), 256.0);
}
TEST(CalcControllerTest, EvaluateInputDoublePoint) {
  CalcController calc;
  EXPECT_THROW(calc.EvaluateInput("2..2", 0, 0.0), std::runtime_error);
}
TEST(CalcControllerTest, EvaluateInputDoubleExponent) {
  CalcController calc;
  EXPECT_THROW(calc.EvaluateInput("2ee2", 0, 0.0), std::runtime_error);
}
TEST(CalcControllerTest, EvaluateInputFunctionWithoutArgument) {
  CalcController calc;
  EXPECT_THROW(calc.EvaluateInput("sin()", 0, 0.0), std::runtime_error);
}
TEST(CalcControllerTest, EvaluateInputOperatorWithoutArgument) {
  CalcController calc;
  EXPECT_THROW(calc.EvaluateInput("2+", 0, 0.0), std::runtime_error);
}
TEST(CalcControllerTest, EvaluateInputOutOfRange) {
  CalcController calc;
  EXPECT_THROW(calc.EvaluateInput("24398572890574985742985742389758247508943734569236457263745967923475843758975^85878867895789437685476875867548097689347658", 0, 0.0), std::runtime_error);
}
TEST(CalcControllerTest, EvaluateInputInvalidArgument) {
  CalcController calc;
  EXPECT_THROW(calc.EvaluateInput("2.4e0000.2", 0, 0.0), std::runtime_error);
}
TEST(CalcControllerTest, EvaluateInputInvalidToken) {
  CalcController calc;
  EXPECT_THROW(calc.EvaluateInput("ахахахахахахахахахах", 0, 0.0), std::runtime_error);
}
TEST(CalcControllerTest, EvaluateInputSinglePow) {
  CalcController calc;
  calc.EvaluateInput("2^2", 0, 0.0);
  EXPECT_EQ(calc.EvaluateOutput(), 4.0);
}

TEST(CalcControllerTest, EvaluateInputXVariavle) {
  CalcController calc;
  calc.EvaluateInput("5+x", 1, 5);
  EXPECT_EQ(calc.EvaluateOutput(), 10.0);
}

TEST(CalcControllerTest, EvaluateInputWithTrigFunctions) {
  CalcController calc;
  calc.EvaluateInput("sin(0)", 0, 0.0);
  EXPECT_EQ(calc.EvaluateOutput(), 0.0);

  calc.EvaluateInput("cos(0)", 0, 0.0);
  EXPECT_EQ(calc.EvaluateOutput(), 1.0);

  calc.EvaluateInput("tan(0)", 0, 0.0);
  EXPECT_EQ(calc.EvaluateOutput(), 0.0);
}

TEST(CalcControllerTest, EvaluateInputWithUpperTrigFunctions) {
  CalcController calc;
  calc.EvaluateInput("acos(0)", 0, 0.0);
  EXPECT_NEAR(calc.EvaluateOutput(), 1.57, 1e-2);

  calc.EvaluateInput("asin(0)", 0, 0.0);
  EXPECT_EQ(calc.EvaluateOutput(), 0.0);

  calc.EvaluateInput("atan(0)", 0, 0.0);
  EXPECT_EQ(calc.EvaluateOutput(), 0.0);
}

TEST(CalcControllerTest, EvaluateInputWithLogFunctions) {
  CalcController calc;
  calc.EvaluateInput("log(10)", 0, 0.0); // Common logarithm
  EXPECT_EQ(calc.EvaluateOutput(), 1.0);

  calc.EvaluateInput("ln(2.71)", 0,
                     0.0); // Natural logarithm, assuming e = 2.71828...
  EXPECT_NEAR(calc.EvaluateOutput(), 1.0, 1e-2);
}

TEST(CalcControllerTest, EvaluateInputWithExponentialAndRoot) {
  CalcController calc;
  calc.EvaluateInput("2^3", 0, 0.0);
  EXPECT_EQ(calc.EvaluateOutput(), 8.0);

  calc.EvaluateInput("sqrt(16)", 0, 0.0);
  EXPECT_EQ(calc.EvaluateOutput(), 4.0);
}

TEST(CalcControllerTest, EvaluateInputWithExponentialNotation) {
  CalcController calc;
  calc.EvaluateInput("1e2+3", 0, 0.0);
  EXPECT_EQ(calc.EvaluateOutput(), 103.0);
}

TEST(CreditControllerTest, CalculateAnnTest) {
  CreditController credit;
  double percents = 5.0;
  double months = 12;
  double sum = 10000;
  double percents_result = 0;
  double result = 0;
  double monthly_pay = 0;

  credit.CalculateAnn(percents, months, sum, percents_result, result,
                       monthly_pay);

  // Замените ожидания на корректные значения
  EXPECT_NEAR(percents_result, 272.898, 1e-2);
  EXPECT_NEAR(result, 10272.9, 1e-2);
  EXPECT_NEAR(monthly_pay, 856.075, 1e-2);
}

TEST(CreditControllerTest, CalculateDiffTest) {
  CreditController credit;
  double percents = 5.0;
  double months = 12;
  double sum = 10000;
  double percents_result = 0;
  double result = 0;
  std::vector<double> monthly_payments;

  int status = credit.CalculateDiff(percents, months, sum, percents_result,
                                     result, monthly_payments);

  EXPECT_EQ(status, 12);
  EXPECT_NEAR(percents_result, 271.804, 1e-2);
  EXPECT_NEAR(result, 10271.8, 1e-2);

  // Проверка количества ежемесячных платежей
  EXPECT_EQ(monthly_payments.size(), months);

  // Примерная проверка первого и последнего платежей
  EXPECT_NEAR(monthly_payments[0], 875.799, 1e-2);
  EXPECT_NEAR(monthly_payments[months - 1], 836.758, 1e-2);
}
} // namespace s21
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  try {
    return RUN_ALL_TESTS();
  } catch (const std::runtime_error &e) {
    std::cerr << "Runtime error: " << e.what() << std::endl;
    return 1;
  }
}