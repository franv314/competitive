#include <bits/stdc++.h>
using namespace std;

const int MOD = 32749;

class Matrix {
    int size;
    vector<vector<long long>> matrix;

public:

    vector<long long>& operator[](const int &idx) {
        return matrix[idx];
    }

    Matrix operator*(Matrix &other) {
        Matrix res = Matrix(size);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                for (int k = 0; k < size; k++) {
                    res[i][j] = (res[i][j] + matrix[i][k] * other[k][j]) % MOD;
                }
            }
        }
        return res;
    }

    Matrix operator^(long long &exp) {
        Matrix res(size), temp = (*this);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                res[i][j] = i == j;
            }
        }
        for (long long e = exp; e; e >>= 1) {
            if (e & 1) res = res * temp;
            temp = temp * temp;
        }
        return res;
    }

    Matrix(int s) : size(s) {
        matrix = vector<vector<long long>>(size, vector<long long>(size));
    }
};

long long n;

Matrix generate_matrix() {
    Matrix mat = Matrix(2);
    mat[0][0] = 3;
    mat[0][1] = 2;
    mat[1][0] = 3;
    mat[1][1] = 3;
    return mat;
}

int main() {
    cin >> n;
    Matrix mat = generate_matrix();
    
    Matrix final = mat ^ n;

    cout << final[0][0] << " " << final[1][0] << "\n";
}