#include "common.h"
#include "gift_wrap.h"
#include "line3.h"
#include "plane3.h"
#include "quad_edge.h"
#include "vec2.h"
#include "vec3.h"
#include "union_find.h"
#include <bits/stdc++.h>
using namespace std;
using int_t = int64_t;

template <typename T>
vector<face_t> weighted_delaunay(const vector<vec2_t<T>> &points, const vector<T> &weights) {
    vector<vec3_t<T>> points_3d(points.size());
    for (int_t i = 0; i < ssize(points); i++) {
        const auto &p2{ points[i] };
        auto &p3{ points_3d[i] };
        p3.x = p2.x;
        p3.y = p2.y;
        p3.z = p2.length_squared() - weights[i] * weights[i];
    }

    const auto hull{ gift_wrap(points_3d) };

    vector<face_t> result;
    for (const auto &face : hull) {
        const auto &p{ points_3d[face.at(0)] };
        const auto &q{ points_3d[face.at(1)] };
        const auto &r{ points_3d[face.at(2)] };
        if (plane3_t<T>{ p, q, r }.normal.z < -EPS<T>) {
            result.emplace_back(face);
        }
    }
    return result;
}

map<edge_t, size_t> get_edge_face_mapping(const std::vector<face_t> &faces) {
    map<edge_t, size_t> edge_to_face;
    for (int_t f = 0; f < ssize(faces); f++) {
        const auto &face{ faces[f] };
        for (int_t i = 0; i < ssize(face); ++i) {
            const int_t j{ (i + 1) % ssize(face) };
            const auto a{ face[i] };
            const auto b{ face[j] };
            edge_to_face.try_emplace(edge_t{ a, b }, f);
        }
    }

    const int_t outer_face{ ssize(faces) };
    for (const auto &face : faces) {
        for (int_t i = 0; i < ssize(face); ++i) {
            const int_t j{ (i + 1) % ssize(face) };
            const auto a{ face[i] };
            const auto b{ face[j] };
            if (!edge_to_face.contains({ b, a })) {
                edge_to_face.try_emplace(edge_t{ b, a }, outer_face);
            }
        }
    }
    return edge_to_face;
}

template <typename T>
bool is_point_strictly_in_polygon(const vector<vec2_t<T>> &poly, const vec2_t<T> q) {
    auto check = [](const vec2_t<T> a, const vec2_t<T> b, const vec2_t<T> c) { return a.x < b.x && b.x <= c.x && a.ccw(c, b) < 0; };
    const auto n{ ssize(poly) };
    bool in{ false };
    for (int i = 0, j = n - 1; i < n; j = i++) {
        const double d{ q.progress(poly[i], poly[j]) };
        if (poly[i].collinear(q, poly[j]) && 0 <= d && d <= 1) {
            return false;
        }
    }
    for (size_t i = 0, j = n - 1; i < n; j = i++) {
        if (check(poly[i], q, poly[j]) || check(poly[j], q, poly[i])) {
            in = !in;
        }
    }
    return in;
}

template <typename T>
size_t get_face(const vector<face_t> &faces, const vector<vec2_t<T>> &points, const vec2_t<T> needle) {
    for (int_t f = 0; f < ssize(faces); f++) {
        const auto &face{ faces[f] };
        vector<vec2_t<T>> poly;
        poly.reserve(size(face));
        for (auto i : face) {
            poly.push_back(points[i]);
        }
        if (is_point_strictly_in_polygon(poly, needle)) {
            return f;
        }
    }
    return ssize(faces);
}

bool reachable_with_updates(int_t n, int_t h, const vec2_t<> start, const vec2_t<> goal, const vector<vec2_t<>> &points,
                            const vector<pair<int_t, int_t>> &camera_updates, int_t update_count) {
    auto scaled_radius_squared = [h](double r) { return r * r - h * h; };
    auto cameras_intersect = [h, scaled_radius_squared](vec2_t<> p1, int_t r1, vec2_t<> p2, int_t r2)
    {
        // r'_1 + r'_2 > sqrt(x^2 + y^2)
        // (r'_1 + r'_2)^2 > x^2 + y^2
        // r'_1^2 + r'_2^2 + 2*r'_1*r'_2 > x^2 + y^2
        // 2*r'_1*r'_2 > x^2 + y^2 - r'_1^2 - r'_2^2
        // right hand side must is negative or
        // 4*r'_1^2*r'_2^2 > (x^2 + y^2 - r'_1^2 - r'_2^2)^2
        if (r1 <= h || r2 <= h) {
            return false;
        }
        const auto d_squared{ (p1 - p2).length_squared() };
        const auto r_prime_1_squared{ scaled_radius_squared(r1) };
        const auto r_prime_2_squared{ scaled_radius_squared(r2) };
        const auto rhs{ d_squared - r_prime_1_squared - r_prime_2_squared };
        return rhs < 0 || 4 * r_prime_1_squared * r_prime_2_squared > rhs * rhs;
    };

    vector<double> weights(n, 0.0);
    for (const auto &[j, r] : span{camera_updates}.subspan(0, update_count)) {
        weights[j] = max(weights[j], static_cast<double>(r));
        const auto r_prime_squared{ scaled_radius_squared(weights[j]) };
        if (points[j].distance_squared(start) < r_prime_squared || points[j].distance_squared(goal) < r_prime_squared) {
            return false;
        }
    }

    const auto faces{ weighted_delaunay(points, weights) };
    const auto edge_to_face{ get_edge_face_mapping(faces) };

    union_find uf(ssize(faces) + 1);
    for (const auto &face : faces) {
        for (int_t i = 0; i < ssize(face); ++i) {
            const int_t j{ (i + 1) % ssize(face) };
            const auto a{ face[i] };
            const auto b{ face[j] };
            if (!cameras_intersect(points[a], weights[a], points[b], weights[b])) {
                uf.unite(edge_to_face.at({ a, b }), edge_to_face.at({ b, a }));
            }
        }
    }

    const auto start_face{ get_face(faces, points, start) };
    const auto goal_face{ get_face(faces, points, goal) };
    return uf.united(start_face, goal_face);
}

int main() {
    cin.sync_with_stdio(false);
    int_t n, h;
    cin >> n >> h;
    vec2_t<> start, goal;
    cin >> start.x >> start.y;
    cin >> goal.x >> goal.y;
    vector<vec2_t<>> points;
    points.reserve(n);
    points.resize(n);
    for (auto &[x, y] : points) {
        cin >> x >> y;
    }

    int_t m;
    cin >> m;
    vector<pair<int_t, int_t>> camera_updates(m);
    for (auto &[j, r] : camera_updates) {
        cin >> j >> r;
        j--;
    }

    int_t lo = 0, hi = m;
    int_t best = -1;
    while (lo <= hi) {
        const auto mid{ midpoint(lo, hi) };
        if (reachable_with_updates(n, h, start, goal, points, camera_updates, mid)) {
            lo = mid + 1;
        }
        else {
            hi = mid - 1;
            best = mid;
        }
    }

    cout << best << endl;

    return 0;
}
