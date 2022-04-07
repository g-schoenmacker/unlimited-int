#include "uint.ih"

// ############################################################################
// Stream insertion operator. Uses str() to insert a string into the stream.
// ############################################################################

std::ostream &Unlimited::operator<<(std::ostream &os, UInt const &s) {
  return os << s.str();
}
