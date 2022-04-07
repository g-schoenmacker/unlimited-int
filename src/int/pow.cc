#include "int.ih"

// ############################################################################
// Power method. Modifies the object and returns a reference to self.
// May throw iff [exp] < 0.
// Uses UInt::pow to do the work.
// ############################################################################

Unlimited::Int &Unlimited::Int::pow(Int const &exp) {
  if (exp.d_negative)
    throw Exception("pow error: Exponent may not be negative");

  d_number.pow(exp.d_number);

  // Result of pow() is negative iff base is negative and [exp] is odd.
  d_negative = d_negative ? exp.bit(0) : false;
  return *this;
}
