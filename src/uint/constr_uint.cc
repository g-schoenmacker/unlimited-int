#include "uint.ih"

// ############################################################################
// UInt unsigned long long/default constructor. If no argument is given, 0 will
// be used. The argument [val] is converted to base [s_max_val] and stored in
// the internal vector [d_number].
//
// Two static members are also set here. [s_num_bits] contains the number of
// bits used in each UInt_t, which is always half the number of bits in the
// type. [s_max_val] contains the upper limit of what can be stored in
// [s_num_bits] bits and is 2 to the power of [s_num_bits]. Note the maximum
// value is actually [s_max_val] - 1, so the modulus operator can be used.
//
// The choice for static members is made to avoid unnamed constants in the code
// There is no real additional gain, but makes for better reading.
// ############################################################################

size_t const Unlimited::UInt::s_num_bits = sizeof(Unlimited::UInt::UInt_t) * 4;

Unlimited::UInt::UInt_t const Unlimited::UInt::s_max_val = UInt_t(1)
                                                           << UInt::s_num_bits;

Unlimited::UInt::UInt(unsigned long long int val) {

  if (!val)
    d_number.push_back(0);

  while (val) {
    d_number.push_back(val % s_max_val);
    val /= s_max_val;
  }
}
