#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n;
  cin >> n;
  vector<int> a(n), b(n);
  for (auto &x : a)
    cin >> x;
  for (auto &x : b)
    cin >> x;

  int cnt = 0;
  for (int i = 0; i < n; i++)
    cnt += b[i] > a[i];

  if (cnt == 0)
    return void(cout << "YES\n");
  if (cnt != 1)
    return void(cout << "NO\n");

  int can_lose = 1e9, must_get = 0;
  for (int i = 0; i < n; i++) {
    if (b[i] > a[i])
      must_get = b[i] - a[i];
    else
      can_lose = min(can_lose, a[i] - b[i]);
  }

  if (can_lose >= must_get)
    cout << "YES\n";
  else
    cout << "NO\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)
    solve();
}
