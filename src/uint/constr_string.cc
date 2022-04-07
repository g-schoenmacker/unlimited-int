#include "uint.ih"

// ############################################################################
// UInt string constructor.
// Uses Str_UInt to convert the string to a number and thus is limited to what
// the Str_UInt string constructor can do. After the Str_UInt construction is
// done, chunks fitting in [s_max_val] are removed one at a time, parallel to
// the method in the uint contructor.
//
// This constructor uses the Str_UInt::divide method and is thus quite slow.
// If your code relies heavily on string construction/conversion and arithmetic
// is incidental, it may be faster to use Str_UInt directly. In any other case,
// UInt is the better class to use because of its much faster arithmetic.
// ############################################################################

Unlimited::UInt::UInt(std::string const &inp) {

  Str_UInt val;
  try {
    val = Str_UInt(inp);
  } catch (Str_UInt::Exception &e) {
    throw Exception(e.what());
  }

  if (!val)
    d_number.push_back(0);

  while (val) {
    Str_UInt div, mod;
    val.divide(s_max_val, div, mod);

    std::istringstream ss(mod.str());
    UInt_t temp;
    ss >> temp;

    d_number.push_back(temp);
    val = div;
  }
}
