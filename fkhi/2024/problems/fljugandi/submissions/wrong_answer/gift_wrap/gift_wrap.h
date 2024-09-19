#include "common.h"
#include "line3.h"
#include "plane3.h"
#include "vec2.h"
#include "vec3.h"

#include <queue>
#include <set>
#include <utility>
#include <vector>

using edge_t = std::pair<std::size_t, std::size_t>;
using face_t = std::vector<std::size_t>;
using hull_t = std::vector<face_t>;

template <typename T = double_t>
using point2d_t = std::pair<std::size_t, vec2_t<T>>;

template <typename T = double_t>
struct compare_z {
    constexpr bool operator()(const vec3_t<T> a, const vec3_t<T> b) {
        if (std::abs(a.z - b.z) < EPS<T>) {
            if (std::abs(a.x - b.x) < EPS<T>) {
                return a.y < b.y;
            }
            else {
                return a.x < b.x;
            }
        }
        return a.z < b.z;
    }
};

template <typename T = double_t>
struct compare_slope {
    // Compare slopes relative to XY plane, normal = (0,0,1)
    vec3_t<T> origin_point;
    constexpr bool operator()(vec3_t<T> a, vec3_t<T> b) {
        if (a == origin_point) {
            return false;
        }
        if (b == origin_point) {
            return true;
        }
        a = a - origin_point;
        b = b - origin_point;
        const auto a_angle{ atan2(a.z, vec3_t<T>{ a.x, a.y, 0 }.length()) };
        const auto b_angle{ atan2(b.z, vec3_t<T>{ b.x, b.y, 0 }.length()) };
        return a_angle < b_angle;
    }
};

// Gift Wrapping Algorithm (3D Convex Hull)
// Returns a set of vector<int> denoting the indices of the
// points of the triangular faces.
// Time Complexity O(nh)
// - n: number of points
// - h: number of points in the convex hull



template <typename T>
std::vector<point2d_t<T>> jarvis_march(std::vector<point2d_t<T>> points) {
    sort(points.begin(), points.end(), [](const point2d_t<T> &a, const point2d_t<T> &b)
         { return a.second.x != b.second.x ? a.second.x < b.second.x : a.second.y < b.second.y; });
    std::vector<point2d_t<T>> hull;
    for (std::size_t i = 0; i < size(points); i++) {
        auto l{ size(hull) };
        while (l >= 2 && hull[l - 2].second.ccw(hull[l - 1].second, points[i].second) <= 0) {
            hull.pop_back();
            l--;
        }
        hull.push_back(points[i]);
    }
    const auto l{ size(hull) };
    for (std::size_t i = size(points) - 2; ; i--) {
        auto r{ size(hull) };
        while (r - l >= 1 && hull[r - 2].second.ccw(hull[r - 1].second, points[i].second) <= 0) {
            hull.pop_back();
            r--;
        }
        if (i == 0) {
            break;
        }
        hull.push_back(points[i]);
    }
    return hull;
}

template <typename T>
std::size_t innermost(const std::vector<vec3_t<T>>& points, std::size_t u, std::size_t v) {
    // Imagine you are the edge PQ, your feet are at Q and your head is at P.
    // In your vision (180°) there is a leftmost (innermost) and a rightmost (outermost) point.
    // Find either of those (or both), for simplicity we will use one and call it T
    // This mixed product is similar to using the sign of cross product (2D) to find counterclockwise turns
    // using the signed volume of a parallelepiped
    const auto &P{ points[u] }, Q{ points[v] };
    std::size_t w{ 0 };
    while (w == u || w == v) {
        w++;
    }
    for (std::size_t i = 0; i < size(points); i++) {
        if (i == u || i == v) {
            continue;
        }
        const auto &innermost{ points[w] }, candidate{ points[i] };
        if ((Q - P) % ((innermost - P) * (candidate - P)) < 0) {
            w = i;
        }
    }
    return w;
}

template <typename T>
std::vector<point2d_t<T>> get_points_in_plane(const std::vector<vec3_t<T>> &points, plane3_t<T> plane, vec3_t<T> right) {
    const auto forward{ plane.normal.normalize() };
    const auto up{ forward * right };
    std::vector<point2d_t<T>> result;
    for (size_t i = 0; i < size(points); i++) {
        if (plane.contains(points[i])) {
            result.push_back({ i, { right % points[i], up % points[i] } });
        }
    }
    return result;
}

template <typename T>
hull_t gift_wrap(std::vector<vec3_t<T>> points) {
    const auto n{ size(points) };
    hull_t res;
    // Degenerate case
    if (n < 3) {
        return res;
    }

    // First find the lowest point P
    const auto low_i{ distance(cbegin(points), min_element(cbegin(points), cend(points), compare_z<T>{})) };

    // Next we find the point Q, such that the angle of (Q-P)
    // with the XY plane is minimized
    const auto low_j{ distance(cbegin(points), min_element(cbegin(points), cend(points), compare_slope<T>{ points[low_i] })) };

    // The edge from P to Q is guaranteed to be part
    // of the convex hull, the rest of the algorithm
    // functions like a breadth first search over faces.
    std::set<edge_t> vis;
    std::queue<edge_t> q;
    q.push({ low_i, low_j });
    auto add = [&q, &vis](edge_t e)
    {
        if (!vis.contains(e)) {
            q.push(e);
        }
    };
    while (!q.empty()) {
        const edge_t cur{ q.front() };
        const auto &[u, v] = cur;
        const auto &P{ points[u] }, Q{ points[v] };
        q.pop();
        if (vis.contains(cur)) {
            continue;
        }

        const auto w{ innermost(points, u, v) };
        const auto &R{ points[w] };
        const plane3_t<T> plane{ P, Q, R };
        assert(plane.contains(P));
        assert(plane.contains(Q));
        assert(plane.contains(R));
        const auto points_in_plane{ get_points_in_plane(points, plane, (Q - P).normalize()) };
        const auto hull{ jarvis_march(points_in_plane) };
        assert(hull.size() >= 3);

        // Add all edges of the face to preserve uniqueness of face in result
        // Add inverted versions of all edges to queue
        // Add the face in an order such that the plane points outward
        res.emplace_back();
        for (std::size_t i = 0; i < size(hull); i++) {
            const std::size_t j{ (i + 1) % ssize(hull) };
            vis.emplace(hull[i].first, hull[j].first);
            add({ hull[j].first, hull[i].first });
            res.back().emplace_back(hull[ssize(hull) - i - 1].first);
        }
    }

    return res;
}
