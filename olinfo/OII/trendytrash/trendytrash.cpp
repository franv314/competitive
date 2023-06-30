#include <bits/stdc++.h>
using namespace std;

int pulisci(int N, int M, vector<string> S) {
    vector<pair<int, int>> rows(N), cols(M);
    
    for (int n = 0; n < N; n++) {
        for (int m = 0; m < M; m++) {
            if (S[n][m] == '0') {
                rows[n].first++;
                cols[m].first++;
            } else {
                rows[n].second++;
                cols[m].second++;
            }
        }
    }

    set<int> rem_rows, rem_cols;
    set<int> rows_to_clear, cols_to_clear;
    for (int n = 0; n < N; n++) {
        rem_rows.insert(n);
        if (rows[n].first == 0 || rows[n].second == 0) {
            rows_to_clear.insert(n);
        }
    }
    for (int m = 0; m < M; m++) {
        rem_cols.insert(m);
        if (cols[m].first == 0 || cols[m].second == 0) {
            cols_to_clear.insert(m);
        }
    }

    while (!rows_to_clear.empty() || !cols_to_clear.empty()) {
        while (!rows_to_clear.empty()) {
            int row = *rows_to_clear.begin(); rows_to_clear.erase(rows_to_clear.begin());
            bool t = S[row][*rem_cols.begin()] == '0';
            rem_rows.erase(row);
            for (auto col: rem_cols) {
                if (t) {
                    cols[col].first--;
                } else {
                    cols[col].second--;
                }
                if (cols[col].first == 0 ^ cols[col].second == 0) {
                    cols_to_clear.insert(col);
                }
            }
        }
        while (!cols_to_clear.empty()) {
            int col = *cols_to_clear.begin(); cols_to_clear.erase(cols_to_clear.begin());
            bool t = S[*rem_rows.begin()][col] == '0';
            rem_cols.erase(col);
            for (auto row: rem_rows) {
                if (t) {
                    rows[row].first--;
                } else {
                    rows[row].second--;
                }
                if (rows[row].first == 0 ^ rows[row].second == 0) {
                    rows_to_clear.insert(row);
                }
            }
        }
    }

    return rem_rows.size() * rem_cols.size();
}