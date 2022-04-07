#include "int/int.h"
#include "uint/uint.h"
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace Unlimited;

void uint_test() {

  std::cout << "\n ----- UInt tests ----- \n\n";

  std::vector<std::string> set_a = {"123456789", "1234567891", "1",
                                    "123456789012345678901234567890", "100"};
  std::vector<std::string> set_b = {"123456689", "00123456789", "000",
                                    "987654321", "0000020"};

  std::cout
      << "Testing constructor, copy constructor and equality operators...\n";
  for (size_t idx = 0; idx < set_a.size(); ++idx) {
    UInt a(set_a[idx]);
    UInt b(a);

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
    UInt a(set_a[idx]);
    UInt b("0");
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

  std::cout << "Testing Int construction...\n";
  assert(UInt(Int("123456789")) == UInt("123456789"));
  assert(UInt(Int("-123456789987654321")) == UInt("123456789987654321"));

  std::cout << "Testing equality operators...\n";
  for (size_t idx = 0; idx < set_a.size(); ++idx) {
    UInt a(set_a[idx]);
    UInt b(set_b[idx]);

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
  UInt a, b;
  for (; a < 1000; ++a, b++) {
    assert(a == b);
  }
  assert(b == 1000);
  for (; a; --a, b--) {
    assert(a == b);
  }
  assert(b == 0);

  std::cout << "Testing divide method...\n";

  UInt big("123456789123456789123456789");
  UInt res, mod;
  big.divide(1, res, mod);
  assert(big == res);
  assert(mod == 0);

  big.divide(2, res, mod);
  assert(res == UInt("61728394561728394561728394"));
  assert(mod == 1);

  big.divide(5, res, mod);
  assert(res == UInt("24691357824691357824691357"));
  assert(mod == 4);

  big.divide(UInt("987654321"), res, mod);
  assert(res == UInt("124999998985937499"));
  assert(mod == 173610);

  big = UInt("12345678912345678912345678912345678912345678912345678912345678912"
             "3456789123456789");
  big.divide(UInt("987654321987654321987654321"), res, mod);
  assert(res == UInt("124999998860937500014238281374822020345314724745683566"));
  assert(mod == UInt("64868103064868103064868103"));

  // Just checking the existance of the operators
  assert((big / mod) ==
         UInt("1903197153769087404945385872058826647050245942909722519"));
  assert((big /= mod) ==
         UInt("1903197153769087404945385872058826647050245942909722519"));
  assert((big % mod) == UInt("38381123895690670931465716"));
  assert((big %= mod) == UInt("38381123895690670931465716"));

  std::cout << "Testing multiplication method...\n";
  assert(UInt(0) * UInt(1234) == UInt(0));
  assert(UInt(1) * UInt(1234) == UInt(1234));
  assert(UInt(2) * UInt(1234) == UInt(2468));

  assert(UInt("987654321987654321") * UInt("112233445566778899") ==
         UInt("110847847585595321123720052648972579"));

  assert(UInt("987654321987654321999") * UInt("112233445566778899111") ==
         UInt("110847847585595321345470894510814328842889"));

  // Just checking the existance of the operator
  assert((big *= mod) ==
         UInt("2489710700611134398732558402699595704578172006456748"));

  std::cout << "Testing addition method...\n";

  assert(UInt(0) + UInt(1234) == UInt(1234));
  assert(UInt(1) + UInt(1234) == UInt(1235));
  assert(UInt(12) + UInt(1234) == UInt(1246));
  assert(UInt(999) + UInt(1) == UInt(1000));

  assert(UInt(1234) + UInt(0) == UInt(1234));
  assert(UInt(1234) + UInt(1) == UInt(1235));
  assert(UInt(1234) + UInt(12) == UInt(1246));
  assert(UInt(1) + UInt(999) == UInt(1000));

  assert(UInt("987654321987654321999") + UInt("00112233445566778899111") ==
         UInt("1099887767554433221110"));

  // Just checking the existance of the operator
  assert((big += mod) ==
         UInt("2489710700611134398732558467567698769446275071324851"));

  std::cout << "Testing subtraction method...\n";

  assert(UInt(1234) - UInt(0) == UInt(1234));
  assert(UInt(1234) - UInt(1) == UInt(1233));
  assert(UInt(1234) - UInt(2) == UInt(1232));
  assert(UInt(1234) - UInt(5) == UInt(1229));
  assert(UInt(1234) - UInt(1234) == UInt(0));

  assert(UInt("987654321987654321999") - UInt("112233445566778899111") ==
         UInt("875420876420875422888"));

  assert((UInt("823456789123456789") - UInt("823456789023456789")) ==
         UInt("100000000"));

  // Just checking the existance of the operator
  assert((big -= mod) ==
         UInt("2489710700611134398732558402699595704578172006456748"));

  std::cout << "Testing power method...\n";
  assert(UInt("123456789").powc(0) == UInt(1));
  assert(UInt("123456789").powc(1) == UInt("123456789"));
  assert(UInt("123456789").powc(2) == UInt("15241578750190521"));
  assert(UInt("123456789").powc(3) == UInt("1881676371789154860897069"));
  assert(UInt("123456789").powc(4) ==
         UInt("232305722798259244150093798251441"));
  assert(UInt("123456789").powc(5) ==
         UInt("28679718602997181072337614380936720482949"));

  res = 81;
  assert(res.pow(23) == UInt("78551672112789411833022577315290546060373041"));

  std::cout << "Testing sqrt method...\n";
  assert(UInt("123456789").sqrtc() == UInt("11111"));
  assert(UInt("15241578750190521").sqrtc() == UInt("123456789"));
  assert(UInt("1881676371789154860897069").sqrtc() == UInt("1371742093758"));
  assert(UInt("232305722798259244150093798251441").sqrtc() ==
         UInt("15241578750190521"));
  assert(UInt("28679718602997181072337614380936720482949").sqrtc() ==
         UInt("169350874231570416987"));
  assert(res.sqrt() == UInt("8862938119652501095929"));

  std::cout << "Testing left shift operator...\n";
  assert((UInt("123456789") << 25) == UInt("4142522431438848"));
  assert((UInt("123456789") << 0) == UInt("123456789"));
  assert((UInt("123456789") << 1) == UInt("246913578"));
  for (size_t pow = 1; pow < 50; ++pow)
    assert((UInt("123456789") << pow) ==
           (UInt("123456789") * UInt(2).powc(pow)));
  assert((big <<= 3) ==
         UInt("19917685604889075189860467221596765636625376051653984"));

  std::cout << "Testing right shift operator...\n";
  assert((UInt("4142522431438848") >> 25) == UInt("123456789"));
  assert((UInt("123456789") >> 0) == UInt("123456789"));
  assert((UInt("123456789") >> 1) == UInt("61728394"));
  assert((UInt("987654321987654321987654321987654321") >> 40) ==
         UInt("898266373030905308030609"));
  assert((big >>= 3) ==
         UInt("2489710700611134398732558402699595704578172006456748"));

  std::cout << "Testing bitwise AND operator...\n";

  assert((UInt("123456789") & UInt("987654321")) == UInt("39471121"));
  assert((UInt("123456789123456789123456789") & UInt("987654321987654321")) ==
         UInt("45194461172732433"));
  assert((UInt("987654321987654321") & UInt("123456789123456789123456789")) ==
         UInt("45194461172732433"));
  assert((UInt("123456789") & UInt(0)) == UInt(0));
  assert((UInt("123456789") & UInt(1)) == UInt(1));
  assert((big &= mod) == UInt("152342437133404011517188"));

  std::cout << "Testing bitwise OR operator...\n";

  assert((UInt("123456789") | UInt("987654321")) == UInt("1071639989"));
  assert((UInt("123456789123456789123456789") | UInt("987654321987654321")) ==
         UInt("123456790065916649938378677"));
  assert((UInt("987654321987654321") | UInt("123456789123456789123456789")) ==
         UInt("123456790065916649938378677"));
  assert((UInt("123456789") | UInt(0)) == UInt("123456789"));
  assert((UInt("123456789") | UInt(2)) == UInt("123456791"));
  assert((big |= mod) == UInt("64868103064868103064868103"));

  std::cout << "Testing bitwise XOR operator...\n";
  assert((UInt("123456789") ^ UInt("987654321")) == UInt("1032168868"));
  assert((UInt("123456789123456789123456789") ^ UInt("987654321987654321")) ==
         UInt("123456790020722188765646244"));
  assert((UInt("987654321987654321") ^ UInt("123456789123456789123456789")) ==
         UInt("123456790020722188765646244"));
  assert((UInt("123456789") ^ UInt(0)) == UInt("123456789"));
  assert((UInt("123456789") ^ UInt(1)) == UInt("123456788"));
  assert((UInt("123456789") ^ UInt(2)) == UInt("123456791"));
  assert((big ^= mod) == UInt(0));

  std::cout << "Testing bit setting methods...\n";
  big.set_bit(0, 1);
  assert(big == UInt(1));
  big.set_bit(1, 1);
  assert(big == UInt(3));
  big.set_bit(2, 1);
  assert(big == UInt(7));
  big.set_bit(1, 0);
  assert(big == UInt(5));
  big = UInt("1365");
  for (size_t idx = 0; idx < 12; ++idx)
    big.set_bit(idx, idx % 2 == 0);
  assert(big == UInt("1365"));
  big.set_bit(70, 1);
  assert(big == UInt("1180591620717411304789"));

  std::cout << "Testing str method...\n";
  assert(UInt("00").str().compare("0") == 0);
  assert(UInt("1").str().compare("1") == 0);
  assert(UInt("12345").str().compare("12345") == 0);
  assert(UInt("987654321987654321999").str().compare("987654321987654321999") ==
         0);

  std::cout << "Testing stream extract method...\n";
  std::istringstream ss("0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19");
  for (UInt a; a < 20; ++a) {
    UInt temp;
    assert(ss >> temp);
    assert(temp == a);
  }
  assert(!(ss >> big));

  std::cout << "Testing unsigned long long conversion method...\n";
  for (unsigned long long idx = 0; idx < ~0ULL - 80000000000001ULL;
       idx += 800000000000000ULL) {
    assert(UInt(idx).ull() == idx);
  }

  assert(UInt("1234567").ull() == 1234567ULL);

  std::cout << "\n ----- End UInt tests ----- \n\n";
}
