#include <iostream>
#include <random>
#include <chrono>
using namespace std;

//класс
class Matrix {
	int row, col;
	int** matr;
public:
	Matrix(int a, int b) : row(a), col(b) {
		matr = new int* [a];
		for (int i = 0; i < a; i++) {
			matr[i] = new int[b];
			for (int j = 0; j < b; j++) {
				matr[i][j] = 0;
			}
		}
	}

	int getRow() { return row; }
	void setMatrRandom();
	friend Matrix operator+ (const Matrix&, const Matrix&);
	friend Matrix operator- (const Matrix&, const Matrix&);
	friend Matrix operator* (const Matrix&, const Matrix&);
	friend ostream& operator<< (ostream&, const Matrix&);
	~Matrix() { 
		for (int i = 0; i < row; i++)
			delete[] matr[i];
		delete[] matr;
	}
};

//заполнение матрицы числами
void Matrix::setMatrRandom() {
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generator(seed);
	std::uniform_int_distribution<int> distribution(1, 10);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			matr[i][j] = distribution(generator);
		}
	}
}

//сложение
Matrix operator+ (const Matrix& left, const Matrix& right) {
	if (left.row == right.row && left.col == right.col) {
		Matrix m(left.row, left.col);
		for (int i = 0; i < left.row; i++) {
			for (int j = 0; j < left.col; j++) {
				m.matr[i][j] = left.matr[i][j] + right.matr[i][j];
			}
		}
		return m;
	}
	else {
		Matrix mm(0, 0);
		cout << "Данные матрицы не подходят для сложения." << endl;
		return mm;
	}
}

//вычитание
Matrix operator- (const Matrix& left, const Matrix& right) {
	if (left.row == right.row && left.col == right.col) {
		Matrix m(left.row, left.col);
		for (int i = 0; i < left.row; i++) {
			for (int j = 0; j < left.col; j++) {
				m.matr[i][j] = left.matr[i][j] - right.matr[i][j];
			}
		}
		return m;
	}
	else {
		Matrix mm(0, 0);
		cout << "Данные матрицы не подходят для вычитания." << endl;
		return mm;
	}
}

//умножение
Matrix operator* (const Matrix& left, const Matrix& right) {
	if (left.col == right.row) {
		Matrix rslt(left.row, right.col);
		for (int i = 0; i < left.row; i++) {
			for (int j = 0; j < right.col; j++) {
				for (int k = 0; k < right.row; k++) {
					rslt.matr[i][j] += left.matr[i][k] * right.matr[k][j];
				}
			}
		}
		return rslt;
	}
	else {
		Matrix mm(0, 0);
		cout << "Данные матрицы не подходят для умножения." << endl;
		return mm;
	}
}

//вывод на экран
ostream& operator<< (ostream& out, const Matrix& m) {
	for (int i = 0; i < m.row; i++) {
		for (int j = 0; j < m.col; j++) {
			out << m.matr[i][j] << ' ';
		}
		out << endl;
	}
	return out;
}

int main() {
	setlocale(LC_ALL, "Russian");
	Matrix m1(3, 3);
	m1.setMatrRandom();
	cout << "Матрица 1: " << "\n" << m1 << endl;
	Matrix m2(3, 3);
	m2.setMatrRandom();
	cout << "Матрица 2: " << "\n" << m2 << endl;
	Matrix m3 = m1 + m2;
	if (int a = m3.getRow()) {
		cout << "Сумма матриц: " << "\n" << m3 << endl;
	}
	Matrix m4 = m1 - m2;
	if (int a = m4.getRow()) {
		cout << "Разность матриц: " << "\n" << m4 << endl;
	}

	Matrix m5(4, 2);
	m5.setMatrRandom();
	cout << "Матрица 3: " << "\n" << m5 << endl;
	Matrix m6(2, 3);
	m6.setMatrRandom();
	cout << "Матрица 4: " << "\n" << m6 << endl;
	Matrix m7 = m5 * m6;
	if (int a = m7.getRow()) {
		cout << "Произведение матриц: " << "\n" << m7 << endl;
	}
}