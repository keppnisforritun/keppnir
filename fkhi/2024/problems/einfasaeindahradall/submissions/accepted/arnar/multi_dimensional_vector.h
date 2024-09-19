#pragma once
#include <array>
#include <vector>

#include "constexpr_for.h"

template<typename T, std::size_t Dims>
struct multi_dimensional_vector {
    static_assert(Dims > 0, "Dimensions must be positive");
    std::array<std::size_t, Dims> sizes;
    std::array<std::size_t, Dims + 1> cum_sizes;
    std::vector<T> data;
    multi_dimensional_vector(const std::array<std::size_t, Dims>& sizes) : sizes(sizes) {
        cum_sizes[Dims] = 1;
        constexpr_for<0ul, Dims, 1ul>([this](auto i) {
            cum_sizes[Dims - i - 1] = cum_sizes[Dims - i] * this->sizes[Dims - i - 1];
        });
        data.resize(size());
    }

    constexpr std::size_t size() const {
        return cum_sizes[0];
    }

    constexpr T& operator[](const std::size_t index) {
        return data[index];
    }

    constexpr T& operator[](const std::array<std::size_t, Dims>& indices) {
        return data[compute_index(indices)];
    }
    
    constexpr auto at(const std::size_t index) const {
        return data.at(index);
    }

    constexpr auto at(const std::array<std::size_t, Dims>& indices) const {
        return data.at(compute_index(indices));
    }

    constexpr auto compute_index(const std::array<std::size_t, Dims>& indices) const {
        std::size_t ind = 0;
        constexpr_for<0ul, Dims, 1ul>([this, &indices, &ind](auto i) {
            ind += indices[i] * cum_sizes[i + 1];
        });
        return ind;
    }
};
