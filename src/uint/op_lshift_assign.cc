#include "uint.ih"

// ############################################################################
// Leftshift-assign operator.
// Because of the internal representation, we always have [s_num_bits] freely
// available to the left of any digit. Each iteration, we shift [s_num_bits] or
// [npos] (if it is smaller) and then restore structure with consolidate().
//
// It may be faster to apply the method used in right-shifting; this is not yet
// tested.
// ############################################################################

Unlimited::UInt &Unlimited::UInt::operator<<=(unsigned npos) {

  while (npos) {
    size_t const shift = npos > s_num_bits ? s_num_bits : npos;
    npos -= shift;
    for (size_t idx = 0; idx < d_number.size(); ++idx)
      d_number[idx] <<= shift;
    consolidate(); // note consolidate() adds new digit if needed
  }

  return *this;
}
