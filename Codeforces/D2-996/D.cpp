#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n, k, l;
  cin >> n >> k >> l;
  vector<int> a(n);
  for (auto &x : a) {
    cin >> x;
    x *= 2;
  }
  l *= 2;
  k *= 2;

  int t = 0;
  int pos = 0;
  int idx = 0;

  t += a[0];
  pos = k;

  for (int idx = 1; idx < n; idx++) {

    int leftmost = a[idx] - t;
    int rightmost = a[idx] + t;
    if (leftmost <= pos) {
      int jump_at = min(rightmost, pos);
      pos = max(pos, jump_at + k);
      continue;
    }

    t += (leftmost - pos) / 2;
    pos = a[idx] - t + k;
  }

  t += max(0, l - pos);

  cout << t << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--)
    solve();
}
