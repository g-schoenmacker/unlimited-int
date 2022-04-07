#include "str_uint.ih"

// ############################################################################
// Stream extraction operator.
// Extract a string from the stream and tries to initialise a Str_UInt object.
// If this fails, the failbit is set in the stream and the argument [s] remains
// uninitialised.
// ############################################################################

std::istream &Unlimited::operator>>(std::istream &is, Str_UInt &s) {

  std::string temp;
  if (!(is >> temp))
    return is;

  try {
    s = Str_UInt(temp);
  } catch (Str_UInt::Exception &e) {
    is.exceptions(std::istream::failbit);
  }

  return is;
}
