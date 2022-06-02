/**
 * @file Sort.h
 * @Author : Luminolt (copper_sulfate@qq.com)
 * @brief
 * @version 0.1
 * @date 2022-05-23
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef INCLUDE_SORT_H
#define INCLUDE_SORT_H

#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <stack>
#include <vector>

class Sort {
public:
    /**
     * @brief Quick Sort (Recursion Version)
     *
     * @tparam T
     * @param data
     */
    template <typename T>
    static void OriginQuickSort(std::vector<T> &data);

    /**
     * @brief Improved Quick Sort
     *
     * @tparam T
     * @param data
     */
    template <typename T>
    static void ImprovedQuickSort(std::vector<T> &data);

    /**
     * @brief My Quick Sort
     *
     * @tparam T
     * @param data
     */
    template <typename T>
    static void MyQuickSort(std::vector<T> &data);

    /**
     * @brief Bukkit Sort
     *
     * @tparam T
     * @param data
     */
    template <typename T>
    static void BukkitSort(std::vector<T> &data);

    /**
     * @brief Random Data Generator
     *
     * @tparam T
     * @param size
     * @return std::vector<T>
     */
    template <typename T>
    static std::vector<T> GenerateRandomData(size_t size);

    /**
     * @brief
     *
     * @tparam T
     * @param data
     * @return bool
     */
    template <typename T>
    static bool CheckSorted(std::vector<T> &data);

    /**
     * @brief Run Test for second mission.
     *
     */
    static void RunTest2();

    /**
     * @brief Run Test for third mission.
     *
     */
    static void RunTest3();

protected:
    /**
     * @brief sub Quick Sort
     *
     * @tparam T
     * @param data
     * @param left
     * @param right
     */
    template <typename T>
    static void subQuickSort(std::vector<T> &data, int left, int right);

    /**
     * @brief sub My Quick Sort
     *
     * @tparam T
     * @param data
     * @param left
     * @param right
     */
    template <typename T>
    static void subMyQSort(std::vector<T> &data, int left, int right);
};

// Definitions

template <typename T>
std::vector<T> Sort::GenerateRandomData(size_t size) {
    std::vector<T> data;
    data.reserve(size);

    // For Debug Device~
    // std::random_device rd;
    // std::mt19937 gen(rd());

    // For Release Device~
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);

    std::uniform_int_distribution<> dis(0, 100);
    for (size_t i = 0; i < size; ++i) {
        data.emplace_back(dis(gen));
    }
    return data;
}

template <typename T>
void Sort::subQuickSort(std::vector<T> &data, int left, int right) {
    if (left >= right) {
        return;
    }

    int i = left;
    int j = right;
    T pivot = data[(left + right) / 2];

    while (i <= j) {
        while (data[i] < pivot) {
            ++i;
        }
        while (data[j] > pivot) {
            --j;
        }
        if (i <= j) {
            std::swap(data[i], data[j]);
            ++i;
            --j;
        }
    }
    subQuickSort(data, left, j);
    subQuickSort(data, i, right);
}

template <typename T>
void Sort::OriginQuickSort(std::vector<T> &data) {
    subQuickSort(data, 0, data.size() - 1);
}

template <typename T>
void Sort::ImprovedQuickSort(std::vector<T> &data) {
    std::stack<std::pair<int, int>> st;

    // Step 1: Push the left and right index to stack
    st.emplace(0, data.size() - 1);

    // Give the subQuickSort
    auto subQuickSort = [](std::vector<T> &data, int left, int right,
                           int pivot_idx) -> std::pair<int, int> {
        int i = left;
        int j = right;
        T pivot = data[pivot_idx];

        while (i <= j) {
            while (data[i] < pivot) {
                ++i;
            }
            while (data[j] > pivot) {
                --j;
            }
            if (i <= j) {
                std::swap(data[i], data[j]);
                ++i;
                --j;
            }
        }
        return std::make_pair(j, i);
        // left < j < i < right
    };

    while (!st.empty()) {
        // (1) Sort the sub-array with mid pivit
        auto [left, right] = st.top();
        st.pop();

        // Check Consistency
        if (left >= right) {
            continue;
        }

        // (3) If the sub-array is too small (size <= 3), use insertion sort
        if (right - left <= 3) {
            for (int i = left + 1; i <= right; ++i) {
                for (int j = i; j > left && data[j] < data[j - 1]; --j) {
                    std::swap(data[j], data[j - 1]);
                }
            }
            continue;
        }
        auto [j, i] = subQuickSort(data, left, right, (left + right) / 2);

        // (2) if left sub-array is bigger, push it to stack
        if (j - left > right - i) {
            st.emplace(left, j);
            st.emplace(i, right);
        } else {
            st.emplace(i, right);
            st.emplace(left, j);
        }
    }
}

template <typename T>
bool Sort::CheckSorted(std::vector<T> &data) {
    for (size_t i = 1; i < data.size(); ++i) {
        if (data[i - 1] > data[i]) {
            return false;
        }
    }
    return true;
}

template <typename T>
void Sort::BukkitSort(std::vector<T> &data) {
    // Step 1: Find the max and min value
    T max = data[0];
    T min = data[0];
    for (size_t i = 1; i < data.size(); ++i) {
        if (data[i] > max) {
            max = data[i];
        }
        if (data[i] < min) {
            min = data[i];
        }
    }

    // Step 2: Create the buckit
    std::vector<T> number(max - min + 1);

    // Step 3: Sort the data
    for (size_t i = 0; i < data.size(); ++i) {
        number[data[i] - min]++;
    }

    // Step 4: Merge the data
    size_t idx = 0;
    for (size_t i = 0; i < number.size(); ++i) {
        for (size_t j = 0; j < number[i]; ++j) {
            data[idx++] = i + min;
        }
    }
}

// subMyQuickSort
template <typename T>
void Sort::subMyQSort(std::vector<T> &data, int left, int right) {
    if (left >= right)
        return;
    if (right - left <= 10) {
        for (auto i = left; i <= right; i++) {
            auto key = data[i];
            auto j = i - 1;
            while (j >= left && key < data[j]) {
                data[j + 1] = data[j];
                j--;
            }
            data[j + 1] = key;
        }
    } else {
        std::swap(data[left], data[left + rand() % (right - left + 1)]);
        auto key = data[left];
        auto i = left, j = left;
        auto k = right;
        while (i <= k) {
            if (data[i] < key) {
                std::swap(data[i], data[j]);
                i++, j++;
            } else if (data[i] > key) {
                std::swap(data[i], data[k]);
                k--;
            } else {
                i++;
            }
        }
        subMyQSort(data, left, j);
        subMyQSort(data, k + 1, right);
    }
}

// My Quick Sort
template <typename T>
void Sort::MyQuickSort(std::vector<T> &data) {
    subMyQSort(data, 0, data.size() - 1);
}

#endif  // INCLUDE_MY_SORT_H