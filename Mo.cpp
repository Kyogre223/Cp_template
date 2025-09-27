static inline long long hilbertOrder(int x, int y, int pow, int rot) {
    if (pow == 0) return 0;
    int hpow = 1 << (pow - 1);
    int seg = (x < hpow) ? ((y < hpow) ? 0 : 3) : ((y < hpow) ? 1 : 2);
    seg = (seg + rot) & 3;
    static const int rotateDelta[4] = {3, 0, 0, 1};
    int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
    int nrot = (rot + rotateDelta[seg]) & 3;
    long long sub = 1LL << (2 * pow - 2);
    long long ans = seg * sub;
    long long add = hilbertOrder(nx, ny, pow - 1, nrot);
    ans += (seg == 1 || seg == 2) ? add : (sub - add - 1);
    return ans;
}

// ---- Problem-specific Mo state: odd/even frequencies in window ----
static const int MAXV = 1'000'000;      // given: A[i] in [0, 1e6]
static int cnts[MAXV + 1];              // frequency table : MAKE THIS GLOBAL TO IMPROVE TIME LIMIT
static int oddKinds;                    // #values currently with odd frequency

struct Query {
    int l, r, idx;
    long long ord;                      // Hilbert order key
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; 
    if (!(cin >> T)) return 0;
    while (T--) {
        int n, q;
        cin >> n >> q;

        vector<int> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];

        // Choose pow for hilbert: smallest pow s.t. 2^pow >= n
        int pow = 0;
        while ((1 << pow) < max(1, n)) ++pow;

        vector<Query> qs;
        qs.reserve(q);
        for (int i = 0; i < q; ++i) {
            int l, r; 
            cin >> l >> r;
            --l; --r;                   // to 0-indexed
            if (l > r) swap(l, r);
            long long ord = hilbertOrder(l, r, pow, 0);
            qs.push_back({l, r, i, ord});
        }

        // Sort by Hilbert order
        sort(qs.begin(), qs.end(), [](const Query& A, const Query& B){
            return A.ord < B.ord;
        });

        // Reset state for this test
        memset(cnts, 0, sizeof(cnts));

        // TODO: ADJUST DATA STRUCTURE HERE
        oddKinds = 0;

        // Mo pointers
        int curL = 0, curR = -1;

        // TODO: ADJUST ADD AND REMOVE ACCORDINGLY;
        auto add = [&](int idx) {
            cnts[a[idx]]++;
            if (cnts[a[idx]] & 1) {
                oddKinds++;
            } else {
                oddKinds--;
            }
        };
        auto rem = [&](int idx) {
            cnts[a[idx]]--;
            if (cnts[a[idx]] & 1) {
                oddKinds++;
            } else {
                oddKinds--;
            }
        };

        vector<int> ans(q);
        for (const auto& qu : qs) {
            int L = qu.l, R = qu.r;
            while (curL > L) add(--curL);
            while (curR < R) add(++curR);
            while (curL < L) rem(curL++);
            while (curR > R) rem(curR--);

            // YES if no odd counts in [L, R]
            ans[qu.idx] = (oddKinds == 0) ? 1 : 0;
        }

        for (int v : ans) cout << (v ? "YES\n" : "NO\n");
    }
    return 0;
}
