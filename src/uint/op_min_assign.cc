#include "uint.ih"

// ############################################################################
// Subtraction-assignment operator: implements subtraction.
// Subtraction goes digit by digit. If there's no carry, the action is easy.
// Otherwise, we find the first non-zero more significant number and take what
// we need from there.
// ############################################################################

Unlimited::UInt &Unlimited::UInt::operator-=(UInt const &oth) {

  if (*this < oth)
    throw Exception("operator-= error: Underflow detected");

  for (size_t idx = 0; idx < oth.d_number.size(); ++idx) {

    if (d_number[idx] >= oth.d_number[idx]) {
      // Simple case, no carry
      d_number[idx] -= oth.d_number[idx];
      continue;
    }

    // We need to steal 1 from the next digit, so find the next non-zero
    // digit, setting all intervening zero-digits to [s_max_val] - 1.
    // There has to be a non-zero digit, because [*this] > [oth].
    size_t cidx = idx + 1;
    while (!d_number[cidx])
      d_number[cidx++] = s_max_val - 1;

    --d_number[cidx]; // decrement first non-zero digit

    // Now that we've done the bookkeeping*, we can set the value of the current
    // [idx]
    // *) Actually, we could have done this any time, but well...
    d_number[idx] += s_max_val - oth.d_number[idx];
  }

  remove_leading_zeroes();

  return *this;
}
