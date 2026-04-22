/**
 * Number Theory Utilities
 * Sieve of Eratosthenes, SPF, and Factorization.
 */
namespace NumberTheory {
    // Sieve to find all primes up to n
    std::vector<long long> sieves(int n) {
        std::vector<bool> is_prime(n + 1, true);
        is_prime[0] = is_prime[1] = false;
        for (int p = 2; p * p <= n; p++) {
            if (is_prime[p]) {
                for (int i = p * p; i <= n; i += p) is_prime[i] = false;
            }
        }
        std::vector<long long> primes;
        for (int p = 2; p <= n; p++) if (is_prime[p]) primes.push_back(p);
        return primes;
    }

    // Precompute Smallest Prime Factor (SPF) for fast factorization
    std::vector<int> calcSPF(int maxN) {
        std::vector<int> spf(maxN + 1);
        std::iota(spf.begin(), spf.end(), 0);
        for (int i = 2; i * i <= maxN; i++) {
            if (spf[i] == i) {
                for (int j = i * i; j <= maxN; j += i)
                    if (spf[j] == j) spf[j] = i;
            }
        }
        return spf;
    }

    // Get all prime factors of N in O(sqrt(N))
    std::vector<long long> factorize(long long N) {
        std::vector<long long> factors;
        for (long long i = 2; i * i <= N; ++i) {
            while (N % i == 0) {
                factors.push_back(i);
                N /= i;
            }
        }
        if (N > 1) factors.push_back(N);
        return factors;
    }
}
