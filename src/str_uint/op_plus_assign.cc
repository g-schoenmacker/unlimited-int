#include "str_uint.ih"

// ############################################################################
// Addition operator: implements addition.
// Addition goes digit by digit. Overflows are resolved immediately.
// ############################################################################

Unlimited::Str_UInt &Unlimited::Str_UInt::operator+=(Str_UInt const &oth) {

  size_t const o_len = oth.length();

  // Make sure [*this] is at least as big as [oth].
  if (length() < o_len)
    d_number += std::string(o_len - length(), '0');

  // Loop over all digits of oth, adding them to this.
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
