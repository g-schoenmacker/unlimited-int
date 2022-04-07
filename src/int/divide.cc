#include "int.ih"

// ############################################################################
// Division method: takes a denominator as input and the result and modulus as
// output. May throw iff [oth] is zero (division by zero).
//
// For the sign determination, the goal is (a/b)*b + a%b == a.
// This implementation does this through the following:
//  7 /  5 ==  1
// -7 /  5 == -2
//  7 / -5 == -2
// -7 / -5 ==  1
//
//  7 %  5 ==  2
// -7 %  5 ==  3
//  7 % -5 == -3
// -7 % -5 == -2
// ############################################################################

void Unlimited::Int::divide(
    Int const &oth, // the denominator part of the division
    Int &res,       // the result of the division
    Int &mod        // the remainder (modulus) of the division
) const {

  try {
    d_number.divide(oth.d_number, res.d_number, mod.d_number);
  } catch (UInt::Exception &c) {
    throw Exception(c.what()); // division by zero
  }

  // Result of division has [d_negative] XOR [oth.d_ngeative] sign.
  res.d_negative =
      (d_negative && !oth.d_negative) || (!d_negative && oth.d_negative);

  // Modulo is < 0 iff [mod] != 0 AND [oth] < 0.
  mod.d_negative = mod.d_number && oth.d_negative;

  // If [res] is negative and a remainder of the division exists,
  // increase [res] (to simulate rounding down) and flip modulus.
  if (res.d_negative && mod.d_number) {
    ++res.d_number;
    mod.d_number = oth.d_number - mod.d_number;
  }
}
