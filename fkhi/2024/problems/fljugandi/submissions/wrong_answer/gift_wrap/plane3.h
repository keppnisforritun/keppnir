#pragma once

#include "common.h"
#include "line3.h"
#include "vec3.h"

template <typename scalar_t>
struct plane3_t {
    using vec_t = vec3_t<scalar_t>;
    using line_t = line3_t<scalar_t>;
    using plane_t = plane3_t<scalar_t>;
    vec_t origin, normal;
    plane3_t(const vec_t a, const vec_t b, const vec_t c) : origin(a), normal(((b - a) * (c - a)).normalize()) {
    }

    constexpr bool contains(const vec_t point) const {
        return std::abs((point - origin) % normal) <= EPS<scalar_t>;
    }

    struct line_intersect_t {
        intersection_t hits;
        vec_t point;
    };

    constexpr line_intersect_t intersect(const line_t line) {
        if (line.direction() % normal <= EPS<scalar_t>) {
            if ((origin - line.p) % normal <= EPS<scalar_t>) {
                return { intersection_t::infinite, {} };
            }
            return { intersection_t::none, {} };
        }
        const auto d{ ((origin - line.p) % normal) / (line.direction().normalize() % normal) };
        return { intersection_t::one, line.p + line.direction().normalize() * d };
    }

    struct plane_intersect_t {
        intersection_t hits;
        line_t line;
    };

    constexpr plane_intersect_t intersect(const plane_t plane) {
        const vec_t n{ normal * plane.normal };
        if (n.is_zero()) {
            return { intersection_t::none, {} };
        }
        const vec3_t v{ n * normal };
        const auto p{ origin + (n * normal) * ((plane.origin - origin) % plane.normal / (v % plane.normal)) };
        const auto q{ p + n };
        return { intersection_t::one, { p, q } };
    }
};
