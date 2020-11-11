/// Matrix. h ���� ����������
/// ���������� ������ Matrix � ���������� ��� ������ � ���, 
/// ������� ������ �������� ��������� ������������ ����� 
#pragma once
#include <vector>

class Matrix {
public:
	Matrix();
	Matrix(size_t m, size_t n);
	Matrix(std::vector<std::vector<double>> values);
	std::vector<double>& operator[](const int& index); /// �������� ������� � �������� �������
	std::vector<std::vector<double>> getValues(); /// ��������� �������� �������
	size_t getM();	/// ��������� ���������� ����� �������
	size_t getN();	/// ��������� ���������� �������� �������
private:
	size_t m_;	/// ���������� ����� �������
	size_t n_;	/// ���������� �������� �������
	std::vector<std::vector<double>> values_;	/// �������� �������
};

Matrix operator*(Matrix& a, Matrix& b);	/// �������� ��������� ���� ������
