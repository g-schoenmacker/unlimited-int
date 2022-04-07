#include "str_uint.ih"

// ############################################################################
// Stream insertion operator. Uses str() to insert a string into the stream.
// ############################################################################

std::ostream &Unlimited::operator<<(std::ostream &os, Str_UInt const &s) {
  return os << s.str();
}
