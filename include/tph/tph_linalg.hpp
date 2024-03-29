#pragma once

#if __cplusplus >= 201703L // C++17 or later.
#define TPH_NODISCARD [[nodiscard]]
#else
#define TPH_NODISCARD
#endif

namespace tph {

// Small, fixed-length vector type, consisting of exactly M elements of type T, and presumed to be a
// column-vector unless otherwise noted.
template <typename ArithT, int M>
struct Vec;

template <typename ArithT>
struct Vec<ArithT, 2> {
  ArithT x;
  ArithT y;
};

template <typename ArithT>
struct Vec<ArithT, 3> {
  ArithT x;
  ArithT y;
  ArithT z;
};

template <typename ArithT>
struct Vec<ArithT, 4> {
  ArithT x;
  ArithT y;
  ArithT z;
  ArithT w;
};

// Convenient type aliases.
using float2 = Vec<float, 2>;
using float3 = Vec<float, 3>;
using float4 = Vec<float, 4>;
using double2 = Vec<double, 2>;
using double3 = Vec<double, 3>;
using double4 = Vec<double, 4>;

namespace tph_linalg_internal {
template <class T>
struct dependent_false {
  static constexpr bool value = false;
};
} // namespace tph_linalg_internal

template <typename ArithT, int M>
TPH_NODISCARD constexpr auto Comp(const Vec<ArithT, M>& a, const int i) noexcept -> decltype(a.x) {
  if constexpr (M == 2) {
    return i == 0 ? a.x : a.y;
  } else if constexpr (M == 3) {
    return i == 0 ? a.x : i == 1 ? a.y : a.z;
  } else if constexpr (M == 4) {
    return i == 0 ? a.x : i == 1 ? a.y : i == 2 ? a.z : a.w;
  } else {
    static_assert(tph_linalg_internal::dependent_false<ArithT>::value, "");
  }
}

// operator==(a, b)
template <typename ArithT, typename ArithT2>
TPH_NODISCARD constexpr auto operator==(const Vec<ArithT, 2>& a, const Vec<ArithT2, 2>& b) noexcept
    -> bool {
  return a.x == b.x && a.y == b.y;
}

template <typename ArithT, typename ArithT2>
TPH_NODISCARD constexpr auto operator==(const Vec<ArithT, 3>& a, const Vec<ArithT2, 3>& b) noexcept
    -> bool {
  return a.x == b.x && a.y == b.y && a.z == b.z;
}

template <typename ArithT, typename ArithT2>
TPH_NODISCARD constexpr auto operator==(const Vec<ArithT, 4>& a, const Vec<ArithT2, 4>& b) noexcept
    -> bool {
  return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
}

// operator!=(a, b)
template <typename ArithT, typename ArithT2>
TPH_NODISCARD constexpr auto operator!=(const Vec<ArithT, 2>& a, const Vec<ArithT2, 2>& b) -> bool {
  return !(a == b);
}

template <typename ArithT, typename ArithT2>
TPH_NODISCARD constexpr auto operator!=(const Vec<ArithT, 3>& a, const Vec<ArithT2, 3>& b) -> bool {
  return !(a == b);
}

template <typename ArithT, typename ArithT2>
TPH_NODISCARD constexpr auto operator!=(const Vec<ArithT, 4>& a, const Vec<ArithT2, 4>& b) -> bool {
  return !(a == b);
}

// operator*(vec, scalar)
// Treat vectors as column vectors (Mx1 matrices).
template <typename ArithT, typename ArithT2>
TPH_NODISCARD constexpr auto operator*(const Vec<ArithT, 2>& a, const ArithT2 b) noexcept
    -> Vec<decltype(a.x * b), 2> {
  return {a.x * b, a.y * b};
}

template <typename ArithT, typename ArithT2>
TPH_NODISCARD constexpr auto operator*(const Vec<ArithT, 3>& a, const ArithT2 b) noexcept
    -> Vec<decltype(a.x * b), 3> {
  return {a.x * b, a.y * b, a.z * b};
}

template <typename ArithT, typename ArithT2>
TPH_NODISCARD constexpr auto operator*(const Vec<ArithT, 4>& a, const ArithT2 b) noexcept
    -> Vec<decltype(a.x * b), 4> {
  return {a.x * b, a.y * b, a.z * b, a.w * b};
}

// operator+(a, b)
template <typename ArithT, typename ArithT2>
TPH_NODISCARD constexpr auto operator+(const Vec<ArithT, 2>& a, const Vec<ArithT2, 2>& b) noexcept
    -> Vec<decltype(a.x + b.x), 2> {
  return {a.x + b.x, a.y + b.y};
}

template <typename ArithT, typename ArithT2>
TPH_NODISCARD constexpr auto operator+(const Vec<ArithT, 3>& a, const Vec<ArithT2, 3>& b) noexcept
    -> Vec<decltype(a.x + b.x), 3> {
  return {a.x + b.x, a.y + b.y, a.z + b.z};
}

template <typename ArithT, typename ArithT2>
TPH_NODISCARD constexpr auto operator+(const Vec<ArithT, 4>& a, const Vec<ArithT2, 4>& b) noexcept
    -> Vec<decltype(a.x + b.x), 4> {
  return {a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
}

// operator-(a, b)
template <typename ArithT, typename ArithT2>
TPH_NODISCARD constexpr auto operator-(const Vec<ArithT, 2>& a, const Vec<ArithT2, 2>& b) noexcept
    -> Vec<decltype(a.x - b.x), 2> {
  return {a.x - b.x, a.y - b.y};
}

template <typename ArithT, typename ArithT2>
TPH_NODISCARD constexpr auto operator-(const Vec<ArithT, 3>& a, const Vec<ArithT2, 3>& b) noexcept
    -> Vec<decltype(a.x - b.x), 3> {
  return {a.x - b.x, a.y - b.y, a.z - b.z};
}

template <typename ArithT, typename ArithT2>
TPH_NODISCARD constexpr auto operator-(const Vec<ArithT, 4>& a, const Vec<ArithT2, 4>& b) noexcept
    -> Vec<decltype(a.x + b.x), 4> {
  return {a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
}

// operator-(a), unary negation.
template <typename ArithT>
TPH_NODISCARD constexpr auto operator-(const Vec<ArithT, 2>& a) noexcept -> Vec<decltype(-a.x), 2> {
  return {-a.x, -a.y};
}

template <typename ArithT>
TPH_NODISCARD constexpr auto operator-(const Vec<ArithT, 3>& a) noexcept -> Vec<decltype(-a.x), 3> {
  return {-a.x, -a.y, -a.z};
}

template <typename ArithT>
TPH_NODISCARD constexpr auto operator-(const Vec<ArithT, 4>& a) noexcept -> Vec<decltype(-a.x), 4> {
  return {-a.x, -a.y, -a.z, -a.w};
}

// operator*=(vec, scalar)
template <typename ArithT, typename ArithT2>
// TPH_NODISCARD
constexpr auto operator*=(Vec<ArithT, 2>& a, const ArithT2 b) noexcept -> decltype(a = a * b) {
  return a = a * b;
}

template <typename ArithT, typename ArithT2>
// TPH_NODISCARD
constexpr auto operator*=(Vec<ArithT, 3>& a, const ArithT2 b) noexcept -> decltype(a = a * b) {
  return a = a * b;
}

template <typename ArithT, typename ArithT2>
// TPH_NODISCARD
constexpr auto operator*=(Vec<ArithT, 4>& a, const ArithT2 b) noexcept -> decltype(a = a * b) {
  return a = a * b;
}

// operator+=(a, b)
template <typename ArithT, typename ArithT2>
// TPH_NODISCARD
constexpr auto operator+=(Vec<ArithT, 2>& a, const Vec<ArithT2, 2>& b) noexcept
    -> decltype(a = a + b) {
  return a = a + b;
}

template <typename ArithT, typename ArithT2>
// TPH_NODISCARD
constexpr auto operator+=(Vec<ArithT, 3>& a, const Vec<ArithT2, 3>& b) noexcept
    -> decltype(a = a + b) {
  return a = a + b;
}

template <typename ArithT, typename ArithT2>
// TPH_NODISCARD
constexpr auto operator+=(Vec<ArithT, 4>& a, const Vec<ArithT2, 4>& b) noexcept
    -> decltype(a = a + b) {
  return a = a + b;
}

// operator-=(a, b)
template <typename ArithT, typename ArithT2>
// TPH_NODISCARD
constexpr auto operator-=(Vec<ArithT, 2>& a, const Vec<ArithT2, 2>& b) noexcept
    -> decltype(a = a - b) {
  return a = a - b;
}

template <typename ArithT, typename ArithT2>
// TPH_NODISCARD
constexpr auto operator-=(Vec<ArithT, 3>& a, const Vec<ArithT2, 3>& b) noexcept
    -> decltype(a = a - b) {
  return a = a - b;
}

template <typename ArithT, typename ArithT2>
// TPH_NODISCARD
constexpr auto operator-=(Vec<ArithT, 4>& a, const Vec<ArithT2, 4>& b) noexcept
    -> decltype(a = a - b) {
  return a = a - b;
}

namespace tph_linalg_internal {

template <typename FloatT>
struct numeric_limits;

template <>
struct numeric_limits<float> {
  TPH_NODISCARD static constexpr auto infinity() noexcept -> float { return __builtin_huge_valf(); }
  TPH_NODISCARD static constexpr auto min() noexcept -> float { return 1.17549435e-38F; }
  TPH_NODISCARD static constexpr auto quiet_NaN() noexcept -> float { return __builtin_nanf(""); }
};

template <>
struct numeric_limits<double> {
  TPH_NODISCARD static constexpr auto infinity() noexcept -> double { return __builtin_huge_val(); }
  TPH_NODISCARD static constexpr auto min() noexcept -> double { return 2.2250738585072016e-308; }
  TPH_NODISCARD static constexpr auto quiet_NaN() noexcept -> double { return __builtin_nan(""); }
};

// From: https://github.com/kthohr/gcem/blob/master/include/gcem_incl/is_nan.hpp
template <typename FloatT>
TPH_NODISCARD constexpr auto is_nan(const FloatT x) noexcept -> bool {
  return x != x;
}

// From: https://github.com/kthohr/gcem/blob/master/include/gcem_incl/is_inf.hpp
template <typename FloatT>
TPH_NODISCARD constexpr auto is_posinf(const FloatT x) noexcept -> bool {
  return x == numeric_limits<FloatT>::infinity();
}

// From: https://github.com/kthohr/gcem/blob/master/include/gcem_incl/abs.hpp
template <typename ArithT>
TPH_NODISCARD constexpr auto abs(const ArithT x) noexcept -> ArithT {
  return ( // deal with signed-zeros
      x == ArithT(0) ? ArithT(0) :
                     // else
          x < ArithT(0) ? -x
                        : x);
}

// From: https://github.com/kthohr/gcem/blob/master/include/gcem_incl/sqrt.hpp
template <typename FloatT>
TPH_NODISCARD constexpr auto SqrtRecur(const FloatT x, const FloatT xn, const int count) noexcept
    -> FloatT {
  // Max iter from https://github.com/kthohr/gcem/blob/master/include/gcem_incl/gcem_options.hpp,
  // GCEM_SQRT_MAX_ITER.

  return (abs(xn - x / xn) / (FloatT(1) + xn) < numeric_limits<FloatT>::min()
              ? // if
              xn
              : count < 100 // max iter
                    ?       // else
                    SqrtRecur(x, FloatT(0.5) * (xn + x / xn), count + 1)
                    : xn);
}

// From: https://github.com/kthohr/gcem/blob/master/include/gcem_incl/sqrt.hpp
template <typename FloatT>
TPH_NODISCARD constexpr auto SqrtCheck(const FloatT x, const FloatT m_val) noexcept -> FloatT {
  return (is_nan(x) ? numeric_limits<FloatT>::quiet_NaN() :
                    //
              x < FloatT(0) ? numeric_limits<FloatT>::quiet_NaN()
                            :
                            //
              is_posinf(x) ? x
                           :
                           // indistinguishable from zero or one
              numeric_limits<FloatT>::min() > abs(x)           ? FloatT(0)
          : numeric_limits<FloatT>::min() > abs(FloatT(1) - x) ? x
                                                               :
                                                               // else
              x > FloatT(4) ? SqrtCheck(x / FloatT(4), FloatT(2) * m_val)
                            : m_val * SqrtRecur(x, x / FloatT(2), 0));
}

// Computes sqrt(x) using a Newton-Raphson approach.
template <typename FloatT>
TPH_NODISCARD constexpr auto sqrt(const FloatT x) noexcept -> FloatT {
  return SqrtCheck(x, FloatT(1));
}

} // namespace tph_linalg_internal

// Cross product.
template <typename ArithT, typename ArithT2>
TPH_NODISCARD constexpr auto Cross(const Vec<ArithT, 2>& a, const Vec<ArithT2, 2>& b) noexcept
    -> decltype(a.x * b.y - a.y * b.x) {
  return a.x * b.y - a.y * b.x;
}

template <typename ArithT, typename ArithT2>
TPH_NODISCARD constexpr auto Cross(const Vec<ArithT, 3>& a, const Vec<ArithT2, 3>& b) noexcept
    -> Vec<decltype(a.y * b.z - a.z * b.y), 3> {
  return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}

// Dot product.
template <typename ArithT, typename ArithT2>
TPH_NODISCARD constexpr auto Dot(const Vec<ArithT, 2>& a, const Vec<ArithT2, 2>& b)
    -> decltype(a.x * b.x + a.y * b.y) {
  return a.x * b.x + a.y * b.y;
}

template <typename ArithT, typename ArithT2>
TPH_NODISCARD constexpr auto Dot(const Vec<ArithT, 3>& a, const Vec<ArithT2, 3>& b)
    -> decltype(a.x * b.x + a.y * b.y + a.z * b.z) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

template <typename ArithT, typename ArithT2>
TPH_NODISCARD constexpr auto Dot(const Vec<ArithT, 4>& a, const Vec<ArithT2, 4>& b)
    -> decltype(a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w) {
  return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

// Length squared.
template <typename ArithT, int M>
TPH_NODISCARD constexpr auto Length2(const Vec<ArithT, M>& a) noexcept -> decltype(Dot(a, a)) {
  return Dot(a, a);
}

// Length/magnitude.
template <typename FloatT, int M>
TPH_NODISCARD constexpr auto Length(const Vec<FloatT, M>& a) noexcept
    -> decltype(tph_linalg_internal::sqrt(Length2(a))) {
  return tph_linalg_internal::sqrt(Length2(a));
}

// Distance squared.
template <typename ArithT, typename ArithT2, int M>
TPH_NODISCARD constexpr auto Distance2(const Vec<ArithT, M>& a, const Vec<ArithT2, M>& b) noexcept
    -> decltype(Length2(b - a)) {
  return Length2(b - a);
}

// Distance.
template <typename FloatT, typename FloatT2, int M>
TPH_NODISCARD constexpr auto Distance(const Vec<FloatT, M>& a, const Vec<FloatT2, M>& b) noexcept
    -> decltype(Length(b - a)) {
  return Length(b - a);
}

// Normalized.
template <typename FloatT, int M>
TPH_NODISCARD constexpr auto Normalized(const Vec<FloatT, M>& a) noexcept
    -> Vec<decltype(a.x * (FloatT(1) / Length(a))), M> {
  return a * (FloatT(1) / Length(a));
}

// Small, fixed-size matrix type, consisting of exactly M rows and N columns of type T, stored in
// column-major order.
template <typename ArithT, int M, int N>
struct Mat;

template <typename ArithT, int M>
struct Mat<ArithT, M, 2> {
  Vec<ArithT, M> x; // Column 0.
  Vec<ArithT, M> y; // Column 1.
};

template <typename ArithT, int M>
struct Mat<ArithT, M, 3> {
  Vec<ArithT, M> x; // Column 0.
  Vec<ArithT, M> y; // Column 1.
  Vec<ArithT, M> z; // Column 2.
};

template <typename ArithT, int M>
struct Mat<ArithT, M, 4> {
  Vec<ArithT, M> x; // Column 0.
  Vec<ArithT, M> y; // Column 1.
  Vec<ArithT, M> z; // Column 2.
  Vec<ArithT, M> w; // Column 3.
};

// Convenient type aliases.
using float2x2 = Mat<float, 2, 2>;
using float2x3 = Mat<float, 2, 3>;
using float3x3 = Mat<float, 3, 3>;
using float2x4 = Mat<float, 2, 4>;
using float3x4 = Mat<float, 3, 4>;
using float4x4 = Mat<float, 4, 4>;
using double2x2 = Mat<double, 2, 2>;
using double2x3 = Mat<double, 2, 3>;
using double3x3 = Mat<double, 3, 3>;
using double2x4 = Mat<double, 2, 4>;
using double3x4 = Mat<double, 3, 4>;
using double4x4 = Mat<double, 4, 4>;

// Construct the matrix:
//
//   a b
//   c d
//
// clang-format off
template <typename ArithT>
TPH_NODISCARD constexpr auto
MakeMat2x2(const ArithT a, const ArithT b, 
           const ArithT c, const ArithT d) noexcept
    -> Mat<ArithT, 2, 2> {
  return {
    {a, c}, // Column 0. 
    {b, d}  // Column 1.
  };
}
// clang-format on

// Construct the matrix:
//
//   a b c
//   d e f
//   g h i
//
// clang-format off
template <typename ArithT>
TPH_NODISCARD constexpr auto
MakeMat3x3(const ArithT a, const ArithT b, const ArithT c, 
           const ArithT d, const ArithT e, const ArithT f,
           const ArithT g, const ArithT h, const ArithT i) noexcept
    -> Mat<ArithT, 3, 3> {
  return {
    {a, d, g}, // Column 0. 
    {b, e, h}, // Column 1.
    {c, f, i}  // Column 2.
  };
}
// clang-format on

// Construct the matrix:
//
//   a b c d
//   e f g h
//   i j k l
//   m n o p
//
// clang-format off
template <typename ArithT>
TPH_NODISCARD constexpr auto
MakeMat4x4(const ArithT a, const ArithT b, const ArithT c, const ArithT d, 
           const ArithT e, const ArithT f, const ArithT g, const ArithT h,
           const ArithT i, const ArithT j, const ArithT k, const ArithT l,
           const ArithT m, const ArithT n, const ArithT o, const ArithT p) 
    noexcept -> Mat<ArithT, 4, 4> {
  return {
    {a, e, i, m}, // Column 0. 
    {b, f, j, n}, // Column 1.
    {c, g, k, o}, // Column 2.
    {d, h, l, p}  // Column 3.
  };
}
// clang-format on

// Return a row from a matrix.
template <typename ArithT, int M, int N>
TPH_NODISCARD constexpr auto Row(const Mat<ArithT, M, N>& a, const int i) noexcept
    -> Vec<ArithT, N> {
  if constexpr (N == 2) {
    return {Comp(a.x, i), Comp(a.y, i)};
  }
  else if constexpr (N == 3) {
    return {Comp(a.x, i), Comp(a.y, i), Comp(a.z, i)};
  }
  else if constexpr (N == 4) {
    return {Comp(a.x, i), Comp(a.y, i), Comp(a.z, i), Comp(a.w, i)};
  }
  else {
    static_assert(tph_linalg_internal::dependent_false<ArithT>::value, "");
  }
}

// Identity.
template <typename ArithT>
TPH_NODISCARD constexpr auto Identity2x2() noexcept -> Mat<ArithT, 2, 2> {
  // clang-format off
  return {
    {ArithT{1}, ArithT{0}}, 
    {ArithT{0}, ArithT{1}}
  };
  // clang-format on
}

template <typename ArithT>
TPH_NODISCARD constexpr auto Identity3x3() noexcept -> Mat<ArithT, 3, 3> {
  // clang-format off
  return {
    {ArithT{1}, ArithT{0}, ArithT{0}}, 
    {ArithT{0}, ArithT{1}, ArithT{0}},
    {ArithT{0}, ArithT{0}, ArithT{1}}
  };
  // clang-format on
}

template <typename ArithT>
TPH_NODISCARD constexpr auto Identity4x4() noexcept -> Mat<ArithT, 4, 4> {
  // clang-format off
  return {
    {ArithT{1}, ArithT{0}, ArithT{0}, ArithT{0}}, 
    {ArithT{0}, ArithT{1}, ArithT{0}, ArithT{0}},
    {ArithT{0}, ArithT{0}, ArithT{1}, ArithT{0}},
    {ArithT{0}, ArithT{0}, ArithT{0}, ArithT{1}}
  };
  // clang-format on
}

// Matrix/vector multiplication.
template <typename ArithT, int M>
constexpr auto Mul(const Mat<ArithT, M, 2>& a, const Vec<ArithT, 2>& b) noexcept -> Vec<ArithT, M> {
  return a.x * b.x + a.y * b.y;
}

template <typename ArithT, int M>
constexpr auto Mul(const Mat<ArithT, M, 3>& a, const Vec<ArithT, 3>& b) noexcept -> Vec<ArithT, M> {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

template <typename ArithT, int M>
constexpr auto Mul(const Mat<ArithT, M, 4>& a, const Vec<ArithT, 4>& b) noexcept -> Vec<ArithT, M> {
  return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

// template <typename ArithT, int M, int N>
// constexpr auto Mul(const Mat<ArithT, M, N>& a, const Mat<ArithT, N, 1>& b) noexcept
//     -> Mat<ArithT, M, 1> {
//   return {Mul(a, b.x)};
// }

template <typename ArithT, int M, int N>
constexpr auto Mul(const Mat<ArithT, M, N>& a, const Mat<ArithT, N, 2>& b) noexcept
    -> Mat<ArithT, M, 2> {
  return {Mul(a, b.x), Mul(a, b.y)};
}

template <typename ArithT, int M, int N>
constexpr auto mul(const Mat<ArithT, M, N>& a, const Mat<ArithT, N, 3>& b) noexcept
    -> Mat<ArithT, M, 3> {
  return {Mul(a, b.x), Mul(a, b.y), Mul(a, b.z)};
}

template <typename ArithT, int M, int N>
constexpr auto Mul(const Mat<ArithT, M, N>& a, const Mat<ArithT, N, 4>& b) noexcept
    -> Mat<ArithT, M, 4> {
  return {mul(a, b.x), mul(a, b.y), mul(a, b.z), mul(a, b.w)};
}

} // namespace tph

#undef TPH_NODISCARD
