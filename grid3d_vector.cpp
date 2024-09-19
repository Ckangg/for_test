#include "grid3d_vector.h"
#include <iostream>
#include <stdexcept>

// 构造函数：构建 3D 网格并初始化
Grid2::Grid2(int nx_, int ny_, int nz_) : nx(nx_), ny(ny_), nz(nz_) {
    data.resize(nx, std::vector<std::vector<double>>(ny, std::vector<double>(nz, 0.0)));
}

// 析构函数：自动调用 vector 的析构，不需要手动释放内存
Grid2::~Grid2() {
    // 无需手动释放内存，std::vector 自动管理内存
}

// 获取 3D 网格中的总元素数量
int Grid2::getSize() const {
    return nx * ny * nz;
}

// 获取网格占用的内存大小（以字节为单位）
int Grid2::getMemory() const {
    return sizeof(double) * getSize();  // 每个元素是 double 类型
}

// 重载 () 操作符，用于访问网格中的元素
double Grid2::operator()(int i, int j, int k) const {
    if (i >= nx || j >= ny || k >= nz || i < 0 || j < 0 || k < 0) {
        throw std::out_of_range("索引超出范围");
    }
    return data[i][j][k];
}

// 设置网格中某个元素的值
void Grid2::set(int i, int j, int k, double value) {
    if (i >= nx || j >= ny || k >= nz || i < 0 || j < 0 || k < 0) {
        throw std::out_of_range("索引超出范围");
    }
    data[i][j][k] = value;
}

// 重载 + 操作符，实现两个网格的逐元素相加
Grid2 Grid2::operator+(const Grid2& grid) {
    if (nx != grid.nx || ny != grid.ny || nz != grid.nz) {
        throw std::invalid_argument("网格尺寸不匹配");
    }

    Grid2 result(nx, ny, nz);
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
std::ostream& operator<<(std::ostream& os, const Grid2& grid) {
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
