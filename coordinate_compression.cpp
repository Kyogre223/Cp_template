    // 2) sort and unique
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());

    // 3) mapping function: original value -> compressed 1..K
    auto get = [&](int x) {
        return int(lower_bound(vals.begin(), vals.end(), x) - vals.begin()) + 1;
    };
