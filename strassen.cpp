#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

const int N = 64; //Все матрицы, размер которых не больше, чем N на N, умножаются по определению (для матриц большего размера применяется алгоритм Штрассена)

double func1(double a, double b, double c, double d);
double func2(double a, double b);
double func3(double a, double b);

//Линейные операции с двумя (четыремя) матрицами
vector<vector<double>> linear2(vector<vector<double>>& A, vector<vector<double>>& B, double (*func)(double, double));
vector<vector<double>> linear4(vector<vector<double>>& A, vector<vector<double>>& B, vector<vector<double>>& C, vector<vector<double>>& D, double (*func)(double, double, double, double));

void print_matrix(vector<vector<double>>& matrix); //Напечатать матрицу
void matrix_filling(vector<vector<double>>& A); //Ввести значения элементов матриц
vector<vector<double>> simple_mul(vector<vector<double>>& A, vector<vector<double>>& B); //Умножение двух матриц А и В по определению
vector <vector<double>> multiplication(vector <vector<double>> A, vector<vector<double>> B); //Умножение с помощью алгоритма Штрассена
vector<vector<double>> get_rand_matrix(size_t n, size_t m); //Получить матрицу со случайными элементами размера n на n

int main()
{
    //A и B -- две n на n матрицы
    size_t n;
    cin >> n;
    if ((n & (n - 1)) != 0) {
        cout << "Must be a power of 2" << endl;
    } else {
        vector<vector<double>> A(n, vector<double>(n, 0)),
        B(n, vector<double>(n, 0)), C(n, vector<double>(n, 0));

        //Можно ввести значения элементов матриц
        //matrix_filling(A);
        //matrix_filling(B);

        double simpleMulMean = 0, StrassenMulMean = 0;

        //Запускаем два алгоритма на случайных матрицах n на n
        for (int u = 0; u < 10; u++) {
            A = get_rand_matrix(n, n);
            B = get_rand_matrix(n, n);

            //Умножение по определению
            double CPU_time;
            clock_t start1 = clock();
            C = simple_mul(A, B);
            clock_t alg1 = clock();
            CPU_time = static_cast<double>(alg1 - start1) / CLOCKS_PER_SEC;

            simpleMulMean += CPU_time;

            cout << endl << "Simple mul: " << CPU_time << endl;

            //Умножение по алгоритму Штрассена
            clock_t start2 = clock();
            C = multiplication(A, B);
            clock_t alg2 = clock();
            CPU_time = static_cast<double>(alg2 - start2) / CLOCKS_PER_SEC;

            StrassenMulMean += CPU_time;

            cout << "Strassen alg: " << CPU_time << endl;

        }

        simpleMulMean /= 10; StrassenMulMean /= 10;
        cout << endl << "Simple mul mean: " << simpleMulMean << endl << "Strassen mean: " << StrassenMulMean << endl;

    }
    return 0;
}

double func1(double a, double b, double c, double d) {
    return a + b + c - d;
}

double func2(double a, double b) {
    return a + b;
}

double func3(double a, double b) {
    return a - b;
}

vector<vector<double>> linear2(vector<vector<double>>& A, vector<vector<double>>& B, double (*func)(double, double)) {
    vector<vector<double>> C(A.size(), vector<double>(A[0].size(), 0));
    for (size_t i = 0; i < A.size(); i++) {
        for (size_t j = 0; j < A[0].size(); j++) {
            C[i][j] = func(A[i][j], B[i][j]);
        }
    }
    return C;
}

vector<vector<double>> linear4(vector<vector<double>>& A, vector<vector<double>>& B, vector<vector<double>>& C, vector<vector<double>>& D, double (*func)(double, double, double, double)) {
    vector<vector<double>> res(A.size(), vector<double>(A[0].size(), 0));
    for (size_t i = 0; i < A.size(); i++) {
        for (size_t j = 0; j < A[0].size(); j++) {
            res[i][j] = func(A[i][j], B[i][j], C[i][j], D[i][j]);
        }
    }
    return res;
}

void print_matrix(vector<vector<double>>& matrix) {
    for (size_t i = 0; i < matrix.size(); i++) {
        for (size_t j = 0; j < matrix[0].size(); j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

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

vector<vector<double>> simple_mul(vector<vector<double>>& A, vector<vector<double>>& B) {
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

vector <vector<double>> multiplication(vector <vector<double>> A, vector<vector<double>> B) {

    size_t n = A.size();
    vector<vector<double>> result(n, vector<double>(n, 0));
    if (n > N) {
        vector <vector<double>> A11(n/2, vector<double>(n/2, 0)), A12(n/2, vector<double>(n/2, 0)), A21(n/2, vector<double>(n/2, 0)), A22(n/2, vector<double>(n/2, 0)),
        B11(n/2, vector<double>(n/2, 0)), B12(n/2, vector<double>(n/2, 0)), B21(n/2, vector<double>(n/2, 0)), B22(n/2, vector<double>(n/2, 0));

        for (size_t i = 0; i < n/2; i++) {
            for (size_t j = 0; j < n/2; j++) {
                A11[i][j] = A[i][j];
                A12[i][j] = A[i][j + n/2];
                A21[i][j] = A[i + n/2][j];
                A22[i][j] = A[i + n/2][j + n/2];

                B11[i][j] = B[i][j];
                B12[i][j] = B[i][j + n/2];
                B21[i][j] = B[i + n/2][j];
                B22[i][j] = B[i + n/2][j + n/2];
            }
        }

        vector<vector<double>> P1(n/2, vector<double>(n/2, 0)), P2(n/2, vector<double>(n/2, 0)), P3(n/2, vector<double>(n/2, 0)), P4(n/2, vector<double>(n/2, 0)), P5(n/2, vector<double>(n/2, 0)),
        P6(n/2, vector<double>(n/2, 0)), P7(n/2, vector<double>(n/2, 0)), C11(n/2, vector<double>(n/2, 0)), C12(n/2, vector<double>(n/2, 0)), C21(n/2, vector<double>(n/2, 0)), C22(n/2, vector<double>(n/2, 0)),
        temp(n/2, vector<double>(n/2, 0));
        P1 = multiplication(linear2(A11, A22, func2), linear2(B11, B22, func2));
        P2 = multiplication(linear2(A21, A22, func2), B11);
        P3 = multiplication(A11, linear2(B12, B22, func3));
        P4 = multiplication(A22, linear2(B21, B11, func3));
        P5 = multiplication(linear2(A11, A12, func2), B22);
        P6 = multiplication(linear2(A21, A11, func3), linear2(B11, B12, func2));
        P7 = multiplication(linear2(A12, A22, func3), linear2(B21, B22, func2));

        C11 = linear4(P1, P4, P7, P5, func1);
        C12 = linear2(P3, P5, func2);
        C21 = linear2(P2, P4, func2);
        C22 = linear4(P1, P3, P6, P2, func1);

        for (size_t i = 0; i < n/2; i++) {
            for (size_t j = 0; j < n/2; j++) {
                result[i][j] = C11[i][j];
                result[i][j + n/2] = C12[i][j];
                result[i + n/2][j] = C21[i][j];
                result[i + n/2][j + n/2] = C22[i][j];
            }
        }

    } else {
        result = simple_mul(A, B);
    }
    return result;
}

vector<vector<double>> get_rand_matrix(size_t n, size_t m) {
    srand(static_cast<unsigned int>(time(nullptr)));
    vector<vector<double>> A(m, vector<double>(n, 0));
    for (size_t i = 0; i < m; i++) {
        for (size_t j = 0; j < n; j++) {
            A[i][j] = rand();
        }
    }
    return A;
}
