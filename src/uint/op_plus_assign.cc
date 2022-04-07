#include "uint.ih"

// ############################################################################
// Addition operator: implements addition.
// Addition goes digit by digit. Overflows are resolved in consolidate().
// ############################################################################

Unlimited::UInt &Unlimited::UInt::operator+=(UInt const &oth) {

  // Make sure [*this] is at least as big as [oth].
  if (d_number.size() < oth.d_number.size())
    d_number.resize(oth.d_number.size());

  // Perform the + operation.
  for (size_t idx = 0; idx < oth.d_number.size(); ++idx)
    d_number[idx] += oth.d_number[idx];

  consolidate();
  return *this;
}