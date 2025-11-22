    auto get = [&](long long x) -> int {
        auto it = upper_bound(vals.begin(), vals.end(), x);
        if (it == vals.begin()) return -1;
        --it;
        return int(it - vals.begin());
    };
