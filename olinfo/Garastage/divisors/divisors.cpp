long long compute(long long n) {
	long long result = 0;
    long long i = 1;
    while (i <= n) {
        long long m = n / i;
        long long r = n % i;
        
        long long d = 1 + r / m;
        result += d * m;
        i += d;
    }
    return result;
}

// floor(n/i) = m
// n = im + r

// floor(n/(i+d)) = m
// n = im + (r-dm)
// r - dm >= 0
// d <= r/m