#include "str_uint.ih"

// ############################################################################
// Subtraction-assignment operator: implements subtraction.
// Subtraction goes digit by digit. If there's no carry, the action is easy.
// Otherwise, we find the first non-zero more significant number and take what
// we need from there.
// ############################################################################

Unlimited::Str_UInt &Unlimited::Str_UInt::operator-=(Str_UInt const &oth) {

  if (*this < oth)
    throw Exception("operator-= error: Underflow detected");

  // Now we know [*this] is larger than [oth].
  size_t const o_len = oth.length();
  for (size_t idx = 0; idx < o_len; ++idx) {

    if (d_number[idx] >= oth.d_number[idx]) {
      // Simple case, no carry.
      d_number[idx] -= oth.d_number[idx] - '0';
      continue;
    }

    // We need to steal 1 from the next digit.
    // Find the next non-zero digit, setting all zero-digits to 9 (or its
    // equivalent). There has to be one, because [*this] > [oth].
    size_t cidx = idx + 1;
    while (d_number[cidx] == '0')
      d_number[cidx++] = '9';
    --d_number[cidx]; // decrement first non-zero number

    // Now that we've done the bookkeeping*, we can set the value of the
    // current [idx].
    // *) Actually, we could have done this any time, but well...
    // +1 because we need to subtract from '10', not '9'.
    d_number[idx] += ('9' + 1) - oth.d_number[idx];
  }

  remove_leading_zeroes();

  return *this;
}
