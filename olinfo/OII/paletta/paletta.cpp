#include <bits/stdc++.h>
using namespace std;

long long count_inv(int n, int arr[]) {
    if (n == 1) return 0;

    long long ans_l = count_inv((n + 1) / 2, arr);
    long long ans_r = count_inv(n / 2, arr + (n + 1) / 2);

    long long ans = 0;
    int i = 0, l = 0, r = (n + 1) / 2;

    int aux[n];
    for (int i = 0; i < n; i++) {
        if (r == n || (l != (n + 1) / 2 && arr[l] <= arr[r])) {
            aux[i] = arr[l++];
        } else {
            aux[i] = arr[r++];
            ans += (n + 1) / 2 - l;
        }
    }
    memcpy(arr, aux, n * sizeof(int));
    return ans_l + ans_r + ans;
}

long long paletta_sort(int N, int V[]) {
    int even[(N + 1) / 2], odd[N / 2];

    for (int i = 0; 2 * i < N; i++)
        if ((even[i] = V[2 * i]) % 2 == 1)
            return -1;
    for (int i = 0; 2 * i + 1 < N; i++)
        if ((odd[i] = V[2 * i + 1]) % 2 == 0)
            return -1;

    return count_inv((N + 1) / 2, even) + count_inv(N / 2, odd);
}