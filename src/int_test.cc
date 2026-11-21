#include "int/int.h"
#include "uint/uint.h"
#include <cassert>
#include <climits>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace Unlimited;

static Int twos(unsigned long long val) {
  return val >> 63 ? -Int(UInt(~val + 1)) : Int(UInt(val));
}

static Int floor_shift(long long val, unsigned shift) {
  long long const div = 1LL << shift;
  return Int(val / div - (val % div < 0));
}

void int_test() {

  std::cout << "\n ----- Int tests ----- \n\n";

  std::vector<std::string> set_a = {
      "123456789", "1234567891", "1", "123456789012345678901234567890",
      "100",       "-10"};
  std::vector<std::string> set_b = {"123456689", "00123456789", "000",
                                    "987654321", "0000020",     "-99999"};

  std::cout
      << "Testing constructor, copy constructor and equality operators...\n";
  for (size_t idx = 0; idx < set_a.size(); ++idx) {
    Int a(set_a[idx]);
    Int b(a);

    assert(!(a > b));
    assert(!(a < b));
    assert(a == b);
    assert(!(a != b));

    assert(!(b > a));
    assert(!(b < a));
    assert(b == a);
    assert(!(b != a));

    assert((!a) == (a == 0));
  }

  std::cout << "Testing constructor, assignment and equality operators...\n";
  for (size_t idx = 0; idx < set_a.size(); ++idx) {
    Int a(set_a[idx]);
    Int b("0");
    b = a;

    assert(!(a > b));
    assert(!(a < b));
    assert(a == b);
    assert(!(a != b));

    assert(!(b > a));
    assert(!(b < a));
    assert(b == a);
    assert(!(b != a));
  }

  std::cout << "Testing UInt construction...\n";
  assert(Int(UInt("123456789")) == Int("123456789"));
  assert(Int(UInt("123456789987654321")) == Int("123456789987654321"));

  std::cout << "Testing equality operators...\n";
  assert(Int("-0") == Int("0"));
  assert(Int("-0") == Int("0000"));
  for (size_t idx = 0; idx < set_a.size(); ++idx) {
    Int a(set_a[idx]);
    Int b(set_b[idx]);

    assert(a > b);
    assert(!(a < b));
    assert(!(a == b));
    assert(a != b);

    assert(!(b > a));
    assert(b < a);
    assert(!(b == a));
    assert(b != a);
  }

  std::cout << "Testing increment, decrement operators...\n";
  Int a = -500, b = -500;
  for (; a < 500; ++a, b++) {
    assert(a == b);
  }
  assert(b == 500);
  for (; a; --a, b--) {
    assert(a == b);
  }
  assert(b == 0);

  for (; a > -500; --a, b--) {
    assert(a == b);
  }
  assert(b == -500);

  std::cout << "Testing divide method...\n";

  Int big("123456789123456789123456789");
  Int res, mod;
  big.divide(1, res, mod);
  assert(big == res);
  assert(mod == 0);

  big.divide(-1, res, mod);
  assert(big == -res);
  assert(mod == 0);

  big.divide(2, res, mod);
  assert(res == Int("61728394561728394561728394"));
  assert(mod == 1);

  big.divide(-2, res, mod);
  assert(res == Int("-61728394561728394561728395"));
  assert(mod == -1);

  big.divide(5, res, mod);
  assert(res == Int("24691357824691357824691357"));
  assert(mod == 4);

  Int big2 = -big;
  big2.divide(5, res, mod);
  assert(res == Int("-24691357824691357824691358"));
  assert(1 == mod);

  big2.divide(7, res, mod);
  assert(res == Int("-17636684160493827017636685"));
  assert(6 == mod);

  big2.divide(-8, res, mod);
  assert(res == Int("15432098640432098640432098"));
  assert(-5 == mod);

  big.divide(Int("987654321"), res, mod);
  assert(res == Int("124999998985937499"));
  assert(mod == 173610);

  big = Int("123456789123456789123456789123456789123456789123456789123456789123"
            "456789123456789");
  big.divide(Int("987654321987654321987654321"), res, mod);
  assert(res == Int("124999998860937500014238281374822020345314724745683566"));
  assert(mod == Int("64868103064868103064868103"));

  // Just checking the existance of the operators
  assert((big / mod) ==
         Int("1903197153769087404945385872058826647050245942909722519"));
  assert((big /= mod) ==
         Int("1903197153769087404945385872058826647050245942909722519"));
  assert((big % mod) == Int("38381123895690670931465716"));
  assert((big %= mod) == Int("38381123895690670931465716"));

  std::cout << "Testing multiplication method...\n";
  assert(Int(0) * Int(1234) == Int(0));
  assert(Int(1) * Int(1234) == Int(1234));
  assert(Int(-1) * Int(1234) == Int(-1234));
  assert(Int(2) * Int(1234) == Int(2468));
  assert(Int(-2) * Int(1234) == Int(-2468));
  assert(Int(-2) * Int(-1234) == Int(2468));

  assert(Int("987654321987654321") * Int("112233445566778899") ==
         Int("110847847585595321123720052648972579"));

  assert(Int("987654321987654321") * Int("-112233445566778899") ==
         Int("-110847847585595321123720052648972579"));

  assert(Int("987654321987654321999") * Int("112233445566778899111") ==
         Int("110847847585595321345470894510814328842889"));

  assert(Int("-987654321987654321999") * Int("112233445566778899111") ==
         Int("-110847847585595321345470894510814328842889"));

  assert(Int("-987654321987654321999") * Int("-112233445566778899111") ==
         Int("110847847585595321345470894510814328842889"));

  // Just checking the existance of the operator
  assert((big *= mod) ==
         Int("2489710700611134398732558402699595704578172006456748"));

  std::cout << "Testing addition method...\n";

  assert(Int(0) + Int(1234) == Int(1234));
  assert(Int(1) + Int(1234) == Int(1235));
  assert(Int(12) + Int(1234) == Int(1246));
  assert(Int(999) + Int(1) == Int(1000));

  assert(Int(0) + Int(-1234) == Int(-1234));
  assert(Int(1) + Int(-1234) == Int(-1233));
  assert(Int(-12) + Int(1234) == Int(1222));
  assert(Int(-999) + Int(-1) == Int(-1000));

  assert(Int(-1234) + Int(0) == Int(-1234));
  assert(Int(-1234) + Int(-1) == Int(-1235));
  assert(Int(-1234) + Int(-12) == Int(-1246));
  assert(Int(-1) + Int(999) == Int(998));
  assert(Int(-1) + Int(1) == Int(0));

  assert(Int(1234) + Int(0) == Int(1234));
  assert(Int(1234) + Int(1) == Int(1235));
  assert(Int(1234) + Int(12) == Int(1246));
  assert(Int(1) + Int(999) == Int(1000));

  assert(Int("987654321987654321999") + Int("00112233445566778899111") ==
         Int("1099887767554433221110"));

  // Just checking the existance of the operator
  assert((big += mod) ==
         Int("2489710700611134398732558467567698769446275071324851"));

  std::cout << "Testing subtraction method...\n";

  assert(Int(1234) - Int(0) == Int(1234));
  assert(Int(1234) - Int(1) == Int(1233));
  assert(Int(1234) - Int(2) == Int(1232));
  assert(Int(1234) - Int(5) == Int(1229));
  assert(Int(1234) - Int(1234) == Int(0));

  assert(Int(1234) - Int(1235) == Int(-1));
  assert(Int(1234) - Int(4321) == Int(-3087));
  assert(Int(2) - Int(1234) == Int(-1232));
  assert(Int(-1234) - Int(-4321) == Int(3087));
  assert(Int(-1234) - Int(-1234) == Int(0));

  assert(Int("987654321987654321999") - Int("112233445566778899111") ==
         Int("875420876420875422888"));

  assert((Int("823456789123456789") - Int("823456789023456789")) ==
         Int("100000000"));

  // Just checking the existance of the operator
  assert((big -= mod) ==
         Int("2489710700611134398732558402699595704578172006456748"));

  std::cout << "Testing unary minus method...\n";
  assert(-Int("987654321987654321999") == Int("-987654321987654321999"));
  assert(-Int("0") == Int("0"));
  assert(-Int("-987654321987654321999") == Int("987654321987654321999"));

  std::cout << "Testing power method...\n";
  assert(Int("-123456789").powc(0) == Int(1));
  assert(Int("-123456789").powc(1) == Int("-123456789"));
  assert(Int("-123456789").powc(2) == Int("15241578750190521"));
  assert(Int("-123456789").powc(3) == Int("-1881676371789154860897069"));
  assert(Int("-123456789").powc(4) == Int("232305722798259244150093798251441"));
  assert(Int("-123456789").powc(5) ==
         Int("-28679718602997181072337614380936720482949"));

  res = -81;
  assert(res.pow(23) == Int("-78551672112789411833022577315290546060373041"));
  res = -res;

  std::cout << "Testing sqrt method...\n";
  assert(Int("123456789").sqrtc() == Int("11111"));
  assert(Int("15241578750190521").sqrtc() == Int("123456789"));
  assert(Int("1881676371789154860897069").sqrtc() == Int("1371742093758"));
  assert(Int("232305722798259244150093798251441").sqrtc() ==
         Int("15241578750190521"));
  assert(Int("28679718602997181072337614380936720482949").sqrtc() ==
         Int("169350874231570416987"));
  assert(res.sqrt() == Int("8862938119652501095929"));

  std::cout << "Testing left shift operator...\n";
  assert((Int("-123456789") << 25) == Int("-4142522431438848"));
  assert((Int("-123456789") << 0) == Int("-123456789"));
  assert((Int("-123456789") << 1) == Int("-246913578"));
  for (size_t pow = 1; pow < 50; ++pow)
    assert((Int("123456789") << pow) == (Int("123456789") * Int(2).powc(pow)));
  assert((big <<= 3) ==
         Int("19917685604889075189860467221596765636625376051653984"));

  std::cout << "Testing right shift operator...\n";
  assert((Int("-4142522431438848") >> 25) == Int("-123456789"));
  assert((Int("-123456789") >> 0) == Int("-123456789"));
  assert((Int("-123456789") >> 1) == Int("-61728395"));
  assert((Int("-987654321987654321987654321987654321") >> 40) ==
         Int("-898266373030905308030610"));
  assert((big >>= 3) ==
         Int("2489710700611134398732558402699595704578172006456748"));

  std::cout << "Testing bitwise AND operator...\n";

  assert((Int("-123456789") & Int("987654321")) == Int("948183201"));
  assert((Int("-123456789123456789123456789") & Int("-987654321987654321")) ==
         Int("-123456790065916649938378677"));
  assert((Int("987654321987654321") & Int("-123456789123456789123456789")) ==
         Int("942459860814921889"));
  assert((Int("123456789") & Int(-0)) == Int(0));
  assert((Int("-123456789") & Int(-1)) == Int("-123456789"));
  assert((big &= mod) == Int("152342437133404011517188"));

  std::cout << "Testing bitwise OR operator...\n";

  assert((Int("123456789") | Int("-987654321")) == Int("-948183201"));
  assert((Int("-123456789123456789123456789") | Int("987654321987654321")) ==
         Int("-123456789078262327950724357"));
  assert((Int("-987654321987654321") | Int("-123456789123456789123456789")) ==
         Int("-45194461172732433"));
  assert((Int("-123456789") | Int(0)) == Int("-123456789"));
  assert((Int("123456789") | Int(-2)) == Int(-1));
  assert((big |= mod) == Int("64868103064868103064868103"));

  std::cout << "Testing bitwise XOR operator...\n";
  assert((Int("-123456789") ^ Int("987654321")) == Int("-1032168870"));
  assert((Int("-123456789123456789123456789") ^ Int("-987654321987654321")) ==
         Int("123456790020722188765646244"));
  assert((Int("987654321987654321") ^ Int("-123456789123456789123456789")) ==
         Int("-123456790020722188765646246"));
  assert((Int("123456789") ^ Int(-0)) == Int("123456789"));
  assert((Int("123456789") ^ Int(-1)) == Int("-123456790"));
  assert((Int("-123456789") ^ Int(-2)) == Int("123456789"));
  assert((big ^= mod) == Int(0));

  std::cout << "Testing bit setting methods...\n";
  big.set_bit(0, 1);
  assert(big == Int(1));
  big.set_bit(1, 1);
  assert(big == Int(3));
  big.set_bit(2, 1);
  assert(big == Int(7));
  big.set_bit(1, 0);
  assert(big == Int(5));
  big = Int("1365");
  for (size_t idx = 0; idx < 12; ++idx)
    big.set_bit(idx, idx % 2 == 0);
  assert(big == Int("1365"));

  std::cout << "Testing str method...\n";
  assert(Int("-00").str().compare("0") == 0);
  assert(Int("-1").str().compare("-1") == 0);
  assert(Int("-12345").str().compare("-12345") == 0);
  assert(
      Int("-987654321987654321999").str().compare("-987654321987654321999") ==
      0);

  std::cout << "Testing stream extract method...\n";
  std::istringstream ss(
      "0 -1 2 -3 4 -5 6 -7 8 -9 -10 11 -12 13 -14 15 -16 17 -18 19");
  for (Int a; a < 20; ++a) {
    Int temp;
    assert(ss >> temp);
    assert(temp == a || -temp == a);
  }
  assert(!(ss >> big));

  std::cout << "Testing long long conversion method...\n";
  assert(Int("0").ll() == 0);
  assert(Int("1").ll() == 1);
  assert(Int("-1").ll() == -1);

  for (long long idx = ~0LL; idx < -~0LL - 80000000000001LL;
       idx += 800000000000000LL) {
    assert(Int(idx).ll() == idx);
  }

  assert(Int("1234567").ll() == 1234567);
  assert(Int("-1234567").ll() == -1234567);

  std::cout << "Testing long long conversion of large values...\n";
  assert(Int(1LL << 56).ll() == 1LL << 56);
  assert(Int(1LL << 60).ll() == 1LL << 60);
  assert(Int(-(1LL << 60)).ll() == -(1LL << 60));
  assert(Int(LLONG_MAX).ll() == LLONG_MAX);
  assert(Int(LLONG_MIN + 1).ll() == LLONG_MIN + 1);
  assert(Int(LLONG_MIN).ll() == LLONG_MIN);
  assert(Int("9223372036854775807").ll() == LLONG_MAX);

  // Negating LLONG_MIN is undefined behaviour, so whether this fails depends
  // on the optimiser; -fsanitize=undefined always catches it.
  std::cout << "Testing construction from LLONG_MIN...\n";
  assert(Int(LLONG_MIN).str() == "-9223372036854775808");
  assert(Int(LLONG_MIN) == Int("-9223372036854775808"));

  std::cout << "Testing results of zero are never negative...\n";
  assert(Int(-5) * Int(0) == Int(0));
  assert(Int(0) * Int(-5) == Int(0));
  assert((Int(-5) * Int(0)).str() == "0");
  {
    Int val(-5);
    val *= 0;
    assert(val == Int(0));
    assert(val.str() == "0");
  }
  assert(Int(0) / Int(-5) == Int(0));
  assert((Int(0) / Int(-5)).str() == "0");
  assert(Int(0) % Int(-5) == Int(0));
  assert((Int(-1) >> 1).str() != "-0");
  assert((Int(-5) ^ Int(5)).str() != "-0");
  assert((Int(-5) & Int(-2)).str() != "-0");
  {
    Int val(-1);
    val.set_bit(0, 0);
    assert(val.str() != "-0");
  }

  std::cout << "Testing right shift past all bits...\n";
  assert((Int(5) >> 100) == Int(0));
  assert((Int("987654321987654321987654321") >> 1000) == Int(0));

  std::cout << "Testing stream extract failure...\n";
  {
    std::istringstream bad("abc");
    Int val(7);
    bool threw = false;
    try {
      bad >> val;
    } catch (...) {
      threw = true;
    }
    assert(!threw);
    assert(bad.fail());
  }

  // "Do as the ints do": bitwise operators follow two's complement semantics.
  std::cout << "Testing bitwise operators match int semantics...\n";
  assert((Int(-1) | Int(2)) == Int(-1));
  assert((Int(-2) & Int(3)) == Int(2));
  assert((Int(-5) ^ Int(3)) == Int(-8));
  assert((Int(-1) >> 1) == Int(-1));
  assert((Int(-7) >> 1) == Int(-4));
  assert((Int(-5) >> 100) == Int(-1));
  for (long long lhs = -20; lhs <= 20; ++lhs) {
    unsigned long long const ulhs = lhs;
    for (long long rhs = -20; rhs <= 20; ++rhs) {
      unsigned long long const urhs = rhs;
      assert((Int(lhs) & Int(rhs)) == twos(ulhs & urhs));
      assert((Int(lhs) | Int(rhs)) == twos(ulhs | urhs));
      assert((Int(lhs) ^ Int(rhs)) == twos(ulhs ^ urhs));
    }
    for (unsigned shift = 0; shift < 8; ++shift) {
      assert((Int(lhs) >> shift) == floor_shift(lhs, shift));
      assert((Int(lhs) << shift) == Int(lhs * (1LL << shift)));
    }
  }
  std::vector<std::string> set_c = {
      "0", "-1", "987654321987654321", "-123456789123456789123456789",
      "-18446744073709551616", "340282366920938463463374607431768211455"};
  for (size_t idx = 0; idx < set_c.size(); ++idx) {
    Int const a(set_c[idx]);
    assert((a ^ Int(-1)) == -a - 1);
    for (unsigned shift = 0; shift < 140; shift += 7) {
      Int const rem = a - ((a >> shift) << shift);
      assert(rem >= 0 && rem < (Int(1) << shift));
    }
    for (size_t odx = 0; odx < set_c.size(); ++odx) {
      Int const b(set_c[odx]);
      assert((a & b) == (b & a));
      assert(a + b == (a ^ b) + Int(2) * (a & b));
      assert((a | b) == (a ^ b) + (a & b));
    }
  }

  std::cout << "Testing bit access matches int semantics...\n";
  assert(Int(-1).bit(0));
  assert(Int(-1).bit(5));
  assert(Int(-1).bit(1000));
  assert(!Int(-2).bit(0));
  assert(Int(-2).bit(1));
  assert(!Int(-8).bit(2));
  assert(Int(-8).bit(3));
  assert(Int(-8).bit(4));
  {
    Int val(-1);
    val.set_bit(5, 0);
    assert(val == Int(-33));
    val.set_bit(5, 1);
    assert(val == Int(-1));
    val.set_bit(0, 0);
    assert(val == Int(-2));
    val.set_bit(100, 0);
    assert(val == -(Int(1) << 100) - 2);
  }
  for (long long val = -40; val <= 40; ++val) {
    unsigned long long const uval = val;
    for (unsigned pos = 0; pos < 63; ++pos) {
      assert(Int(val).bit(pos) == bool((uval >> pos) & 1));
      Int set(val), clear(val);
      set.set_bit(pos, 1);
      clear.set_bit(pos, 0);
      assert(set == twos(uval | (1ULL << pos)));
      assert(clear == twos(uval & ~(1ULL << pos)));
    }
    for (unsigned pos = 63; pos < 200; pos += 17)
      assert(Int(val).bit(pos) == (val < 0));
  }
  for (size_t idx = 0; idx < set_c.size(); ++idx) {
    Int const a(set_c[idx]);
    for (unsigned pos = 0; pos < 200; pos += 3) {
      Int const mask = Int(1) << pos;
      assert(a.bit(pos) == bool(a & mask));
      Int set(a), clear(a);
      set.set_bit(pos, 1);
      clear.set_bit(pos, 0);
      assert(set == (a | mask));
      assert(clear == (a & (-mask - 1)));
      assert(set.bit(pos) && !clear.bit(pos));
    }
  }

  std::cout << "Testing divide with aliased arguments...\n";
  {
    Int num(-17), den(5), res, mod;
    num.divide(den, num, mod);
    assert(num == Int(-4) && mod == Int(3));
    num = -17;
    num.divide(den, res, den);
    assert(res == Int(-4) && den == Int(3));
    num = -17;
    num.divide(num, res, num);
    assert(res == Int(1) && num == Int(0));
    num = 17;
    den = -5;
    num.divide(den, den, num);
    assert(den == Int(-4) && num == Int(-3));
  }

  std::cout << "Testing string construction of large numbers...\n";
  assert(Int("-1" + std::string(10000, '0')) == -Int(10).powc(10000));

  std::cout << "\n ----- End Int tests ----- \n\n";
}
