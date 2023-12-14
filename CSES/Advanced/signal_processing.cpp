#include <bits/stdc++.h>
using namespace std;
 
typedef complex<double> cx;
 
cx A[1 << 19], B[1 << 19], temp[1 << 19];
 
void fft(cx arr[], int step, int size) {
    if (size == 1) return;
 
    cx omega = exp(2i * (M_PI / size));
    fft(arr,        step * 2, size / 2);
    fft(arr + step, step * 2, size / 2);
 
    for (int j = 0; j < size; j++) temp[j * step] = arr[j * step];
 
    cx w = 1;
    for (int j = 0; j < size / 2; j++) {
        arr[j * step] =
            temp[j * step * 2] + w * temp[step + j * step * 2];
        arr[(j + size / 2) * step] =
            temp[j * step * 2] - w * temp[step + j * step * 2];
        
        w *= omega;
    }
}
 
void ifft(cx arr[], int step, int size) {
    if (size == 1) return;
 
    cx omega = exp(-2i * (M_PI / size));
    ifft(arr,        step * 2, size / 2);
    ifft(arr + step, step * 2, size / 2);
 
    for (int j = 0; j < size; j++) temp[j * step] = arr[j * step];
 
    cx w = 1;
    for (int j = 0; j < size / 2; j++) {
        arr[j * step] =
            temp[j * step * 2] + w * temp[step + j * step * 2];
        arr[(j + size / 2) * step] =
            temp[j * step * 2] - w * temp[step + j * step * 2];
        
        w *= omega;
    }
}
 
int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int n, m; cin >> n >> m;
    int size = 1 << (int)ceil(log2(n + m - 1));
 
    for (int i = 0; i < n; i++) cin >> A[i];
    for (int i = m - 1; i >= 0; i--) cin >> B[i];
 
    fft(A, 1, size);
    fft(B, 1, size);
 
    for (int i = 0; i < size; i++) A[i] *= B[i];
    ifft(A, 1, size);
 
    for (int i = 0; i < n + m - 1; i++) cout << (int)(A[i].real() / size + 0.5)  << " ";
}