#include "uint.ih"

// ############################################################################
// Square root method. Modifies the object and returns a reference to self.
// Based on the algorithm of Martin Guy and the mysterious C. Woo, found at
// http://medialab.freaknet.org/martin/src/sqrt/
// ############################################################################

Unlimited::UInt &Unlimited::UInt::sqrt() {

  UInt res, pbit;
  pbit.d_number.resize(d_number.size());
  pbit.set_bit(num_bits() - 2, 1); // set top power-of-4 bit to one

  // [pbit] starts at the highest power of four <= [*this].
  while (pbit > *this)
    pbit >>= 2;

  while (pbit) {
    UInt const t(res + pbit);
    res >>= 1;
    if (*this >= t) {
      *this -= t;
      res += pbit;
    }
    pbit >>= 2;
  }

  return *this = std::move(res);
}
