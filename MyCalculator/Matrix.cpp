/// Matrix.cpp файл реализации
/// Определяет объекты матриц и действия с ними

#include "pch.h"
#include "Matrix.h"

///  Конструкторы класса
Matrix::Matrix() : m_(0), n_(0), values_(0, std::vector<double>(0, 0)) { };


Matrix::Matrix(size_t m, size_t n) : m_(m), n_(n), values_(m, std::vector<double>(n, 0)) { };


Matrix::Matrix(std::vector<std::vector<double>> values) : m_(values.size()), n_(values[0].size()), values_(values) { };

///  Перегрузка оператора[] для доступа к элементам матрицы
std::vector<double>& Matrix::operator[](const int& index) {
    return values_[index];
};

///  Получение значения матрицы
std::vector<std::vector<double>> Matrix::getValues() {
    return values_;
};

///  Получение количества строк матрицы
size_t Matrix::getM() {
    return m_;
};

///  Получение количества столбцов матрицы
size_t Matrix::getN() {
    return n_;
};

///  Перегрузка оператора * для операции умножения матриц
Matrix operator* (Matrix& a, Matrix& b) {
    size_t am = a.getM(), an = a.getN(), bm = b.getM(), bn = b.getN();

    std::vector<std::vector<double>> product(am, std::vector<double>(bn, 0));

    for (size_t i = 0; i < am; i++)
    {
        for (size_t j = 0; j < bn; j++)
        {
            for (size_t inner = 0; inner < an; inner++)
            {
                product[i][j] += a[i][inner] * b[inner][j];
            }
        }

    }
    return Matrix(product);
};