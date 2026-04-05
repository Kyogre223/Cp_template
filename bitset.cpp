#include <bits/stdc++.h>
using namespace std;

template <size_t N>
class CustomBitset {
private:
    static constexpr size_t WORD_BITS = 64;
    static constexpr size_t NUM_WORDS = (N + WORD_BITS - 1) / WORD_BITS;
    static constexpr size_t LAST_BITS = (N % WORD_BITS == 0 ? WORD_BITS : N % WORD_BITS);

    array<uint64_t, NUM_WORDS> data{};

    static int ctz64(uint64_t x) {
#if defined(__GNUG__) || defined(__clang__)
        return __builtin_ctzll(x);
#else
        int cnt = 0;
        while ((x & 1ULL) == 0) {
            x >>= 1;
            ++cnt;
        }
        return cnt;
#endif
    }

    static int clz64(uint64_t x) {
#if defined(__GNUG__) || defined(__clang__)
        return __builtin_clzll(x);
#else
        int cnt = 0;
        uint64_t mask = 1ULL << 63;
        while ((x & mask) == 0) {
            mask >>= 1;
            ++cnt;
        }
        return cnt;
#endif
    }

    static constexpr uint64_t last_mask() {
        if constexpr (LAST_BITS == 64) return ~0ULL;
        else return (1ULL << LAST_BITS) - 1;
    }

    void trim_last_word() {
        data[NUM_WORDS - 1] &= last_mask();
    }

public:
    static constexpr size_t npos = static_cast<size_t>(-1);

    CustomBitset() {
        reset();
    }

    void reset() {
        data.fill(0);
    }

    void set() {
        data.fill(~0ULL);
        trim_last_word();
    }

    void set(size_t pos) {
        data[pos / WORD_BITS] |= (1ULL << (pos % WORD_BITS));
    }

    void reset(size_t pos) {
        data[pos / WORD_BITS] &= ~(1ULL << (pos % WORD_BITS));
    }

    void flip(size_t pos) {
        data[pos / WORD_BITS] ^= (1ULL << (pos % WORD_BITS));
    }

    bool test(size_t pos) const {
        return (data[pos / WORD_BITS] >> (pos % WORD_BITS)) & 1ULL;
    }

    size_t size() const {
        return N;
    }

    bool any() const {
        for (size_t i = 0; i < NUM_WORDS; ++i) {
            if (data[i]) return true;
        }
        return false;
    }

    bool none() const {
        return !any();
    }

    bool all() const {
        for (size_t i = 0; i + 1 < NUM_WORDS; ++i) {
            if (data[i] != ~0ULL) return false;
        }
        return data[NUM_WORDS - 1] == last_mask();
    }

    size_t count() const {
        size_t ans = 0;
        for (size_t i = 0; i < NUM_WORDS; ++i) {
#if defined(__GNUG__) || defined(__clang__)
            ans += __builtin_popcountll(data[i]);
#else
            uint64_t x = data[i];
            while (x) {
                x &= (x - 1);
                ++ans;
            }
#endif
        }
        return ans;
    }

    CustomBitset& operator|=(const CustomBitset& other) {
        for (size_t i = 0; i < NUM_WORDS; ++i) data[i] |= other.data[i];
        return *this;
    }

    CustomBitset& operator&=(const CustomBitset& other) {
        for (size_t i = 0; i < NUM_WORDS; ++i) data[i] &= other.data[i];
        return *this;
    }

    CustomBitset& operator^=(const CustomBitset& other) {
        for (size_t i = 0; i < NUM_WORDS; ++i) data[i] ^= other.data[i];
        trim_last_word();
        return *this;
    }

    CustomBitset operator|(const CustomBitset& other) const {
        CustomBitset res = *this;
        res |= other;
        return res;
    }

    CustomBitset operator&(const CustomBitset& other) const {
        CustomBitset res = *this;
        res &= other;
        return res;
    }

    CustomBitset operator^(const CustomBitset& other) const {
        CustomBitset res = *this;
        res ^= other;
        return res;
    }

    CustomBitset operator~() const {
        CustomBitset res;
        for (size_t i = 0; i < NUM_WORDS; ++i) res.data[i] = ~data[i];
        res.trim_last_word();
        return res;
    }

    CustomBitset operator<<(size_t shift) const {
        CustomBitset res;
        if (shift >= N) return res;

        size_t word_shift = shift / WORD_BITS;
        size_t bit_shift = shift % WORD_BITS;

        for (size_t i = NUM_WORDS; i-- > 0;) {
            if (i < word_shift) continue;
            uint64_t val = data[i - word_shift] << bit_shift;
            if (bit_shift && i > word_shift) {
                val |= data[i - word_shift - 1] >> (WORD_BITS - bit_shift);
            }
            res.data[i] = val;
        }

        res.trim_last_word();
        return res;
    }

    CustomBitset operator>>(size_t shift) const {
        CustomBitset res;
        if (shift >= N) return res;

        size_t word_shift = shift / WORD_BITS;
        size_t bit_shift = shift % WORD_BITS;

        for (size_t i = 0; i < NUM_WORDS; ++i) {
            if (i + word_shift >= NUM_WORDS) continue;
            uint64_t val = data[i + word_shift] >> bit_shift;
            if (bit_shift && i + word_shift + 1 < NUM_WORDS) {
                val |= data[i + word_shift + 1] << (WORD_BITS - bit_shift);
            }
            res.data[i] = val;
        }

        res.trim_last_word();
        return res;
    }

    CustomBitset& operator<<=(size_t shift) {
        *this = *this << shift;
        return *this;
    }

    CustomBitset& operator>>=(size_t shift) {
        *this = *this >> shift;
        return *this;
    }

    size_t lowest_set_index() const {
        for (size_t i = 0; i < NUM_WORDS; ++i) {
            if (data[i]) {
                size_t pos = i * WORD_BITS + ctz64(data[i]);
                return pos < N ? pos : npos;
            }
        }
        return npos;
    }

    size_t lowest_unset_index() const {
        for (size_t i = 0; i < NUM_WORDS; ++i) {
            uint64_t mask = (i + 1 == NUM_WORDS ? last_mask() : ~0ULL);
            uint64_t inv = (~data[i]) & mask;
            if (inv) {
                size_t pos = i * WORD_BITS + ctz64(inv);
                return pos < N ? pos : npos;
            }
        }
        return npos;
    }

    size_t highest_set_index() const {
        for (size_t i = NUM_WORDS; i-- > 0;) {
            uint64_t word = data[i];
            if (word) {
                size_t msb = 63 - clz64(word);
                size_t pos = i * WORD_BITS + msb;
                return pos < N ? pos : npos;
            }
        }
        return npos;
    }

    size_t highest_unset_index() const {
        for (size_t i = NUM_WORDS; i-- > 0;) {
            uint64_t mask = (i + 1 == NUM_WORDS ? last_mask() : ~0ULL);
            uint64_t inv = (~data[i]) & mask;
            if (inv) {
                size_t msb = 63 - clz64(inv);
                size_t pos = i * WORD_BITS + msb;
                return pos < N ? pos : npos;
            }
        }
        return npos;
    }

    string to_string() const {
        string s;
        s.reserve(N);
        for (size_t i = N; i-- > 0;) {
            s.push_back(test(i) ? '1' : '0');
        }
        return s;
    }
};
