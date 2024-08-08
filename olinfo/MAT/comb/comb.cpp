int is_prime(int N) {
  for (int i = 2; i * i <= N; i++)
    if (N % i == 0)
      return 0;
  return 1;
}

void suddividi(int N, int* X, int* Y) {
  int p = 2 * N + 1;
  while (!is_prime(p))
    p++;

  for (int i = 2 * N, j = p - i; i > j; i--, j++) {
    *X = i;
    *Y = j;
    X++;
    Y++;
  }

  if (p != 2 * N + 1)
    suddividi((p - 2 * N - 1) / 2, X, Y);
}