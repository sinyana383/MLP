//
// Created by 1 on 13.01.2023.
//

#include "Control.hpp"

namespace s21 {

Control::Control() {
  _matrix.initModel(_hiddenLayeresNb + 2);
}
void Control::saveWeights(const std::string &fileName) {
  if (_mlpType == MATRIX)
    _matrix.exportWeightsToFile(fileName);
  else
    _graph.SaveWeights(fileName);
}
void Control::loadWeights(const std::string &fileName) {
  if (_mlpType == MATRIX)
    _matrix.importWeightsFromFile(fileName);
  else
    _graph.LoadWeights(fileName);
}

void Control::crossValidation(int k) { // не работает
  if (_mlpType == MATRIX) {
    if (_matrix.getDataFromFile(_trainFile) < 0) return;
    _matrix.genWeights();
    _matrix.crossValid(k);
  } else {
    _graph.GenerateWeightNeuron();
    _graph.CrossValidation(_trainFile, k);
  }
}

std::vector<int> Control::predict(std::vector<double> pixel) { // вернет номер буквы, скорее всего
  std::vector<std::vector<double>> newInput(1, pixel);
  if (_mlpType == MATRIX) {
    _matrix.setInput(newInput);
    _matrix.importWeightsFromFile(_weightsFile);
	return _matrix.predictLetter();
  } else {
    _graph.setInput(newInput);
    _graph.LoadWeights(_weightsFile);
    return _graph.Predict(_trainFile); // поменять функцию
  }
}

void Control::train(int epochNb, std::vector<double> &errors) {
  if (_mlpType == MATRIX) {
    if (_matrix.getDataFromFile(_trainFile) < 0) return;
    _matrix.genWeights();
    _matrix.epoch(epochNb, errors);
  } else {
    if (_graph.LoadValuesTrain(_trainFile) < 0) return;
    _graph.GenerateWeightNeuron();
    _graph.EpochTrain(epochNb, &errors);
  }
}
std::vector<double> Control::test(double part) {
  if (_mlpType == MATRIX) {
    if (_matrix.getDataFromFile(_testFile) < 0) return std::vector<double>(0);
    _matrix.test(part);
	return _matrix.CalculateMetrics();
  } else {
    if (_graph.LoadValuesTest(_testFile) < 0) return std::vector<double>(0);
    _graph.Test(part);
	return _graph.CalculateMetrics();
  }
}

void Control::setHiddenLayerNb(int nb) {
  _hiddenLayeresNb = nb;
  if (_mlpType == GRAPH)
    _graph.ResizePerceptron(nb);
  else
    _matrix.initModel(_hiddenLayeresNb + 2);
}

void Control::setMlpType(bool type) {
  _mlpType = type;
  if (_mlpType == GRAPH)
    _graph.ResizePerceptron(_hiddenLayeresNb);
  else
    _matrix.initModel(_hiddenLayeresNb + 2);
}

}



