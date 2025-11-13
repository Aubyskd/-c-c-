#include <iostream>
#include <vector>
#include <iomanip>  // 用于格式化输出

using namespace std;

int main() {
    cout << "=== C++ 矩阵（二维数组）详解 ===" << endl << endl;

    // 1. 矩阵的声明和初始化
    cout << "1. 矩阵的声明和初始化方法：" << endl;
    cout << "=================================" << endl;

    // 方法1：使用 vector<vector<int>> 并直接初始化
    vector<vector<int>> matrix1 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    // 方法2：先声明大小，再赋值
    vector<vector<int>> matrix2(3, vector<int>(3));  // 3x3矩阵，初始值为0
    matrix2[0][0] = 10; matrix2[0][1] = 20; matrix2[0][2] = 30;
    matrix2[1][0] = 40; matrix2[1][1] = 50; matrix2[1][2] = 60;
    matrix2[2][0] = 70; matrix2[2][1] = 80; matrix2[2][2] = 90;

    // 方法3：使用传统二维数组
    int matrix3[3][3] = {
        {100, 200, 300},
        {400, 500, 600},
        {700, 800, 900}
    };

    cout << "方法1 - vector<vector<int>> 直接初始化：" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << setw(4) << matrix1[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\n方法2 - 先声明大小再赋值：" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << setw(4) << matrix2[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\n方法3 - 传统二维数组：" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << setw(4) << matrix3[i][j] << " ";
        }
        cout << endl;
    }

    // 2. 矩阵的基本操作
    cout << "\n\n2. 矩阵的基本操作：" << endl;
    cout << "===================" << endl;

    // 获取矩阵大小
    cout << "matrix1 的行数: " << matrix1.size() << endl;
    cout << "matrix1 的列数: " << matrix1[0].size() << endl;

    // 访问和修改元素
    cout << "\n修改前 matrix1[1][1] = " << matrix1[1][1] << endl;
    matrix1[1][1] = 999;
    cout << "修改后 matrix1[1][1] = " << matrix1[1][1] << endl;

    // 3. 动态创建矩阵
    cout << "\n\n3. 动态创建矩阵：" << endl;
    cout << "=================" << endl;

    int rows = 4, cols = 5;
    vector<vector<int>> dynamic_matrix(rows, vector<int>(cols, 0));  // 初始化为0

    // 填充一些数据
    int value = 1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            dynamic_matrix[i][j] = value++;
        }
    }

    cout << "动态创建的 " << rows << "x" << cols << " 矩阵：" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << setw(3) << dynamic_matrix[i][j] << " ";
        }
        cout << endl;
    }

    // 4. 矩阵的实际应用 - 图像处理
    cout << "\n\n4. 矩阵的实际应用 - 图像处理：" << endl;
    cout << "================================" << endl;

    // 创建一个简单的图案矩阵
    vector<vector<int>> image = {
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1},
        {1, 0, 1, 0, 1},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1}
    };

    cout << "5x5 图像矩阵（1=黑色，0=白色）：" << endl;
    for (int i = 0; i < image.size(); i++) {
        for (int j = 0; j < image[i].size(); j++) {
            cout << image[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\n对应的图形输出：" << endl;
    for (int i = 0; i < image.size(); i++) {
        for (int j = 0; j < image[i].size(); j++) {
            cout << (image[i][j] ? "\u2588\u2588" : "  ");
        }
        cout << endl;
    }

    // 5. 矩阵运算示例
    cout << "\n\n5. 矩阵运算示例：" << endl;
    cout << "=================" << endl;

    vector<vector<int>> A = { {1, 2}, {3, 4} };
    vector<vector<int>> B = { {5, 6}, {7, 8} };
    vector<vector<int>> C(2, vector<int>(2, 0));  // 结果矩阵

    // 矩阵相加
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    cout << "矩阵 A:" << endl;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }

    cout << "矩阵 B:" << endl;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            cout << B[i][j] << " ";
        }
        cout << endl;
    }

    cout << "A + B = C:" << endl;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            cout << C[i][j] << " ";
        }
        cout << endl;
    }

    // 6. 重要概念总结
    cout << "\n\n6. 重要概念总结：" << endl;
    cout << "=================" << endl;
    cout << "vector<vector<int>> 是动态二维数组" << endl;
    cout << "matrix[i][j] 访问第i行第j列的元素" << endl;
    cout << "matrix.size() 获取行数" << endl;
    cout << "matrix[0].size() 获取列数" << endl;
    cout << "矩阵在图像处理中非常重要" << endl;
    cout << "每个像素点就是一个矩阵元素" << endl;

    cout << "=== 不规则矩阵（锯齿矩阵）示例 ===" << endl << endl;

    // 1. 创建不规则矩阵 - 每行列数不同
    vector<vector<int>> irregular_matrix = {
        {1, 2, 3},                    // 第0行：3列
        {4, 5, 6, 7, 8},             // 第1行：5列
        {9, 10},                      // 第2行：2列
        {11, 12, 13, 14, 15, 16, 17}, // 第3行：7列
        {18}                          // 第4行：1列
    };

    cout << "1. 不规则矩阵示例：" << endl;
    cout << "=================" << endl;
    for (int i = 0; i < irregular_matrix.size(); i++) {
        cout << "第" << i << "行 (" << irregular_matrix[i].size() << "列): ";
        for (int j = 0; j < irregular_matrix[i].size(); j++) {
            cout << irregular_matrix[i][j] << " ";
        }
        cout << endl;
    }

    // 2. 动态创建不规则矩阵
    cout << "\n2. 动态创建不规则矩阵：" << endl;
    cout << "=====================" << endl;

    vector<vector<int>> dynamic_irregular(5);  // 创建5行，但每行列数未定

    // 为每一行分配不同数量的列
    dynamic_irregular[0].resize(3);   // 第0行：3列
    dynamic_irregular[1].resize(1);   // 第1行：1列
    dynamic_irregular[2].resize(4);   // 第2行：4列
    dynamic_irregular[3].resize(2);   // 第3行：2列
    dynamic_irregular[4].resize(6);   // 第4行：6列

    // 填充数据
    int value_1 = 1;
    for (int i = 0; i < dynamic_irregular.size(); i++) {
        for (int j = 0; j < dynamic_irregular[i].size(); j++) {
            dynamic_irregular[i][j] = value_1++;
        }
    }

    cout << "动态创建的不规则矩阵：" << endl;
    for (int i = 0; i < dynamic_irregular.size(); i++) {
        cout << "第" << i << "行 (" << dynamic_irregular[i].size() << "列): ";
        for (int j = 0; j < dynamic_irregular[i].size(); j++) {
            cout << setw(3) << dynamic_irregular[i][j] << " ";
        }
        cout << endl;
    }

    // 3. 实际应用：三角形图案
    cout << "\n3. 实际应用：三角形图案：" << endl;
    cout << "=======================" << endl;

    vector<vector<int>> triangle = {
        {1},                    // 第0行：1个元素
        {1, 1},                 // 第1行：2个元素
        {1, 2, 1},              // 第2行：3个元素
        {1, 3, 3, 1},           // 第3行：4个元素
        {1, 4, 6, 4, 1}         // 第4行：5个元素
    };

    cout << "杨辉三角形（帕斯卡三角形）：" << endl;
    for (int i = 0; i < triangle.size(); i++) {
        // 打印前导空格，让三角形居中
        for (int k = 0; k < (triangle.size() - i - 1); k++) {
            cout << "  ";
        }

        for (int j = 0; j < triangle[i].size(); j++) {
            cout << setw(4) << triangle[i][j];
        }
        cout << endl;
    }

    // 4. 实际应用：不同长度的单词列表
    cout << "\n4. 实际应用：不同长度的单词列表：" << endl;
    cout << "================================" << endl;

    vector<vector<string>> word_matrix = {
        {"Hello"},                           // 1个单词
        {"I", "am"},                         // 2个单词
        {"a", "good", "student"},            // 3个单词
        {"I", "love", "programming", "very", "much"}  // 5个单词
    };

    for (int i = 0; i < word_matrix.size(); i++) {
        cout << "第" << i << "行 (" << word_matrix[i].size() << "个单词): ";
        for (int j = 0; j < word_matrix[i].size(); j++) {
            cout << word_matrix[i][j] << " ";
        }
        cout << endl;
    }

    // 5. 访问不规则矩阵的注意事项
    cout << "\n5. 访问不规则矩阵的注意事项：" << endl;
    cout << "=============================" << endl;

    cout << "矩阵总行数: " << irregular_matrix.size() << endl;
    for (int i = 0; i < irregular_matrix.size(); i++) {
        cout << "第" << i << "行的列数: " << irregular_matrix[i].size() << endl;
    }

    cout << "\n安全访问示例：" << endl;
    // 安全的访问方式 - 先检查边界
    int row = 1, col = 3;
    if (row < irregular_matrix.size() && col < irregular_matrix[row].size()) {
        cout << "irregular_matrix[" << row << "][" << col << "] = "
            << irregular_matrix[row][col] << endl;
    }
    else {
        cout << "索引超出边界！" << endl;
    }

    // 6. 重要概念总结
    cout << "\n6. 重要概念总结：" << endl;
    cout << "=================" << endl;
    cout << "每行的列数可以不同" << endl;
    cout << "这种矩阵叫做'不规则矩阵'或'锯齿矩阵'" << endl;
    cout << "访问时必须注意边界检查" << endl;
    cout << "适用于存储不同长度的数据" << endl;
    cout << "常用于树形结构、三角形等场景" << endl;

    return 0;
}


/*
一 三种声明方法
1.vector<vector<int>> matrix={
    {1,2,3},
    {4,5,6},
    {7,8,9}
};
动态大小，内存安全

2.先声明大小再赋值
vector<vector<int>> matrix(3,vecotr<int>(3));
matrix[0][0]=1;matrix[0][1]=2;   逐个赋值
可以动态创建任意大小的矩阵

3.传统二维数组
int matrix[3][3]{
    {1,2,3},
    {4,5,6},
    {7,8,9}
};
大小固定，容易出错

二 常规操作
1.访问元素
matrix[i][j]   第i行第j列的元素

2.获取大小
matrix.size()  #行数
matrix[0].size()  #列数

3.遍历矩阵
for(int i=0;i<matrix.size();i++){
    for(int j=0;j<matrix[i].size();j++){
        cout<<matrix[i][j]<<" ";
    }
    cout<<endl;
}

三  不规则矩阵
vector<vector<int>> matrix = {
    {1, 2, 3},                    // 第0行：3列
    {4, 5, 6, 7, 8},             // 第1行：5列
    {9, 10},                      // 第2行：2列
    {11, 12, 13, 14, 15, 16, 17}, // 第3行：7列
    {18}                          // 第4行：1列
};

访问时注意事项
// 安全访问方式 - 先检查边界
if (row < matrix.size() && col < matrix[row].size()) {
    cout << matrix[row][col];
}



*/
