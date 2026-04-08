struct PolyHash {
    // Use a random base to prevent anti-hash tests
    static inline uint64_t base = 0;
    std::vector<uint64_t> hashed, powers;

    PolyHash(const std::vector<int>& v) {
        if (base == 0) base = random_val(10007, 1000000007) | 1; // Must be odd
        int n = v.size();
        hashed.assign(n + 1, 0);
        powers.assign(n + 1, 1);
        for (int i = 0; i < n; i++) {
            // Using unsigned long long allows automatic overflow (mod 2^64)
            hashed[i + 1] = hashed[i] * base + v[i];
            powers[i + 1] = powers[i] * base;
        }
    }

    // Get hash of subarray v[l...r] (inclusive)
    uint64_t get_hash(int l, int r) {
        return hashed[r + 1] - hashed[l] * powers[r - l + 1];
    }
};
