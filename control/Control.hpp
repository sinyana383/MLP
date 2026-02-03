//
// Created by 1 on 13.01.2023.
//

#ifndef CPP7_MLP_SRC_CONTROL_HPP_
#define CPP7_MLP_SRC_CONTROL_HPP_

#include <string>
#include <vector>

#include "mainwindow.h"
#include "../model/Matrix/Matrix.hpp"
#include "../model/Graph/graph.h"

#define DEFAULTTRAIN "/Users/ddurrand/Desktop/untitled3/emnist-letters-train.csv"
#define DEFAULTTEST "/Users/ddurrand/Desktop/untitled3/emnist-letters-test.csv"
#define DEFAULTWEIGHTS "/Users/ddurrand/Desktop/untitled3/weights.w"
#define MATRIX false
#define GRAPH true

namespace s21 {
class Control {
 private:
    // replace to MLP class
  s21::Matrix 			_matrix;
  s21::GraphPerceptron 	_graph;
  MainWindow w;

  bool _mlpType = MATRIX; // должно отображ у пользователя
  int _hiddenLayeresNb = 2;

  std::vector<double> _errors;
  std::string _trainFile = DEFAULTTRAIN;
  std::string _testFile = DEFAULTTEST;
  std::string _weightsFile = DEFAULTWEIGHTS;
 public:
  Control();
  void showWindow() {w.show();}
  void setMlpType(bool type);
  void setHiddenLayerNb(int nb);
  void setTrainFile(std::string const &trainFile) { _trainFile = trainFile; }
  void setTestFile(std::string const &testFile) { _testFile = testFile; }

  void saveWeights(std::string const &fileName);
  void loadWeights(std::string const &fileName);

  std::vector<int> predict(std::vector<double> pixel);
  void crossValidation(int k);
  void train(int epochNb, std::vector<double> &errors); // ошибки
  std::vector<double> test(double part); // Метрики
};
}

#endif //CPP7_MLP_SRC_CONTROL_HPP_
