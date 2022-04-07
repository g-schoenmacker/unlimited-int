#include "uint.ih"

// ############################################################################
// Rightshift operator.
// Rightshifting is difficult in the representation used.
// Instead, we just build a new UInt in which we set all the right bits.
// ############################################################################

Unlimited::UInt Unlimited::UInt::operator>>(unsigned npos) const {
  UInt out;
  out.d_number.resize(d_number.size());

  size_t const max_idx = num_bits() - npos;
  for (size_t idx = 0; idx < max_idx; ++idx)
    out.set_bit(idx, bit(idx + npos));

  out.remove_leading_zeroes();

  return out;
}
