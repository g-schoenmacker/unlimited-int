#include "uint.ih"

// ############################################################################
// Compare method parallel to std::string::compare method. Returns 1 if [*this]
// is larger than [oth], -1 if it is smaller and 0 if they are equal.
// ############################################################################

int Unlimited::UInt::compare(UInt const &oth) const {
  // Number with the most digits is largest.
  if (d_number.size() != oth.d_number.size())
    return d_number.size() > oth.d_number.size() ? 1 : -1;

  // Number with the first bigger digit is largest.
  for (size_t idx = d_number.size(); idx--;) {
    if (d_number[idx] != oth.d_number[idx])
      return d_number[idx] > oth.d_number[idx] ? 1 : -1;
  }

  return 0; // equal
}
