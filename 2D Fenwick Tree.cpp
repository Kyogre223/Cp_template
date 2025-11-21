struct Fenwick2D {
    int n, m;
    vector<vector<long long>> bit;

    Fenwick2D(int n, int m) : n(n), m(m) {
        bit.assign(n, vector<long long>(m, 0));
    }

    // add delta to a[x][y]
    void add(int x, int y, long long delta) {
        for (int i = x; i < n; i = i | (i + 1))
            for (int j = y; j < m; j = j | (j + 1))
                bit[i][j] += delta;
    }

    // prefix sum: sum of a[0..x][0..y]
    long long sum(int x, int y) const {
        long long ret = 0;
        for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
            for (int j = y; j >= 0; j = (j & (j + 1)) - 1)
                ret += bit[i][j];
        return ret;
    }

    // sum of rectangle: a[x1..x2][y1..y2]
    long long sum(int x1, int y1, int x2, int y2) const {
        auto S = [&](int x, int y) -> long long {
            if (x < 0 || y < 0) return 0;
            return sum(x, y);
        };
        return S(x2, y2)
             - S(x1 - 1, y2)
             - S(x2, y1 - 1)
             + S(x1 - 1, y1 - 1);
    }
};
