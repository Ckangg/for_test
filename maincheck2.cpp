#include "grid3d_vector.h"
#include <iostream>

// 测试 Grid2 类的功能
void check_grid_vector(int nx, int ny, int nz) {
    Grid2 grid(nx, ny, nz);
    std::cout << "grid size: " << grid.getSize() << std::endl;
    std::cout << "grid memory: " << grid.getMemory() << " bytes" << std::endl;

    // 设置网格中的每个元素
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            for (int k = 0; k < nz; k++) {
                grid.set(i, j, k, 100 * i + 10 * j + k);
            }
        }
    }

    // 输出网格内容
    std::cout << "Grid 2: " << grid;

    // 将两个相同的网格相加
    Grid2 grid_sum = grid + grid;
    std::cout << "Grid 2 + Grid 2: " << grid_sum;
}

int main() {
    int nx = 2;
    int ny = 3;
    int nz = 4;

    // 使用 check_grid_vector 测试 Grid2 类
    check_grid_vector(nx, ny, nz);

    return 0;
}
