#include "uint.ih"

// ############################################################################
// Division method: takes a denominator as input and the result and modulus as
// output. May throw iff [oth] is zero (division by zero).
//
// Implementation of the below pseudocode from
// http://en.wikipedia.org/wiki/Division_(digital)
//
// if D == 0 then throw DivisionByZeroException end
// Q := 0				(initialize quotient and remainder to
// zero) R := 0 for i = n-1...0 do	(where n is # of bits)
//   R := R << 1		(left-shift R by 1 bit)
//   R(0) := N(i)		(set the least-significant bit of R
//   if R >= D then		 equal to bit i of the numerator)
//     R = R - D
//     Q(i) := 1
//   end
// end
//
// ############################################################################

void Unlimited::UInt::divide(
    UInt const &oth, // the denominator part of the division
    UInt &res,       // the result of the division
    UInt &mod        // the remainder (modulus) of the division
) const {

  if (!oth)
    throw Exception("divide error: Division by zero");

  res = 0;
  res.d_number.resize(d_number.size());
  mod = 0;

  for (size_t i = num_bits(); i--;) {
    mod <<= 1;
    mod.set_bit(0, bit(i)); // set least sig bit of [mod] to i'th bit of [this]

    // The below is equivalent to:
    // if (mod < oth) continue;
    // ...but written out to avoid function call overhead.

    if (mod.d_number.size() < oth.d_number.size())
      continue;

    if (mod.d_number.size() == oth.d_number.size()) {
      bool mod_is_smaller = false;
      for (size_t idx = mod.d_number.size(); idx--;) {
        if (mod.d_number[idx] == oth.d_number[idx])
          continue;
        mod_is_smaller = mod.d_number[idx] < oth.d_number[idx];
        break;
      }
      if (mod_is_smaller)
        continue;
    }

    // End of: if (mod < oth) continue;

    mod -= oth;
    res.set_bit(i, 1);
  }

  res.remove_leading_zeroes();
}
