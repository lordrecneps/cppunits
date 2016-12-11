#include <iostream>

#include "unit.hpp"

using namespace units;

int main(int argc, char** argv) {
  Unit<double, 0, 0, 0, 0, 0, 0, 0, 5, 7> test1(2.0);
  Unit<double, 0, 0, 0, 0, 0, 0, 0, 2, 3> test2(3.0);
  auto test = test1 * test2;
  std::cout << "mul " << decltype(test)::scale::num << "/" << decltype(test)::scale::den << ", v " << test.GetValue() << std::endl;
  auto best = test1 / test2;
  std::cout << "div " << decltype(best)::scale::num << "/" << decltype(best)::scale::den << ", v " << best.GetValue() << std::endl;

  auto zest = test1 + test1;
  std::cout << "add " << decltype(zest)::scale::num << "/" << decltype(zest)::scale::den << ", v " << zest.GetValue() << std::endl;

  auto fest = test1 - test1;
  std::cout << "sub " << decltype(fest)::scale::num << "/" << decltype(fest)::scale::den << ", v " << fest.GetValue() << std::endl;

  i::Meter meter(100);
  i::Second sec(1);
  i::Kilogram kg(1);
  i::Gram g(1000);

  if (meter * sec * kg == Unit<int64_t, 1, 1, 0, 0, 0, 0, 1, 1000, 1>(100))
    std::cout << "Pass" << std::endl;
  else
    std::cout << "Fail" << std::endl;

  if (meter * sec * g == Unit<int64_t, 1, 1, 0, 0, 0, 0, 1, 1000, 1>(100))
    std::cout << "Pass" << std::endl;
  else
    std::cout << "Fail" << std::endl;
  return 0;

}
