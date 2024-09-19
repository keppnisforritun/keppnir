#pragma once

template <typename scalar_t>
constexpr scalar_t EPS = scalar_t(5e-6L);

enum class intersection_t { none, one, infinite };
