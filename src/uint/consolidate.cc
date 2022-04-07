#include "uint.ih"

// ############################################################################
// Consolidate method, which returns the internal representation of [d_number]
// to its 'rest state', making sure each digit is smaller than [s_max_val].
//
// In the multiplication and addition methods, digitwise processing may result
// in a digit being larger than [s_max_val]. This method is called to fix this.
// ############################################################################

void Unlimited::UInt::consolidate() {

  size_t len = d_number.size();
  for (size_t idx = 0; idx < len; ++idx) {

    if (d_number[idx] < s_max_val)
      continue; // nothing to do

    if (idx + 1 == len) { // new element is needed
      d_number.push_back(d_number[idx] / s_max_val);
      ++len;
    } else { // increment next element
      d_number[idx + 1] += d_number[idx] / s_max_val;
    }

    d_number[idx] %= s_max_val;
  }
}
