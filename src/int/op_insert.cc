#include "int.ih"

// ############################################################################
// Stream insertion operator. Uses str() to insert a string into the stream.
// ############################################################################

std::ostream &Unlimited::operator<<(std::ostream &os, Int const &s) {
  return os << s.str();
}
