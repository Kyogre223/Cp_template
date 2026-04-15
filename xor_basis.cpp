// this finds the XOR basis of a set of numbers, and as well as the maximum, and can be achieved or not.

struct XorBasis {
    long long basis[60];  // For 60-bit numbers
    int size = 0;
    
    XorBasis() {
        memset(basis, 0, sizeof(basis));
    }
    
    void add(long long x) {
        for (int i = 59; i >= 0; i--) {
            if (!((x >> i) & 1)) continue;  // bit i not set
            
            if (basis[i] == 0) {
                // No basis element with this leading bit
                basis[i] = x;
                size++;
                return;
            }
            
            // Reduce x using basis[i]
            x ^= basis[i];
        }
        // x became 0 — was already representable
    }
    
    long long maxXor(long long x = 0) {
        for (int i = 59; i >= 0; i--) {
            if (basis[i] == 0) continue;
            x = max(x, x ^ basis[i]);
        }
        return x;
    }
    
    bool canRepresent(long long x) {
        for (int i = 59; i >= 0; i--) {
            if (!((x >> i) & 1)) continue;
            
            if (basis[i] == 0) return false;
            x ^= basis[i];
        }
        return x == 0;
    }
    
    long long countDistinct() {
        return 1LL << size;  // 2^size distinct values
    }
};
