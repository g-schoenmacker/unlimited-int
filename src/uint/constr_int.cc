#include "uint.ih"

// ############################################################################
// UInt Int constructor.
// Ignored any sign and simply copies the internal number.
// ############################################################################

Unlimited::UInt::UInt(Int const &val) : d_number(val.d_number.d_number) {}
