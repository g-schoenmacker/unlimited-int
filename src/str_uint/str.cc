#include "str_uint.ih"

// ############################################################################
// String conversion method.
// Converts the internal number to a printable string by reversing a copy.
// ############################################################################

std::string Unlimited::Str_UInt::str() const {
  std::string out(d_number);
  std::reverse(out.begin(), out.end());
  return out;
}