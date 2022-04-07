#include "uint.ih"

// ############################################################################
// Set bit value of d_number at position [pos] to [val].
// If [pos] does not exists, create it.
// Removes all leading zeroes after setting bit.
// ############################################################################

void Unlimited::UInt::set_bit(size_t pos, bool val) {
  size_t const idx = pos / s_num_bits;

  if (idx >= d_number.size()) {
    if (!val)
      return;
    d_number.resize(idx + 1);
  }

  pos %= s_num_bits;
  d_number[idx] = val ? d_number[idx] | UInt_t(UInt_t(1) << pos)
                      : d_number[idx] & UInt_t(~(UInt_t(1) << pos));

  if (!val && idx == d_number.size() - 1)
    remove_leading_zeroes();
}
