#include "int.ih"

// ############################################################################
// Subtraction-assignment operator. Performs checks on [d_negative] and leaves
// the actual work to UInt.
// ############################################################################

Unlimited::Int &Unlimited::Int::operator-=(Int const &oth) {
  if (d_negative == oth.d_negative) {
    // If both are either positive or negative, there are 4 cases:
    // 1. 10 - 8
    // 2. 10 - 12
    // 3. -10 - -8
    // 4. -10 - -12
    if (d_number < oth.d_number) {
      // cases 2 and 4
      d_negative = !d_negative; // sign change
      d_number = oth.d_number - d_number;
    } else if (!(d_number -= oth.d_number)) // cases 1 and 3
      d_negative = false;                   // avoid negative zero
  } else {
    // One is negative, one positive. Two cases (with x > -1):
    // 1. -10 - x => -(10 + x)
    // 2. 10 - -x => 10 + x
    // Therefore addition and no sign change.
    d_number += oth.d_number;
  }
  return *this;
}