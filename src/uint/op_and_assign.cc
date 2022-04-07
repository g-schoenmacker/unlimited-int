#include "uint.ih"

// ############################################################################
// Bitwise AND-assign operator. Rather straightforward, really.
// ############################################################################

Unlimited::UInt &Unlimited::UInt::operator&=(UInt const &oth) {

  // Make sure [*this] is at MOST as big as [oth].
  if (d_number.size() > oth.d_number.size())
    d_number.resize(oth.d_number.size());

  // Perform the & operation.
  for (size_t idx = d_number.size(); idx--;)
    d_number[idx] &= oth.d_number[idx];

  remove_leading_zeroes();

  return *this;
}
