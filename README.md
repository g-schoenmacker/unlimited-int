# About

Small, speedy unlimited integer class collection for C++

# Goal

Include one header file and you're ready to go.

This project aims to provide a collection of classes for speedy, unlimited precision integer calculation in C++. The focus is ease of use without the need to learn how to install or use the software. This is achieved by following the motto "do as the ints do": the unlimited integer can be used exactly as if it were a normal int by including a single header file.

# When (not) to use

Use this if you want:
 - Easy to use, installation free solution
 - Relatively fast unlimited precision integer calculation

Do not use this if you need: 
 - Extremely fast calculation

This library may be used for accurate and relatively fast unlimited integer calculation in non time critial applications. On difficult platforms (such as MinGW, for example), it can be a solution because it requires little from the environment and needs no installation. If speed is critial or you need floating point operations, consider using GMP (http://gmplib.org) or Boost Multiprecision (https://github.com/boostorg/multiprecision).

# Summary

All the information you need to get started using this library.

## Quick start

Here you will find all the information you need to get started using the library.

### Downloading the header file

In the repo, you will find the `unlimited_int.h` header file. Download this and save it to (some place reachable from) your source code directory.

### Including the header file

Add the following line to any source code document in which you want to use the library (note the _path/to/_ part needs to be edited by you):

`#include "path/to/unlimited_int.h"`

### Using the header file

Everything provided by the library can be found in the *Unlimited* namespace. The library provides three classes: *Unlimited::Str_UInt*, *Unlimited::UInt* and *Unlimited::Int*. If you're unsure which to use, pick the latter.

You can use the Unlimited::Int type as if it were an int. You can assign, compare and calculate the normal way. If you need any specific operation, try looking it up in the documentation of the class.

# Documentation for the Int class

## Unlimited::Int

The Unlimited::Int represents a signed integral number of arbitrary precision.

### Constructors

<table border='1' cellpadding='2'>
 <tr>
  <th width='30%'>Function definition</th>
  <th>Specifics</th>
 </tr>
 <tr>
  <td valign='top'><pre>Int::Int(long long = 0)</pre></td>
  <td valign='top'>long long int constructor. Implicit, converts int-types to Int. Default argument is 0.

    Unlimited::Int a; // a equals 0
    Unlimited::Int b(-42);
    b += 42; // Implicit construction used to construct Int(42) from '42'.

  </td>
 </tr>
 <tr>
  <td valign='top'><pre>explicit Int::Int(std::string const &)</pre></td>
  <td valign='top'>std::string constructor. Ignores any leading zeroes. Explicit, throws _Unlimited::Int::Exception_ if string contains characters other than '-' (as first character) or '0'-'9'. Does not support any other (exponential, scientific) notations.

    Unlimited::Int a("-10000000");
    std::string b_val("4200");
    Unlimited::Int b(b_val);

 </td>
 </tr>
 <tr>
  <td valign='top'><pre>explicit Int::Int(UInt const &)</pre></td>
  <td valign='top'>UInt constructor. Explicit, converts UInt to Int.

    Unlimited::Int b(Unlimited::UInt(1)); // a equals 1
    Unlimited::UInt u_int(42);
    Unlimited::Int b(u_int); // b equals 42

  </td>
 </tr>
 <tr>
  <td valign='top'><pre>Int::Int(Int const &)</pre></td>
  <td valign='top'>Copy constructor, compiler generated.

    Unlimited::Int a(42);
    Unlimited::Int b(a); // b equals a equals 42

   </td>
 </tr>
 <tr>
  <td valign='top'><pre>Int::Int(Int &&)</pre></td>
  <td valign='top'>Move constructor, compiler generated.

    Unlimited::Int a(Unlimited::Int("123456789")); // a equals 123456789
    Unlimited::Int b(42);
    Unlimited::Int c(std::move(b)); // c equals 42. value of b unknown.

   </td>
 </tr>
</table>

### Assignment operators 

<table border='1' cellpadding='2'>
 <tr>
  <th width='30%'>Function definition</th>
  <th>Specifics</th>
 </tr>
 <tr>
  <td valign='top'><pre>Int &Int::operator=(Int const &)</pre></td>
  <td valign='top'>Copy assignment operator. Compiler generated.

  </td>
 </tr>
 <tr>
  <td valign='top'><pre>Int &Int::operator=(Int &&)</pre></td>
  <td valign='top'>Move assignment operator. Compiler generated. Due to implicit long long int constructor, can process direct assigments from int types.

  </td>
 </tr>
</table>

### Overloaded arithmetic operators 

<table border='1' cellpadding='2'>
 <tr>
  <th width='30%'>Function definition</th>
  <th>Specifics</th>
 </tr>
 <tr>
  <td valign='top'> *Function definition*</td>
  <td valign='top'>*Specifics* </td>
 </tr>
 <tr>
  <td valign='top'><pre>Int operator+(Int const &, Int const &)</pre></td>
  <td valign='top'>Normal binary + behaviour.

    Unlimited::Int a(42);
    Unlimited::Int b = a + a; // 84

  </td>
 </tr>
 <tr>
  <td valign='top'><pre>Int &Int::operator+=(Int const &)</pre></td>
  <td valign='top'>Normal += behaviour.

    Unlimited::Int a; // 0
    a += 10; // 10
    a += a; // 20

 </td>
 </tr>
 <tr>
  <td valign='top'><pre>Int operator-(Int const &, Int const &)</pre></td>
  <td valign='top'>Normal binary - behaviour.

    Unlimited::Int a(42);
    Unlimited::Int b = a - a; // 0

  </td>
 </tr>
 <tr>
  <td valign='top'><pre>Int &Int::operator-=(Int const &)</pre></td>
  <td valign='top'>Normal -= behaviour.

    Unlimited::Int a; // 0
    a -= 10; // -10
    a -= a; // 0

  </td>
 </tr>
 <tr>
  <td valign='top'><pre>Int operator`*`(Int const &, Int const &)</pre></td>
  <td valign='top'>Normal binary `*` behaviour.

    Unlimited::Int a(42);
    Unlimited::Int b = a * a; // 1764

  </td>
 </tr>
 <tr>
  <td valign='top'><pre>Int &Int::operator`*`=(Int const &)</pre></td>
  <td valign='top'>Normal `*`= behaviour.

    Unlimited::Int a(1); // 1
    a *= 10; // 100
    a *= a; // 10000

  </td>
 </tr>
 <tr>
  <td valign='top'><pre>Int operator/(Int const &, Int const &)</pre></td>
  <td valign='top'>Normal binary / behaviour. Throws _Unlimited::Int::Exception_ (divison by zero) if second operand equals 0. Result is negative only if exactly one of the operands is negative. It behaves so that `(a/b)*b + a%b == a` holds. Note the examples.

    Unlimited::Int a(42);
    Unlimited::Int b = -90 / a; // -2
    Unlimited::Int c = b / 0; // throws Unlimited::Int::Exception

    Unlimited::Int seven(7);
    Unlimited::Int minus_seven(-7);

    Unlimited::Int d = seven /  5; // 1
    Unlimited::Int e = minus_seven /  5; // -2
    Unlimited::Int f = seven / -5; // -2
    Unlimited::Int g = minus_seven / -5; // 1

  </td>
 </tr>
 <tr>
  <td valign='top'><pre>Int &Int::operator/=(Int const &)</pre></td>
  <td valign='top'>Normal /= behaviour. Throws _Unlimited::Int::Exception_ (divison by zero) if second operand equals 0. Result is negative only if exactly one of the operands is negative. It behaves so that `(a/b)*b + a%b == a` holds. Note the examples of the binary operator/.

    Unlimited::Int a("10000"); // 10000
    a /= -10; // -1000
    a /= a; // 1
    a /= 0; // throws Unlimited::Int::Exception

  </td>
 </tr>
 <tr>
  <td valign='top'><pre>Int operator%(Int const &, Int const &)</pre></td>
  <td valign='top'>Normal binary % behaviour. Throws _Unlimited::Int::Exception_ (divison by zero) if second operand equals 0. Result is negative only if the second operand is negative. It behaves so that `(a/b)*b + a%b == a` holds. Note the examples.

    Unlimited::Int a(42);
    Unlimited::Int b = 90 % a; // 6
    Unlimited::Int c = b % 0; // throws Unlimited::Int::Exception

    Unlimited::Int seven(7);
    Unlimited::Int minus_seven(-7);

    Unlimited::Int d = seven %  5; // 2
    Unlimited::Int e = minus_seven %  5; // 3
    Unlimited::Int f = seven % -5; // -3
    Unlimited::Int g = minus_seven % -5; // -2

  </td>
 </tr>
 <tr>
  <td valign='top'><pre>Int &Int::operator%=(Int const &)</pre></td>
  <td valign='top'>Normal %= behaviour. Throws _Unlimited::Int::Exception_ (divison by zero) if second operand equals 0. Result is negative only if the second operand is negative. It behaves so that `(a/b)*b + a%b == a` holds. Note the examples of the binary operator%.

    Unlimited::Int a(10); // 10
    a %= 6; // 4
    a %= 3; // 1

  </td>
 </tr>
 <tr>
  <td valign='top'><pre>Int Int::operator-() const</pre></td>
  <td valign='top'>Unary minus. Normal behaviour.

    Unlimited::Int a(42);
    -a; // returns Unlimited::Int(-42) but does not change a
    Unlimited::Int b = -a; // -42

  </td>
 </tr>
 <tr>
  <td valign='top'><pre>Int Int::operator++(int)</pre></td>
  <td valign='top'>Postfix increment operator. Normal behaviour.

    Unlimited::Int a(42);
    Unlimited::Int b = a++; // b equals 42. a equals 43.

 </td>
 </tr>
 <tr>
  <td valign='top'><pre>Int Int::operator--(int)</pre></td>
  <td valign='top'>Postfix decrement operator. Normal behaviour.

    Unlimited::Int a(42);
    Unlimited::Int b = a--; // b equals 42. a equals 41.

  </td>
 </tr>
 <tr>
  <td valign='top'><pre>Int &Int::operator++()</pre></td>
  <td valign='top'>Prefix increment operator. Normal behaviour.

    Unlimited::Int a(42);
    Unlimited::Int b = ++a; // b equals 43. a equals 43.

  </td>
 </tr>
 <tr>
  <td valign='top'><pre>Int &Int::operator--()</pre></td>
  <td valign='top'>Prefix decrement operator. Normal behaviour.

    Unlimited::Int a(42);
    Unlimited::Int b = --a; // b equals 41. a equals 41.

 </td>
 </tr>
</table>

### Other arithmetic methods

<table border='1' cellpadding='2'>
 <tr>
  <th width='30%'>Function definition</th>
  <th>Specifics</th>
 </tr>
 <tr>
  <td valign='top'><pre>void Int::divide(Int const &, Int &, Int &) const</pre></td>
  <td valign='top'>Takes divisor as first (input) argument, and a reference to the result of the division and the modulus as the second and third (output) arguments. Output argument are reassigned during calculation, so never use (one of) the input arguments also as output parameter. Should be used if both the result and modulus of the division are needed. Throws _Unlimited::Int::Exception_ (divison by zero) if first argument equals 0.  operands is negative. It behaves so that `(a/b)*b + a%b == a` holds. Note the examples.

    Unlimited::Int seven(7);
    Unlimited::Int minus_seven(-7);

    Unlimited::Int res, mod; // create output arguments

    seven.divide(5, res, mod); // res equals 1. mod equals 2.
    minus_seven.divide(5, res, mod); // res equals -2. mod equals 3.
    seven.divide(-5, res, mod); // res equals -2. mod equals -3.
    minus_seven.divide(-5, res, mod); // res equals 1. mod equals -2.

    seven.divide(0, res, mod); // throws Unlimited::Int::Exception

  </td>
 </tr>
 <tr>
  <td valign='top'><pre>Int &Int::pow(Int const &)</pre></td>
  <td valign='top'>Raises object to the power of argument. Changes object value and returns reference to self. Throws _Unlimited::Int::Exception_ if argument is negative.

    Unlimited::Int a(2);
    a.pow(10); // a equals 1024
    a.pow(0); // a equals 1
    a.pow(-1); // throws Unlimited::Int::Exception

  </td>
 </tr>
 <tr>
  <td valign='top'><pre>Int Int::powc(Int const &) const</pre></td>
  <td valign='top'>Raises object to the power of argument. Does not change object value and returns a new object. Throws _Unlimited::Int::Exception_ if argument is negative.

    Unlimited::Int const two(2);
    Unlimited::Int b = two.powc(9); // b equals 512
    Unlimited::Int c = (-two).powc(9); // b equals -512
    a.powc(-1); // throws Unlimited::Int::Exception

  </td>
 </tr>
 <tr>
  <td valign='top'><pre>Int &Int::sqrt()</pre></td>
  <td valign='top'>Calculates the integer square root. Changes object value and returns reference to self. Throws _Unlimited::Int::Exception_ if number is negative.

    Unlimited::Int a("1000");
    a.sqrt(); // a equals 31.
    Unlimited::Int b = a.sqrt(); // b equals 5. a equals 5.

  </td>
 </tr>
 <tr>
  <td valign='top'><pre>Int Int::sqrtc() const</pre></td>
  <td valign='top'>Calculates the integer square root. Does not change object value and returns a new object. Throws _Unlimited::Int::Exception_ if number is negative.

    Unlimited::Int a("1000");
    Unlimited::Int b = a.sqrtc(); // b equals 31. a equals 1000.

  </td>
 </tr>
</table>

### Conversion methods

<table border='1' cellpadding='2'>
 <tr>
  <th width='30%'>Function definition</th>
  <th>Specifics</th>
 </tr>
 <tr>
  <td valign='top'><pre>explicit Int::operator bool() const</pre></td>
  <td valign='top'>Explicit bool conversion operator. Returns false if object equals 0, true otherwise.

    Unlimited::Int a(0);
    Unlimited::Int b(-1);

    if (a) {
      // not executed
    }
    if (b) {
      // executed
    }

  </td>
 </tr>
 <tr>
  <td valign='top'><pre>long long Int::ll() const</pre></td>
  <td valign='top'>Converts number to long long. If the internal number is too large, produces wrong result without warning. Result may differ from machine to machine due to size of `long long int`.

    Unlimited::Int a(-10);

    long long b = a.ll(); // b equals -10

  </td>
 </tr>
 <tr>
  <td valign='top'><pre>std::string Int::str() const</pre></td>
  <td valign='top'>Converts number to string.

    Unlimited::Int a(-10);
    Unlimited::Int b("1234567890");

    std::string s1 = a.str(); // s1 equals "-10"
    std::string s2 = b.str(); // s2 equals "1234567890"

  </td>
 </tr>
</table>

### Comparison operators

<table border='1' cellpadding='2'>
 <tr>
  <th width='30%'>Function definition</th>
  <th>Specifics</th>
 </tr>
 <tr>
  <td valign='top'><pre>bool operator==(Int const &, Int const &)</pre></td>
  <td valign='top'>Equality. </td>
 </tr>
 <tr>
  <td valign='top'><pre>bool operator!=(Int const &, Int const &)</pre></td>
  <td valign='top'>Inequality. </td>
 </tr>
 <tr>
  <td valign='top'><pre>bool operator<(Int const &, Int const &)</pre></td>
  <td valign='top'>Smaller than. </td>
 </tr>
 <tr>
  <td valign='top'><pre>bool operator<=(Int const &, Int const &)</pre></td>
  <td valign='top'>Smaller than or equals. </td>
 </tr>
 <tr>
  <td valign='top'><pre>bool    Unlimited::Int a(-10);
    Unlimited::Int b("1234567890");

    std::string s1 = a.str(); // s1 equals "-10"
    std::string s2 = b.str(); // s2 equals "1234567890"
 operator>(Int const &, Int const &)</pre></td>
  <td valign='top'>Larger than. </td>
 </tr>
 <tr>
  <td valign='top'><pre>bool operator>=(Int const &, Int const &)</pre></td>
  <td valign='top'>Larger than or equals. </td>
 </tr>
 <tr>
  <td valign='top'><pre>explicit operator Int::bool() const</pre></td>
  <td valign='top'>Already mentioned under 'conversion methods'. Repeated here for clarity. </td>
 </tr>
</table>

### Other comparison methods

<table border='1' cellpadding='2'>
 <tr>
  <th width='30%'>Function definition</th>
  <th>Specifics</th>
 </tr>
 <tr>
  <td valign='top'><pre>int Int::compare(Int const &) const</pre></td>
  <td valign='top'>Compare method. Returns 1 if object is larger than argument, -1 if it is smaller than argument and 0 if they are equal. </td>
 </tr>
</table>

### Bitwise operators

<table border='1' cellpadding='2'>
 <tr>
  <th width='30%'>Function definition</th>
  <th>Specifics</th>
 </tr>
 <tr>
  <td valign='top'><pre>Int operator&(Int const &, Int const &)</pre></td>
  <td valign='top'>Bitwise AND operator. Result is negative if and only if both operands are negative. </td>
 </tr>
 <tr>
  <td valign='top'><pre>Int &Int::operator&=(Int const &oth)</pre></td>
  <td valign='top'>Bitwise AND-assign. Follows same rules as AND. Changes object and returns reference to self.</td>
 </tr>
 <tr>
  <td valign='top'><pre>Int operator|(Int const &, Int const &)</pre></td>
  <td valign='top'>Bitwise OR operator. Result is negative if one or both operands are negative. </td>
 </tr>
 <tr>
  <td valign='top'><pre>Int &Int::operator|=(Int const &oth)</pre></td>
  <td valign='top'>Bitwise OR-assign. Follows same rules as OR. Changes object and returns reference to self.</td>
 </tr>
 <tr>
  <td valign='top'><pre>Int operator^(Int const &, Int const &)</pre></td>
  <td valign='top'>Bitwise XOR operator. Result is negative if and only if one of the operands is negative. </td>
 </tr>
 <tr>
  <td valign='top'><pre>Int &Int::operator^=(Int const &oth)</pre></td>
  <td valign='top'>Bitwise XOR-assign. Follows same rules as XOR. Changes object and returns reference to self.</td>
 </tr>
 <tr>
  <td valign='top'><pre>Int Int::operator<<(unsigned) const</pre></td>
  <td valign='top'>Left-shift operator. Does not affect sign. Takes unsigned argument (and not Int). </td>
 </tr>
 <tr>
  <td valign='top'><pre>Int &Int::operator<<=(unsigned)</pre></td>
  <td valign='top'>Left-shift-assign operator. Follows same rules as left-shift. </td>
 </tr>
 <tr>
  <td valign='top'><pre>Int Int::operator>>(unsigned) const</pre></td>
  <td valign='top'>Right-shift operator. Does not affect sign. Takes unsigned argument (and not Int). </td>
 </tr>
 <tr>
  <td valign='top'><pre>Int &Int::operator>>=(unsigned)</pre></td>
  <td valign='top'>Right-shift-assign operator. Follows same rules as right-shift. </td>
 </tr>
</table>

### Other bitwise methods

<table border='1' cellpadding='2'>
 <tr>
  <th width='30%'>Function definition</th>
  <th>Specifics</th>
 </tr>
 <tr>
  <td valign='top'><pre>size_t Int::num_bits() const</pre></td>
  <td valign='top'>Returns the number of bits currently allocated to store the number. This number is equal to or larger than the number of bits needed to store the number. </td>
 </tr>
 <tr>
  <td valign='top'><pre>bool Int::bit(size_t n) const</pre></td>
  <td valign='top'>Returns the value of the _n_ th bit in the number. Returns true if bit is set, false otherwise. If the _n_ th bit does not currently exist, false is returned. </td>
 </tr>
 <tr>
  <td valign='top'><pre>void Int::set_bit(size_t n, bool val)</pre></td>
  <td valign='top'>Sets the value of bit _n_ to _val_. If the _n_ th bit does not currently exist, number is enlarged. </td>
 </tr>
</table>

### Stream operators

<table border='1' cellpadding='2'>
 <tr>
  <th width='30%'>Function definition</th>
  <th>Specifics</th>
 </tr>
 <tr>
  <td valign='top'><pre>std::ostream &operator<<(std::ostream &, Int const &)</pre></td>
  <td valign='top'>Inserts a string representation of an Int object into an ostream. </td>
 </tr>
 <tr>
  <td valign='top'><pre>std::istream &operator>>(std::istream &, Int &)</pre></td>
  <td valign='top'>Extracts an Int object from an istream. If extraction fails, _std::istream::failbit_ is set. </td>
 </tr>
</table>


### Other methods

<table border='1' cellpadding='2'>
 <tr>
  <th width='30%'>Function definition</th>
  <th>Specifics</th>
 </tr>
 <tr>
  <td valign='top'><pre>void Int::swap(Int &)</pre></td>
  <td valign='top'>Swaps value of object with that of argument. </td>
 </tr>
</table>
