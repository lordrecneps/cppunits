#include <iostream>

#include "unit.hpp"

int main(int argc, char** argv) {
  Unit<double, 0, 0, 0, 0, 0, 0, 0, 5, 7> test1(2.0);
  Unit<double, 0, 0, 0, 0, 0, 0, 0, 2, 3> test2(3.0);
  auto test = test1 * test2;
  std::cout << "mul " << test.GetScale().num << "/" << test.GetScale().den << ", v " << test.GetValue() << std::endl;
  auto best = test1 / test2;
  std::cout << "div " << best.GetScale().num << "/" << best.GetScale().den << ", v " << best.GetValue() << std::endl;

  auto zest = test1 + test1;
  std::cout << "add " << zest.GetScale().num << "/" << zest.GetScale().den << ", v " << zest.GetValue() << std::endl;

  auto fest = test1 - test1;
  std::cout << "sub " << fest.GetScale().num << "/" << fest.GetScale().den << ", v " << fest.GetValue() << std::endl;
  return 0;
}
