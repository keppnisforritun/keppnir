#pragma once
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct intx {
    intx() { normalize(1); }
    intx(std::string n) { init(n); }
    intx(int n) { std::stringstream ss; ss << n; init(ss.str()); }
    intx(const intx& other)
        : sign(other.sign), data(other.data) { }
    int sign;
    std::vector<unsigned int> data;
    static const int dcnt = 9;
    static const unsigned int radix = 1000000000U;
    int size() const { return data.size(); }
    void init(std::string n) {
        intx res; res.data.clear();
        if (n.empty()) n = "0";
        if (n[0] == '-') res.sign = -1, n = n.substr(1);
        for (int i = n.size() - 1; i >= 0; i -= intx::dcnt) {
            unsigned int digit = 0;
            for (int j = intx::dcnt - 1; j >= 0; j--) {
                int idx = i - j;
                if (idx < 0) continue;
                digit = digit * 10 + (n[idx] - '0'); }
            res.data.push_back(digit); }
        data = res.data;
        normalize(res.sign); }
    intx& normalize(int nsign) {
        if (data.empty()) data.push_back(0);
        for (int i = data.size() - 1; i > 0 && data[i] == 0; i--)
            data.erase(data.begin() + i);
        sign = data.size() == 1 && data[0] == 0 ? 1 : nsign;
        return *this; }
    friend std::ostream& operator <<(std::ostream& outs, const intx& n) {
        if (n.sign < 0) outs << '-';
        bool first = true;
        for (int i = n.size() - 1; i >= 0; i--) {
            if (first) outs << n.data[i], first = false;
            else {
                unsigned int cur = n.data[i];
                std::stringstream ss; ss << cur;
                std::string s = ss.str();
                int len = s.size();
                while (len < intx::dcnt) outs << '0', len++;
                outs << s; } }
        return outs; }
    std::string to_string() const {
        std::stringstream ss; ss << *this; return ss.str(); }
    bool operator <(const intx& b) const {
        if (sign != b.sign) return sign < b.sign;
        if (size() != b.size())
            return sign == 1 ? size() < b.size() : size() > b.size();
        for (int i = size() - 1; i >= 0; i--)
            if (data[i] != b.data[i])
                return sign == 1 ? data[i] < b.data[i]
                    : data[i] > b.data[i];
        return false; }
    bool operator <=(const intx& b) const {
        return !(b < *this);
    }
    bool operator >(const intx& b) const {
        return b < *this;
    }
    bool operator >=(const intx& b) const {
        return !(*this < b);
    }
    bool operator ==(const intx& b) const {
        return !(b < *this) && !(*this < b);
    }
    bool operator !=(const intx& b) const {
        return b < *this || *this < b;
    }
    intx operator -() const {
        intx res(*this); res.sign *= -1; return res; }
    friend intx abs(const intx &n) { return n < 0 ? -n : n; }
    intx operator +(const intx& b) const {
        if (sign > 0 && b.sign < 0) return *this - (-b);
        if (sign < 0 && b.sign > 0) return b - (-*this);
        if (sign < 0 && b.sign < 0) return -((-*this) + (-b));
        intx c; c.data.clear();
        unsigned long long carry = 0;
        for (int i = 0; i < size() || i < b.size() || carry; i++) {
            carry += (i < size() ? data[i] : 0ULL) +
                (i < b.size() ? b.data[i] : 0ULL);
            c.data.push_back(carry % intx::radix);
            carry /= intx::radix; }
        return c.normalize(sign); }
    intx operator -(const intx& b) const {
        if (sign > 0 && b.sign < 0) return *this + (-b);
        if (sign < 0 && b.sign > 0) return -(-*this + b);
        if (sign < 0 && b.sign < 0) return (-b) - (-*this);
        if (*this < b) return -(b - *this);
        intx c; c.data.clear();
        long long borrow = 0;
        for (int i = 0; i < size(); i++) {
            borrow = data[i] - borrow
                - (i < b.size() ? b.data[i] : 0ULL);
            c.data.push_back(borrow < 0 ? intx::radix + borrow
                    : borrow);
            borrow = borrow < 0 ? 1 : 0; }
        return c.normalize(sign); }
    intx operator *(const intx& b) const {
        intx c; c.data.assign(size() + b.size() + 1, 0);
        for (int i = 0; i < size(); i++) {
            long long carry = 0;
            for (int j = 0; j < b.size() || carry; j++) {
                if (j < b.size())
                    carry += (long long)data[i] * b.data[j];
                carry += c.data[i + j];
                c.data[i + j] = carry % intx::radix;
                carry /= intx::radix; } }
        return c.normalize(sign * b.sign); }
    friend std::pair<intx,intx> divmod(const intx& n, const intx& d) {
        assert(!(d.size() == 1 && d.data[0] == 0));
        intx q, r; q.data.assign(n.size(), 0);
        for (int i = n.size() - 1; i >= 0; i--) {
            r.data.insert(r.data.begin(), 0);
            r = r + n.data[i];
            long long k = 0;
            if (d.size() < r.size())
                k = (long long)intx::radix * r.data[d.size()];
            if (d.size() - 1 < r.size()) k += r.data[d.size() - 1];
            k /= d.data.back();
            r = r - abs(d) * k;
            // if (r < 0) for (ll t = 1LL << 62; t >= 1; t >>= 1) {
            //     intx dd = abs(d) * t;
            //     while (r + dd < 0) r = r + dd, k -= t; }
            while (r < 0) r = r + abs(d), k--;
            q.data[i] = k; }
        return std::pair<intx, intx>(q.normalize(n.sign * d.sign), r);
    }
    intx operator /(const intx& d) const {
        return divmod(*this,d).first;
    }
    intx operator %(const intx& d) const {
        return divmod(*this,d).second * sign;
    }
};


using int_t = intx;

std::istream& operator>>(std::istream& in, int_t& x) {
    std::int64_t y;
    in >> y;
    x = y;
    return in;
}

template <typename scalar_t>
constexpr scalar_t EPS = scalar_t(5e-6L);

template <>
intx EPS<intx>{ 0 };


enum class intersection_t { none, one, infinite };
