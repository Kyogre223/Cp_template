#include <vector>
#include <map>
#include <bitset>


constexpr std::size_t MAX_K = 1'000'001;

// all reachable targets with maximum as target
std::vector<int> reachableSumsBitset(const std::vector<int>& arr, int target) {
    std::bitset<MAX_K> dp;
    dp[0] = 1;

    // Count frequencies of each weight
    std::map<int, int> counts;
    for (int x : arr) {
        if (x <= target) {
            counts[x]++;
        }
    }

    // Binary splitting
    std::vector<int> bundles;
    for (const auto& [weight, count] : counts) {
        int rem = count;
        for (int b = 1; b <= rem; b <<= 1) {
            bundles.push_back(b * weight);
            rem -= b;
        }
        if (rem > 0) {
            bundles.push_back(rem * weight);
        }
    }

    // 0/1 subset sum on the bundles
    for (int bw : bundles) {
        dp |= (dp << bw);
    }

    // Collect all reachable sums up to target
    std::vector<int> reachable;
    for (int s = 0; s <= target; ++s) {
        if (dp[s]) {
            reachable.push_back(s);
        }
    }

    return reachable;
}




// SUBSET SUM OPTIMISATION where Summation(A_i) <= N, where N is the length of the array. 
// Will pass for N <= 1e6; 
// helps whether we can reach a certain K or not;

const int MAX_K = 1000001; // Adjust based on problem constraints

bool subsetSumBitset(const std::vector<int>& arr, int target) {
    std::bitset<MAX_K> dp;
    dp[0] = 1;

    // 1. Group by frequency
    std::map<int, int> counts;
    for (int x : arr) if (x <= target) counts[x]++;

    // 2. Binary Splitting (The Envelope Trick)
    std::vector<int> bundles;
    for (auto const& [weight, count] : counts) {
        int rem = count;
        for (int b = 1; b <= rem; b <<= 1) {
            bundles.push_back(b * weight);
            rem -= b;
        }
        if (rem > 0) bundles.push_back(rem * weight);
    }

    for (int b_weight : bundles) {
        dp |= (dp << b_weight);
        if (dp[target]) return true; 
    }

    return dp[target];
}
