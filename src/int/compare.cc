#include "int.ih"

// ############################################################################
// Compare method parallel to std::string::compare method. Returns 1 if [*this]
// is larger than [oth], -1 if it is smaller and 0 if they are equal.
// ############################################################################

int Unlimited::Int::compare(Int const &oth) const {

  if (!d_negative && oth.d_negative)
    return 1;

  if (d_negative && !oth.d_negative)
    return -1;

  return d_negative ? -d_number.compare(oth.d_number)
                    : d_number.compare(oth.d_number);
}
