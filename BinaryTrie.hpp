/**
 * Binary Trie
 * Used for XOR maximization and MEX queries.
 */
struct BinTrie {
    struct Node {
        int children[2] = {-1, -1};
        int count = 0; // Number of strings passing through/ending here
    };

    std::vector<Node> nodes;
    int B; // Number of bits (e.g., 30)

    BinTrie(int bits = 31) : B(bits) { nodes.emplace_back(); }

    void add(int num) {
        int curr = 0;
        for (int i = B; i >= 0; --i) {
            int b = (num >> i) & 1;
            if (nodes[curr].children[b] == -1) {
                nodes[curr].children[b] = nodes.size();
                nodes.emplace_back();
            }
            curr = nodes[curr].children[b];
            nodes[curr].count++;
        }
    }

    // Returns max (num ^ x) for any x in trie
    int findMaxXor(int num) {
        int curr = 0, best = 0;
        for (int i = B; i >= 0; --i) {
            int b = (num >> i) & 1;
            if (nodes[curr].children[b ^ 1] != -1) {
                best |= (1 << i);
                curr = nodes[curr].children[b ^ 1];
            } else {
                curr = nodes[curr].children[b];
            }
        }
        return best;
    }
};
