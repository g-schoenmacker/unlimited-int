#include "uint.ih"

// ############################################################################
// Implementation of unsigned long long converstion.
// Not declared as an operator to avoid complications.
// Note it will fail to produce the right value without warning
// if [*this] > ull type.
// ############################################################################

unsigned long long Unlimited::UInt::ull() const {

  unsigned long long out = 0;
  size_t const max =
      sizeof(out) * 8 < num_bits() ? sizeof(out) * 8 : num_bits();

  for (size_t idx = 0; idx < max; ++idx)
    if (bit(idx))
      out |= 1ULL << idx;

  return out;
}