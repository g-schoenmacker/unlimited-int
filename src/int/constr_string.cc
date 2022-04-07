#include "int.ih"

// ############################################################################
// Int string constructor.
// ############################################################################

Unlimited::Int::Int(std::string const &inp) : d_negative(inp[0] == '-') {
  try {
    if (d_negative) {
      std::string cinp(inp);
      cinp.erase(0, 1); // remove '-'
      d_number = UInt(cinp);
    } else
      d_number = UInt(inp);
  } catch (UInt::Exception &e) {
    throw Exception(e.what());
  }

  // to avoid -0
  if (!d_number)
    d_negative = false;
}
