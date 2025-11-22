template <class T>
struct Compressor {
    vector<T> vals;     // sorted unique values

    Compressor() = default;

    // Build from an existing array
    explicit Compressor(const vector<T>& a) {
        vals = a;
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
    }

    // Add single value (if you want to build incrementally)
    void add(T x) {
        vals.push_back(x);
    }

    // Call after adding values manually
    void build() {
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
    }

    // Get compressed index (0-based)
    int get(T x) const {
        return int(lower_bound(vals.begin(), vals.end(), x) - vals.begin());
    }

    // Optional: decompress index -> original value
    T operator[](int i) const {
        return vals[i];
    }
};
