/*
 * This template is valid both in C and in C++,
 * so you can expand it with code from both languages.
 */

#include <assert.h>
#include <math.h>
#include <stdio.h>

// input data
double R, C, K;

int main() {
  //  uncomment the following lines if you want to read/write from files
  //  freopen("input.txt", "r", stdin);
  //  freopen("output.txt", "w", stdout);

  assert(3 == scanf("%lf %lf %lf", &R, &C, &K));

  // insert your code here

  printf("%lld\n", (long long)ceil(R / K) * (long long)ceil(C / K));  // print the result
  return 0;
}