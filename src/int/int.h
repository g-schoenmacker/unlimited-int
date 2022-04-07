#ifndef INCL_UNLIMITED_INT_H
#define INCL_UNLIMITED_INT_H

// ############################################################################
// Int is based on UInt and can do anything it can.
// ############################################################################

#include <iosfwd>    // forward declarations of std::ostream, std::istream
#include <stdexcept> // std::runtime_error
#include <string>    // std::string for str()

#include "../uint/uint.h" // UInt

namespace Unlimited {

class Int {

  // UInt is a friend, purely for UInt(Int) constructor.
  friend class UInt;

  // Private data member: if true iff Int holds a negative number.
  bool d_negative;

  // Private data member: stores the number.
  UInt d_number;

public:
  // Integer and default constructor, declared inline.
  Int(long long int = 0);

  // String constructor.
  explicit Int(std::string const &);

  // UInt constructor, declared inline.
  explicit Int(UInt const &);

  // Arithmetic assignment operators.
  Int &operator+=(Int const &);
  Int &operator-=(Int const &);
  Int &operator*=(Int const &);
  Int &operator/=(Int const &);
  Int &operator%=(Int const &);

  // Unary minus operator.
  Int operator-() const;

  // Division method, taking divisor, result and modulus.
  void divide(Int const &, Int &, Int &) const;

  // Power method, taking exponent.
  Int &pow(Int const &);       // changes object
  Int powc(Int const &) const; // returns new object

  // Square root method
  Int &sqrt();       // changes object
  Int sqrtc() const; // returns new object

  // Increment and decrement operators, defined inline below.
  Int operator++(int); // postfix
  Int operator--(int); // postfix
  Int &operator++();   // prefix
  Int &operator--();   // prefix

  // Bitwise assignment operators
  Int &operator&=(Int const &); // implementation
  Int &operator|=(Int const &); // implementation
  Int &operator^=(Int const &); // implementation
  Int &operator<<=(unsigned);   // implementation
  Int &operator>>=(unsigned);   // wraps >> inline

  Int operator<<(unsigned) const; // wraps <<= inline
  Int operator>>(unsigned) const; // implementation

  // Individual bit access methods, all inline.
  size_t num_bits() const;
  bool bit(size_t) const;
  void set_bit(size_t, bool);

  // Comparison method.
  int compare(Int const &) const; // implementation

  // Bool operator, explicit.
  explicit operator bool() const;

  // Long long conversion method.
  long long ll() const;

  // String conversion method.
  std::string str() const; // implementation

  // Swap method, defined inline.
  void swap(Int &);

  // Error class.
  class Exception : public std::runtime_error {
  public:
    Exception(std::string const &s) : std::runtime_error(s){};
  };

}; // end class Int

// Declaration of stream insert and extract operators.
std::ostream &operator<<(std::ostream &, Int const &);
std::istream &operator>>(std::istream &, Int &);

// Definition of free functions.
// Definition of free binary arithmetic operators.
inline Int operator+(Int const &rhs, Int const &lhs) {
  Int out(rhs);
  out += lhs;
  return out;
}

inline Int operator-(Int const &rhs, Int const &lhs) {
  Int out(rhs);
  out -= lhs;
  return out;
}

inline Int operator*(Int const &rhs, Int const &lhs) {
  Int out(rhs);
  out *= lhs;
  return out;
}

inline Int operator/(Int const &rhs, Int const &lhs) {
  Int out(rhs);
  out /= lhs;
  return out;
}

inline Int operator%(Int const &rhs, Int const &lhs) {
  Int out(rhs);
  out %= lhs;
  return out;
}

// Definition of free comparison operators.
// Definition of comparison operators.
inline bool operator==(Int const &rhs, Int const &lhs) {
  return !rhs.compare(lhs);
}

inline bool operator!=(Int const &rhs, Int const &lhs) {
  return rhs.compare(lhs);
}

inline bool operator<(Int const &rhs, Int const &lhs) {
  return rhs.compare(lhs) < 0;
}

inline bool operator>(Int const &rhs, Int const &lhs) {
  return rhs.compare(lhs) > 0;
}

inline bool operator<=(Int const &rhs, Int const &lhs) {
  return rhs.compare(lhs) <= 0;
}

inline bool operator>=(Int const &rhs, Int const &lhs) {
  return rhs.compare(lhs) >= 0;
}

// Definition of free bitwise operators.
inline Int operator&(Int const &rhs, Int const &lhs) {
  Int out(rhs);
  out &= lhs;
  return out;
}

inline Int operator|(Int const &rhs, Int const &lhs) {
  Int out(rhs);
  out |= lhs;
  return out;
}

inline Int operator^(Int const &rhs, Int const &lhs) {
  Int out(rhs);
  out ^= lhs;
  return out;
}

// Definition of all inline class methods below.

// Int constructor.
inline Int::Int(long long int n)
    : d_negative(n < 0), d_number(n < 0 ? -n : n){};

// UInt constructor.
inline Int::Int(UInt const &uint) : d_negative(false), d_number(uint){};

// Definition of wrappers for arithmetic operators.
inline Int &Int::operator*=(Int const &oth) {
  // d_negative is d_negative XOR oth.d_negative.
  d_negative =
      (d_negative && !oth.d_negative) || (!d_negative && oth.d_negative);
  d_number *= oth.d_number;
  return *this;
}

inline Int &Int::operator/=(Int const &oth) {
  Int res, mod;
  divide(oth, res, mod);
  return *this = res;
}

inline Int &Int::operator%=(Int const &oth) {
  Int res, mod;
  divide(oth, res, mod);
  return *this = mod;
}

// Definiton of unary minus operator.
inline Int Int::operator-() const {
  Int out(*this);
  if (d_number)
    out.d_negative = !d_negative;
  return out;
}

// Definition of constant power method.
inline Int Int::powc(Int const &exp) const {
  Int out(*this);
  out.pow(exp);
  return out;
}

// Definition of sqrt methods.
// May throw iff [*this] < 0.
inline Int &Int::sqrt() {
  if (d_negative)
    throw Exception("sqrt error: Can not take sqrt of negative "
                    "number (result would be complex)");
  d_number.sqrt();
  return *this;
}

inline Int Int::sqrtc() const {
  Int out(*this);
  out.sqrt();
  return out;
}

// Definition of increment & decrement operators.
inline Int Int::operator++(int) {
  Int out(*this);
  ++*this;
  return out;
}

inline Int Int::operator--(int) {
  Int out(*this);
  --*this;
  return out;
}

inline Int &Int::operator++() { return *this += 1; }

inline Int &Int::operator--() { return *this -= 1; }

// Definition of bitwise assignment operators. Note they DO affect sign.
inline Int &Int::operator&=(Int const &oth) {
  d_number &= oth.d_number;
  d_negative = d_negative && oth.d_negative;
  return *this;
}

inline Int &Int::operator|=(Int const &oth) {
  d_number |= oth.d_number;
  d_negative = d_negative || oth.d_negative;
  return *this;
}

inline Int &Int::operator^=(Int const &oth) {
  d_number ^= oth.d_number;
  d_negative =
      (d_negative && !oth.d_negative) || (!d_negative && oth.d_negative);
  return *this;
}

// Definition of shift assign operators. Shifts do not affect sign.
inline Int &Int::operator>>=(unsigned n) {
  d_number >>= n;
  return *this;
}

inline Int &Int::operator<<=(unsigned n) {
  d_number <<= n;
  return *this;
}

// Definition of shift operators.
inline Int Int::operator<<(unsigned n) const {
  Int out(*this);
  out <<= n;
  return out;
}

inline Int Int::operator>>(unsigned n) const {
  Int out(*this);
  out >>= n;
  return out;
}

// Definition of individual bit access methods.
// Method num_bits() returns the number of bits the Int has in use.
inline size_t Int::num_bits() const { return d_number.num_bits(); }

// Method bit(pos) returns true if bit at pos is set.
inline bool Int::bit(size_t pos) const { return d_number.bit(pos); }

// Method set_bit(pos, val) sets bit at [pos] to [val].
inline void Int::set_bit(size_t pos, bool val) { d_number.set_bit(pos, val); }

// The bool operator does not use compare() to avoid the overhead of
// constructing Int(0) for each comparison.
// Declared 'explicit' which avoids trouble.
inline Int::operator bool() const { return !!d_number; }

// Definition of string conversion method.
inline std::string Int::str() const {
  return d_negative ? std::string("-") + d_number.str() : d_number.str();
}

// Implementation of swap method, using std::vector::swap().
inline void Int::swap(Int &oth) {
  bool temp = d_negative;
  d_negative = oth.d_negative;
  oth.d_negative = temp;
  d_number.swap(oth.d_number);
}

} // end namespace Unlimited

#endif
