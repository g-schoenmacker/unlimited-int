#include "uint.ih"

// ############################################################################
// UInt string constructor.
// Uses Str_UInt to validate the string and thus is limited to what the
// Str_UInt string constructor can do. After validation, the decimal digits are
// processed in chunks of at most nine: each digit of [d_number] is multiplied
// by the chunk's power of ten and the chunk is added, after which consolidate()
// restores the internal representation, as in multiplication and addition.
// ############################################################################

Unlimited::UInt::UInt(std::string const &inp) : d_number(1) {

  Str_UInt val;
  try {
    val = Str_UInt(inp);
  } catch (Str_UInt::Exception &e) {
    throw Exception(e.what());
  }

  std::string const digits(val.str());
  for (size_t idx = 0; idx < digits.size(); idx += 9) {
    UInt_t scale = 1;
    UInt_t chunk = 0;
    for (size_t cidx = idx; cidx < idx + 9 && cidx < digits.size(); ++cidx) {
      scale *= 10;
      chunk = chunk * 10 + (digits[cidx] - '0');
    }

    for (size_t nidx = 0; nidx < d_number.size(); ++nidx)
      d_number[nidx] *= scale;
    d_number[0] += chunk;
    consolidate();
  }
}
