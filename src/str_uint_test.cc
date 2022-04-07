#include "str_uint/str_uint.h"
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace Unlimited;

void str_uint_test() {

  std::cout << "\n ----- Str_UInt tests ----- \n\n";

  std::vector<std::string> set_a = {"123456789", "1234567891", "1",
                                    "123456789012345678901234567890", "100"};
  std::vector<std::string> set_b = {"123456689", "00123456789", "000",
                                    "987654321", "0000020"};

  std::cout
      << "Testing constructor, copy constructor and equality operators...\n";
  for (size_t idx = 0; idx < set_a.size(); ++idx) {
    Str_UInt a(set_a[idx]);
    Str_UInt b(a);

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
    Str_UInt a(set_a[idx]);
    Str_UInt b("0");
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

  std::cout << "Testing equality operators...\n";
  for (size_t idx = 0; idx < set_a.size(); ++idx) {
    Str_UInt a(set_a[idx]);
    Str_UInt b(set_b[idx]);

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
  Str_UInt a, b;
  for (; a < 1000; ++a, b++) {
    assert(a == b);
  }
  assert(b == 1000);
  for (; a; --a, b--) {
    assert(a == b);
  }
  assert(b == 0);

  std::cout << "Testing divide method...\n";

  Str_UInt big("123456789123456789123456789");
  Str_UInt res, mod;
  big.divide(1, res, mod);
  assert(big == res);
  assert(mod == 0);

  Str_UInt temp("123456789");
  temp.divide(256, res, mod);
  assert(res == Str_UInt("482253"));
  assert(mod == Str_UInt(21));

  big.divide(2, res, mod);
  assert(res == Str_UInt("61728394561728394561728394"));
  assert(mod == 1);

  big.divide(5, res, mod);
  assert(res == Str_UInt("24691357824691357824691357"));
  assert(mod == 4);

  big.divide(Str_UInt("987654321"), res, mod);
  assert(res == Str_UInt("124999998985937499"));
  assert(mod == 173610);

  big = Str_UInt("1234567891234567891234567891234567891234567891234567891234567"
                 "89123456789123456789");
  big.divide(Str_UInt("987654321987654321987654321"), res, mod);
  assert(res ==
         Str_UInt("124999998860937500014238281374822020345314724745683566"));
  assert(mod == Str_UInt("64868103064868103064868103"));

  // Just checking the existance of the operators
  assert((big / mod) ==
         Str_UInt("1903197153769087404945385872058826647050245942909722519"));
  assert((big /= mod) ==
         Str_UInt("1903197153769087404945385872058826647050245942909722519"));
  assert((big % mod) == Str_UInt("38381123895690670931465716"));
  assert((big %= mod) == Str_UInt("38381123895690670931465716"));

  std::cout << "Testing multiplication method...\n";
  assert(Str_UInt(0) * Str_UInt(1234) == Str_UInt(0));
  assert(Str_UInt(1) * Str_UInt(1234) == Str_UInt(1234));
  assert(Str_UInt(2) * Str_UInt(1234) == Str_UInt(2468));

  assert(Str_UInt("987654321987654321") * Str_UInt("112233445566778899") ==
         Str_UInt("110847847585595321123720052648972579"));

  assert(Str_UInt("987654321987654321999") *
             Str_UInt("112233445566778899111") ==
         Str_UInt("110847847585595321345470894510814328842889"));

  // Just checking the existance of the operator
  assert((big *= mod) ==
         Str_UInt("2489710700611134398732558402699595704578172006456748"));

  std::cout << "Testing addition method...\n";

  assert(Str_UInt(0) + Str_UInt(1234) == Str_UInt(1234));
  assert(Str_UInt(1) + Str_UInt(1234) == Str_UInt(1235));
  assert(Str_UInt(12) + Str_UInt(1234) == Str_UInt(1246));
  assert(Str_UInt(999) + Str_UInt(1) == Str_UInt(1000));

  assert(Str_UInt(1234) + Str_UInt(0) == Str_UInt(1234));
  assert(Str_UInt(1234) + Str_UInt(1) == Str_UInt(1235));
  assert(Str_UInt(1234) + Str_UInt(12) == Str_UInt(1246));
  assert(Str_UInt(1) + Str_UInt(999) == Str_UInt(1000));

  assert(Str_UInt("987654321987654321999") +
             Str_UInt("00112233445566778899111") ==
         Str_UInt("1099887767554433221110"));

  // Just checking the existance of the operator
  assert((big += mod) ==
         Str_UInt("2489710700611134398732558467567698769446275071324851"));

  std::cout << "Testing subtraction method...\n";

  assert(Str_UInt(1234) - Str_UInt(0) == Str_UInt(1234));
  assert(Str_UInt(1234) - Str_UInt(1) == Str_UInt(1233));
  assert(Str_UInt(1234) - Str_UInt(2) == Str_UInt(1232));
  assert(Str_UInt(1234) - Str_UInt(5) == Str_UInt(1229));
  assert(Str_UInt(1234) - Str_UInt(1234) == Str_UInt(0));

  assert(Str_UInt("987654321987654321999") -
             Str_UInt("112233445566778899111") ==
         Str_UInt("875420876420875422888"));

  assert(Str_UInt("823456789123456789") - Str_UInt("823456789023456789") ==
         Str_UInt("100000000"));

  // Just checking the existance of the operator
  assert((big -= mod) ==
         Str_UInt("2489710700611134398732558402699595704578172006456748"));

  std::cout << "Testing digit methods...\n";
  assert(Str_UInt(0).length() == 1);
  assert(Str_UInt(5).length() == 1);
  assert(Str_UInt(123).length() == 3);
  Str_UInt dig("0123456789"); // note 0 will be discarded
  for (size_t idx = 0; idx < 9; ++idx) {
    assert(idx + 1 == dig.digit(idx));
    dig.digit(idx, 9);
  }
  assert(dig == Str_UInt("999999999"));

  std::cout << "Testing str method...\n";
  assert(Str_UInt("00").str().compare("0") == 0);
  assert(Str_UInt("1").str().compare("1") == 0);
  assert(Str_UInt("12345").str().compare("12345") == 0);
  assert(Str_UInt("987654321987654321999")
             .str()
             .compare("987654321987654321999") == 0);

  std::cout << "Testing stream extract method...\n";
  std::istringstream ss("0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19");
  for (Str_UInt a; a < 20; ++a) {
    Str_UInt temp;
    assert(ss >> temp);
    assert(temp == a);
  }
  assert(!(ss >> dig));

  std::cout << "\n ----- End Str_UInt tests ----- \n\n";
}
