#include "int.ih"

// ############################################################################
// Addition-assignment operator. Performs checks on [d_negative] and leaves
// the actual work to UInt.
// ############################################################################

Unlimited::Int &Unlimited::Int::operator+=(Int const &oth) {

  // If both are either positive or negative, just add the numbers.
  if (d_negative == oth.d_negative)
    d_number += oth.d_number;
  else {
    // If both are either positive or negative, there are 4 cases:
    // 1. 10 + -8
    // 2. 10 + -12
    // 3. -10 + 8
    // 4. -10 + 12
    // In cases 2 and 4, d_number < oth.d_number:
    if (d_number < oth.d_number) {
      d_negative = !d_negative; // switch case
      d_number = oth.d_number - d_number;
    } else if (!(d_number -= oth.d_number)) // case 1 and 3
      d_negative = false;                   // avoid negative zero
  }

  return *this;
}