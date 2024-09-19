#pragma once
#include <algorithm>
#include <array>
#include <cassert>
#include <bit>
#include <iostream>
#include <type_traits>
#include <utility>
#include <vector>

#include "constexpr_for.h"
#include "inner_type.h"
#include "vector_dimension.h"
#include "multi_dimensional_vector.h"

template <typename T>
struct add_t {
    constexpr T operator()(const T a, const T b) const {
        return a + b;
    }
};

template <typename T>
struct sub_t {
    constexpr T operator()(const T a, const T b) const {
        return a - b;
    }
};

template <typename T, std::size_t num_dimensions, typename op_t = add_t<T>, typename inv_t = sub_t<T>, T identity = T{}>
class range_query_t {
    using container_t = multi_dimensional_vector<T, num_dimensions>;
    static_assert(num_dimensions >= 1ull, "Range query type must have at least 1 dimension.");
    container_t data;
    std::array<size_t, num_dimensions> dimensions;
    std::array<size_t, num_dimensions + 1> cum_dimensions;
    constexpr static op_t op{};
    constexpr static inv_t inv{};
    static_assert(op(identity, identity) == identity, "Applying operation on two identities does not result in identity.");
    static_assert(inv(identity, identity) == identity, "Applying inverse operation on two identities does not result in identity.");

    template <std::size_t Depth>
    constexpr void compute_prefix(std::size_t offset, const container_t& source) {
        if constexpr (Depth < num_dimensions) {
            std::size_t window_size{ data.cum_sizes[Depth+1] };
            compute_prefix<Depth + 1>(offset, source);
            for (std::size_t i = 1; i < data.sizes[Depth]; i++) {
                compute_prefix<Depth+1>(offset + i * window_size, source);
                for (std::size_t j = 0; j < window_size; j++) {
                    data[offset + i * window_size + j] += data[offset + (i-1) * window_size + j];
                }
            }
        }
    }
    
public:
    range_query_t(const container_t& arr) : data(arr) {
        compute_prefix<0>(0, arr);
    }

    constexpr T operator()(const std::array<std::size_t, num_dimensions>& lower, const std::array<std::size_t, num_dimensions>& upper) const {
        bool is_empty = false;
        constexpr_for<0ul, num_dimensions, 1ul>([&lower, &upper, &is_empty](auto j){
            if (lower[j] > upper[j]) {
                is_empty = true;
            }
        });
        if (is_empty) {
            return identity;
        }
        constexpr std::size_t limit{ 1ull << num_dimensions };
        T result{ identity };
        std::size_t ind = 0;
        std::size_t return_identity_count = 0;
        constexpr_for<0ul, num_dimensions, 1ul>([this, &ind, &upper, &lower, &return_identity_count](auto j) {
            auto cur_ind = lower[j] - 1;
            return_identity_count += lower[j] == 0;
            ind += cur_ind * data.cum_sizes[j + 1];
        });
        std::size_t gray_code = 0;
        bool should_subtract = num_dimensions % 2 != 0;
        {
            const auto value = return_identity_count ? identity : data.at(ind);
            result = should_subtract ? inv(result, value) : op(result, value);
        }
        for (std::size_t i = 1; i < limit; i++) {
        //constexpr_for_bucketed<0ul, limit, 1ul, 512ul>([&lower, &upper, &result, this](auto i){
            const std::size_t gray_ind = i ? std::countr_zero(i) : 0;
            const std::size_t gray_bit = (1 << gray_ind);
            bool is_upper = (gray_code & gray_bit);
            ind -= (is_upper ? upper[gray_ind] : lower[gray_ind] - 1) * data.cum_sizes[gray_ind + 1];
            return_identity_count -= !is_upper && lower[gray_ind] == 0;

            gray_code ^= gray_bit;
            should_subtract = !should_subtract;

            is_upper = (gray_code & gray_bit);
            ind += (is_upper ? upper[gray_ind] : lower[gray_ind] - 1) * data.cum_sizes[gray_ind + 1];
            return_identity_count += !is_upper && lower[gray_ind] == 0;
            const auto value = return_identity_count ? identity : data.at(ind);
            result = should_subtract ? inv(result, value) : op(result, value);
        }
        return result;
    }
};
