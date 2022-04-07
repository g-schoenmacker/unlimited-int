#include "int/int.h"
#include "uint/uint.h"
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace Unlimited;

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
  assert((Int("-123456789") >> 1) == Int("-61728394"));
  assert((Int("-987654321987654321987654321987654321") >> 40) ==
         Int("-898266373030905308030609"));
  assert((big >>= 3) ==
         Int("2489710700611134398732558402699595704578172006456748"));

  std::cout << "Testing bitwise AND operator...\n";

  assert((Int("-123456789") & Int("987654321")) == Int("39471121"));
  assert((Int("-123456789123456789123456789") & Int("-987654321987654321")) ==
         Int("-45194461172732433"));
  assert((Int("987654321987654321") & Int("-123456789123456789123456789")) ==
         Int("45194461172732433"));
  assert((Int("123456789") & Int(-0)) == Int(0));
  assert((Int("-123456789") & Int(-1)) == Int(-1));
  assert((big &= mod) == Int("152342437133404011517188"));

  std::cout << "Testing bitwise OR operator...\n";

  assert((Int("123456789") | Int("-987654321")) == Int("-1071639989"));
  assert((Int("-123456789123456789123456789") | Int("987654321987654321")) ==
         Int("-123456790065916649938378677"));
  assert((Int("-987654321987654321") | Int("-123456789123456789123456789")) ==
         Int("-123456790065916649938378677"));
  assert((Int("-123456789") | Int(0)) == Int("-123456789"));
  assert((Int("123456789") | Int(-2)) == Int("-123456791"));
  assert((big |= mod) == Int("64868103064868103064868103"));

  std::cout << "Testing bitwise XOR operator...\n";
  assert((Int("-123456789") ^ Int("987654321")) == Int("-1032168868"));
  assert((Int("-123456789123456789123456789") ^ Int("-987654321987654321")) ==
         Int("123456790020722188765646244"));
  assert((Int("987654321987654321") ^ Int("-123456789123456789123456789")) ==
         Int("-123456790020722188765646244"));
  assert((Int("123456789") ^ Int(-0)) == Int("123456789"));
  assert((Int("123456789") ^ Int(-1)) == Int("-123456788"));
  assert((Int("-123456789") ^ Int(-2)) == Int("123456791"));
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

  std::cout << "\n ----- End Int tests ----- \n\n";
}
