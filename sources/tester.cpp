//
// Copyright 2020 Boryabes <box.bern@yandex.ru>
//

#include "tester.hpp"

#include "algorithm"
#include "chrono"
#include "random"
#include "sstream"

void tester::straightTest() {
  varOfTest = "direction";
  durationsOfTest.clear();  //очищение массива длительности каждого эксперемента
  [[maybe_unused]] int vault;  //переменная для обращения к элементам массива
  for (const double &size : sizesOfBufs) {
    int *arr1 = new int[static_cast<int>(
        size / four)];  //создаем массив с количеством элементов равным размеру
                        //буффера делить на размер типа инт (4 байта)
    for (int i = 0; i < size / four;
         i +=
         sixteen) {  //иду по каждому 16-му элементу, строчка 20-24 прогрев кеша
      vault = arr1[i];
    }
    auto startTime =
        std::chrono::steady_clock::now();  //запоминаю текущее время
    for (int item = 0; item < kylo1000; ++item) {  //читаю массив 1000 раз
      for (int i = 0; i < size / four; i += sixteen) {
        vault = arr1[i];
      }
    }
    auto endTime =
        std::chrono::steady_clock::now();  //текущее время(после эксперемента)
    durationsOfTest.push_back(  //добавляю длительность эксперемента в массив
        std::chrono::duration_cast<std::chrono::microseconds>(endTime -
                                                              startTime)
            .count() /kylo1000);  //длительность одного прохода
    delete[] arr1;  //удаляю этот массив чтобы он не занимал место в памяти
  }
}

void tester::revertTest() {
  varOfTest = "reverse";
  durationsOfTest.clear();

  [[maybe_unused]] int vault;

  for (const double &size : sizesOfBufs) {
    int *arr1 = new int[static_cast<int>(size / four)];
    for (int i = size / four - 1; i > 0; i -= sixteen) {
      vault = arr1[i];
    }
    auto startTime = std::chrono::steady_clock::now();
    for (int i = 0; i < kylo1000; ++i) {
      for (int j = size / four - 1; j > 0; j -= sixteen) {
        vault = arr1[j];
      }
    }
    auto endTime = std::chrono::steady_clock::now();

    durationsOfTest.push_back(
        std::chrono::duration_cast<std::chrono::microseconds>(endTime -
                                                              startTime)
            .count() /
        kylo1000);
    delete[] arr1;
  }
}

void tester::randomTest() {
  varOfTest = "random";
  durationsOfTest.clear();
  [[maybe_unused]] int vault;

  for (const double &size : sizesOfBufs) {
    int *arr1 = new int[static_cast<int>(size / four)];
    std::vector<int> indexesOfBlocks;  //создаем массив для индексов
    for (int j = 0; j < size / four;
         j += sixteen) {  //заполняю массив и прогреваю в это же время
      indexesOfBlocks.push_back(j);
      vault = arr1[j];
    }
    auto rng = std::default_random_engine{};  //создается объекст класса
                                              //дефолРандомЕнджен
    std::shuffle(indexesOfBlocks.begin(), indexesOfBlocks.end(),
                 rng);  //функция библ алгоритм, шафл перемешивает все элементы
                        //массива рнг-генератор случайных чисел

    auto startTime = std::chrono::steady_clock::now();
    for (int i = 0; i < kylo1000; ++i) {
      for (auto index : indexesOfBlocks) {
        vault = arr1[index];
      }
    }
    auto endTime = std::chrono::steady_clock::now();
    durationsOfTest.push_back(
        std::chrono::duration_cast<std::chrono::microseconds>(endTime -
                                                              startTime)
            .count() /
        kylo1000);
    delete[] arr1;
  }
}

std::stringstream tester::getExp(int indexOfBuf) {
  std::stringstream ss;
  ss << "\t- experiment:\n"
     << "\t\tnumber: " << indexOfBuf + 1 << "\n"
     << "\t\tinput_data:\n"
     << "\t\t\tbuffer_size: " << sizesOfBufs[indexOfBuf] / kylo1024 << "Kb"
     << "\n"
     << "\t\tresults:\n"
     << "\t\t\tduration: " << durationsOfTest[indexOfBuf] << "mcs" << '\n';
  return ss;
}

std::string tester::getInvestigation() {
  std::stringstream ss;
  ss << "investigation:\n"
     << "\ttravel_variant:" << varOfTest << "\n";
  for (size_t duration = 0; duration < durationsOfTest.size(); ++duration) {
    ss << getExp(duration).str();
  }
  ss << "\n";
  return ss.str();
}

std::string tester::getVarOfTest() { return varOfTest; }

size_t tester::getSizeOfBufArr() { return sizesOfBufs.size(); }

std::ostream &operator<<(std::ostream &out, tester &invest) {
  out << "investigation:\n"
      << "\ttravel_variant: " << invest.getVarOfTest() << "\n";
  for (size_t i = 0; i < invest.getSizeOfBufArr(); ++i)
    out << invest.getExp(i).str();
  out << "\n";
  return out;
}

void tester::setBufs() {
  sizesOfBufs.push_back(sizesOfCashes[0] / 2.0 );
  for (int i = 1048576; i < 1.5 * sizesOfCashes[2]; i *= 2) {
    sizesOfBufs.push_back(i);
  }
  sizesOfBufs.push_back(sizesOfCashes[2] * 1.5);
}
