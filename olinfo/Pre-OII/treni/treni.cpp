#define MAX(a,b) (a>b?a:b)

int tempo_massimo(int N, int a[], int b[])
{
    int opt_posso = 0, opt_non_posso = 0;
    for (int i = 0; i < N; i++) {
        int temp = opt_posso;
        opt_posso = opt_non_posso;
        opt_non_posso = MAX(temp + MAX(a[i], b[i]), opt_non_posso + a[i]);
    }
    return MAX(opt_non_posso, opt_posso);
}