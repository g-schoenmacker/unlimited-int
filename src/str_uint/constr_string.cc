#include "str_uint.ih"

// ############################################################################
// Str_UInt string constructor.
// Only a string consisting of at least 1 numerical character can be used. The
// method does not take alternative notations such as scientific.
// Leading zeroes are discarded.
// The value of d_number is reversed because it eases calculation if the least
// significant number is first in the string.
// This constructor is explicit because most users will expect it to be.
// ############################################################################

Unlimited::Str_UInt::Str_UInt(std::string const &number) : d_number(number) {
  // check for invalid characters
  if (d_number.empty())
    throw Exception("Str_UInt(string) error: empty string construction");
  for (size_t idx = 0; idx < d_number.size(); ++idx) {
    if (d_number[idx] < '0' || d_number[idx] > '9')
      throw Exception(std::string("Str_UInt(string) error: '") + d_number +
                      "' is not a valid number");
  }

  std::reverse(d_number.begin(), d_number.end());
  remove_leading_zeroes();
}
