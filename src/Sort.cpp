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

#include <atomic>

void Sort::RunTest2() {
    std::cout << "4-2 Quick Sort" << std::endl;

    int size = 4;
    std::cout << std::setw(12) << "Size";
    std::cout << std::setw(16) << "Ori time(ms)";
    std::cout << std::setw(16) << "Imp time(ms)";
    std::cout << std::setw(16) << "My time(ms)";
    std::cout << std::setw(16) << "Ori Sorted?";
    std::cout << std::setw(16) << "Imp Sorted?";
    std::cout << std::setw(16) << "My Sorted?" << std::endl;
    std::cout << "---------------------------------------------------------------------------------"
                 "--------------------------------------------------------------------\n";

    double time;

    enum QSTYPE { ORIGIN, IMPROVED, MY };

    auto func = [&time, &size](QSTYPE type, std::vector<int> &data) {
        unsigned long long int sum_counter = 0;
        auto start = std::chrono::high_resolution_clock::now();
        switch (type) {
        case ORIGIN: Sort::OriginQuickSort(data); break;
        case IMPROVED: Sort::ImprovedQuickSort(data); break;
        case MY: Sort::MyQuickSort(data); break;
        }
        auto end = std::chrono::high_resolution_clock::now();
        time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << std::setw(16) << time;
    };

    int size_flag = 1;

    do {
        std::cout << std::setw(12) << "4e" << size_flag;
        auto data1 = GenerateRandomData<int>(size);
        auto data2(data1);  // deep copy
        auto data3(data1);  // deep copy
        func(ORIGIN, data1);
        func(IMPROVED, data2);
        func(MY, data3);
        std::cout << std::setw(16) << CheckSorted(data1);
        std::cout << std::setw(16) << CheckSorted(data2);
        std::cout << std::setw(16) << CheckSorted(data3);
        std::cout << std::endl;
        size *= 10;
        ++size_flag;
    } while (size < 4e8);

    std::cout << "---------------------------------------------------------------------------------"
                 "--------------------------------------------------------------------\n";

    std::cout << "NOTICE: Data are generated from mt19937 with uniform distribution.\n";

    std::cout << "Ori - Original QuickSort\n";
    std::cout << "Imp - Improved QuickSort\n";
    std::cout << "My  - My QuickSort\n";

    std::cout << "Here are something have to be declared: \n";
    std::cout << "    When following the instruction, as you can see, it decrease the efficiency\n";
    std::cout << "    The possible reason are (1) stack push-pop operation, (2) lambda "
                 "expression,\n";
    std::cout << "(3) threshold setting\n";
    std::cout << "    So I added my QSort Version, that change the threshold and details.\n";

    system("pause");
}

void Sort::RunTest3() {
    std::cout << "4-3 Range Sort" << std::endl;
    std::cout << std::setw(12) << "Size";
    std::cout << std::setw(16) << "time(ms)";
    std::cout << std::setw(16) << "Sorted?" << std::endl;
    std::cout << "--------------------------------------------------\n";

    int size = 4;
    int size_flag = 1;

    do {
        std::cout << std::setw(12) << "4e" << size_flag;

        auto data = GenerateRandomData<int>(size);
        auto start = std::chrono::high_resolution_clock::now();
        Sort::BukkitSort(data);
        auto end = std::chrono::high_resolution_clock::now();
        auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        std::cout << std::setw(16) << time;
        std::cout << std::setw(16) << CheckSorted(data);
        std::cout << std::endl;

        size *= 10;
        ++size_flag;
    } while (size < 4e8);
    std::cout << "--------------------------------------------------\n";

    std::cout << "NOTICE: Data are generated from mt19937 with uniform distribution (0~100).\n";

    system("pause");
}