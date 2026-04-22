/**
 * Modular Math Utilities
 * Functions for binary exponentiation and modular arithmetic.
 */
namespace Math {
    // Computes (a^b) % c
    long long binpow(long long a, long long b, long long m) {
        a %= m;
        long long res = 1;
        while (b > 0) {
            if (b & 1) res = res * a % m;
            a = a * a % m;
            b >>= 1;
        }
        return res;
    }

    // Modular Multiplicative Inverse using Fermat's Little Theorem (p must be prime)
    long long mminvprime(long long a, long long p) {
        return binpow(a, p - 2, p);
    }

    // Safe modular subtraction
    long long mod_sub(long long a, long long b, long long mod) {
        return (a % mod - b % mod + mod) % mod;
    }
}
