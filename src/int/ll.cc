#include "int.ih"

// ############################################################################
// Long long conversion.
// Not declared as an operator to avoid complications.
// Note it will fail to produce the right value without warning
// if [*this] > ll type.
// ############################################################################

long long Unlimited::Int::ll() const {
  long long out = 0;
  size_t const max =
      (sizeof(out) - 1) * 8 < num_bits() ? (sizeof(out) - 1) * 8 : num_bits();
  for (size_t idx = 0; idx < max; ++idx)
    if (bit(idx))
      out |= 1ULL << idx;
  return d_negative ? -out : out;
}