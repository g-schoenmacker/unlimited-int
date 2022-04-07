#include "uint.ih"

// ############################################################################
// Multiplication operator: implements multiplication.
// Multiplication is done digit by digit. This is possible because each digit
// < [s_max_val], so the highest multiplication result is smaller than
// [s_max_val]^2 which can be stored in a UInt_t.
// Overflow of internal representation is dealt with in consilidate().
// Friend of UInt class.
// ############################################################################

Unlimited::UInt Unlimited::operator*(Unlimited::UInt const &rhs,
                                     Unlimited::UInt const &lhs) {

  Unlimited::UInt res;

  // Either check for zeroes here or call remove_leading_zeroes() at the end.
  // This seemed more neat.
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
