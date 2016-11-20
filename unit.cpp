#include <iostream>

#include "unit.hpp"

int main(int argc, char** argv) {
  Unit<double, 0, 0, 0, 0, 0, 0, 0, 5, 7> test1(2.0);
  Unit<double, 0, 0, 0, 0, 0, 0, 0, 2, 3> test2(3.0);
  auto test = test1 * test2;
  std::cout << "mul " << test.GetScale().num << "/" << test.GetScale().den << ", v " << test.GetValue() << std::endl;
  auto best = test1 / test2;
  std::cout << "div " << best.GetScale().num << "/" << best.GetScale().den << ", v " << best.GetValue() << std::endl;
  return 0;
}
