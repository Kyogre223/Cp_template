struct BIT {
    int n;
    vector<long long> bit;

    BIT(int n) : n(n), bit(n+1, 0) {}

    void add(int i, long long v) {
        for (; i <= n; i += i & -i)
            bit[i] += v;
    }

    long long sum(int i) const {
        long long s = 0;
        for (; i > 0; i -= i & -i)
            s += bit[i];
        return s;
    }
};

struct RangeFenwick {
    int n;
    BIT B1, B2;

    RangeFenwick(int n) : n(n), B1(n), B2(n) {}

    // add v to all elements in [l, r]
    void rangeAdd(int l, int r, long long v) {
        B1.add(l, v);
        B1.add(r+1, -v);

        B2.add(l, v*(l-1));
        B2.add(r+1, -v*r);
    }

    // prefix sum: sum of arr[1..x]
    long long prefixSum(int x) const {
        return x * B1.sum(x) - B2.sum(x);
    }

    // range sum: sum of arr[l..r]
    long long rangeSum(int l, int r) const {
        return prefixSum(r) - prefixSum(l-1);
    }
};
