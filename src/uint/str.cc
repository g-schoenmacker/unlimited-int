#include "uint.ih"

// ############################################################################
// String conversion method.
// Uses Str_UInt to convert internal number of base [s_max_val] to base 10.
//
// The algorithm is simple: in [power] is stored the power-value of the current
// digit, which is pow([s_max_val], [digit-idx]). Each digit is multiplied by
// this power, then added to the output.
// ############################################################################

std::string Unlimited::UInt::str() const {

  Str_UInt power(1);
  Str_UInt const max_val(s_max_val);
  Str_UInt out;

  for (size_t idx = 0; idx < d_number.size(); ++idx) {
    out += Str_UInt(d_number[idx]) * power;
    power *= max_val;
  }

  return out.str();
}
