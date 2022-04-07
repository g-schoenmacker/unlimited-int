#include "uint.ih"

// ############################################################################
// Power method. Modifies the object and returns a reference to self.
// Checks for default (0) case, then performs power raising with the standard
// fast power raising algorithm.
// ############################################################################

Unlimited::UInt &Unlimited::UInt::pow(UInt const &oth) {

  if (!oth)
    return *this = 1;

  UInt exp(oth);

  UInt const one(1);
  UInt left_over(1);
  while (exp != one) {
    // Multiply [*this] by itself.
    // If odd, multiply by [*this] at the very end also.
    // After that, halve [exp] and continue.
    if (exp.bit(0))
      left_over *= *this;
    *this *= *this;
    exp >>= 1;
  }

  return *this *= left_over;
}
