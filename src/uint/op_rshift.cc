#include "uint.ih"

// ############################################################################
// Rightshift operator.
// Whole digits are dropped first, then each remaining digit is shifted by the
// rest of [npos], taking the bits shifted in from the next more significant
// digit. Because each digit uses at most [s_num_bits] bits, the next digit can
// be leftshifted within a UInt_t before the modulus removes the excess.
// ############################################################################

Unlimited::UInt Unlimited::UInt::operator>>(unsigned npos) const {
  UInt out;
  if (npos >= num_bits())
    return out;

  size_t const skip = npos / s_num_bits;
  size_t const shift = npos % s_num_bits;
  out.d_number.resize(d_number.size() - skip);

  for (size_t idx = 0; idx < out.d_number.size(); ++idx) {
    out.d_number[idx] = d_number[idx + skip] >> shift;
    if (idx + skip + 1 < d_number.size())
      out.d_number[idx] |=
          (d_number[idx + skip + 1] << (s_num_bits - shift)) % s_max_val;
  }

  out.remove_leading_zeroes();

  return out;
}
