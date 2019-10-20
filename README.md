# Unsigned integers with undefined overflow

This library provides `uint7_t`, `uint15_t`, `uint31_t` and `uint63_t`.

| | `unsigned` | `signed` | `uint_mersenne` |
| --- | :---: | :---: | :---: |
| non-negative | ✔️ | | ✔️ |
| undefined overflow | | ✔️ | ✔️ |
| signed difference | | ✔️ | ✔️ |
| no implicit conversion from signed | | | ✔️ |
| uses all bits | ✔️ | ✔️ | |

# Usage

```
#include <uint_mersenne.h>
```

# Further Reading

- Robert Edler [Should I use Signed or Unsigned Ints In C? (Part 1)](https://blog.robertelder.org/signed-or-unsigned/) [(Part 2)](https://blog.robertelder.org/signed-or-unsigned-part-2/)
- Scott Meyers [Signed and Unsigned Types in Interfaces](https://www.aristeia.com/Papers/C++ReportColumns/sep95.pdf)
- C++ reference [Implicit conversions](https://en.cppreference.com/w/cpp/language/implicit_conversion)

[![Build Status](https://travis-ci.com/AtnNn/uint_mersenne.svg?branch=master)](https://travis-ci.com/AtnNn/uint_mersenne)