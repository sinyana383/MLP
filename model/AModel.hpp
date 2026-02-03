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

class AModel {

public:
  // принимает массив пикселей[784]
  // возвращает векторх[4], где первая четверка предпологаемых букв
  std::vector<std::vector<double>> recognizeLetter(std::vector<std::vector<double>> input);

  // принимает число то 0 - 1 для, определяя какая часть букв из выборки будет тестироваться
  // возвращает массив метрик в таком порядке: accuracy, f_measure, precision, recall, total_time
  std::vector<double> test(float sample);
  
  // принимает кол-во эпох
  // возвращает массив контрольных значений ошибки – процент неправильно угаданных во время обучения
  std::vector<double> train(int epoch);

  // принимает 
  // запускать процесс обучения с применением кросс-валидации для заданного числа групп k
  // !!! возвращает массив контрольных значений ошибки – (пока непонятно как высчитывать)
  std::vector<double> train(int k);

  // нужно полностью переиницилизировать модель
  // true - память перевыделенна, false – неудача
  bool changeLayersNumber(int layersNb);

  // загрузка весов из файла
  // true - успех, false – неудача
  bool importWeights(std::string const &fileName);

  // выгрузка весов в файл
  // true - успех, false – неудача
  bool exportWeights(const std::string &fileName);

}