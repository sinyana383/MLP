#include "graph.h"

namespace s21 
{

GraphPerceptron::GraphPerceptron() : GraphPerceptron(2) {}

GraphPerceptron::GraphPerceptron(int count_hidden_layers) : count_hidden_layers_(count_hidden_layers) 
{
  count_layers_ = count_hidden_layers_ + 2;
  number_out_layer_ = count_layers_ - 1;
  layers_.resize(count_layers_);
  InitGraphPerceptron();
}

void GraphPerceptron::InitGraphPerceptron() 
{
  layers_[0].SetCountNeuron(inNeuronsNb);

  layers_[1].SetCountNeuron(hiddenNeuronsNb);
  layers_[1].SetCountWeightNeuron(inNeuronsNb);

  for (size_t i = 2; i < number_out_layer_; i++) 
  {
    layers_[i].SetCountNeuron(hiddenNeuronsNb);
    layers_[i].SetCountWeightNeuron(hiddenNeuronsNb);
  }
  layers_[number_out_layer_].SetCountNeuron(outNeuronsNb);
  layers_[number_out_layer_].SetCountWeightNeuron(hiddenNeuronsNb);
}

void GraphPerceptron::GenerateWeightNeuron() 
{
  for (size_t i = 1; i < count_layers_; i++) 
    layers_[i].SetWeightsNeuron();
}

int GraphPerceptron::LoadValuesTrain(std::string const &filename_train)
{
  if (getDataFromFile(filename_train) < 0) return -1;
  vector_vectorovi4 = GetInput();
  return 1;
}

int GraphPerceptron::LoadValuesTest(std::string const &filename_test)
{
  if (getDataFromFile(filename_test) < 0) return -1;
  vector_for_test = GetInput();
  return 1;
}

void GraphPerceptron::EpochTrain(int epoch, std::vector<double> *report_graph) 
{
  size_letter_for_epoch = epoch * (int)vector_vectorovi4.size();
  for (int k = 0; k < epoch; k++) 
  {
    _rightPredicts = 0;
    for (size_t d = 0; d < vector_vectorovi4.size(); d++)
    {
      TrainForthBack(d);
    }
    report_graph->push_back(100 - (CalculatePercentTrain() * 100));
  }
}

void GraphPerceptron::TrainForthBack(int d) 
{
  _expectedLetter = vector_vectorovi4[d][0] - 1;
  for (size_t i = 1; i < vector_vectorovi4[d].size(); i++) 
    layers_[0].SetNeuronValue(i, vector_vectorovi4[d][i] / 255);
  ForwardPropagation();
  CountingSuccessfulLetters();
  BackwardPropagation();
}

void GraphPerceptron::ForwardPropagation() 
{
  for (size_t l = 1; l < count_layers_; l++)
    {
     for (size_t n = 0; n < layers_[l].GetCountNeuron(); n++) 
     {
      double sum = 0;
      for (size_t w = 0; w < layers_[l - 1].GetCountNeuron(); w++) 
        sum += layers_[l - 1].GetNeuronValue(w) * layers_[l].GetWeightNeuron(n, w);
      layers_[l].SetNeuronValue(n + 1, sigmoid(sum));
    }
  }
}

void GraphPerceptron::BackwardPropagation() 
{
  for (size_t l = number_out_layer_; l != 0; l--)
  {
    for (size_t n = 0; n < layers_[l].GetCountNeuron(); n++) 
    {
      double error = 0;
      if (l == number_out_layer_) 
      {
        if (n == _expectedLetter)
          error = layers_[number_out_layer_].GetNeuronValue(n) - 1;
        else 
          error = layers_[number_out_layer_].GetNeuronValue(n);
      } 
      else 
      {
        for (size_t n_r = 0; n_r < layers_[l + 1].GetCountNeuron(); n_r++)
          error += layers_[l + 1].GetNeuronDelta(n_r) * layers_[l + 1].GetWeightNeuron(n_r, n);
      }
      layers_[l].SetNeuronError(n, error);

      double delta_weight = error * df_sigmoid(layers_[l].GetNeuronValue(n));

      layers_[l].SetNeuronDeltaWeight(n, delta_weight);
      if (std::abs(delta_weight) - 0.00001 > 0)
        WeightsCalculation(l, n, delta_weight);
    }
  }
}

void GraphPerceptron::WeightsCalculation(int l, int n, double delta_weight) 
{
  for (size_t w = 0; w < layers_[l - 1].GetCountNeuron(); w++) 
  {
    double new_weight = layers_[l].GetWeightNeuron(n, w) - layers_[l - 1].GetNeuronValue(w) * delta_weight * LerningStep;
    layers_[l].SetNeuronWeights(n, w, new_weight);
  }
}


void GraphPerceptron::SaveWeights(const std::string &saveFile)
{
  std::fstream outweights;

  outweights.open(saveFile, std::ios::out);

  if (!outweights) 
  {
    std::cerr << "file couldn't be opened ";
    exit(1);
  }

  for (size_t l = 1; l < count_layers_; l++) 
  {
    for (size_t n = 0; n < layers_[l].GetCountNeuron(); n++) 
    {
      for (size_t n_w = 0; n_w < layers_[l - 1].GetCountNeuron(); n_w++) 
        outweights << layers_[l].GetWeightNeuron(n, n_w) << ",";
    }
  }
  outweights.close();
}

void GraphPerceptron::LoadWeights(std::string const &filename_weights)
{
  std::ifstream inweights(filename_weights, std::ios::in);
  if (!inweights.bad() && inweights.is_open())
  {
    std::string line;

    while (inweights >> line) 
    {
      size_t i = 0;
      char *ptrEnd;

      if (isdigit(line[i]) || line[i] == '-')
      {
        for (size_t l = 1; l < count_layers_; l++) 
        {
          for (size_t n = 0; n < layers_[l].GetCountNeuron(); n++) 
          {
            for (size_t n_w = 0; n_w < layers_[l - 1].GetCountNeuron(); n_w++) 
            {
              layers_[l].SetNeuronWeights(n, n_w, strtod(&line[i], &ptrEnd));
              do 
              {
                i++;
              } while (line[i] != ',' && i < line.size());
              i++;
            }
          }
        }
      }
    }
  }
  inweights.close();
}


std::vector<int> GraphPerceptron::Predict(std::string name_image) 
{
//  LoadValuesTest(name_image);
  Test(1);
  return FindMaximumPredict();
}

int GraphPerceptron::FindMaximum() 
{
  double maximum = 0.0;
  int index_max = 0;

  for (size_t n = 0; n < layers_[number_out_layer_].GetCountNeuron(); n++) 
  {
    if (layers_[number_out_layer_].GetNeuronValue(n) > maximum) 
    {
      maximum = layers_[number_out_layer_].GetNeuronValue(n);
      index_max = n;
    }
  }
  return index_max;
}

std::vector<int> GraphPerceptron::FindMaximumPredict() 
{
  std::vector<int> index_max(4);
  std::map<double, int> sort;
  for (size_t n = 0; n < layers_[number_out_layer_].GetCountNeuron(); n++) 
    sort.insert({layers_[number_out_layer_].GetNeuronValue(n), n});
  std::map<double, int>::reverse_iterator answer = sort.rbegin();
  for (int i = 0; i < 4 && answer != sort.rend(); i++) 
  {
    index_max[i] = answer->second + 1;
    answer++;
  }
  return index_max;
}

void GraphPerceptron::Test(double test_sample)
{
  auto start = std::chrono::steady_clock::now();
  _rightPredicts = 0;
  size_letter_for_epoch =
      (int)((double)vector_for_test.size() * test_sample);
  for (size_t d = 0; d < (size_t)size_letter_for_epoch; d++)
  {
    TestForthBack(d);
  }
  auto end = std::chrono::steady_clock::now();
  auto diff = end - start;
  _time = std::chrono::duration <double> (diff).count();
  std::cout << CalculatePercent(1) << std::endl;
}

void GraphPerceptron::TestForthBack(int d) 
{
  _expectedLetter = vector_for_test[d][0] - 1;
  for (size_t n = 1; n < vector_for_test[d].size(); n++)
    layers_[0].SetNeuronValue(n, vector_for_test[d][n] / 255);
  ForwardPropagation();
  CountingSuccessfulLetters();
}

double GraphPerceptron::CalculatePercent(int k_group) 
{
  return _rightPredicts / ((double)vector_for_test.size() / k_group);
}

void GraphPerceptron::CountingSuccessfulLetters() 
{
  if ((size_t)layers_[number_out_layer_].FindMaximum() == _expectedLetter)
  {
    _rightPredicts++;
    true_positive += 1;
    true_negative += 25;
  } 
  else 
  {
    false_negative += 1;
    false_positive += 1;
    true_negative += 24;
  }
}

void GraphPerceptron::Testing(char *filename_test) 
{
  if (LoadValuesTest(filename_test) < 0) return;
  Test(full_sample);
}

void GraphPerceptron::Clear() 
{
  for (size_t i = 0; i < count_layers_; i++)
    layers_[i].ClearFunction();
  layers_.clear();
  for (size_t d = 0; d < vector_vectorovi4.size(); d++) 
    vector_vectorovi4[d].clear();
  vector_vectorovi4.clear();
  for (size_t d = 0; d < vector_for_test.size(); d++) 
    vector_for_test[d].clear();
  vector_for_test.clear();

  _rightPredicts = 0;
  _expectedLetter = 0;
  count_hidden_layers_ = 0;
  count_layers_ = 0;
  number_out_layer_ = 0;
}

void GraphPerceptron::ResizePerceptron(int count_hidden_layers) 
{
  Clear();
  count_hidden_layers_ = count_hidden_layers;
  count_layers_ = count_hidden_layers + 2;
  number_out_layer_ = count_layers_ - 1;
  layers_.resize(count_layers_);
  InitGraphPerceptron();
}

void GraphPerceptron::CrossValidation(std::string filename_train, int k_validation) {
  _k = k_validation;
  if (getDataFromFile(filename_train) < 0) return;
  vector_vectorovi4 = GetInput();
  vector_for_test = GetInput();
  size_letter_for_epoch = k_validation * (int)vector_vectorovi4.size();
  int one_part = vector_vectorovi4.size() / _k;

  for (int k_count = 1; k_count <= _k; k_count++) {
    for (int k_inner = 1; k_inner <= _k; k_inner++) {
      if (k_inner == k_count) k_inner++;
      for (int d = one_part * (k_inner - 1);
           k_inner <= _k && d < (one_part * k_inner);
           d++) {
        TrainForthBack(d);
      }
    }
	_rightPredicts = 0;
    for (int d = one_part * (k_count - 1); d < (one_part * k_count); d++)
      TestForthBack(d);
    std::cout << CalculatePercent(_k) << std::endl;
//    if (k_count < _k) GenerateWeightNeuron(); // что это?
  }
}

void GraphPerceptron::PrintPerceptron() 
{
  std::cout << "Слоев: " << count_hidden_layers_ + 2 << "\n";
  std::cout << "count_hidden_layers_ " << count_hidden_layers_ << "\n";

  std::cout << "Входной слой: " << "\n";
  layers_[0].PrintLayer();

  std::cout << "\n";

  for (int i = 0; i < count_hidden_layers_; i++) 
  {
    std::cout << "Скрытый слой [" << i + 1 << "]: " << "\n";
    layers_[i + 1].PrintLayer();
    std::cout << "\n";
  }

  std::cout << "Выходной слой: " << "\n";
  layers_[count_hidden_layers_ + 1].PrintLayer();

  std::cout << "\n";
}
}; 
