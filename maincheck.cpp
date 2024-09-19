#include "grid3d_1d_array.h"
#include <iostream>

void check_grid_1d_array(int nx, int ny, int nz)
{
    Grid1 grid(nx, ny, nz);
    std::cout << "grid size: " << grid.getSize() << std::endl;
    std::cout << "grid memory: " << grid.getMemory() << " bytes" << std::endl;
 
    // 设置网格中的元素
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            for (int k = 0; k < nz; k++) {
                grid.set(i, j, k, 100 * i + 10 * j + k);
            }
        }
    }

    // 输出网格内容
    std::cout << "Grid 1: " << grid;

    // 逐元素相加
    Grid1 grid_sum = grid + grid;
    std::cout << "Grid 1 + Grid 1: " << grid_sum;
}

int main() {
    // 设置网格的尺寸
    int nx = 2;
    int ny = 3;
    int nz = 4;

    // 检查 1D 数组实现的 3D 网格
    check_grid_1d_array(nx, ny, nz);

    return 0;
}
