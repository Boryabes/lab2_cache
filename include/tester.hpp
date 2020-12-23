// Copyright 2020 Boryabes <box.bern@yandex.ru
#ifndef INCLUDE_TESTERCASHES_HPP_
#define INCLUDE_TESTERCASHES_HPP_
#include "string"
#include "vector"
class tester { //
 private:
  std::string varOfTest; //вариант прохода кеша

  std::vector<double> sizesOfCashes = {0.385, 2, 4 };
  std::vector<double> sizesOfBufs; //размер массива буфферов
  std::vector<double> durationsOfTest; //длительность каждого теста
  const int kylo1024 = 1024;
  const int kylo1000 = 1000;
  const double four = 4.;
  const int sixteen = 16;

 public:
  void straightTest(); //прямой проход
  void randomTest(); //рандомный проход
  void revertTest(); //обратный проход
  void setBufs(); //с помощью моих кешей высчитывает эксперементальные буфферы
  friend std::ostream & operator << (std::ostream & out, tester & a); //перегрузка операторов для вывода
  std::string getVarOfTest(); //для доступа к приватным полям(для доступа к варианту прохода)
  size_t getSizeOfBufArr(); //метод для доступа к размеру массива буфферов

  std::stringstream getExp(int indexOfBuf); //для вывода одного эксперемента
  std::string getInvestigation();

};
#endif  // INCLUDE_TESTERCASHES_HPP_
