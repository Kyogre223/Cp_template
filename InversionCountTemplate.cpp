long long countInversions(vector<int> a) {
    int n = (int)a.size();

    // 1) Coordinate compression
    vector<int> comp = a;
    sort(comp.begin(), comp.end());
    comp.erase(unique(comp.begin(), comp.end()), comp.end());

    auto get = [&](int x) {
        return int(lower_bound(comp.begin(), comp.end(), x) - comp.begin()) + 1; // 1-based
    };

    int m = (int)comp.size();
    vector<long long> bit(m + 1, 0);

    auto update = [&](int i, long long v) {
        for (; i <= m; i += i & -i) bit[i] += v;
    };

    auto query = [&](int i) {
        long long s = 0;
        for (; i > 0; i -= i & -i) s += bit[i];
        return s;
    };

    long long inv = 0;

    // 2) Process array left to right
    for (int i = 0; i < n; ++i) {
        int pos = get(a[i]);
        // previous elements > a[i] = total seen - those <= a[i]
        inv += query(m) - query(pos);
        update(pos, 1);
    }

    return inv;
}
