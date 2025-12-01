struct DSU {
    vector<int> parent, sz;

    DSU(int n) : parent(n), sz(n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
        return true;
    }

    int size(int x) {
        return sz[find(x)];
    }
};

/* parity dsu */
struct ParityDSU {
    vector<int> parent, sz;
    vector<int> parity;  
    // parity[x] = parity from x to parent[x]
    // 0 = same color as parent
    // 1 = opposite color

    ParityDSU(int n) : parent(n), sz(n, 1), parity(n, 0) {
        iota(parent.begin(), parent.end(), 0);
    }

    // find root, while returning parity from x to the root
    pair<int,int> find(int x) {
        if (parent[x] == x) 
            return {x, 0};
        auto [root, p] = find(parent[x]);
        parity[x] ^= p;
        parent[x] = root;
        return {root, parity[x]};
    }

    // merge sets with constraint:
    // parity(u) XOR parity(v) = rel
    // rel = 0 => same color
    // rel = 1 => opposite color
    bool unite(int u, int v, int rel) {
        auto [ru, pu] = find(u);
        auto [rv, pv] = find(v);

        if (ru == rv) {
            // Check if existing relationship is consistent
            return ((pu ^ pv) == rel);
        }

        // union by size
        if (sz[ru] < sz[rv]) {
            swap(ru, rv);
            swap(pu, pv);
        }

        // attach rv under ru
        parent[rv] = ru;

        // compute parity to enforce constraint
        // par[rv] = pu XOR pv XOR rel
        parity[rv] = pu ^ pv ^ rel;

        sz[ru] += sz[rv];
        return true;
    }
};


ParityDSU dsu(n);
for (auto [u, v] : edges) {
    if (!dsu.unite(u, v, 1)) {
        cout << "Not bipartite\n";
        break;
    }
}
