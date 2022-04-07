#include "str_uint.ih"

// ############################################################################
// Division method: takes a denominator as input and the result and modulus as
// output. May throw iff [oth] is zero (division by zero).
// This method is notably slow, boiling down to repeatedly subtracting [oth]
// from [*this] and incrementing [res]. Avoid using this method if speed is an
// issue: use the UInt class instead.
// ############################################################################

void Unlimited::Str_UInt::divide(
    Str_UInt const &oth, // the denominator part of the division
    Str_UInt &res,       // the result of the division
    Str_UInt &mod        // the remainder (modulus) of the division
) const {
  if (!oth)
    throw Exception("divide error: Division by zero");

  // Initialise output arguments.
  res = Str_UInt(0);
  mod = *this;

  size_t const o_len = oth.d_number.length();
  size_t const o_sig = oth.d_number[o_len - 1] - '0';

  // In this loop we find the largest multiple of a power of 10 which, when
  // multiplied by [oth], is this smaller than [mod].
  // When found, we add this [factor] to [res] and subtract [mod_diff] from
  // [mod]. This is done as long as [mod] > [oth], othwise, we're done.
  while (mod > oth) {
    size_t const m_len = mod.d_number.length();

    // Initialise [pow_10] to be 10 to the power of [m_len] - [o_len].
    Str_UInt pow_10(std::string("1") + std::string(m_len - o_len, '0'));

    // To see how many times our power of 10 by [oth] fits into [mod]
    // we need to estimate the [small_factor]. We do this by dividing the
    // (two) most significant number(s) of [mod] by the most significant
    // number of [oth].
    size_t m_sig = mod.d_number[m_len - 1] - '0';

    // The factor may actually be larger than [mod] and we need it to be
    // smaller. If it is larger, we go one 10-power lower which is
    // guaranteed to have a smaller result than mod.
    if (pow_10 * oth > mod) {
      pow_10.d_number.erase(0, 1);                        // remove one 0
      m_sig = m_sig * 10 + mod.d_number[m_len - 2] - '0'; // index exists
    }

    // If [small_factor] is 0 or 1, we can ignore it because [factor] is
    // equal to [pow_10].
    size_t small_factor = m_sig / o_sig;
    if (small_factor < 2) {
      mod -= pow_10 * oth;
      res += pow_10;
      continue;
    }

    Str_UInt factor(pow_10 * small_factor);
    Str_UInt mod_diff(factor * oth);

    // [small_factor] is an estimate which may be too large.
    // This is the case iff [mod_diff] > [mod].
    while (mod_diff > mod) {
      factor = --small_factor == 1 ? pow_10 : pow_10 * small_factor;
      mod_diff = factor * oth;
    }

    mod -= mod_diff;
    res += factor;
  }
}
