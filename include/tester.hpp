// Copyright 2020 Boryabes <box.bern@yandex.ru
#ifndef INCLUDE_TESTERCASHES_HPP_
#define INCLUDE_TESTERCASHES_HPP_
#include "string"
#include "vector"
class tester {
 private:
  std::string varOfTest;

  std::vector<double> sizesOfCashes = {393216, 2097152, 4194304};
  std::vector<double> sizesOfBufs;
  std::vector<double> durationsOfTest;
  const int kylo1024 = 1024;
  const int kylo1000 = 1000;
  const double four = 4.;
  const int sixteen = 16;
  const int mb1 = 1048576;

 public:
  void straightTest();
  void randomTest();
  void revertTest();
  void setBufs();
  friend std::ostream& operator<<(std::ostream& out, tester& a);
  std::string getVarOfTest();

  size_t getSizeOfBufArr();

  std::stringstream getExp(int indexOfBuf);
  std::string getInvestigation();
};
#endif  // INCLUDE_TESTERCASHES_HPP_