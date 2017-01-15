#pragma once
/**
 * @~english
 * @file unit.hpp
 * @brief Compile time, constexpr class for expressing SI units.
 */

#include <cstdint>
#include <ratio>
#include <type_traits>

namespace units {

/**
 * @~english
 * @brief Constexpr ready class for expressing SI units. Supports basic arithmetic.
 */
template <typename ValueType, int32_t Time, int32_t Distance, int32_t Luminance, int32_t Temperature,
          int32_t Radians, int32_t Amperes, int32_t Mass, size_t Num = 1, size_t Denom = 1>
class Unit {
 public:
  static_assert(std::is_arithmetic<ValueType>::value && !std::is_same<bool, ValueType>::value,
                "Only built-in integral and floating point types supported.");

  /**
   * @~english
   * The scale of the unit. E.g. cm, mm, etc.
   */
  using scale = std::ratio<Num, Denom>;

  /**
   * @~english
   * Unit type with identical units but different ratio.
   */
  template <size_t Num2, size_t Den2>
  using units = Unit<ValueType, Time, Distance, Luminance, Temperature, Radians, Amperes, Mass, Num2, Den2>;

  /**
   * @~english
   * Value constructor
   * @param value The value with the given units.
   */
  constexpr Unit(ValueType value) : value_(value) {}

  /**
   * @~english
   * Conversion operator to a different ratio.
   * @return Unit with the same value and given ratio.
   */
  template <size_t Num2, size_t Den2>
  operator units<Num2, Den2>() const noexcept {
    using r = typename units<Num2, Den2>::scale;
    using s = std::ratio_divide<r, scale>;
    return units<Num2, Den2>(s::num * value_ / s::den);
  }

  /**
   * @~english
   * Gets the numerator of the unit ratio
   * @return The numerator
   */
  static constexpr size_t GetNum() noexcept { return scale::num; }

  /**
   * @~english
   * Gets the denominator of the unit ratio
   * @return The denominator
   */
  static constexpr size_t GetDen() noexcept { return scale::den; }

  /**
   * @~english
   * Gets the value with the given units.
   * @return value with the given units.
   */
  constexpr ValueType GetValue() const noexcept { return value_; }

  template <size_t Num2, size_t Denom2>
  bool operator==(const units<Num2, Denom2>& other) const noexcept {
    using s = std::ratio_divide<scale, typename std::decay<decltype(other)>::type::scale>;
    return value_ * s::num == other.GetValue() * s::den;
  }

  template <size_t Num2, size_t Denom2>
  bool operator!=(const units<Num2, Denom2>& other) const noexcept {
    return !(*this == other);
  }

  template <size_t Num2, size_t Denom2>
  bool operator<(const units<Num2, Denom2>& other) const noexcept {
    using s = std::ratio_divide<scale, typename std::decay<decltype(other)>::type::scale>;
    return value_ * s::num < other.GetValue() * s::den;
  }

  template <size_t Num2, size_t Denom2>
  bool operator>(const units<Num2, Denom2>& other) const noexcept {
    using s = std::ratio_divide<scale, typename std::decay<decltype(other)>::type::scale>;
    return value_ * s::num > other.GetValue() * s::den;
  }

  template <size_t Num2, size_t Denom2>
  bool operator>=(const units<Num2, Denom2>& other) const noexcept {
    return !(*this < other);
  }

  template <size_t Num2, size_t Denom2>
  bool operator<=(const units<Num2, Denom2>& other) const noexcept {
    return !(*this > other);
  }

  /**
   * @~english
   * Multiplication operator
   * @param other The value to multiply by
   * @return A new unit class with the multiplied units and value
   */
  template <int32_t S, int32_t M, int32_t C, int32_t K, int32_t Rad, int32_t A, int32_t KG, size_t Num2, size_t Denom2>
  constexpr
  Unit<ValueType, S + Time, M + Distance, C + Luminance, K + Temperature, Rad + Radians, A + Amperes, KG + Mass,
       std::ratio<Num * Num2, Denom * Denom2>::num, std::ratio<Num * Num2, Denom * Denom2>::den>
  operator*(const Unit<ValueType, S, M, C, K, Rad, A, KG, Num2, Denom2>& other) const {
    return {value_ * other.GetValue()};
  }

  /**
   * @~english
   * Constant multiplication operator
   * @param other The constant to multiply by
   * @return A new unit muliplied by the given constant
   */
  template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value && !std::is_same<bool, T>::value>::type>
  constexpr Unit operator*(T c) {
    return Unit(value_ * c);
  }

  /**
   * @~english
   * Constant multiplication assignment operator
   * @param other The constant to multiply by
   * @return A reference to the unit after muliplication by the given constant
   */
  template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value && !std::is_same<bool, T>::value>::type>
  constexpr Unit& operator*=(T c) {
    value_ *= c;
    return *this;
  }

  /**
   * @~english
   * Constant division operator
   * @param other The constant to divide by
   * @return A new unit divided by the given constant
   */
  template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value && !std::is_same<bool, T>::value>::type>
  constexpr Unit operator/(T c) {
    return Unit(value_ / c);
  }

  /**
   * @~english
   * Constant division assignment operator
   * @param other The constant to divide by
   * @return A reference to the unit after division by the given constant
   */
  template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value && !std::is_same<bool, T>::value>::type>
  constexpr Unit& operator/=(T c) {
    value_ /= c;
    return *this;
  }

  /**
   * @~english
   * Division operator
   * @param other The value to divide by
   * @return A new unit class with the divided units and value
   */
  template <int32_t S, int32_t M, int32_t C, int32_t K, int32_t Rad, int32_t A, int32_t KG, size_t Num2,
            size_t Denom2>
  constexpr
  Unit<ValueType, Time - S, Distance - M, Luminance + C, Temperature + K, Radians + Rad, Amperes + A, Mass + KG,
       std::ratio<Num * Denom2, Denom * Num2>::num, std::ratio<Num * Denom2, Denom * Num2>::den>
  operator/(const Unit<ValueType, S, M, C, K, Rad, A, KG, Num2, Denom2>& other) const {
    return {value_ / other.GetValue()};
  }

  /**
   * @~english
   * Addition operator
   * @param other The amount to add by
   * @return New unit with the result of the addition
   */
  constexpr Unit operator+(const Unit& other) const {
    return {value_ + other.value_};
  }

  /**
   * @~english
   * Addition assignment operator
   * @param other The amount to add by
   * @return Reference to the unit after addition
   */
  constexpr Unit& operator+=(const Unit& other) const {
    value_ += other.value_;
    return *this;
  }

  /**
   * @~english
   * Constant subtraction operator
   * @param other The amoutn to subtract by
   * @return A new unit with the result of the subtraction
   */
  constexpr Unit operator-(const Unit& other) const {
    return {value_ - other.value_};
  }

  /**
   * @~english
   * Subtraction assignment operator
   * @param other The amount to subtract by
   * @return Reference to the unit after subtraction
   */
  constexpr Unit& operator-=(const Unit& other) const {
    value_ -= other.value_;
    return *this;
  }

 private:
  /**
   * @~english
   * The unit value.
   */
  ValueType value_;
};

/**
 * @~english
 * Defines all the base SI units with the given arithmetic type.
 * @param type The arithmetic type used to store the value of the unit.
 */
#define DEFINE_BASE(type) \
using Second = Unit<type, 1, 0, 0, 0, 0, 0, 0, 1, 1>; \
using Meter = Unit<type, 0, 1, 0, 0, 0, 0, 0, 1, 1>;  \
using Candela = Unit<type, 0, 0, 1, 0, 0, 0, 0, 1, 1>;\
using Kelvin = Unit<type, 0, 0, 0, 1, 0, 0, 0, 1, 1>; \
using Radian = Unit<type, 0, 0, 0, 0, 1, 0, 0, 1, 1>; \
using Ampere = Unit<type, 0, 0, 0, 0, 0, 1, 0, 1, 1>; \
using Gram = Unit<type, 0, 0, 0, 0, 0, 0, 1, 1, 1>;

/**
 * @~english
 * Defines all the base SI units with the given prefix
 * @param type The arithmetic type used to store the value of the unit.
 * @param name The name of the prefix
 * @param num The numerator of the fraction represented by this prefix
 * @param num The denominator of the fraction represented by this prefix
 */
#define DEFINE_PREFIX(type, name, num, denom) \
using name##second = Unit<type, 1, 0, 0, 0, 0, 0, 0, num, denom>;  \
using name##meter = Unit<type, 0, 1, 0, 0, 0, 0, 0, num, denom>;   \
using name##candela = Unit<type, 0, 0, 1, 0, 0, 0, 0, num, denom>; \
using name##kelvin = Unit<type, 0, 0, 0, 1, 0, 0, 0, num, denom>;  \
using name##radian = Unit<type, 0, 0, 0, 0, 1, 0, 0, num, denom>;  \
using name##ampere = Unit<type, 0, 0, 0, 0, 0, 1, 0, num, denom>;  \
using name##gram = Unit<type, 0, 0, 0, 0, 0, 0, 1, num, denom>;

/**
 * @~english
 * Defines all the prefixes for all base SI units that can fit in 64-bit types
 * @param type The arithmetic type used to store the value of the unit.
 */
#define DEFINE_PREFIXES(type) \
DEFINE_PREFIX(type, Atto, 1, 1000000000000000000) \
DEFINE_PREFIX(type, Femto, 1, 1000000000000000) \
DEFINE_PREFIX(type, Pico, 1, 1000000000000) \
DEFINE_PREFIX(type, Nano, 1, 1000000000) \
DEFINE_PREFIX(type, Micro, 1, 1000000) \
DEFINE_PREFIX(type, Milli, 1, 1000) \
DEFINE_PREFIX(type, Centi, 1, 100) \
DEFINE_PREFIX(type, Deci, 1, 10) \
DEFINE_PREFIX(type, Deca, 10, 1) \
DEFINE_PREFIX(type, Hecto, 100, 1) \
DEFINE_PREFIX(type, Kilo, 1000, 1) \
DEFINE_PREFIX(type, Mega, 1000000, 1) \
DEFINE_PREFIX(type, Giga, 1000000000, 1) \
DEFINE_PREFIX(type, Tera, 1000000000000, 1) \
DEFINE_PREFIX(type, Peta, 1000000000000000, 1) \
DEFINE_PREFIX(type, Exa,  1000000000000000000, 1)


namespace i {

/**
 * @~english
 * All int64-based SI units
 */
DEFINE_BASE(int64_t)
DEFINE_PREFIXES(int64_t)

}  // namespace i

namespace d {

/**
 * @~english
 * All double-based SI units
 */
DEFINE_BASE(double)
DEFINE_PREFIXES(double)

}  // namespace d

}  // namespace units

