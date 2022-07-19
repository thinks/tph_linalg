#pragma once

#if __cplusplus >= 201703L
#define TPH_NODISCARD [[nodiscard]]
#else
#define TPH_NODISCARD 
#endif 

namespace tph {
template <typename ArithT>
struct Vec2 {
  ArithT x;
  ArithT y;
};
using float2 = Vec2<float>;
using double2 = Vec2<double>;

template <typename ArithT>
struct Vec3 {
  ArithT x;
  ArithT y;
  ArithT z;
};
using float3 = Vec3<float>;
using double3 = Vec3<double>;

template <typename ArithT>
struct Vec4 {
  ArithT x;
  ArithT y;
  ArithT z;
  ArithT w;
};
using float4 = Vec4<float>;
using double4 = Vec4<double>;

// operator==(a, b)
template <typename ArithT, typename ArithT2>
TPH_NODISCARD constexpr auto operator==(const Vec2<ArithT>& a, const Vec2<ArithT2>& b) noexcept
    -> bool {
  return a.x == b.x && a.y == b.y;
}

template <typename ArithT, typename ArithT2>
TPH_NODISCARD constexpr auto operator==(const Vec3<ArithT>& a, const Vec3<ArithT2>& b) noexcept
    -> bool {
  return a.x == b.x && a.y == b.y && a.z == b.z;
}

template <typename ArithT, typename ArithT2>
TPH_NODISCARD constexpr auto operator==(const Vec4<ArithT>& a, const Vec4<ArithT2>& b) noexcept
    -> bool {
  return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
}

// operator!=(a, b)
template <typename ArithT, typename ArithT2>
TPH_NODISCARD constexpr auto operator!=(const Vec2<ArithT>& a, const Vec2<ArithT2>& b) -> bool {
  return !(a == b);
}

template <typename ArithT, typename ArithT2>
TPH_NODISCARD constexpr auto operator!=(const Vec3<ArithT>& a, const Vec3<ArithT2>& b) -> bool {
  return !(a == b);
}

template <typename ArithT, typename ArithT2>
TPH_NODISCARD constexpr auto operator!=(const Vec4<ArithT>& a, const Vec4<ArithT2>& b) -> bool {
  return !(a == b);
}

// operator+(a, b)
template <typename ArithT, typename ArithT2>
TPH_NODISCARD constexpr auto operator+(const Vec2<ArithT>& a, const Vec2<ArithT2>& b) noexcept
    -> Vec2<decltype(a.x + b.x)> {
  return {a.x + b.x, a.y + b.y};
}

template <typename ArithT, typename ArithT2>
TPH_NODISCARD constexpr auto operator+(const Vec3<ArithT>& a, const Vec3<ArithT2>& b) noexcept
    -> Vec3<decltype(a.x + b.x)> {
  return {a.x + b.x, a.y + b.y, a.z + b.z};
}

template <typename ArithT, typename ArithT2>
TPH_NODISCARD constexpr auto operator+(const Vec4<ArithT>& a, const Vec4<ArithT2>& b) noexcept
    -> Vec4<decltype(a.x + b.x)> {
  return {a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
}

// operator-(a, b)
template <typename ArithT, typename ArithT2>
TPH_NODISCARD constexpr auto operator-(const Vec2<ArithT>& a, const Vec2<ArithT2>& b) noexcept
    -> Vec2<decltype(a.x - b.x)> {
  return {a.x - b.x, a.y - b.y};
}

template <typename ArithT, typename ArithT2>
TPH_NODISCARD constexpr auto operator-(const Vec3<ArithT>& a, const Vec3<ArithT2>& b) noexcept
    -> Vec3<decltype(a.x - b.x)> {
  return {a.x - b.x, a.y - b.y, a.z - b.z};
}

template <typename ArithT, typename ArithT2>
TPH_NODISCARD constexpr auto operator-(const Vec4<ArithT>& a, const Vec4<ArithT2>& b) noexcept
    -> Vec4<decltype(a.x + b.x)> {
  return {a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
}

// operator+=(a, b)
template <typename ArithT, typename ArithT2>
TPH_NODISCARD constexpr auto operator+=(Vec2<ArithT>& a, const Vec2<ArithT2>& b) noexcept
    -> decltype(a = a + b) {
  return a = a + b;
}

template <typename ArithT, typename ArithT2>
TPH_NODISCARD constexpr auto operator+=(Vec3<ArithT>& a, const Vec3<ArithT2>& b) noexcept
    -> decltype(a = a + b) {
  return a = a + b;
}

template <typename ArithT, typename ArithT2>
TPH_NODISCARD constexpr auto operator+=(Vec4<ArithT>& a, const Vec4<ArithT2>& b) noexcept
    -> decltype(a = a + b) {
  return a = a + b;
}

// operator-=(a, b)
template <typename ArithT, typename ArithT2>
TPH_NODISCARD constexpr auto operator-=(Vec2<ArithT>& a, const Vec2<ArithT2>& b) noexcept
    -> decltype(a = a - b) {
  return a = a - b;
}

template <typename ArithT, typename ArithT2>
TPH_NODISCARD constexpr auto operator-=(Vec3<ArithT>& a, const Vec3<ArithT2>& b) noexcept
    -> decltype(a = a - b) {
  return a = a - b;
}

template <typename ArithT, typename ArithT2>
TPH_NODISCARD constexpr auto operator-=(Vec4<ArithT>& a, const Vec4<ArithT2>& b) noexcept
    -> decltype(a = a - b) {
  return a = a - b;
}

// Cross product.
template <typename ArithT, typename ArithT2>
TPH_NODISCARD constexpr auto Cross(const Vec2<ArithT>& a, const Vec2<ArithT2>& b) noexcept
    -> decltype(a.x * b.y - a.y * b.x) {
  return a.x * b.y - a.y * b.x;
}

template <typename ArithT, typename ArithT2>
TPH_NODISCARD constexpr auto Cross(const Vec3<ArithT>& a, const Vec3<ArithT2>& b) noexcept
    -> Vec3<decltype(a.y * b.z - a.z * b.y)> {
  return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}

#if 0
template <class T>
constexpr vec<T, 2> cross(T a, const vec<T, 2>& b) {
  return {-a * b.y, a * b.x};
}
template <class T>
constexpr vec<T, 2> cross(const vec<T, 2>& a, T b) {
  return {a.y * b, -a.x * b};
}
#endif

} // namespace tph

#undef TPH_NODISCARD
