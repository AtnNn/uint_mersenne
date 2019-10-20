
#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#define UINT_MERSENNE_ALWAYS_POSITIVE_CUSTOM
#include "uint_mersenne.h"

namespace uint_mersenne {
template <class T> inline T always_positive(T x) {
  if (x < 0) {
    throw std::runtime_error("negative");
  }
  return x;
}
} // namespace uint_mersenne

TEST_CASE("Construct") {
  CHECK(uint7_t{0}.to_unsigned() == 0);
  CHECK(uint7_t{0}.to_signed() == 0);
  CHECK(uint15_t{0}.to_unsigned() == 0);
  CHECK(uint15_t{0}.to_signed() == 0);
  CHECK(uint31_t{0}.to_unsigned() == 0);
  CHECK(uint31_t{0}.to_signed() == 0);
  CHECK(uint63_t{0}.to_unsigned() == 0);
  CHECK(uint63_t{0}.to_signed() == 0);
  CHECK(uint7_t{0x7F}.to_unsigned() == 0x7F);
  CHECK(uint7_t{0x7F}.to_signed() == 0x7F);
  CHECK(uint15_t{0x7FFF}.to_unsigned() == 0x7FFF);
  CHECK(uint15_t{0x7FFF}.to_signed() == 0x7FFF);
  CHECK(uint31_t{0x7FFFFFFF}.to_unsigned() == 0x7FFFFFFF);
  CHECK(uint31_t{0x7FFFFFFF}.to_signed() == 0x7FFFFFFF);
  CHECK(uint63_t{0x7FFFFFFFFFFFFFFF}.to_unsigned() == 0x7FFFFFFFFFFFFFFF);
  CHECK(uint63_t{0x7FFFFFFFFFFFFFFF}.to_signed() == 0x7FFFFFFFFFFFFFFF);
  CHECK(uint7_t{uint7_t{1}}.to_unsigned() == 1);
  CHECK(uint7_t{uint7_t{1}}.to_signed() == 1);
  CHECK_THROWS(uint7_t{-1});
  CHECK_THROWS(uint15_t{-1});
  CHECK_THROWS(uint31_t{-1});
  CHECK_THROWS(uint63_t{-1});
}

TEST_CASE("Conversion") {

  CHECK(uint7_t{0x40}.to_signed_extend() == static_cast<int8_t>(0xC0));
  CHECK(uint15_t{0x4000}.to_signed_extend() == static_cast<int16_t>(0xC000));
  CHECK(uint31_t{0x40000000}.to_signed_extend() ==
        static_cast<int32_t>(0xC0000000));
  CHECK(uint63_t{0x4000000000000000}.to_signed_extend() ==
        static_cast<int64_t>(0xC000000000000000));
}

TEST_CASE("Arithmetic") {}
