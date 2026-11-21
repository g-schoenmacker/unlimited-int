#include "int.ih"

// ############################################################################
// Long long conversion.
// Not declared as an operator to avoid complications.
// Note it will fail to produce the right value without warning
// if [*this] > ll type.
// ############################################################################

long long Unlimited::Int::ll() const {
  unsigned long long const out = d_number.ull();
  return d_negative ? -out : out;
}