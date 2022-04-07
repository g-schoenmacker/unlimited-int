#include "int.ih"

// ############################################################################
// Stream extraction operator.
// Extract a string from the stream and tries to initialise a Int object.
// If this fails, the failbit is set in the stream and the argument [s] remains
// uninitialised.
// ############################################################################

std::istream &Unlimited::operator>>(std::istream &is, Int &s) {

  std::string temp;
  if (!(is >> temp))
    return is;

  try {
    s = Int(temp);
  } catch (UInt::Exception &e) {
    is.exceptions(std::istream::failbit);
  }

  return is;
}
