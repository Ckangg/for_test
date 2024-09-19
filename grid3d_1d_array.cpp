#include "grid3d_1d_array.h"
#include <iostream>
#include <stdexcept>

// 构造函数：构建网格并初始化变量
Grid1::Grid1(int nx_, int ny_, int nz_) : nx(nx_), ny(ny_), nz(nz_) {
    // 分配 1D 数组，大小为 nx * ny * nz
    data = new double[nx * ny * nz]();
}

// 析构函数：释放内存
Grid1::~Grid1() {
    delete[] data;  // 释放动态分配的内存
}

// 获取 3D 网格中的总元素数量
int Grid1::getSize() const {
    return nx * ny * nz;
}

// 获取网格使用的内存大小（以字节为单位）
int Grid1::getMemory() const {
    return sizeof(double) * getSize();  // 每个元素是 double 类型
}

// 重载 () 操作符，用于访问网格中的元素
double Grid1::operator()(int i, int j, int k) const {
    if (i >= nx || j >= ny || k >= nz || i < 0 || j < 0 || k < 0) {
        throw std::out_of_range("索引超出范围");
    }
    return data[i * (ny * nz) + j * nz + k];
}

// 设置网格中某个元素的值
void Grid1::set(int i, int j, int k, double value) {
    if (i >= nx || j >= ny || k >= nz || i < 0 || j < 0 || k < 0) {
        throw std::out_of_range("索引超出范围");
    }
    data[i * (ny * nz) + j * nz + k] = value;
}

// 重载 + 操作符，实现两个网格的逐元素相加
Grid1 Grid1::operator+(const Grid1& grid) {
    if (nx != grid.nx || ny != grid.ny || nz != grid.nz) {
        throw std::invalid_argument("网格尺寸不匹配");
    }

    Grid1 result(nx, ny, nz);
    for (int i = 0; i < getSize(); ++i) {
        result.data[i] = this->data[i] + grid.data[i];
    }
    return result;
}

// 重载 << 操作符，用于输出网格的内容
std::ostream& operator<<(std::ostream& os, const Grid1& grid) {
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
