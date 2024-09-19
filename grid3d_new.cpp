#include "grid3d_new.h"
#include <iostream>
#include <stdexcept>

// 构造函数：动态分配三维数组并初始化
Grid3::Grid3(int nx_, int ny_, int nz_) : nx(nx_), ny(ny_), nz(nz_) {
    // 动态分配三维数组
    data = new double**[nx];  // 分配 nx 个 double**
    for (int i = 0; i < nx; ++i) {
        data[i] = new double*[ny];  // 为每个 nx 分配 ny 个 double*
        for (int j = 0; j < ny; ++j) {
            data[i][j] = new double[nz]();  // 为每个 ny 分配 nz 个 double，并初始化为 0.0
        }
    }
}

// 析构函数：释放动态分配的三维数组内存
Grid3::~Grid3() {
    for (int i = 0; i < nx; ++i) {
        for (int j = 0; j < ny; ++j) {
            delete[] data[i][j];  // 释放内层的 double 数组
        }
        delete[] data[i];  // 释放中间层的 double* 数组
    }
    delete[] data;  // 释放最外层的 double** 数组
}

// 获取 3D 网格中的总元素数量
int Grid3::getSize() const {
    return nx * ny * nz;
}

// 获取网格占用的内存大小（以字节为单位）
int Grid3::getMemory() const {
    return sizeof(double) * getSize();  // 每个元素是 double 类型
}

// 重载 () 操作符，用于访问网格中的元素
double Grid3::operator()(int i, int j, int k) const {
    if (i >= nx || j >= ny || k >= nz || i < 0 || j < 0 || k < 0) {
        throw std::out_of_range("索引超出范围");
    }
    return data[i][j][k];
}

// 设置网格中某个元素的值
void Grid3::set(int i, int j, int k, double value) {
    if (i >= nx || j >= ny || k >= nz || i < 0 || j < 0 || k < 0) {
        throw std::out_of_range("索引超出范围");
    }
    data[i][j][k] = value;
}

// 重载 + 操作符，实现两个网格的逐元素相加
Grid3 Grid3::operator+(const Grid3& grid) {
    if (nx != grid.nx || ny != grid.ny || nz != grid.nz) {
        throw std::invalid_argument("网格尺寸不匹配");
    }

    Grid3 result(nx, ny, nz);
    for (int i = 0; i < nx; ++i) {
        for (int j = 0; j < ny; ++j) {
            for (int k = 0; k < nz; ++k) {
                result.data[i][j][k] = this->data[i][j][k] + grid.data[i][j][k];
            }
        }
    }
    return result;
}

// 重载 << 操作符，用于输出网格的内容
std::ostream& operator<<(std::ostream& os, const Grid3& grid) {
    for (int i = 0; i < grid.nx; ++i) {
        for (int j = 0; j < grid.ny; ++j) {
            for (int k = 0; k < grid.nz; ++k) {
                os << grid(i, j, k) << " ";
            }
            os << std::endl;  // 输出每一行之后换行
        }
        os << std::endl;  // 每层之间空一行
    }
    return os;
}
