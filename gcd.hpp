#pragma once
/**
 * @~english
 * @file unit.hpp
 * @brief Compile time, constexpr class for expressing SI units.
 */

#include <type_traits>

namespace units {

template<typename T>
constexpr auto abs(T i) -> typename std::enable_if<std::is_integral<T>::value, T>::type
{ return i < T(0) ? -i : i; }

template<typename T>
constexpr T gcd(T m, T n)
{ return n == 0 ? abs(m) : gcd(n, abs(m) % abs(n)); }

template<typename T>
constexpr T lcm(T m, T n)
{ return m * n == 0 ? 0 : (abs(m) / gcd(m,n)) * abs(n); }

}  // namespace units
