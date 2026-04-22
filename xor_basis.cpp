struct XorBasis {
    long long basis[60];
    int rank = 0;
    
    XorBasis() {
        memset(basis, 0, sizeof(basis));
    }
    
    // Add a vector to the basis
    // Returns true if it was independent (added to basis)
    // Returns false if it was dependent (already representable)
    bool add(long long x) {
        for (int i = 59; i >= 0; i--) {
            if (!((x >> i) & 1)) continue;
            
            if (basis[i] == 0) {
                basis[i] = x;
                rank++;
                return true;  // Independent
            }
            x ^= basis[i];
        }
        return false;  // Dependent (x became 0)
    }
    
    // Check if x can be represented as XOR of basis vectors
    bool canRepresent(long long x) {
        for (int i = 59; i >= 0; i--) {
            if (!((x >> i) & 1)) continue;
            if (basis[i] == 0) return false;
            x ^= basis[i];
        }
        return true;  // x reduced to 0
    }
    
    // Find maximum XOR achievable, optionally starting with x
    long long maxXor(long long x = 0) {
        for (int i = 59; i >= 0; i--) {
            if (basis[i] == 0) continue;
            x = max(x, x ^ basis[i]);
        }
        return x;
    }
    
    // Find minimum XOR achievable (among non-zero values)
    long long minXor() {
        for (int i = 0; i < 60; i++) {
            if (basis[i] != 0) return basis[i];
        }
        return 0;  // Empty basis
    }
    
    // Count distinct XOR values achievable
    long long countDistinct() {
        return 1LL << rank;
    }
    
    // Get the rank
    int getRank() {
        return rank;
    }
};
