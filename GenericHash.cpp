#include <vector>
#include <functional>

const size_t NULL_HASH = 0xDEADC0DE;  // for null conditions generically.
struct VectorHasher {
    template <typename T>
    size_t operator()(const std::vector<T>& v) const {
        size_t seed = 0;
        for (const T& i : v) {
            seed ^= std::hash<T>{}(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};
