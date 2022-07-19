// Copyright (C) Tommy Hinks <tommy.hinks@gmail.com>
// This file is subject to the license terms in the LICENSE file
// found in the top-level directory of this distribution.

#include <type_traits>

#include <tph/tph_linalg.hpp>

int main(int argc, char* argv[]) {
  static_assert(sizeof(tph::Vec2<float>) == 2 * sizeof(float));
  

  constexpr tph::Vec3<float> a{1.0F, 2.0F, 3.0F};
  constexpr tph::Vec3<float> b{4.0F, 5.0F, 6.0F};

  static_assert((a - b) == tph::Vec3<float>{1.0F - 4.0F, 2.0F - 5.0F, 3.0F - 6.0F});

  return 0;
}