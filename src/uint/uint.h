#ifndef INCL_UNLIMITED_UINT_H
#define INCL_UNLIMITED_UINT_H

// ############################################################################
// UInt is the main calculation class, supporting
// - Implicit unsigned integer and string construction;
// - Addition and subtraction;
// - Multiplication, division and modulus calculation;
// - Bit shifting and bit access;
// - Bitwise AND, OR and XOR operators;
// - Power raising and square root calculation;
// - Conversion to unsigned long long;
// - Equality comparison;
// - String conversion, stream insertion and extraction.
//
// The class is based on a vector of unsigned ints of type UInt_t. Normally,
// never more than the lower half of the bits of any UInt_t will be used.
// The number of used bits is stored in [s_num_bits] and the maximum value
// of any UInt_t is stored in [s_max_val].
//
// This means any multiplication or addition can be done value-wise and still
// fit into the UInt_t. After all the value-wise calculations are done, these
// results may be higher than [s_max_val] but will never have overflowed. Then
// all values are checked in consolidate() to make sure they confirm to the
// internal structure of the class. This methods allows for fast calculation.
// ############################################################################

#include <iosfwd>    // forward declarations of std::ostream, std::istream
#include <stdexcept> // std::runtime_error
#include <vector>    // std::vector

namespace Unlimited {

class Int; // forward declaration for UInt to Int conversion

class UInt {

  // Main integer unit. May be any unsigned int type (not char/bool).
  typedef unsigned long long UInt_t;

  // Contains the upper limit of bits which may be used in an UInt_t.
  static size_t const s_num_bits;

  // Contains the upper limit for the value of the UInt_t.
  static UInt_t const s_max_val;

  // Private data member: stores the number in base [s_max_val].
  std::vector<UInt_t> d_number;

public:
  // Unsigned integer and default constructor.
  UInt(unsigned long long int = 0);

  // String constructor, uses Str_UInt.
  explicit UInt(std::string const &);

  // Int constructor.
  explicit UInt(Int const &);

  // Arithmetic assignment operators.
  UInt &operator+=(UInt const &); // implementation
  UInt &operator-=(UInt const &); // implementation
  UInt &operator*=(UInt const &); // wraps * inline
  UInt &operator/=(UInt const &); // wraps / inline
  UInt &operator%=(UInt const &); // wraps % inline

  // Free function op* needs access to d_number.
  friend UInt operator*(UInt const &, UInt const &); // implementation

  // Division method, taking divisor, result and modulus.
  void divide(UInt const &, UInt &, UInt &) const;

  // Power method, taking exponent.
  UInt &pow(UInt const &);       // changes object
  UInt powc(UInt const &) const; // returns new object

  // Square root method
  UInt &sqrt();       // changes object
  UInt sqrtc() const; // returns new object

  // Increment and decrement operators, defined inline below.
  UInt operator++(int); // postfix
  UInt operator--(int); // postfix
  UInt &operator++();   // prefix
  UInt &operator--();   // prefix

  // Bitwise assignment operators
  UInt &operator&=(UInt const &); // implementation
  UInt &operator|=(UInt const &); // implementation
  UInt &operator^=(UInt const &); // implementation
  UInt &operator<<=(unsigned);    // implementation
  UInt &operator>>=(unsigned);    // wraps >> inline

  UInt operator<<(unsigned) const; // wraps <<= inline
  UInt operator>>(unsigned) const; // implementation

  // Individual bit access methods.
  size_t num_bits() const;    // inline
  bool bit(size_t) const;     // inline
  void set_bit(size_t, bool); // implementation

  // Comparison method.
  int compare(UInt const &) const; // implementation

  // Bool operator, explicit.
  explicit operator bool() const;

  // Unsigned long long conversion method.
  unsigned long long ull() const;

  // String conversion method.
  std::string str() const; // implementation

  // Swap method, defined inline.
  void swap(UInt &);

  // Error class.
  class Exception : public std::runtime_error {
  public:
    Exception(std::string const &s) : std::runtime_error(s){};
  };

private:
  // Method consolidate: restores internal representation.
  void consolidate();

  // Method remove_leading_zeroes: defined inline in uint.ih.
  void remove_leading_zeroes();

}; // end class UInt

// Declaration of stream insert and extract operators.
std::ostream &operator<<(std::ostream &, UInt const &);
std::istream &operator>>(std::istream &, UInt &);

// Definition of free functions.
// Definition of free binary arithmetic operators.
inline UInt operator+(UInt const &rhs, UInt const &lhs) {
  UInt out(rhs);
  out += lhs;
  return out;
}

inline UInt operator-(UInt const &rhs, UInt const &lhs) {
  UInt out(rhs);
  out -= lhs;
  return out;
}

inline UInt operator/(UInt const &rhs, UInt const &lhs) {
  UInt out(rhs);
  out /= lhs;
  return out;
}

inline UInt operator%(UInt const &rhs, UInt const &lhs) {
  UInt out(rhs);
  out %= lhs;
  return out;
}

// Definition of free comparison operators.
// Definition of comparison operators.
inline bool operator==(UInt const &rhs, UInt const &lhs) {
  return !rhs.compare(lhs);
}

inline bool operator!=(UInt const &rhs, UInt const &lhs) {
  return rhs.compare(lhs);
}

inline bool operator<(UInt const &rhs, UInt const &lhs) {
  return rhs.compare(lhs) < 0;
}

inline bool operator>(UInt const &rhs, UInt const &lhs) {
  return rhs.compare(lhs) > 0;
}

inline bool operator<=(UInt const &rhs, UInt const &lhs) {
  return rhs.compare(lhs) <= 0;
}

inline bool operator>=(UInt const &rhs, UInt const &lhs) {
  return rhs.compare(lhs) >= 0;
}

// Definition of free bitwise operators.
inline UInt operator&(UInt const &rhs, UInt const &lhs) {
  UInt out(rhs);
  out &= lhs;
  return out;
}

inline UInt operator|(UInt const &rhs, UInt const &lhs) {
  UInt out(rhs);
  out |= lhs;
  return out;
}

inline UInt operator^(UInt const &rhs, UInt const &lhs) {
  UInt out(rhs);
  out ^= lhs;
  return out;
}

// Definition of all inline class methods below.
// Definition of wrappers for arithmetic operators.
inline UInt &UInt::operator*=(UInt const &oth) { return *this = *this * oth; }

inline UInt &UInt::operator/=(UInt const &oth) {
  UInt res, mod;
  divide(oth, res, mod);
  return *this = std::move(res);
}

inline UInt &UInt::operator%=(UInt const &oth) {
  UInt res, mod;
  divide(oth, res, mod);
  return *this = std::move(mod);
}

// Definition of constant power method.
inline UInt UInt::powc(UInt const &oth) const {
  UInt out(*this);
  out.pow(oth);
  return out;
}

// Definition of constant sqrt method.
inline UInt UInt::sqrtc() const {
  UInt out(*this);
  out.sqrt();
  return out;
}

// Definition of increment & decrement operators.
inline UInt UInt::operator++(int) {
  UInt out(*this);
  ++*this;
  return out;
}

inline UInt UInt::operator--(int) {
  UInt out(*this);
  --*this;
  return out;
}

inline UInt &UInt::operator++() { return *this += 1; }

inline UInt &UInt::operator--() { return *this -= 1; }

// Definition of rightshift assign operator.
inline UInt &UInt::operator>>=(unsigned n) { return *this = *this >> n; }

// Definition of leftshift operator.
inline UInt UInt::operator<<(unsigned n) const {
  UInt out(*this);
  out <<= n;
  return out;
}

// Definition of individual bit access methods.
// Method num_bits() returns the number of bits the UInt has in use.
inline size_t UInt::num_bits() const { return d_number.size() * s_num_bits; }

// Method bit(pos) returns true if bit at pos is set.
inline bool UInt::bit(size_t pos) const {
  size_t const idx = pos / s_num_bits;
  if (idx >= d_number.size())
    return 0;
  pos %= s_num_bits;
  return d_number[idx] & (UInt_t(1) << pos);
}

// The bool operator does not use compare() to avoid the overhead of
// constructing UInt(0) for each comparison.
// Declared 'explicit' which avoids trouble.
inline UInt::operator bool() const {
  return d_number.size() != 1 || d_number[0];
}

// Implementation of swap method, using std::vector::swap().
inline void UInt::swap(UInt &oth) { d_number.swap(oth.d_number); }

UInt operator*(UInt const &, UInt const &);

} // end namespace Unlimited

#endif
