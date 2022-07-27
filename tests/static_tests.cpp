// Copyright (C) Tommy Hinks <tommy.hinks@gmail.com>
// This file is subject to the license terms in the LICENSE file
// found in the top-level directory of this distribution.

#include <functional>
#include <type_traits>

#include <tph/tph_linalg.hpp>

#define HAS_CPP17 (__cplusplus >= 201703L)

int main(int /*argc*/, char* /*argv*/[]) {
  static_assert(sizeof(tph::Vec<float, 2>) == 2 * sizeof(float), "");
  static_assert(sizeof(tph::Vec<float, 3>) == 3 * sizeof(float), "");
  static_assert(sizeof(tph::Vec<float, 4>) == 4 * sizeof(float), "");

  // Construction.
  constexpr tph::Vec<float, 2> a2{1.0F, 2.0F};
  constexpr tph::Vec<float, 3> a3{1.0F, 2.0F, 3.0F};
  constexpr tph::Vec<float, 4> a4{1.0F, 2.0F, 3.0F, 4.0F};
  static_assert(a2.x == 1.0F && a2.y == 2.0F, "");
  static_assert(a3.x == 1.0F && a3.y == 2.0F && a3.z == 3.0F, "");
  static_assert(a4.x == 1.0F && a4.y == 2.0F && a4.z == 3.0F && a4.w == 4.0F, "");

  // Default initialization.
  {
    constexpr tph::Vec<float, 2> a2_0 = {};
    constexpr tph::Vec<float, 3> a3_0 = {};
    constexpr tph::Vec<float, 4> a4_0 = {};
    static_assert(a2_0.x == 0.0F && a2_0.y == 0.0F, "");
    static_assert(a3_0.x == 0.0F && a3_0.y == 0.0F && a3_0.z == 0.0F, "");
    static_assert(a4_0.x == 0.0F && a4_0.y == 0.0F && a4_0.z == 0.0F && a4_0.w == 0.0F, "");
  }

  constexpr tph::Vec<float, 2> b2{3.0F, 4.0F};
  constexpr tph::Vec<float, 3> b3{4.0F, 5.0F, 6.0F};
  constexpr tph::Vec<float, 4> b4{5.0F, 6.0F, 7.0F, 8.0F};

  // operator==(a, b)
  static_assert(a2 == a2 && !(a2 == b2), "");
  static_assert(a3 == a3 && !(a3 == b3), "");
  static_assert(a4 == a4 && !(a4 == b4), "");

  // operator!=(a, b)
  static_assert(a2 != b2 && !(a2 != a2), "");
  static_assert(a3 != b3 && !(a3 != a3), "");
  static_assert(a4 != b4 && !(a4 != a4), "");

  // operator*(vec, scalar)
  static_assert(a2 * 2 == tph::Vec<float, 2>{2, 4}, "");
  static_assert(a3 * 2 == tph::Vec<float, 3>{2, 4, 6}, "");
  static_assert(a4 * 2 == tph::Vec<float, 4>{2, 4, 6, 8}, "");

  // operator+(a, b)
  static_assert(a2 + b2 == tph::Vec<float, 2>{4, 6}, "");
  static_assert(a3 + b3 == tph::Vec<float, 3>{5, 7, 9}, "");
  static_assert(a4 + b4 == tph::Vec<float, 4>{6, 8, 10, 12}, "");

  // operator-(a, b)
  static_assert(a2 - b2 == tph::Vec<float, 2>{-2, -2}, "");
  static_assert(a3 - b3 == tph::Vec<float, 3>{-3, -3, -3}, "");
  static_assert(a4 - b4 == tph::Vec<float, 4>{-4, -4, -4, -4}, "");

  // operator*=(vec, scalar)
#if HAS_CPP17
  static_assert(
      []() constexpr {
        auto a = tph::Vec<float, 2>{1, 2};
        a *= 2;
        return a;
      }() == tph::Vec<float, 2>{2, 4},
      "");
  static_assert(
      []() constexpr {
        auto a = tph::Vec<float, 3>{1, 2, 3};
        a *= 2;
        return a;
      }() == tph::Vec<float, 3>{2, 4, 6},
      "");
  static_assert(
      []() constexpr {
        auto a = tph::Vec<float, 4>{1, 2, 3, 4};
        a *= 2;
        return a;
      }() == tph::Vec<float, 4>{2, 4, 6, 8},
      "");
#endif

  return 0;
}
