#include "grid3d_new.h"  // 包含 Grid3 的头文件
#include <iostream>

// 测试 Grid3 类的功能
void check_grid_new(int nx, int ny, int nz) {
    Grid3 grid(nx, ny, nz);  // 创建 Grid3 对象
    std::cout << "grid size: " << grid.getSize() << std::endl;  // 输出网格大小
    std::cout << "grid memory: " << grid.getMemory() << " bytes" << std::endl;  // 输出内存大小

    // 设置网格中的每个元素
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            for (int k = 0; k < nz; k++) {
                grid.set(i, j, k, 100 * i + 10 * j + k);  // 设置元素值
            }
        }
    }

    // 输出网格内容
    std::cout << "Grid 3: " << std::endl << grid;

    // 将两个相同的网格相加
    Grid3 grid_sum = grid + grid;
    std::cout << "Grid 3 + Grid 3: " << std::endl << grid_sum;
}

int main() {
    int nx = 2;  // 设置 x 方向的大小
    int ny = 3;  // 设置 y 方向的大小
    int nz = 4;  // 设置 z 方向的大小

    // 使用 check_grid_new 测试 Grid3 类
    check_grid_new(nx, ny, nz);

    return 0;
}
