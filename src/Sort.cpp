/**
 * @file Sort.cpp
 * @Author : Luminolt (copper_sulfate@qq.com)
 * @brief
 * @version 0.1
 * @date 2022-05-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "Sort.h"

void Sort::RunTest() {
    auto data = Sort::GenerateRandomData<double>(4e5);
    // Sort::ImprovedQuickSort(data);
    Sort::BukkitSort(data);
    std::cout << "Sorted: " << Sort::CheckSorted(data) << std::endl;
}