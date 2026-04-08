#include <vector>
#include <functional>

// Generic Vector Hasher
struct VectorHasher {
    template <typename T>
    size_t operator()(const std::vector<T>& v) const {
        size_t seed = 0;
        for (const T& i : v) {
            // This is the "Magic" hash_combine logic
            // It prevents common collisions (like [1, 2] vs [2, 1])
            seed ^= std::hash<T>{}(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};
