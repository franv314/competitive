#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

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

int n, k;
long long t;

vector<int> current;
vector<vector<int>> partitions;

long long frac_val(long long num, long long den) {
    long long inv = 1, temp = den;
    for (int exp = MOD - 2; exp; exp >>= 1) {
        if (exp & 1) inv = (inv * temp) % MOD;
        temp = (temp * temp) % MOD;
    }
    return (num * inv) % MOD;
}

void generate_partitions() {
    int current_sum = accumulate(current.begin(), current.end(), 0);
    if (current_sum == n) {
        partitions.push_back(current);
    } else {
        int begin_at = current.empty() ? 1 : current.back();
        for (int i = begin_at; i + current_sum <= n; i++) {
            current.push_back(i);
            generate_partitions();
            current.pop_back();
        }
    }
}

Matrix generate_matrix() {
    Matrix mat = Matrix(partitions.size());
    for (int idx = 0; idx < partitions.size(); idx++) {
        vector<int> partition = partitions[idx];
        for (int i = 0; i < partition.size(); i++) {
            for (int j = 0; j < partition.size(); j++) {
                vector<int> new_partition = partition;
                new_partition[j]++;
                if (--new_partition[i] == 0)
                    new_partition.erase(new_partition.begin() + i);
                sort(new_partition.begin(), new_partition.end());
                
                int new_idx = find(partitions.begin(), partitions.end(), new_partition) - partitions.begin();

                mat[new_idx][idx] = (mat[new_idx][idx] + frac_val(partition[i] * partition[j], n * n)) % MOD;
            }
        }
    }
    return mat;
}

int main() {
    cin >> n >> t >> k;

    generate_partitions();
    Matrix mat = generate_matrix();
    
    Matrix final = mat ^ t;

    long long ans = 0;
    for (int i = 0; i < partitions.size(); i++) {
        if (partitions[i].size() >= k)
            ans = (ans + final[i][0]) % MOD;
    }
    cout << ans << "\n";
}