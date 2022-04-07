#ifndef INCL_UNLIMITED_STR_UINT_H
#define INCL_UNLIMITED_STR_UINT_H

// ############################################################################
// Str_UInt is a slow, unlimited unsigned int supporting:
// - Implicit unsigned integer and string construction;
// - Addition and subtraction;
// - Multiplication, division and modulus (division/modulus is notably slow);
// - Equality comparison;
// - String conversion, stream insertion and extraction.
//
// The class is based on a string representation of the number and performs all
// calculations in this form. This means arithmatic is slow while conversion to
// string (and thus printing) is very fast.
//
// Use this class when heavy string conversion or manipulation is required. In
// almost all cases the use of UInt is recommended over this class.
//
// Str_UInt is used in UInt to convert from and to base-10.
// ############################################################################

#include <iosfwd>    // forward declarations of std::ostream, std::istream
#include <stdexcept> // std::runtime_error
#include <string>    // std::string

namespace Unlimited {

class Str_UInt {

  // Private data member: stores the (reversed) number internally.
  std::string d_number;

public:
  // Unsigned integer and default constructor.
  Str_UInt(unsigned long long = 0);

  // String constructor.
  explicit Str_UInt(std::string const &);

  // Arithmetic assignment operators.
  Str_UInt &operator+=(Str_UInt const &); // implementation
  Str_UInt &operator-=(Str_UInt const &); // implementation
  Str_UInt &operator*=(Str_UInt const &); // wraps * inline
  Str_UInt &operator/=(Str_UInt const &); // wraps divide inline
  Str_UInt &operator%=(Str_UInt const &); // wraps divide inline

  // Friend op* method, needs direct access to d_number.
  friend Str_UInt operator*(Str_UInt const &, Str_UInt const &);

  // Division method, taking divisor, result and modulus.
  void divide(Str_UInt const &, Str_UInt &, Str_UInt &) const;

  // Increment and decrement operators, defined inline below.
  Str_UInt operator++(int); // postfix increment, wraps operator+=
  Str_UInt operator--(int); // postfix decrement, wraps operator-=
  Str_UInt &operator++();   // prefix increment, wraps operator+=
  Str_UInt &operator--();   // prefix decrement, wraps operator-=

  // Comparison method, wraps std::string compare() inline.
  int compare(Str_UInt const &) const;

  // Friend compare methods, need direct access to d_number.
  friend bool operator==(Str_UInt const &, Str_UInt const &);
  friend bool operator!=(Str_UInt const &, Str_UInt const &);

  // Bool operator, explicit to avoid all sorts of trouble.
  explicit operator bool() const; // C++11

  // Methods for getting length and individual digits, all inline.
  size_t length() const;
  size_t digit(size_t) const;
  void digit(size_t, size_t);

  // String representation method.
  std::string str() const;

  // Exception class.
  class Exception : public std::runtime_error {
  public:
    Exception(std::string const &s) : std::runtime_error(s){};
  };

private:
  // Method for removing leading zeroes, inline in str_uint.ih.
  void remove_leading_zeroes();
}; // end class Str_UInt

Str_UInt operator*(Str_UInt const &, Str_UInt const &);

// Declaration of stream insert and extract operators, free functions.
std::ostream &operator<<(std::ostream &, Str_UInt const &);
std::istream &operator>>(std::istream &, Str_UInt &);

// Definition of inline free functions.
// Definition of (free) atrimetic operators.
// Note: operator* is defined in op_mult.cc.
inline Str_UInt operator+(Str_UInt const &rhs, Str_UInt const &lhs) {
  Str_UInt out(rhs);
  out += lhs;
  return out;
}

inline Str_UInt operator-(Str_UInt const &rhs, Str_UInt const &lhs) {
  Str_UInt out(rhs);
  out -= lhs;
  return out;
}

inline Str_UInt operator/(Str_UInt const &rhs, Str_UInt const &lhs) {
  Str_UInt out(rhs);
  out /= lhs;
  return out;
}

inline Str_UInt operator%(Str_UInt const &rhs, Str_UInt const &lhs) {
  Str_UInt out(rhs);
  out %= lhs;
  return out;
}

// Definition of (free) comparison operators.
inline bool operator==(Str_UInt const &rhs, Str_UInt const &lhs) {
  return !rhs.d_number.compare(lhs.d_number); // friend
}

inline bool operator!=(Str_UInt const &rhs, Str_UInt const &lhs) {
  return rhs.d_number.compare(lhs.d_number); // friend
}

inline bool operator<=(Str_UInt const &rhs, Str_UInt const &lhs) {
  return rhs.length() < lhs.length() ||
         (rhs.length() == lhs.length() && rhs.compare(lhs) <= 0);
}

inline bool operator>=(Str_UInt const &rhs, Str_UInt const &lhs) {
  return rhs.length() > lhs.length() ||
         (rhs.length() == lhs.length() && rhs.compare(lhs) >= 0);
}

inline bool operator<(Str_UInt const &rhs, Str_UInt const &lhs) {
  return rhs.length() < lhs.length() ||
         (rhs.length() == lhs.length() && rhs.compare(lhs) < 0);
}

inline bool operator>(Str_UInt const &rhs, Str_UInt const &lhs) {
  return rhs.length() > lhs.length() ||
         (rhs.length() == lhs.length() && rhs.compare(lhs) > 0);
}

// Definition of all inline class methods below.
// Definition of wrappers for arithmetic operators.
inline Str_UInt &Str_UInt::operator*=(Str_UInt const &oth) {
  return *this = *this * oth;
}

inline Str_UInt &Str_UInt::operator/=(Str_UInt const &oth) {
  Str_UInt out, mod;
  divide(oth, out, mod);
  return *this = out;
}

inline Str_UInt &Str_UInt::operator%=(Str_UInt const &oth) {
  Str_UInt out, mod;
  divide(oth, out, mod);
  return *this = mod;
}

// Definition of increment & decrement operators.
inline Str_UInt Str_UInt::operator++(int) {
  Str_UInt copy(*this);
  ++*this;
  return copy;
}

inline Str_UInt Str_UInt::operator--(int) {
  Str_UInt copy(*this);
  --*this;
  return copy;
}

inline Str_UInt &Str_UInt::operator++() { return *this += 1; }

inline Str_UInt &Str_UInt::operator--() { return *this -= 1; }

// Definition of comparison method.
// Must reverse d_number before comparing.
inline int Str_UInt::compare(Str_UInt const &o) const {
  return str().compare(o.str());
}

// Definition of operator bool.
inline Str_UInt::operator bool() const {
  return d_number.length() != 1 || d_number[0] != '0';
}

// Definition of length, access methods.
inline size_t Str_UInt::length() const { return d_number.length(); }

inline size_t Str_UInt::digit(size_t idx) const {
  return d_number[length() - idx - 1] - '0'; // assume idx for speed
}

inline void Str_UInt::digit(size_t idx, size_t val) {
  if (val > 9)
    throw Exception("digit error: invalid value");
  d_number[length() - idx - 1] = val + '0'; // assume idx
}
} // end namespace Unlimited

#endif
