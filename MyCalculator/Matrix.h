/// Matrix. h файл объ€влени€
/// ќбъ€вление класса Matrix и операторов дл€ работы с ним, 
/// объекты класса €вл€ютс€ матрицами вещественных чисел 
#pragma once
#include <vector>

class Matrix {
public:
	Matrix();
	Matrix(size_t m, size_t n);
	Matrix(std::vector<std::vector<double>> values);
	std::vector<double>& operator[](const int& index); /// оператор доступа к элементу матрицы
	std::vector<std::vector<double>> getValues(); /// получение значений матрицы
	size_t getM();	/// получение количества строк матрицы
	size_t getN();	/// получение количества столбцов матрицы
private:
	size_t m_;	/// количество строк матрицы
	size_t n_;	/// количество столбцов матрицы
	std::vector<std::vector<double>> values_;	/// значени€ матрицы
};

Matrix operator*(Matrix& a, Matrix& b);	/// ќператор умножени€ двух матриц
