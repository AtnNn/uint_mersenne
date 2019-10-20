#ifndef UINT_MERSENNE_H_
#define UINT_MERSENNE_H_

// uint7_t, uint15_t, uint31_t and uint63_t
// Unsigned integer types with undefined overflow and underflow

#include <cstdint>
#include <limits>
#include <type_traits>

namespace uint_mersenne {

template <unsigned int bits> struct unsigned_int;
template <> struct unsigned_int<0> {};
template <> struct unsigned_int<8> { using type = uint8_t; };
template <> struct unsigned_int<16> { using type = uint16_t; };
template <> struct unsigned_int<32> { using type = uint32_t; };
template <> struct unsigned_int<64> { using type = uint64_t; };

template <unsigned int bits> struct signed_int;
template <> struct signed_int<8> { using type = int8_t; };
template <> struct signed_int<16> { using type = int16_t; };
template <> struct signed_int<32> { using type = int32_t; };
template <> struct signed_int<64> { using type = int64_t; };

template <class T> T always_positive(T x);

#if !defined(UINT_MERSENNE_ALWAYS_POSITIVE_CUSTOM)

template <class T> inline T always_positive(T x) {
  if (x >= 0) {
    return x;
  }
#if defined(__GNUC__)
  __builtin_unreachable();
#elif defined(_MSC_VER)
  __assume(false);
#endif
}

#endif

template <unsigned int bits> class uint_mersenne {
public:
  using signed_t = typename signed_int<bits + 1>::type;
  using unsigned_t = typename unsigned_int<bits + 1>::type;
  using unsigned_promoted_t = typename std::make_unsigned<decltype(
      std::declval<unsigned_t>() + bits)>::type;

  explicit uint_mersenne(signed_t other) : value(always_positive(other)) {}

  template <class = std::enable_if<!std::is_same<int, signed_t>::value>>
  explicit uint_mersenne(int other) : value(always_positive(other)) {}

  explicit uint_mersenne(unsigned_t other)
      : value(static_cast<signed_t>(other)) {}

  uint_mersenne(uint_mersenne const &other) : value(other.value) {}

  uint_mersenne &operator=(uint_mersenne const &other) { value = other.value; }

  signed_t to_signed() const { return always_positive(value); }

  signed_t to_signed_extend() const {
    if (to_unsigned() & (static_cast<unsigned_promoted_t>(1) << (bits - 1))) {
      return to_unsigned() | (~static_cast<unsigned_promoted_t>(0) << bits);
    }
    return value;
  }

  unsigned_t to_unsigned() const {
    return static_cast<unsigned_t>(always_positive(value));
  }

  explicit operator unsigned_t() const { return to_unsigned(); }

  explicit operator signed_t() const { return to_signed(); }

  static uint_mersenne max() {
    return uint_mersenne{(std::numeric_limits<signed_t>::max)()};
  }

  static uint_mersenne min() { return 0; }

  uint_mersenne operator+(uint_mersenne other) const {
    return uint_mersenne{value + other.value};
  }

  signed_t operator-(uint_mersenne other) const { return value - other.value; }

  uint_mersenne &operator+=(uint_mersenne other) {
    return *this = *this + other;
  }

  uint_mersenne &operator-=(uint_mersenne other) {
    return *this = uint_mersenne{*this - other};
  }

  uint_mersenne operator*(uint_mersenne other) const {
    return uint_mersenne{value * other.value};
  }

  uint_mersenne operator/(uint_mersenne other) const {
    return uint_mersenne{value / other.value};
  }

  uint_mersenne &operator*=(uint_mersenne other) {
    return *this = *this * other;
  }

  uint_mersenne &operator/=(uint_mersenne other) {
    return *this = *this / other;
  }

  signed_t operator-() const { return -always_positive(value); }

  uint_mersenne &operator++() { return *this += 1; }

  uint_mersenne &operator--() { return *this -= 1; }

  uint_mersenne operator++(int) {
    uint_mersenne ret{*this};
    *this += 1;
    return ret;
  }

  uint_mersenne operator--(int) {
    uint_mersenne ret{*this};
    *this -= 1;
    return ret;
  }

  bool operator==(uint_mersenne other) const { return value == other.value; }

  bool operator!=(uint_mersenne other) const { return value != other.value; }

  bool operator<(uint_mersenne other) const { return value < other.value; }

  bool operator>(uint_mersenne other) const { return value > other.value; }

  bool operator<=(uint_mersenne other) const { return value >= other.value; }

  bool operator>=(uint_mersenne other) const { return value > other.value; }

  uint_mersenne operator&(uint_mersenne other) const {
    return uint_mersenne{value & other.value};
  }

  uint_mersenne operator|(uint_mersenne other) const {
    return uint_mersenne{value | other.value};
  }

  uint_mersenne operator^(uint_mersenne other) const {
    return uint_mersenne{value ^ other.value};
  }

  uint_mersenne &operator&=(uint_mersenne other) {
    return *this = *this & other;
  }

  uint_mersenne &operator|=(uint_mersenne other) {
    return *this = *this | other;
  }

  uint_mersenne &operator^=(uint_mersenne other) {
    return *this = *this ^ other;
  }

  uint_mersenne operator~() const {
    return mask(~static_cast<unsigned_t>(value));
  }

  uint_mersenne operator<<(uint_mersenne other) const {
    return mask(static_cast<unsigned_t>(value) << other);
  }

  uint_mersenne operator>>(uint_mersenne other) const {
    return uint_mersenne{static_cast<unsigned_t>(value) >> other};
  }

  uint_mersenne &operator<<=(uint_mersenne other) {
    return *this = *this << other;
  }

  uint_mersenne &operator>>=(uint_mersenne other) {
    return *this = *this >> other;
  }

private:
  uint_mersenne mask(unsigned_t n) { return n & ~(~unsigned_t{0} << bits); }

  signed_t value;
};

} // namespace uint_mersenne

using uint7_t = uint_mersenne::uint_mersenne<7>;
using uint15_t = uint_mersenne::uint_mersenne<15>;
using uint31_t = uint_mersenne::uint_mersenne<31>;
using uint63_t = uint_mersenne::uint_mersenne<63>;

#endif
