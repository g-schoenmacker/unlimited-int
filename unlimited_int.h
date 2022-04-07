#ifndef INCL_UNLIMITED_INT_H_1
#define INCL_UNLIMITED_INT_H_1

// ############################################################################
// Unlimited-int library full header: contains all definition.
// Version 1.0.
// Project can be found at https://github.com/g-schoenmacker/unlimited-int/
// ############################################################################

#include <algorithm>
#include <istream>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace Unlimited {

// ############################################################################

class Str_UInt;
bool operator<(Str_UInt const &, Str_UInt const &);
bool operator>(Str_UInt const &, Str_UInt const &);

class Str_UInt {

  std::string d_number;

public:
  // ####################################################################
  Str_UInt(unsigned long long val = 0) {
    std::ostringstream ss;
    ss << val;
    d_number = ss.str();
    std::reverse(d_number.begin(), d_number.end());
  }

  // ####################################################################
  explicit Str_UInt(std::string const &number) : d_number(number) {
    if (d_number.empty())
      throw Exception("Str_UInt error: empty string construction");
    for (size_t idx = 0; idx < d_number.size(); ++idx) {
      if (d_number[idx] < '0' || d_number[idx] > '9')
        throw Exception(std::string("Str_UInt(string) error: '") + d_number +
                        "' is not a valid number");
    }

    std::reverse(d_number.begin(), d_number.end());
    remove_leading_zeroes();
  }

  // ####################################################################
  Str_UInt &operator+=(Str_UInt const &oth) {
    size_t const o_len = oth.length();
    if (length() < o_len)
      d_number += std::string(o_len - length(), '0');

    for (size_t idx = 0; idx < o_len; ++idx) {
      d_number[idx] += oth.d_number[idx] - '0';

      for (size_t cidx = idx; d_number[cidx] > '9'; ++cidx) {
        if (cidx + 1 == length())
          d_number += std::string("1");
        else
          ++d_number[cidx + 1];
        d_number[cidx] -= 10;
      }
    }

    return *this;
  }

  // ####################################################################
  Str_UInt &operator-=(Str_UInt const &oth) {
    if (*this < oth)
      throw Exception("operator-= error: Underflow detected");

    size_t const o_len = oth.length();
    for (size_t idx = 0; idx < o_len; ++idx) {

      if (d_number[idx] >= oth.d_number[idx]) {
        d_number[idx] -= oth.d_number[idx] - '0';
        continue;
      }

      size_t cidx = idx + 1;
      while (d_number[cidx] == '0')
        d_number[cidx++] = '9';
      --d_number[cidx];

      d_number[idx] += ('9' + 1) - oth.d_number[idx];
    }
    remove_leading_zeroes();
    return *this;
  }

  // ####################################################################
  Str_UInt &operator*=(Str_UInt const &oth) { return *this = *this * oth; }

  // ####################################################################
  Str_UInt &operator/=(Str_UInt const &oth) {
    Str_UInt out, mod;
    divide(oth, out, mod);
    return *this = out;
  }

  // ####################################################################
  Str_UInt &operator%=(Str_UInt const &oth) {
    Str_UInt out, mod;
    divide(oth, out, mod);
    return *this = mod;
  }

  // ####################################################################
  friend Str_UInt operator*(Str_UInt const &, Str_UInt const &);

  // ####################################################################
  void divide(Str_UInt const &oth, Str_UInt &res, Str_UInt &mod) const {
    if (!oth)
      throw Exception("divide error: Division by zero");

    res = Str_UInt(0);
    mod = *this;

    size_t const o_len = oth.d_number.length();
    size_t const o_sig = oth.d_number[o_len - 1] - '0';

    while (mod > oth) {
      size_t const m_len = mod.d_number.length();
      Str_UInt pow_10(std::string("1") + std::string(m_len - o_len, '0'));

      size_t m_sig = mod.d_number[m_len - 1] - '0';

      if (pow_10 * oth > mod) {
        pow_10.d_number.erase(0, 1);
        m_sig = m_sig * 10 + mod.d_number[m_len - 2] - '0';
      }

      size_t small_factor = m_sig / o_sig;
      if (small_factor < 2) {
        mod -= pow_10 * oth;
        res += pow_10;
        continue;
      }

      Str_UInt factor(pow_10 * small_factor);
      Str_UInt mod_diff(factor * oth);

      while (mod_diff > mod) {
        factor = --small_factor == 1 ? pow_10 : pow_10 * small_factor;
        mod_diff = factor * oth;
      }

      mod -= mod_diff;
      res += factor;
    }
  }

  // ####################################################################
  Str_UInt operator++(int) {
    Str_UInt copy(*this);
    ++*this;
    return copy;
  }

  // ####################################################################
  Str_UInt operator--(int) {
    Str_UInt copy(*this);
    --*this;
    return copy;
  }

  // ####################################################################
  Str_UInt &operator++() { return *this += 1; }

  // ####################################################################
  Str_UInt &operator--() { return *this -= 1; }

  // ####################################################################
  int compare(Str_UInt const &o) const { return str().compare(o.str()); }

  // ####################################################################
  friend bool operator==(Str_UInt const &, Str_UInt const &);

  // ####################################################################
  friend bool operator!=(Str_UInt const &, Str_UInt const &);

  // ####################################################################
  explicit operator bool() const // C++11
  {
    return d_number.length() != 1 || d_number[0] != '0';
  }

  // ####################################################################
  size_t length() const { return d_number.length(); }

  // ####################################################################
  size_t digit(size_t idx) const { return d_number[length() - idx - 1] - '0'; }

  // ####################################################################
  void digit(size_t idx, size_t val) {
    if (val > 9)
      throw Exception("digit error: invalid value");
    d_number[length() - idx - 1] = val + '0';
  }

  // ####################################################################
  std::string str() const {
    std::string out(d_number);
    std::reverse(out.begin(), out.end());
    return out;
  }

  // ####################################################################
  class Exception : public std::runtime_error {
  public:
    Exception(std::string const &s) : std::runtime_error(s){};
  };

private:
  // ####################################################################
  void remove_leading_zeroes() {
    size_t len = length() - 1;
    while (len && d_number[len] == '0')
      d_number.erase(len--, 1);
  }
};

// ########################################################################
inline Str_UInt operator*(Str_UInt const &rhs, Str_UInt const &lhs) {
  if (!lhs || !rhs)
    return Str_UInt(0);

  size_t const len = rhs.length();
  size_t const o_len = lhs.length();

  Str_UInt out;
  out.d_number = std::string(len + o_len - 1, '0');

  for (size_t cidx = 0; cidx < len; ++cidx) {
    for (size_t oidx = 0; oidx < o_len; ++oidx) {
      int res = (rhs.d_number[cidx] - '0') * (lhs.d_number[oidx] - '0');
      out.d_number[cidx + oidx] += res;

      unsigned char c;
      for (size_t bidx = cidx + oidx;
           (c = static_cast<unsigned char>(out.d_number[bidx])) > '9'; ++bidx) {
        if (bidx + 1 == out.d_number.length())
          out.d_number += std::string("0");
        out.d_number[bidx + 1] += (c - '0') / 10;
        out.d_number[bidx] = (c - '0') % 10 + '0';
      }
    }
  }

  return out;
}

// ########################################################################
inline std::ostream &operator<<(std::ostream &os, Str_UInt const &s) {
  return os << s.str();
}

// ########################################################################
inline std::istream &operator>>(std::istream &is, Str_UInt &s) {
  std::string temp;
  if (!(is >> temp))
    return is;

  try {

    s = Str_UInt(temp);
  } catch (Str_UInt::Exception &e) {
    is.exceptions(std::istream::failbit);
  }

  return is;
}

// ########################################################################
inline Str_UInt operator+(Str_UInt const &rhs, Str_UInt const &lhs) {
  Str_UInt out(rhs);
  out += lhs;
  return out;
}

// ########################################################################
inline Str_UInt operator-(Str_UInt const &rhs, Str_UInt const &lhs) {
  Str_UInt out(rhs);
  out -= lhs;
  return out;
}

// ########################################################################
inline Str_UInt operator/(Str_UInt const &rhs, Str_UInt const &lhs) {
  Str_UInt out(rhs);
  out /= lhs;
  return out;
}

// ########################################################################
inline Str_UInt operator%(Str_UInt const &rhs, Str_UInt const &lhs) {
  Str_UInt out(rhs);
  out %= lhs;
  return out;
}

// ########################################################################
inline bool operator==(Str_UInt const &rhs, Str_UInt const &lhs) {
  return !rhs.d_number.compare(lhs.d_number);
}

// ########################################################################
inline bool operator!=(Str_UInt const &rhs, Str_UInt const &lhs) {
  return rhs.d_number.compare(lhs.d_number);
}

// ########################################################################
inline bool operator<=(Str_UInt const &rhs, Str_UInt const &lhs) {
  return rhs.length() < lhs.length() ||
         (rhs.length() == lhs.length() && rhs.compare(lhs) <= 0);
}

// ########################################################################
inline bool operator>=(Str_UInt const &rhs, Str_UInt const &lhs) {
  return rhs.length() > lhs.length() ||
         (rhs.length() == lhs.length() && rhs.compare(lhs) >= 0);
}

// ########################################################################
inline bool operator<(Str_UInt const &rhs, Str_UInt const &lhs) {
  return rhs.length() < lhs.length() ||
         (rhs.length() == lhs.length() && rhs.compare(lhs) < 0);
}

// ########################################################################
inline bool operator>(Str_UInt const &rhs, Str_UInt const &lhs) {
  return rhs.length() > lhs.length() ||
         (rhs.length() == lhs.length() && rhs.compare(lhs) > 0);
}

// ############################################################################

class Int;
class UInt;
bool operator!=(UInt const &, UInt const &);
bool operator<(UInt const &, UInt const &);
bool operator>(UInt const &, UInt const &);
bool operator>=(UInt const &, UInt const &);

UInt operator+(UInt const &, UInt const &);

class UInt {

  typedef unsigned long long UInt_t;
  std::vector<UInt_t> d_number;

public:
  // ####################################################################
  UInt(unsigned long long int val = 0) {
    if (!val)
      d_number.push_back(0);

    while (val) {
      d_number.push_back(val % (UInt_t(1) << (sizeof(UInt_t) * 4)));
      val /= (UInt_t(1) << (sizeof(UInt_t) * 4));
    }
  }

  // ####################################################################
  explicit UInt(std::string const &inp) {
    Str_UInt val;
    try {
      val = Str_UInt(inp);
    } catch (Str_UInt::Exception &e) {
      throw Exception(e.what());
    }

    if (!val)
      d_number.push_back(0);

    while (val) {
      Str_UInt div, mod;
      val.divide(UInt_t(1) << (sizeof(UInt_t) * 4), div, mod);

      std::istringstream ss(mod.str());
      UInt_t temp;
      ss >> temp;

      d_number.push_back(temp);
      val = div;
    }
  }

  // ####################################################################
  UInt(Int const &);

  // ####################################################################
  UInt &operator+=(UInt const &oth) {
    if (d_number.size() < oth.d_number.size())
      d_number.resize(oth.d_number.size());

    for (size_t idx = 0; idx < oth.d_number.size(); ++idx)
      d_number[idx] += oth.d_number[idx];

    consolidate();
    return *this;
  }

  // ####################################################################
  UInt &operator-=(UInt const &oth) {
    if (*this < oth)
      throw Exception("operator-= error: Underflow detected");

    for (size_t idx = 0; idx < oth.d_number.size(); ++idx) {

      if (d_number[idx] >= oth.d_number[idx]) {
        d_number[idx] -= oth.d_number[idx];
        continue;
      }

      size_t cidx = idx + 1;
      while (!d_number[cidx])
        d_number[cidx++] = (UInt_t(1) << (sizeof(UInt_t) * 4)) - 1;

      --d_number[cidx];

      d_number[idx] += (UInt_t(1) << (sizeof(UInt_t) * 4)) - oth.d_number[idx];
    }

    remove_leading_zeroes();

    return *this;
  }

  // ####################################################################
  UInt &operator*=(UInt const &oth) { return *this = *this * oth; }

  // ####################################################################
  UInt &operator/=(UInt const &oth) {
    UInt res, mod;
    divide(oth, res, mod);
    return *this = std::move(res); // C++11
  }

  // ####################################################################
  UInt &operator%=(UInt const &oth) {
    UInt res, mod;
    divide(oth, res, mod);
    return *this = std::move(mod); // C++11
  }

  // ####################################################################
  friend UInt operator*(UInt const &, UInt const &);

  // ####################################################################
  void divide(UInt const &oth, UInt &res, UInt &mod) const {

    if (!oth)
      throw Exception("divide error: Division by zero");

    res = 0;
    res.d_number.resize(d_number.size());
    mod = 0;

    for (size_t i = num_bits(); i--;) {
      mod <<= 1;
      mod.set_bit(0, bit(i));

      if (mod.d_number.size() < oth.d_number.size())
        continue;

      if (mod.d_number.size() == oth.d_number.size()) {
        bool mod_is_smaller = false;
        for (size_t idx = mod.d_number.size(); idx--;) {
          if (mod.d_number[idx] == oth.d_number[idx])
            continue;
          mod_is_smaller = mod.d_number[idx] < oth.d_number[idx];
          break;
        }
        if (mod_is_smaller)
          continue;
      }

      mod -= oth;
      res.set_bit(i, 1);
    }

    res.remove_leading_zeroes();
  }

  // ####################################################################
  UInt &pow(UInt const &oth) {
    if (!oth)
      return *this = 1;

    UInt exp(oth);

    UInt const one(1);
    UInt left_over(1);
    while (exp != one) {
      if (exp.bit(0))
        left_over *= *this;
      *this *= *this;
      exp >>= 1;
    }

    return *this *= left_over;
  }

  // ####################################################################
  UInt powc(UInt const &oth) const {
    UInt out(*this);
    out.pow(oth);
    return out;
  }

  // ####################################################################
  UInt &sqrt() {
    UInt res, pbit;
    pbit.d_number.resize(d_number.size());
    pbit.set_bit(num_bits() - 2, 1);

    while (pbit > *this)
      pbit >>= 2;

    while (pbit) {
      UInt const t(res + pbit);
      res >>= 1;
      if (*this >= t) {
        *this -= t;
        res += pbit;
      }
      pbit >>= 2;
    }

    return *this = std::move(res); // C++11
  }

  // ####################################################################
  UInt sqrtc() const {
    UInt out(*this);
    out.sqrt();
    return out;
  }

  // ####################################################################
  UInt operator++(int) {
    UInt out(*this);
    ++*this;
    return out;
  }

  // ####################################################################
  UInt operator--(int) {
    UInt out(*this);
    --*this;
    return out;
  }

  // ####################################################################
  UInt &operator++() { return *this += 1; }

  // ####################################################################
  UInt &operator--() { return *this -= 1; }

  // ####################################################################
  UInt &operator&=(UInt const &oth) {
    if (d_number.size() > oth.d_number.size())
      d_number.resize(oth.d_number.size());

    for (size_t idx = d_number.size(); idx--;)
      d_number[idx] &= oth.d_number[idx];

    remove_leading_zeroes();

    return *this;
  }

  // ####################################################################
  UInt &operator|=(UInt const &oth) {
    if (d_number.size() < oth.d_number.size())
      d_number.resize(oth.d_number.size());

    for (size_t idx = oth.d_number.size(); idx--;)
      d_number[idx] |= oth.d_number[idx];

    return *this;
  }

  // ####################################################################
  UInt &operator^=(UInt const &oth) {
    if (d_number.size() < oth.d_number.size())
      d_number.resize(oth.d_number.size());

    for (size_t idx = oth.d_number.size(); idx--;)
      d_number[idx] ^= oth.d_number[idx];

    remove_leading_zeroes();
    return *this;
  }

  // ####################################################################
  UInt &operator<<=(unsigned n) {
    while (n) {
      size_t const shift = n > (sizeof(UInt_t) * 4) ? (sizeof(UInt_t) * 4) : n;
      n -= shift;
      for (size_t idx = 0; idx < d_number.size(); ++idx)
        d_number[idx] <<= shift;
      consolidate();
    }

    return *this;
  }

  // ####################################################################
  UInt &operator>>=(unsigned n) { return *this = *this >> n; }

  // ####################################################################
  UInt operator<<(unsigned n) const {
    UInt out(*this);
    out <<= n;
    return out;
  }

  // ####################################################################
  UInt operator>>(unsigned n) const {
    UInt out;
    out.d_number.resize(d_number.size());

    size_t const max_idx = num_bits() - n;
    for (size_t idx = 0; idx < max_idx; ++idx)
      out.set_bit(idx, bit(idx + n));

    out.remove_leading_zeroes();

    return out;
  }

  // ####################################################################
  size_t num_bits() const { return d_number.size() * (sizeof(UInt_t) * 4); }

  // ####################################################################
  bool bit(size_t pos) const {
    size_t const idx = pos / (sizeof(UInt_t) * 4);
    if (idx >= d_number.size())
      return 0;
    pos %= (sizeof(UInt_t) * 4);
    return d_number[idx] & (UInt_t(1) << pos);
  }

  // ####################################################################
  void set_bit(size_t pos, bool val) {
    size_t const idx = pos / (sizeof(UInt_t) * 4);

    if (idx >= d_number.size()) {
      if (!val)
        return;
      d_number.resize(idx + 1);
    }

    pos %= (sizeof(UInt_t) * 4);
    d_number[idx] = val ? d_number[idx] | UInt_t(UInt_t(1) << pos)
                        : d_number[idx] & UInt_t(~(UInt_t(1) << pos));

    if (!val && idx == d_number.size() - 1)
      remove_leading_zeroes();
  }

  // ####################################################################
  int compare(UInt const &oth) const {
    if (d_number.size() != oth.d_number.size())
      return d_number.size() > oth.d_number.size() ? 1 : -1;

    for (size_t idx = d_number.size(); idx--;) {
      if (d_number[idx] != oth.d_number[idx])
        return d_number[idx] > oth.d_number[idx] ? 1 : -1;
    }

    return 0;
  }

  // ####################################################################
  explicit operator bool() const // C++11
  {
    return d_number.size() != 1 || d_number[0];
  }

  // ####################################################################
  unsigned long long ull() const {
    unsigned long long out = 0;
    size_t const max =
        sizeof(out) * 8 < num_bits() ? sizeof(out) * 8 : num_bits();

    for (size_t idx = 0; idx < max; ++idx)
      if (bit(idx))
        out |= 1ULL << idx;

    return out;
  }

  // ####################################################################
  std::string str() const {
    Str_UInt power(1);
    Str_UInt const max_val((UInt_t(1) << (sizeof(UInt_t) * 4)));
    Str_UInt out;

    for (size_t idx = 0; idx < d_number.size(); ++idx) {
      out += Str_UInt(d_number[idx]) * power;
      power *= max_val;
    }

    return out.str();
  }

  // ####################################################################
  void swap(UInt &oth) { d_number.swap(oth.d_number); }

  // ####################################################################
  class Exception : public std::runtime_error {
  public:
    Exception(std::string const &s) : std::runtime_error(s){};
  };

private:
  // ####################################################################
  void consolidate() {
    size_t len = d_number.size();
    for (size_t idx = 0; idx < len; ++idx) {

      if (d_number[idx] < (UInt_t(1) << (sizeof(UInt_t) * 4)))
        continue;

      if (idx + 1 == len) {
        d_number.push_back(d_number[idx] / (UInt_t(1) << (sizeof(UInt_t) * 4)));
        ++len;
      } else {
        d_number[idx + 1] +=
            d_number[idx] / (UInt_t(1) << (sizeof(UInt_t) * 4));
      }

      d_number[idx] %= (UInt_t(1) << (sizeof(UInt_t) * 4));
    }
  }

  // ####################################################################
  void remove_leading_zeroes() {
    size_t len = d_number.size() - 1;
    while (len && !d_number[len])
      d_number.erase(d_number.begin() + len--);
  }
};

// ########################################################################
inline std::ostream &operator<<(std::ostream &os, UInt const &s) {
  return os << s.str();
}

// ########################################################################
inline std::istream &operator>>(std::istream &is, UInt &s) {
  std::string temp;
  if (!(is >> temp))
    return is;

  try {
    s = UInt(temp);
  } catch (Str_UInt::Exception &e) {
    is.exceptions(std::istream::failbit);
  }

  return is;
}

// ########################################################################
inline UInt operator+(UInt const &rhs, UInt const &lhs) {
  UInt out(rhs);
  out += lhs;
  return out;
}

// ########################################################################
inline UInt operator-(UInt const &rhs, UInt const &lhs) {
  UInt out(rhs);
  out -= lhs;
  return out;
}

// ########################################################################
inline UInt operator*(UInt const &rhs, UInt const &lhs) {
  UInt res;
  if (!lhs || !rhs)
    return res;

  res.d_number.resize(rhs.d_number.size() + lhs.d_number.size() - 1);
  for (size_t lidx = 0; lidx < lhs.d_number.size(); ++lidx) {
    for (size_t idx = 0; idx < rhs.d_number.size(); ++idx)
      res.d_number[idx + lidx] += rhs.d_number[idx] * lhs.d_number[lidx];
    res.consolidate();
  }

  return res;
}

// ########################################################################
inline UInt operator/(UInt const &rhs, UInt const &lhs) {
  UInt out(rhs);
  out /= lhs;
  return out;
}

// ########################################################################
inline UInt operator%(UInt const &rhs, UInt const &lhs) {
  UInt out(rhs);
  out %= lhs;
  return out;
}

// ########################################################################
inline bool operator==(UInt const &rhs, UInt const &lhs) {
  return !rhs.compare(lhs);
}

// ########################################################################
inline bool operator!=(UInt const &rhs, UInt const &lhs) {
  return rhs.compare(lhs);
}

// ########################################################################
inline bool operator<(UInt const &rhs, UInt const &lhs) {
  return rhs.compare(lhs) < 0;
}

// ########################################################################
inline bool operator>(UInt const &rhs, UInt const &lhs) {
  return rhs.compare(lhs) > 0;
}

// ########################################################################
inline bool operator<=(UInt const &rhs, UInt const &lhs) {
  return rhs.compare(lhs) <= 0;
}

// ########################################################################
inline bool operator>=(UInt const &rhs, UInt const &lhs) {
  return rhs.compare(lhs) >= 0;
}

// ########################################################################
inline UInt operator&(UInt const &rhs, UInt const &lhs) {
  UInt out(rhs);
  out &= lhs;
  return out;
}

// ########################################################################
inline UInt operator|(UInt const &rhs, UInt const &lhs) {
  UInt out(rhs);
  out |= lhs;
  return out;
}

// ########################################################################
inline UInt operator^(UInt const &rhs, UInt const &lhs) {
  UInt out(rhs);
  out ^= lhs;
  return out;
}

// ############################################################################

class Int {

  friend class UInt;
  bool d_negative;
  UInt d_number;

public:
  // ####################################################################
  Int(long long int n = 0) : d_negative(n < 0), d_number(n < 0 ? -n : n) {}

  // ####################################################################
  explicit Int(std::string const &inp) : d_negative(inp[0] == '-') {
    try {
      if (d_negative) {
        std::string cinp(inp);
        cinp.erase(0, 1);
        d_number = UInt(cinp);
      } else
        d_number = UInt(inp);
    } catch (UInt::Exception &e) {
      throw Exception(e.what());
    }

    if (!d_number)
      d_negative = false;
  }

  // ####################################################################
  explicit Int(UInt const &uint) : d_negative(false), d_number(uint) {}

  // ####################################################################
  Int &operator+=(Int const &oth) {
    if (d_negative == oth.d_negative)
      d_number += oth.d_number;
    else {
      if (d_number < oth.d_number) {
        d_negative = !d_negative;
        d_number = oth.d_number - d_number;
      } else if (!(d_number -= oth.d_number))
        d_negative = false;
    }

    return *this;
  }

  // ####################################################################
  Int &operator-=(Int const &oth) {
    if (d_negative == oth.d_negative) {
      if (d_number < oth.d_number) {
        d_negative = !d_negative;
        d_number = oth.d_number - d_number;
      } else if (!(d_number -= oth.d_number))
        d_negative = false;
    } else {
      d_number += oth.d_number;
    }
    return *this;
  }

  // ####################################################################
  Int &operator*=(Int const &oth) {
    d_negative =
        (d_negative && !oth.d_negative) || (!d_negative && oth.d_negative);
    d_number *= oth.d_number;
    return *this;
  }

  // ####################################################################
  Int &operator/=(Int const &oth) {
    Int res, mod;
    divide(oth, res, mod);
    return *this = res;
  }

  // ####################################################################
  Int &operator%=(Int const &oth) {
    Int res, mod;
    divide(oth, res, mod);
    return *this = mod;
  }

  // ####################################################################
  Int operator-() const {
    Int out(*this);
    if (d_number)
      out.d_negative = !d_negative;
    return out;
  }

  // ####################################################################
  void divide(Int const &oth, Int &res, Int &mod) const {
    try {
      d_number.divide(oth.d_number, res.d_number, mod.d_number);
    } catch (UInt::Exception &c) {
      throw Exception(c.what());
    }

    res.d_negative =
        (d_negative && !oth.d_negative) || (!d_negative && oth.d_negative);
    mod.d_negative = mod.d_number && oth.d_negative;
    if (res.d_negative && mod.d_number) {
      ++res.d_number;
      mod.d_number = oth.d_number - mod.d_number;
    }
  }

  // ####################################################################
  Int &pow(Int const &exp) {
    if (exp.d_negative)
      throw Exception("pow error: Exponent may not be negative");
    d_number.pow(exp.d_number);
    d_negative = d_negative ? exp.bit(0) : false;
    return *this;
  }

  // ####################################################################
  Int powc(Int const &exp) const {
    Int out(*this);
    out.pow(exp);
    return out;
  }

  // ####################################################################
  Int &sqrt() {
    if (d_negative)
      throw Exception("sqrt error: Can not take sqrt of negative "
                      "number (result would be complex)");
    d_number.sqrt();
    return *this;
  }

  // ####################################################################
  Int sqrtc() const {
    Int out(*this);
    out.sqrt();
    return out;
  }

  // ####################################################################
  Int operator++(int) {
    Int out(*this);
    ++*this;
    return out;
  }

  // ####################################################################
  Int operator--(int) {
    Int out(*this);
    --*this;
    return out;
  }

  // ####################################################################
  Int &operator++() { return *this += 1; }

  // ####################################################################
  Int &operator--() { return *this -= 1; }

  // ####################################################################
  Int &operator&=(Int const &oth) {
    d_number &= oth.d_number;
    d_negative = d_negative && oth.d_negative;
    return *this;
  }

  // ####################################################################
  Int &operator|=(Int const &oth) {
    d_number |= oth.d_number;
    d_negative = d_negative || oth.d_negative;
    return *this;
  }

  // ####################################################################
  Int &operator^=(Int const &oth) {
    d_number ^= oth.d_number;
    d_negative =
        (d_negative && !oth.d_negative) || (!d_negative && oth.d_negative);
    return *this;
  }

  // ####################################################################
  Int &operator<<=(unsigned n) {
    d_number <<= n;
    return *this;
  }

  // ####################################################################
  Int &operator>>=(unsigned n) {
    d_number >>= n;
    return *this;
  }

  // ####################################################################
  Int operator<<(unsigned n) const {
    Int out(*this);
    out <<= n;
    return out;
  }

  // ####################################################################
  Int operator>>(unsigned n) const {
    Int out(*this);
    out >>= n;
    return out;
  }

  // ####################################################################
  size_t num_bits() const { return d_number.num_bits(); }

  // ####################################################################
  bool bit(size_t pos) const { return d_number.bit(pos); }

  // ####################################################################
  void set_bit(size_t pos, bool val) { d_number.set_bit(pos, val); }

  // ####################################################################
  int compare(Int const &oth) const {
    if (!d_negative && oth.d_negative)
      return 1;

    if (d_negative && !oth.d_negative)
      return -1;

    return d_negative ? -d_number.compare(oth.d_number)
                      : d_number.compare(oth.d_number);
  }

  // ####################################################################
  explicit operator bool() const // C++11
  {
    return !!d_number;
  }

  // ####################################################################
  long long ll() const {
    long long out = 0;
    size_t const max =
        (sizeof(out) - 1) * 8 < num_bits() ? (sizeof(out) - 1) * 8 : num_bits();
    for (size_t idx = 0; idx < max; ++idx)
      if (bit(idx))
        out |= 1ULL << idx;
    return d_negative ? -out : out;
  }

  // ####################################################################
  std::string str() const {
    return d_negative ? std::string("-") + d_number.str() : d_number.str();
  }

  // ####################################################################
  void swap(Int &oth) {
    bool temp = d_negative;
    d_negative = oth.d_negative;
    oth.d_negative = temp;
    d_number.swap(oth.d_number);
  }

  // ####################################################################
  class Exception : public std::runtime_error {
  public:
    Exception(std::string const &s) : std::runtime_error(s){};
  };
};

// ########################################################################
inline std::ostream &operator<<(std::ostream &os, Int const &s) {
  return os << s.str();
}

// ########################################################################
inline std::istream &operator>>(std::istream &is, Int &s) {
  std::string temp;
  if (!(is >> temp))
    return is;

  try {
    s = Int(temp);
  } catch (UInt::Exception &e) {
    is.exceptions(std::istream::failbit);
  }

  return is;
}

// ########################################################################
inline Int operator+(Int const &rhs, Int const &lhs) {
  Int out(rhs);
  out += lhs;
  return out;
}

// ########################################################################
inline Int operator-(Int const &rhs, Int const &lhs) {
  Int out(rhs);
  out -= lhs;
  return out;
}

// ########################################################################
inline Int operator*(Int const &rhs, Int const &lhs) {
  Int out(rhs);
  out *= lhs;
  return out;
}

// ########################################################################
inline Int operator/(Int const &rhs, Int const &lhs) {
  Int out(rhs);
  out /= lhs;
  return out;
}

// ########################################################################
inline Int operator%(Int const &rhs, Int const &lhs) {
  Int out(rhs);
  out %= lhs;
  return out;
}

// ########################################################################
inline bool operator==(Int const &rhs, Int const &lhs) {
  return !rhs.compare(lhs);
}

// ########################################################################
inline bool operator!=(Int const &rhs, Int const &lhs) {
  return rhs.compare(lhs);
}

// ########################################################################
inline bool operator<(Int const &rhs, Int const &lhs) {
  return rhs.compare(lhs) < 0;
}

// ########################################################################
inline bool operator>(Int const &rhs, Int const &lhs) {
  return rhs.compare(lhs) > 0;
}

// ########################################################################
inline bool operator<=(Int const &rhs, Int const &lhs) {
  return rhs.compare(lhs) <= 0;
}

// ########################################################################
inline bool operator>=(Int const &rhs, Int const &lhs) {
  return rhs.compare(lhs) >= 0;
}

// ########################################################################
inline Int operator&(Int const &rhs, Int const &lhs) {
  Int out(rhs);
  out &= lhs;
  return out;
}

// ########################################################################
inline Int operator|(Int const &rhs, Int const &lhs) {
  Int out(rhs);
  out |= lhs;
  return out;
}

// ########################################################################
inline Int operator^(Int const &rhs, Int const &lhs) {
  Int out(rhs);
  out ^= lhs;
  return out;
}

// ########################################################################
inline UInt::UInt(Int const &val) : d_number(val.d_number.d_number) {}

// ############################################################################

} // namespace Unlimited

#endif
