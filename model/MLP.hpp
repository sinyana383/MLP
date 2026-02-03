#ifndef COMMON_H
#define COMMON_H

#include <atomic>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <mutex>
#include <vector>
#include <ctime>

namespace s21 {
constexpr int size_string = 1024;
constexpr double LerningStep = 0.25;
constexpr double outNeuronsNb = 26;
constexpr double hiddenNeuronsNb = 40;
constexpr double inNeuronsNb = 784;
constexpr int full_sample = 5; //? или обосновать или удалить

class MLP {
 public:
  // Input
  int getDataFromFile(std::string const &fileName);
  std::vector<std::vector<double>> GetInput() { return _input; }
  virtual void setInput(std::vector<std::vector<double>> const &input) { _input = input; }
  void ClearInput();

  // Common
  std::vector<double> CalculateMetrics();
  // static
  static double sigmoid(double value) { return 1.0 / (1.0 + exp(-value)); }
  static double df_sigmoid(double value) { return value * (1 - value); }
  static int error(const std::string &massage);

 protected:
  std::vector<std::vector<double>> _input;

  // test/train
  int _k = 0;
  int _rightPredicts = 0;

  // metrics
  int true_positive = 0;
  int true_negative = 0;
  int false_positive = 0;
  int false_negative = 0;

  double accuracy = 0;
  double f_measure = 0;
  double precision = 0;
  double recall = 0;
  double total_time = 0;

  std::vector<double> metrics{};
};

}
#endif  
