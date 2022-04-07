#include "str_uint.ih"

// ############################################################################
// Str_UInt unsigned long long/default constructor. If no argument is given, 0
// will be used.
// Converts the integer to a string, then assigns it to d_number. There is no
// need for input checking, because if [val] is a unsigned value, it will be a
// valid value for Str_UInt.
// The value of d_number is reversed because it eases calculation if the least
// significant number is first in the string.
// The constructor is not explicit because most users will expect it not to be.
// ############################################################################

Unlimited::Str_UInt::Str_UInt(unsigned long long val) {
  std::ostringstream ss;
  ss << val;
  d_number = ss.str();
  std::reverse(d_number.begin(), d_number.end());
}
