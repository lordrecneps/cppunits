#define CATCH_CONFIG_MAIN
#include "test/catch.hpp"

#include <iostream>

#include "unit.hpp"

using namespace units;

TEST_CASE( "Unit arithmetic") {
  constexpr Unit<double, 0, 0, 0, 0, 0, 0, 0, 5, 7> t1(2.0);
  constexpr Unit<double, 0, 0, 0, 0, 0, 0, 0, 2, 3> t2(3.0);

  REQUIRE((t1 * t2).GetNum() == 10);
  REQUIRE((t1 * t2).GetDen() == 21);
  REQUIRE((t1 * t2).GetValue() == 6.0);

  REQUIRE((t1 / t2).GetNum() == 15);
  REQUIRE((t1 / t2).GetDen() == 14);
  REQUIRE((t1 / t2).GetValue() == (2.0 / 3.0));

  REQUIRE((t1 + t1).GetNum() == 5);
  REQUIRE((t1 + t1).GetDen() == 7);
  REQUIRE((t1 + t1).GetValue() == 4.0);

  REQUIRE((t1 - t1).GetNum() == 5);
  REQUIRE((t1 - t1).GetDen() == 7);
  REQUIRE((t1 - t1).GetValue() == 0.0);

  REQUIRE((t1 + t2).GetNum() == 1);
  REQUIRE((t1 + t2).GetDen() == 21);
  REQUIRE((t1 + t2).GetValue() == 72.0);

  REQUIRE((t1 - t2).GetNum() == 1);
  REQUIRE((t1 - t2).GetDen() == 21);
  REQUIRE((t1 - t2).GetValue() == -12.0);

  constexpr i::Meter meter(100);
  constexpr i::Second sec(1);
  constexpr i::Kilogram kg(1);
  constexpr i::Gram g(1000);

  REQUIRE((meter * sec * kg) == (Unit<int64_t, 1, 1, 0, 0, 0, 0, 1, 1000, 1>(100)));
  REQUIRE((meter * sec * g) == (Unit<int64_t, 1, 1, 0, 0, 0, 0, 1, 1000, 1>(100)));
}
