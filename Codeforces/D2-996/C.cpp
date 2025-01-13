#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n, m;
  cin >> n >> m;
  string s;
  cin >> s;
  vector<vector<long long>> a(n, vector<long long>(m));
  for (auto &row : a)
    for (auto &elem : row)
      cin >> elem;

  auto sum_row = [&](int col, int row) {
    return accumulate(a[row].begin(), a[row].end(), 0LL) - a[row][col];
  };
  auto sum_col = [&](int col, int row) {
    long long sum = -a[row][col];
    for (int i = 0; i < n; i++)
      sum += a[i][col];
    return sum;
  };

  int x = 0, y = 0;
  for (auto c : s) {
    if (c == 'D') {
      a[y][x] = -sum_row(x, y);
      y++;
    } else {
      a[y][x] = -sum_col(x, y);
      x++;
    }
  }
  a[y][x] = -sum_row(x, y);

  for (auto row : a) {
    for (auto elem : row)
      cout << elem << " ";
    cout << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)
    solve();
}
