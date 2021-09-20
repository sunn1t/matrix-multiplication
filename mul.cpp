#include <iostream>
#include <vector>

using namespace std;

//Ввод значений элементов матрицы
void matrix_filling(vector<vector<double>>& A) {
    size_t m = A.size();
    if (m > 0) {
        size_t n = A[0].size();
        for (size_t i = 0; i < m; i++) {
            for (size_t j = 0; j < n; j++) {
                cin >> A[i][j];
            }
        }
    }
}

//Вывести матрицу
void print_matrix(vector<vector<double>>& matrix) {
    for (size_t i = 0; i < matrix.size(); i++) {
        for (size_t j = 0; j < matrix[0].size(); j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

//Умножение матриц по определению
vector<vector<double>> simple_mul(vector<vector<double>> A, vector<vector<double>> B) {
    size_t m = A.size(), l = B.size(), n = B[0].size();
    vector<vector<double>> C(m, vector<double>(n, 0));
    for (size_t i = 0; i < m; i++) {
        for (size_t j = 0; j < n; j++) {
            for (size_t k = 0; k < l; k++) {
                C[i][j] += A[i][k]*B[k][j];
            }
        }
    }
    return C;
}

int main()
{
    size_t m_1, m_2, n_1, n_2;

    cin >> m_1 >> n_1;
    vector<vector<double>> matrixA(m_1, vector<double>(n_1, 0));
    matrix_filling(matrixA);

    cin >> m_2 >> n_2;
    if (n_1 != m_2) {
        cout << "Multiplication's impossible" << endl;
    } else {
        vector <vector <double>> result(m_1, vector<double>(n_2, 0));
        vector<vector<double>> matrixB(m_2, vector<double>(n_2, 0));
        matrix_filling(matrixB);
        cout << endl;
        result = simple_mul(matrixA, matrixB);
        print_matrix(result);
    }

    return 0;
}



