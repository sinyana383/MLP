#include "MLP.hpp"

namespace s21 {

int MLP::getDataFromFile(std::string const &fileName) {
  ClearInput();

  std::ifstream fin(fileName, std::ios::in);
  if (!fin.bad() && fin.is_open()) {
	std::vector<double> numbers;
	std::string line;
	while (fin >> line) {
//      numbers.reserve(inNeuronsNb);
	  char *pStart = &(line[0]);
	  char *pEnd;
	  do {
		numbers.push_back(std::strtod(pStart, &pEnd));
		pStart = pEnd + 1;
	  } while (*pEnd);
	  if (numbers.size() != 785) return error("size is not 784 pixels");
	  _input.push_back(numbers);
	  numbers.clear();
	}
  } else
	return error("couldn't open file");
  if(_input.empty())
	return error("empty file");
  return 1;
}

void MLP::ClearInput() {
  for (size_t j = 0; j < _input.size(); j++) {
	_input[j].clear();
  }
  _input.clear();
}

std::vector<double> MLP::CalculateMetrics() {
  metrics.clear();
  accuracy =
	  (double) (true_positive + true_negative) /
		  (double) (true_positive + true_negative + false_positive + false_negative);
  precision = (double) true_positive / (double) (true_positive + false_positive);
  recall = (double) true_positive / (double) (true_positive + false_negative);
  f_measure = 2 * ((precision * recall) / (precision + recall));

  _rightPredicts = 0;
  true_positive = 0;
  true_negative = 0;
  false_positive = 0;
  false_negative = 0;

  metrics.push_back(accuracy);
  metrics.push_back(precision);
  metrics.push_back(recall);
  metrics.push_back(f_measure);
  metrics.push_back(_time);
  return metrics;
}
int MLP::error(const std::string &massage) {
  std::cout << massage << std::endl;
  return -1;
}
}