#pragma once
/**
 * @~english
 * @file unit.hpp
 * @brief Compile time, constexpr class for expressing SI units.
 */

#include <cstdint>
#include <ratio>
#include <type_traits>

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
   * Value constructor
   * @param value The value with the given units.
   */
  constexpr Unit(ValueType value) : value_(value) {}

  /**
   * @~english
   * Gets the scale for the given units.
   * @return The scale of the units.
   */
  constexpr std::ratio<Num, Denom> GetScale() const noexcept { return scale_; }
  
  /**
   * @~english
   * Gets the value with the given units.
   * @return value with the given units.
   */
  constexpr ValueType GetValue() const noexcept { return value_; }

  bool operator==(const Unit& other) const noexcept {
    return value_ == other.value_;
  }
  
  /**
   * @~english
   * Multiplication operator
   * @param other The value to multiply by
   * @return A new unit class with the multiplied units and value
   */
  template <int32_t S, int32_t M, int32_t C, int32_t K, int32_t Rad, int32_t A, int32_t KG, size_t Num2, 
            size_t Denom2>
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
   * The scale of the unit. E.g. cm, mm, etc.
   */
  std::ratio<Num, Denom> scale_;

  /**
   * @~english
   * The unit value.
   */
  ValueType value_;
};

