#include "Graph/graph.h"
#include "Matrix/Matrix.hpp"

#include "control/Control.hpp"

void testGraph();
void testMatrix();

void printErrors(std::vector<double> &errors);

void controlling()
{
  s21::Control con;
  std::string line;

  std::vector<double> errors;
  errors.clear();

  std::getline(std::cin, line);
  while (line != "exit")
  {
	switch (line[0]) {
	  case 'g': //graph
		con.setMlpType(GRAPH);
		break;
	  case 'm': // matrix
		con.setMlpType(MATRIX);
		break;
	  case '2':
		con.setHiddenLayerNb(2);
		break;
	  case '3':
		con.setHiddenLayerNb(3);
		break;
	  case '4':
		con.setHiddenLayerNb(4);
		break;
	  case '5':
		con.setHiddenLayerNb(5);
		break;
	  case 's': // save
		con.saveWeights(DEFAULTWEIGHTS);
		break;
	  case 'l': // load
		con.loadWeights(DEFAULTWEIGHTS);
		break;
	  case 'e': //epoch
	  	int a;
	  	std::cin >> a;
		con.train(a, errors);
		if (!errors.empty())
			printErrors(errors);
		errors.clear();
		break;
	  case 't':
		double p;
		std::cin >> p;
		errors = con.test(p);
		printErrors(errors);
		break;
	  case 'c':
		int b;
		std::cin >> b;
		con.crossValidation(b);
		break;
	}
	std::getline(std::cin, line);
  }
}

int main(void)
{
  controlling();
//  testGraph();
//  testMatrix();

//  s21::Control con;
//  std::vector<double> errors;
//
////  con.setMlpType(MATRIX);
////  con.setHiddenLayerNb(2);
////  con.train(4,errors);
////  con.saveWeights("weights.w");
////  printErrors(errors);
////  errors.clear();
//
////  con.setMlpType(GRAPH);
//////  con.train(2, errors);
////  con.loadWeights("weights.w");
////  con.test(1);
//
//  con.setMlpType(MATRIX);
//  con.setTestFile("letter");
////  con.loadWeights("weights.w");
////  con.test(1);
//  con.predict(errors);
  return 0;
}
void printErrors(std::vector<double> &errors) {
  for (double error : errors)
    std::cout << error << " ";
  std::cout << std::endl;
}

void testGraph()
{
  auto start = std::chrono::steady_clock::now();
  std::vector<double> report;
  s21::GraphPerceptron graph(2);


  graph.InitGraphPerceptron();
//  graph.GenerateWeightNeuron();
  graph.LoadWeights("rand.w");
//  graph.LoadWeights("rand.w");

  graph.LoadValuesTrain(R"(C:\Users\1\Desktop\MLP\emnist-letters-train.csv)");
  graph.EpochTrain(1, &report);

//  graph.CrossValidation("/Users/ddurrand/Desktop/Den1s/emnist-letters-train.csv", 2);


//  char a[200] = R"(C:\Users\1\Desktop\MLP\emnist-letters-test.csv)";
//  graph.Testing(a);
//  std::cout << report[0] << std::endl;

  auto end = std::chrono::steady_clock::now();
  auto diff = end - start;
  std::cout << std::chrono::duration <double> (diff).count() << " sec" << std::endl;
}

void testMatrix()
{
  auto start = std::chrono::steady_clock::now();
  s21::Matrix matrix;

  matrix.getDataFromFile(R"(C:\Users\1\Desktop\MLP\emnist-letters-train.csv)");
  matrix.initModel(4);
  matrix.genWeights();
  matrix.exportWeightsToFile("rand.w");
//  matrix.importWeightsFromFile("rand.w");
//  matrix.epoch();

//  matrix.getDataFromFile(R"(C:\Users\1\Desktop\MLP\emnist-letters-test.csv)");
//  matrix.initModel(4);
//  matrix.importWeightsFromFile("weights.w");
//  matrix.test();

  auto end = std::chrono::steady_clock::now();
  auto diff = end - start;
  std::cout << std::chrono::duration <double> (diff).count() << " sec" << std::endl;
}

// G -> M 0.701554054
//0.603615
//151.159 sec
// M -> G 96.2834 0.696892 14.2813
//52746 / 88800
//122.636 sec