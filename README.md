# 实现思路及本地运行截图

1. 矩阵加法：add_matrix 
   [![pETEszV.png](https://s21.ax1x.com/2025/04/26/pETEszV.png)](https://imgse.com/i/pETEszV)
2. 矩阵减法：sub_matrix 
   [![pETE4iR.png](https://s21.ax1x.com/2025/04/26/pETE4iR.png)](https://imgse.com/i/pETE4iR)

3. 矩阵乘法：mul_matrix 
    [![pETEfo9.png](https://s21.ax1x.com/2025/04/26/pETEfo9.png)](https://imgse.com/i/pETEfo9)
    
4. 矩阵数乘：scale_matrix 
   [![pETEWdJ.png](https://s21.ax1x.com/2025/04/26/pETEWdJ.png)](https://imgse.com/i/pETEWdJ)

5. 矩阵转置：transpose_matrix
   [![pETEzWt.png](https://s21.ax1x.com/2025/04/26/pETEzWt.png)](https://imgse.com/i/pETEzWt)
6. 求矩阵行列式：det_matrix
   - 实现思路：运用递归，当行列式维数大于2时，将行列式沿第一列展开，即调用函数自身求解子矩阵行列式。当n=2时为递归终点。
   - 本地运行截图：
   [![pETVpSP.png](https://s21.ax1x.com/2025/04/26/pETVpSP.png)](https://imgse.com/i/pETVpSP)

7. 矩阵求逆：inv_matrix
    - 实现思路：先判断a的行列式是否为0，若为0输出报错，若不为零开始计算。只需得到a的伴随矩阵和a的行列式，然后调用数乘函数即可。对于伴随矩阵中的每个元素，先生成其对应的子矩阵，然后调用行列式函数计算该子矩阵的行列式，再乘正负系数即可。
    - 本地运行截图：
    [![pETExJI.png](https://s21.ax1x.com/2025/04/26/pETExJI.png)](https://imgse.com/i/pETExJI)
    
8. 矩阵求秩：rank_matrix
   - 实现思路：首先假设矩阵的秩为0,通过高斯消元法将矩阵逐步化为行阶梯形，逐列寻找非零主元并进行行交换，对下方行实施消元操作消除当前列的非主元元素，每列循环完矩阵的秩加一，除非该列的主元及其下方的元素都为0。
   - 本地运行截图：
    [![pETZkjK.png](https://s21.ax1x.com/2025/04/26/pETZkjK.png)](https://imgse.com/i/pETZkjK)

9. 矩阵的迹：trace_matrix
   [![pETZFc6.png](https://s21.ax1x.com/2025/04/26/pETZFc6.png)](https://imgse.com/i/pETZFc6)