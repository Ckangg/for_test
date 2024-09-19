import matplotlib.pyplot as plt
import pandas as pd

# 从 CSV 文件中读取数据
grid1_data = pd.read_csv('performance_grid1.csv')
grid2_data = pd.read_csv('performance_grid2.csv')
grid3_data = pd.read_csv('performance_grid3.csv')

# 创建绘图
plt.figure(figsize=(10, 6))

# 绘制 Grid1 的性能数据
plt.plot(grid1_data['Size'], grid1_data['AverageTime'], marker='o', label='Grid1 (1D Array)')

# 绘制 Grid2 的性能数据
plt.plot(grid2_data['Size'], grid2_data['AverageTime'], marker='s', label='Grid2 (std::vector)')

# 绘制 Grid3 的性能数据
plt.plot(grid3_data['Size'], grid3_data['AverageTime'], marker='^', label='Grid3 (new operator)')

# 设置图例、标题和标签
plt.legend()
plt.title('Performance Comparison of Grid Implementations')
plt.xlabel('Grid Size (n x n x n)')
plt.ylabel('Average Execution Time (seconds)')
plt.grid(True)

# 保存和显示图表
plt.savefig('performance_comparison.png')
plt.show()
