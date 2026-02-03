#ifndef GRAPH_H
#define GRAPH_H

#include <locale.h>

#include <cmath>
#include <vector>

#include "../MLP.hpp"
#include "layer.h"

namespace s21 {

class GraphPerceptron : public MLP {
 public:
  void setInput(std::vector<std::vector<double>> const &input) override { _input = input;  vector_vectorovi4 = _input; vector_for_test = _input; }

  //___________Create_And_Init_GraphPerceptron___________//
  GraphPerceptron();
  GraphPerceptron(int layer_hidden_count);
  void InitGraphPerceptron();
  void GenerateWeightNeuron();

  //_____________________Parse_File______________________//
  int LoadValuesTrain(std::string const &filename_train);
  int LoadValuesTest(std::string const &filename_test);
  // void SetStartValues(const char* filename_train, const char* filename_test);

  //________________________Train________________________//
  void CrossValidation(std::string filename_train, int k_validation);
  void EpochTrain(int epoch, std::vector<double> *report_graph);
  //  void CrossValidation(const char* filename_train, int k_validation);
  void TrainForthBack(int d) ;

  //_________________ForwardPropagation__________________//
  void ForwardPropagation();

  //_________________BackwardPropagation_________________//
  void BackwardPropagation();
  void WeightsCalculation(int l, int n, double delta_weight);

  //__________________Save_Load_Weights__________________//
  void SaveWeights(const std::string &saveFile) ;
  void LoadWeights(std::string const &filename_weights) ;

  //_______________________Predict_______________________//
  std::vector<int> Predict(std::string name_image);
  int FindMaximum();
  std::vector<int> FindMaximumPredict();

  //________________________Test_________________________//
  void Test(double test_sample);
  void TestForthBack(int d) ;
  double CalculatePercent(int k_group) ;
  void CountingSuccessfulLetters();
  void Testing(char *filename_test);

  //________________PrintGraphPerceptron_________________//
  void PrintPerceptron();

  //__________________ResizePerceptron___________________//
  void Clear();
  void ResizePerceptron(int count_hidden_layers);

  double CalculatePercentTrain() {
	double k =
		((double)_rightPredicts / (double)vector_vectorovi4.size());
	return k;
  }

 private:
  std::vector<std::vector<double>> vector_vectorovi4;
  std::vector<std::vector<double>> vector_for_test;

  size_t _expectedLetter = 0;
  int size_letter_for_epoch = 0;
  //  size_t successful_find_letter_{};
  size_t count_hidden_layers_{};
  size_t count_layers_{};
  size_t number_out_layer_{};
  std::vector<Layer> layers_;
};

}  // namespace s21
#endif  // SRC_MODEL_GRAPHPERCEPTRON_H_
