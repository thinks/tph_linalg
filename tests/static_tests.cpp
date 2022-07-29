// Copyright (C) Tommy Hinks <tommy.hinks@gmail.com>
// This file is subject to the license terms in the LICENSE file
// found in the top-level directory of this distribution.

#include <cmath> // std::sqrt
#include <type_traits>

#include <tph/tph_linalg.hpp>

#define HAS_CPP17 (__cplusplus >= 201703L)
//#define HAS_CPP20 (__cplusplus >= 202002L)

// From: https://github.com/kthohr/gcem/blob/master/include/gcem_incl/abs.hpp
template <typename ArithT>
static constexpr auto ce_abs(const ArithT x) noexcept -> ArithT {
  return ( // deal with signed-zeros
      x == ArithT(0) ? ArithT(0) :
                     // else
          x < ArithT(0) ? -x
                        : x);
}

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

  // operator-(a)
  static_assert(-a2 == tph::Vec<float, 2>{-1.0F, -2.0F}, "");
  static_assert(-a3 == tph::Vec<float, 3>{-1.0F, -2.0F, -3.0F}, "");
  static_assert(-a4 == tph::Vec<float, 4>{-1.0F, -2.0F, -3.0F, -4.0F}, "");

  // Dot product.
  static_assert(tph::Dot(a2, b2) == 11.0F, "");
  static_assert(tph::Dot(a3, b3) == 32.0F, "");
  static_assert(tph::Dot(a4, b4) == 70.0F, "");

  // Length squared.
  static_assert(tph::Length2(a2) == 5.0F, "");
  static_assert(tph::Length2(a3) == 14.0F, "");
  static_assert(tph::Length2(a4) == 30.0F, "");

  // Distance squared.
  static_assert(tph::Distance2(a2, b2) == 8.0F, "");
  static_assert(tph::Distance2(a3, b3) == 27.0F, "");
  static_assert(tph::Distance2(a4, b4) == 64.0F, "");

  // Use pre-computed sqrt-values, issues with clang not supporting
  // constexpr std::sqrt when linking to libstdc++...
  //
  // Also, std::sqrt is only constexpr from C++20 and onward...

  // Length.
  {
    constexpr auto kSqrt5 = 2.236067977F;
    constexpr auto kSqrt14 = 3.7416573867F;
    constexpr auto kSqrt30 = 5.4772255750F;
    static_assert(ce_abs(tph::Length(a2) - kSqrt5) < 1e-6F, "");
    static_assert(ce_abs(tph::Length(a3) - kSqrt14) < 1e-6F, "");
    static_assert(ce_abs(tph::Length(a4) - kSqrt30) < 1e-6F, "");
  }

  // Distance.
  {
    constexpr auto kSqrt8 = 2.8284271247F;
    constexpr auto kSqrt27 = 5.1961524227F;
    constexpr auto kSqrt64 = 8.0F;
    static_assert(ce_abs(tph::Distance(a2, b2) - kSqrt8) < 1e-6F, "");
    static_assert(ce_abs(tph::Distance(a3, b3) - kSqrt27) < 1e-6F, "");
    static_assert(ce_abs(tph::Distance(a4, b4) - kSqrt64) < 1e-6F, "");
  }

  // Normalized.
  {
    static_assert(tph::Normalized(a2) == (a2 * (1.0F / tph::Length(a2))), "");
    static_assert(tph::Normalized(a3) == (a3 * (1.0F / tph::Length(a3))), "");
    static_assert(tph::Normalized(a4) == (a4 * (1.0F / tph::Length(a4))), "");
  }

#if HAS_CPP17 // Need lambdas to be implicitly constexpr.
  // operator*=(vec, scalar)
  static_assert(
      []() {
        auto a = tph::Vec<float, 2>{1, 2};
        a *= 2;
        return a;
      }() == tph::Vec<float, 2>{2, 4},
      "");
  static_assert(
      []() {
        auto a = tph::Vec<float, 3>{1, 2, 3};
        a *= 2;
        return a;
      }() == tph::Vec<float, 3>{2, 4, 6},
      "");
  static_assert(
      []() {
        auto a = tph::Vec<float, 4>{1, 2, 3, 4};
        a *= 2;
        return a;
      }() == tph::Vec<float, 4>{2, 4, 6, 8},
      "");

  // operator+=(vec, vec)
  static_assert(
      []() {
        auto a = tph::Vec<float, 2>{1, 2};
        a += tph::Vec<int, 2>{2, 2};
        return a;
      }() == tph::Vec<float, 2>{3, 4},
      "");
  static_assert(
      []() {
        auto a = tph::Vec<float, 3>{1, 2, 3};
        a += tph::Vec<int, 3>{2, 2, 2};
        return a;
      }() == tph::Vec<float, 3>{3, 4, 5},
      "");
  static_assert(
      []() {
        auto a = tph::Vec<float, 4>{1, 2, 3, 4};
        a += tph::Vec<int, 4>{2, 2, 2, 2};
        return a;
      }() == tph::Vec<float, 4>{3, 4, 5, 6},
      "");

  // operator-=(vec, vec)
  static_assert(
      []() {
        auto a = tph::Vec<float, 2>{1, 2};
        a -= tph::Vec<int, 2>{2, 2};
        return a;
      }() == tph::Vec<float, 2>{-1, 0},
      "");
  static_assert(
      []() {
        auto a = tph::Vec<float, 3>{1, 2, 3};
        a -= tph::Vec<int, 3>{2, 2, 2};
        return a;
      }() == tph::Vec<float, 3>{-1, 0, 1},
      "");
  static_assert(
      []() {
        auto a = tph::Vec<float, 4>{1, 2, 3, 4};
        a -= tph::Vec<int, 4>{2, 2, 2, 2};
        return a;
      }() == tph::Vec<float, 4>{-1, 0, 1, 2},
      "");

#endif // HAS_CPP17

  return 0;
}
