#include "uint.ih"

// ############################################################################
// Bitwise OR-assign operator. Rather straightforward, really.
// ############################################################################

Unlimited::UInt &Unlimited::UInt::operator|=(UInt const &oth) {

  // Make sure [*this] is at least as big as [oth].
  if (d_number.size() < oth.d_number.size())
    d_number.resize(oth.d_number.size());

  // Perform the | operation.
  for (size_t idx = oth.d_number.size(); idx--;)
    d_number[idx] |= oth.d_number[idx];

  return *this;
}
