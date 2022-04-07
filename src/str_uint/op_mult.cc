#include "str_uint.ih"

// ############################################################################
// Multiplication operator: implements multiplication.
// Multiplication is done digit by digit. This is possible because each digit
// < 10, so the highest multiplication result is 9 * 9 = 81 which can be stored
// in a char. Overflow is dealt with right away.
// Friend method of Str_UInt.
// ############################################################################

Unlimited::Str_UInt Unlimited::operator*(Str_UInt const &rhs,
                                         Str_UInt const &lhs) {

  if (!lhs || !rhs)
    return Str_UInt(0);

  size_t const len = rhs.length();
  size_t const o_len = lhs.length();

  Str_UInt out;
  out.d_number = std::string(len + o_len - 1, '0');

  for (size_t cidx = 0; cidx < len; ++cidx) {
    for (size_t oidx = 0; oidx < o_len; ++oidx) {

      // Multiply.
      int res = (rhs.d_number[cidx] - '0') * (lhs.d_number[oidx] - '0');
      out.d_number[cidx + oidx] += res;

      // Deal with any overflow.
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
