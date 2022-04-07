#include "uint.ih"

// ############################################################################
// Stream extraction operator.
// Extract a string from the stream and tries to initialise a UInt object.
// If this fails, the failbit is set in the stream and the argument [s] remains
// uninitialised.
// ############################################################################

std::istream &Unlimited::operator>>(std::istream &is, UInt &s) {

  std::string temp;
  if (!(is >> temp))
    return is;

  try {
    s = UInt(temp);
  } catch (Str_UInt::Exception &e) {
    is.exceptions(std::istream::failbit);
  }

  return is;
}
