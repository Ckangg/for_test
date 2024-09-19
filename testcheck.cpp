#include <iostream>
#include <cassert>
#include <chrono>
#include <fstream>
#include "grid3d_1d_array.h"
#include "grid3d_vector.h"
#include "grid3d_new.h"

using namespace std;

void testPerformanceGrid1() {
    ofstream file("performance_grid1.csv"); // 打开文件
    file << "Size,AverageTime\n"; // 写入表头

    int sizes[] = {10, 50, 100, 200}; // 不同的 n 值
    for (int n : sizes) {
        cout << "Testing Grid1 with size " << n << " x " << n << " x " << n << "...\n";
        
        double total_time = 0;
        for (int run = 0; run < 5; ++run) { // 运行 5 次
            Grid1 grid(n, n, n);
            auto start = chrono::high_resolution_clock::now();
            Grid1 grid_sum = grid + grid;
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> elapsed = end - start;

            if (run != 0) { // 不计算第一次的时间
                total_time += elapsed.count();
            }

            cout << "Run " << run + 1 << ": " << elapsed.count() << " seconds\n";
        }

        double avg_time = total_time / 4; // 后 4 次的平均时间
        cout << "Average Time for Grid1 size " << n << ": " << avg_time << " seconds\n";
        
        // 将结果写入文件
        file << n << "," << avg_time << "\n";
    }
    file.close(); // 关闭文件
}

// 测试 Grid2 的性能，并将结果保存到 CSV 文件
void testPerformanceGrid2() {
    ofstream file("performance_grid2.csv");
    file << "Size,AverageTime\n";

    int sizes[] = {10, 50, 100, 200}; // 不同的 n 值
    for (int n : sizes) {
        cout << "Testing Grid2 with size " << n << " x " << n << " x " << n << "...\n";
        
        double total_time = 0;
        for (int run = 0; run < 5; ++run) { // 运行 5 次
            Grid2 grid(n, n, n);
            auto start = chrono::high_resolution_clock::now();
            Grid2 grid_sum = grid + grid;
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> elapsed = end - start;

            if (run != 0) { // 不计算第一次的时间
                total_time += elapsed.count();
            }

            cout << "Run " << run + 1 << ": " << elapsed.count() << " seconds\n";
        }

        double avg_time = total_time / 4; // 后 4 次的平均时间
        cout << "Average Time for Grid2 size " << n << ": " << avg_time << " seconds\n";
        
        // 将结果写入文件
        file << n << "," << avg_time << "\n";
    }
    file.close();
}

// 测试 Grid3 的性能，并将结果保存到 CSV 文件
void testPerformanceGrid3() {
    ofstream file("performance_grid3.csv");
    file << "Size,AverageTime\n";

    int sizes[] = {10, 50, 100, 200}; // 不同的 n 值
    for (int n : sizes) {
        cout << "Testing Grid3 with size " << n << " x " << n << " x " << n << "...\n";
        
        double total_time = 0;
        for (int run = 0; run < 5; ++run) { // 运行 5 次
            Grid3 grid(n, n, n);
            auto start = chrono::high_resolution_clock::now();
            Grid3 grid_sum = grid + grid;
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> elapsed = end - start;

            if (run != 0) { // 不计算第一次的时间
                total_time += elapsed.count();
            }

            cout << "Run " << run + 1 << ": " << elapsed.count() << " seconds\n";
        }

        double avg_time = total_time / 4; // 后 4 次的平均时间
        cout << "Average Time for Grid3 size " << n << ": " << avg_time << " seconds\n";
        
        // 将结果写入文件
        file << n << "," << avg_time << "\n";
    }
    file.close();
}

// 测试所有 Grid 的性能
void testAllPerformance() {
    cout << "\nPerformance Testing for Grid1:\n";
    testPerformanceGrid1();

    cout << "\nPerformance Testing for Grid2:\n";
    testPerformanceGrid2();

    cout << "\nPerformance Testing for Grid3:\n";
    testPerformanceGrid3();
}
// 测试 Grid1 类（1D 数组实现）
void testGrid1() {
    cout << "Running tests for Grid1 (1D Array)...\n";

    Grid1 grid1(2, 3, 4);
    assert(grid1.getSize() == 2 * 3 * 4); // 验证大小
    assert(grid1.getMemory() == 2 * 3 * 4 * sizeof(double)); // 验证内存

    // 设置和读取元素
    grid1.set(1, 2, 3, 5.5);
    assert(grid1(1, 2, 3) == 5.5);

    // 检查函数：设置网格元素并逐元素相加
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 4; k++) {
                grid1.set(i, j, k, 100 * i + 10 * j + k);
            }
        }
    }

    cout << "Grid 1: " << grid1;

    Grid1 grid1_sum = grid1 + grid1;
    cout << "Grid 1 + Grid 1: " << grid1_sum;

    // 测试越界访问
    try {
        grid1.set(3, 3, 3, 1.0); // 索引越界
        assert(false); // 不应当到达此行
    } catch (const std::out_of_range&) {
        cout << "Out of range set test passed for Grid1.\n";
    }

    try {
        double val = grid1(2, 3, 4); // 索引越界
        assert(false); // 不应当到达此行
    } catch (const std::out_of_range&) {
        cout << "Out of range get test passed for Grid1.\n";
    }

    cout << "All tests passed for Grid1.\n";
}

// 测试 Grid2 类（std::vector 实现）
void testGrid2() {
    cout << "Running tests for Grid2 (std::vector)...\n";

    Grid2 grid2(3, 4, 2);
    assert(grid2.getSize() == 3 * 4 * 2); // 验证大小
    assert(grid2.getMemory() == 3 * 4 * 2 * sizeof(double)); // 验证内存

    // 设置和读取元素
    grid2.set(2, 3, 1, 8.8);
    assert(grid2(2, 3, 1) == 8.8);

    // 检查函数：设置网格元素并逐元素相加
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 2; k++) {
                grid2.set(i, j, k, 100 * i + 10 * j + k);
            }
        }
    }

    cout << "Grid 2: " << grid2;

    Grid2 grid2_sum = grid2 + grid2;
    cout << "Grid 2 + Grid 2: " << grid2_sum;

    // 测试越界访问
    try {
        grid2.set(3, 4, 2, 1.0); // 索引越界
        assert(false); // 不应当到达此行
    } catch (const std::out_of_range&) {
        cout << "Out of range set test passed for Grid2.\n";
    }

    try {
        double val = grid2(0, 4, 1); // 索引越界
        assert(false); // 不应当到达此行
    } catch (const std::out_of_range&) {
        cout << "Out of range get test passed for Grid2.\n";
    }

    cout << "All tests passed for Grid2.\n";
}

// 测试 Grid3 类（new 操作符实现）
void testGrid3() {
    cout << "Running tests for Grid3 (new operator)...\n";

    Grid3 grid3(4, 2, 3);
    assert(grid3.getSize() == 4 * 2 * 3); // 验证大小
    assert(grid3.getMemory() == 4 * 2 * 3 * sizeof(double)); // 验证内存

    // 设置和读取元素
    grid3.set(3, 1, 2, 3.3);
    assert(grid3(3, 1, 2) == 3.3);

    // 检查函数：设置网格元素并逐元素相加
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 3; k++) {
                grid3.set(i, j, k, 100 * i + 10 * j + k);
            }
        }
    }

    cout << "Grid 3: " << grid3;

    Grid3 grid3_sum = grid3 + grid3;
    cout << "Grid 3 + Grid 3: " << grid3_sum;

    // 测试越界访问
    try {
        grid3.set(4, 2, 3, 1.0); // 索引越界
        assert(false); // 不应当到达此行
    } catch (const std::out_of_range&) {
        cout << "Out of range set test passed for Grid3.\n";
    }

    try {
        double val = grid3(3, 2, 3); // 索引越界
        assert(false); // 不应当到达此行
    } catch (const std::out_of_range&) {
        cout << "Out of range get test passed for Grid3.\n";
    }

    cout << "All tests passed for Grid3.\n";
}

int main() {
    // 测试 Grid1 实现
    testGrid1();

    // 测试 Grid2 实现
    testGrid2();

    // 测试 Grid3 实现
    testGrid3();

    cout << "All functional tests finished successfully.\n";

    // 性能测试
    testAllPerformance();

    return 0;
}
