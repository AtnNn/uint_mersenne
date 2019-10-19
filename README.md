# Unsigned integers with undefined overflow

This library provides `uint7_t`, `uint15_t`, `uint31_t` and `uint63_t`.

# Usage

```
#include <uint_mersenne.h>
```

# Comparison

| | `unsigned` | `signed` | `uint_mersenne` |
| --- | :---: | :---: | :---: |
| non-negative | ✔️ | | ✔️ |
| undefined overflow | | ✔️ | ✔️ |
| signed difference | | ✔️ | ✔️ |
# Further Reading


- https://stackoverflow.com/questions/18795453/why-prefer-signed-over-unsigned-in-c