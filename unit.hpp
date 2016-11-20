#include <cstdint>
#include <ratio>
#include <type_traits>

template <typename ValueType, int32_t Time, int32_t Distance, int32_t Luminance, int32_t Temperature,
          int32_t Radians, int32_t Amperes, int32_t Mass, size_t Num = 1, size_t Denom = 1>
class Unit {
 public:
  static_assert(std::is_arithmetic<ValueType>::value && !std::is_same<bool, ValueType>::value,
                "Only built-in integral and floating point types supported.");

  constexpr Unit(ValueType value) : value_(value) {}
  
  constexpr std::ratio<Num, Denom> GetScale() const noexcept { return scale_; }

  constexpr ValueType GetValue() const noexcept { return value_; }
  
  template <int32_t S, int32_t M, int32_t C, int32_t K, int32_t Rad, int32_t A, int32_t KG, size_t Num2, 
            size_t Denom2>
  constexpr
  Unit<ValueType, S + Time, M + Distance, C + Luminance, K + Temperature, Rad + Radians, A + Amperes, KG + Mass, 
       std::ratio<Num * Num2, Denom * Denom2>::num, std::ratio<Num * Num2, Denom * Denom2>::den>
  operator*(const Unit<ValueType, S, M, C, K, Rad, A, KG, Num2, Denom2> other) const {
    return {value_ * other.GetValue()};
  }

  template <int32_t S, int32_t M, int32_t C, int32_t K, int32_t Rad, int32_t A, int32_t KG, size_t Num2, 
            size_t Denom2>
  constexpr
  Unit<ValueType, Time - S, Distance - M, Luminance + C, Temperature + K, Radians + Rad, Amperes + A, Mass + KG,
       std::ratio<Num * Denom2, Denom * Num2>::num, std::ratio<Num * Denom2, Denom * Num2>::den>
  operator/(const Unit<ValueType, S, M, C, K, Rad, A, KG, Num2, Denom2> other) const {
    return {value_ / other.GetValue()};
  }

 private:
  std::ratio<Num, Denom> scale_;
  ValueType value_;
};

